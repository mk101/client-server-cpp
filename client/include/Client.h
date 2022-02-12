#pragma once
#include <sdkddkver.h>
#include <cstdlib>
#include <cstring>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace boost::system;
using namespace boost::asio;

class Client {
 private:
  // Max length of received message
  static constexpr int32_t maxLength = 1024;
  io_context context;
  tcp::socket s;
  bool isClosed = false;
  bool isStarted = false;
 public:
  Client();
  ~Client();
  // Connect client to server at [endpoint] location
  void start(const tcp::endpoint &endpoint);
  // Close connection
  void close();
  // Send message to server
  void sendMessage(const char *message, size_t size);
  // Get message from server
  std::string receivedMessage();
};