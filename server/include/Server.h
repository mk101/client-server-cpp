#pragma once
#include <sdkddkver.h>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>

#include <boost/asio.hpp>
#include "CardParser.h"

using namespace boost::asio;
using namespace boost::system;
using ip::tcp;

class Server {
 private:
  // Path to patient files directory
  std::string directory;
  io_context context;
  tcp::acceptor acceptor;

  class Session : public std::enable_shared_from_this<Session> {
   private:
    tcp::socket socket;
    // max length of received/sent message
    static constexpr int32_t maxLength = 1024;
    // received/sent message
    char data[maxLength] = "";

    // Wait until client send message and send him free patient using write method
    void read();
    // Send patient data to client and return to read method
    void write(size_t length);
   public:
    explicit Session(tcp::socket socket);
    void start();
  };

  // Accept client and start with him new session
  void acceptClient();

 public:
  Server(std::string directory, const tcp::endpoint &endpoint);
  ~Server();
  void run();
  void stop();
};