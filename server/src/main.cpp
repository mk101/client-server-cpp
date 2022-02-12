#include <iostream>
#include "Server.h"

int main() {
  Queue<PatientCard> queue;
  queue.push({"Ivan", "Ivanov", "Ivanovich", 2000, Gender::Male});
  queue.push({"Ivan1", "Ivanov1", "Ivanovich1", 2001, Gender::Male});

  tcp::endpoint endpoint(ip::address::from_string("127.0.0.1"), 8080);
  Server server(queue, endpoint);
  server.run();
  return 0;
}
