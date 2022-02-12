//#define BOOST_LOG_DYN_LINK 1
#include <iostream>
#include "Client.h"

int main() {
  Client c;
  c.start(tcp::endpoint(ip::address::from_string("127.0.0.1"), 8080));
  c.sendMessage("get", 4);
  std::cout << c.receivedMessage() << std::endl;
  c.sendMessage("get", 4);
  std::cout << c.receivedMessage() << std::endl;
  c.sendMessage("get", 4);
  std::cout << c.receivedMessage();
  c.close();
  return 0;
}
