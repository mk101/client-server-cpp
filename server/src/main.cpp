#include <iostream>
#include "Server.h"

int main() {
  tcp::endpoint endpoint(ip::address::from_string("127.0.0.1"), 8080);
  Server server("", endpoint);
  server.run();
  return 0;
}
