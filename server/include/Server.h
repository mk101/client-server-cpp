#pragma once
#include <sdkddkver.h>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <cstring>

#include <boost/asio.hpp>
#include "CardParser.h"
#include "Queue.h"

using namespace boost::asio;
using namespace boost::system;
using ip::tcp;

using Utils::Queue;

class Server {
 private:
  io_context context;
  tcp::acceptor acceptor;
  Queue<PatientCard> queue;

  class Session : public std::enable_shared_from_this<Session> {
   private:
    tcp::socket socket;
    // max length of received/sent message
    static constexpr int32_t maxLength = 1024;
    // received/sent message
    char data[maxLength] = "";
    // Pointer to current patient.
    // If null, client not request patient yet
    std::unique_ptr<PatientCard> currentPatient;
    // Reference to server queue
    Queue<PatientCard> &queue;

    // Wait until client send message and send him free patient using write method
    void read();
    // Send patient data to client and return to read method
    void write(size_t length);
   public:
    explicit Session(tcp::socket socket, Queue<PatientCard> &queue);
    ~Session();
    void start();
    void close();
  };

  // Accept client and start with him new session
  void acceptClient();

 public:
  Server(const Queue<PatientCard> &queue, const tcp::endpoint &endpoint);
  ~Server();
  void run();
  void stop();
};