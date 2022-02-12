//#define BOOST_LOG_DYN_LINK 1
#include <iostream>
#include "ResponseParser.h"
#include "Client.h"

int main() {
  Client client;
  std::string answer;
  try {
    client.start(tcp::endpoint(ip::address::from_string("127.0.0.1"), 8080));
  } catch (const std::exception &e) {
    std::cerr << "Cannot connect to server";
    exit(42);
  }

  while (true) {
    std::cout << "Type 'get' to get free patient, or 'end' to close application" << std::endl;
    std::cout << "> ";
    std::cin >> answer;
    if (answer != "get" && answer != "end") {
      std::cout << "Unknown command" << std::endl;
      continue;
    }

    if (answer == "get") {
      client.sendMessage("get", 4);
      auto patient = ResponseParser::parse(client.receivedMessage());
      std::cout << "Free patient:" << std::endl << patient.toString()
        << std::endl << "This patient will be blocked to another doctors, while you see him data" << std::endl;
    } else if (answer == "end") {
      client.close();
      break;
    }
  }
  return 0;
}
