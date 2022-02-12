//#define BOOST_LOG_DYN_LINK 1
#include <iostream>
#include "Client.h"

int main() {
  Client c;
  c.start(tcp::endpoint(ip::address::from_string("127.0.0.1"), 8080));
  c.sendMessage("test", 5);
  std::cout << c.receivedMessage();
  return 0;
}
