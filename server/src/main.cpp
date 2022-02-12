#include <iostream>
#include <filesystem>
#include "Server.h"

char pathToDirectory[128] = "../../patients/";

size_t fileCount() {
  using std::filesystem::directory_iterator;
  return std::distance(directory_iterator(pathToDirectory), directory_iterator{});
}

Queue<PatientCard> createQueue() {
  Queue<PatientCard> queue(fileCount());
  std::cout << "Load files:" << std::endl;
  for (const auto &entry : std::filesystem::directory_iterator(pathToDirectory)) {
    std::cout << '\t' << entry.path().string() << std::endl;
    queue.push(CardParser::parseFile(entry.path().string()));
  }

  return queue;
}

int main(int32_t argc, char *argv[]) {
  if (argc > 1) {
    strcpy_s(pathToDirectory, argv[1]);
  }
  auto queue = createQueue();

  tcp::endpoint endpoint(ip::address::from_string("127.0.0.1"), 8080);
  Server server(queue, endpoint);
  server.run();
  return 0;
}
