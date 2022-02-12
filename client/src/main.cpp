//#define BOOST_LOG_DYN_LINK 1
#include <iostream>
#include "ResponseParser.h"
#include "Client.h"

int main() {
  Client c;
  c.start(tcp::endpoint(ip::address::from_string("127.0.0.1"), 8080));
  c.sendMessage("get", 4);
  std::cout << ResponseParser::parse(c.receivedMessage()).toString() << std::endl;
  c.sendMessage("get", 4);
  std::cout << ResponseParser::parse(c.receivedMessage()).toString() << std::endl;
  c.sendMessage("get", 4);
  std::cout << ResponseParser::parse(c.receivedMessage()).toString();
  c.close();
  return 0;
}
