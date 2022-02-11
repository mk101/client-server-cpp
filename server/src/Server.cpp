#include "Server.h"

Server::Session::Session(tcp::socket socket) : socket(std::move(socket)) {}
void Server::Session::start() {
  read();
}

void Server::Session::read() {
  auto self(shared_from_this());
  socket.async_read_some(buffer(data, maxLength),
                         [this, self](error_code ec, size_t length) {
   if (!ec) {
     write(length);
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

Server::Server(std::string directory, const tcp::endpoint &endpoint)
  : directory(std::move(directory)), context(), acceptor(context, endpoint) {
  acceptClient();
}

void Server::acceptClient() {
  acceptor.async_accept(
      [this](error_code ec, tcp::socket socket) {
        if (!ec) { // If accept is successful, start new session
          std::make_shared<Session>(std::move(socket))->start();
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
