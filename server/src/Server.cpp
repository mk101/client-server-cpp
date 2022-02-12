#include "Server.h"

Server::Session::Session(tcp::socket socket, Queue<PatientCard> &queue)
: socket(std::move(socket)), currentPatient(nullptr),
  queue(queue){}

void Server::Session::start() {
  read();
}

void Server::Session::read() {
  auto self(shared_from_this());
  socket.async_read_some(buffer(data, maxLength),
                         [this, self](error_code ec, size_t length) {
   if (!ec) {
     if (strcmp("end", data) == 0) {
       if (currentPatient) {
         queue.push(*currentPatient);
         return;
       }
     }

     if (!currentPatient) { // currentPatient == nullptr
       currentPatient = std::make_unique<PatientCard>(queue.pop());
     } else {
       queue.push(*currentPatient);
       currentPatient = std::make_unique<PatientCard>(queue.pop());
     }
     auto patientStr = CardParser::convertToString(*currentPatient);
     strcpy_s(data, patientStr.c_str());
     write(patientStr.size()+1);
   }
  });
}

void Server::Session::write(size_t length) {
  auto self(shared_from_this());
  async_write(socket, buffer(data, length),
              [this, self](error_code ec, std::size_t /*length*/){
    if (!ec) {
      read();
    }
  });
}

Server::Server(const Queue<PatientCard> &queue, const tcp::endpoint &endpoint)
  : queue(queue), context(), acceptor(context, endpoint) {
  acceptClient();
}

void Server::acceptClient() {
  acceptor.async_accept(
      [this](error_code ec, tcp::socket socket) {
        if (!ec) { // If accept is successful, start new session
          std::make_shared<Session>(std::move(socket), queue)->start();
        }
        acceptClient(); // Anyway, continue listening
      }
    );
}

void Server::run() {
  context.run();
}

void Server::stop() {
  context.stop();
}

Server::~Server() {
  if (!context.stopped()) {
    stop();
  }
}
