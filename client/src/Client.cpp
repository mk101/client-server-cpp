#include "Client.h"
Client::Client() : context(), s(context) {}

void Client::start(const tcp::endpoint &endpoint) {
  if (isStarted) {
    return;
  }
  tcp::resolver resolver(context);
  connect(s, resolver.resolve(endpoint));
  isStarted = true;
  isClosed = false;
}

void Client::sendMessage(const char *message, size_t size) {
  write(s, buffer(message,size));
}
std::string Client::receivedMessage() {
  char reply[maxLength];
  s.read_some(buffer(reply, maxLength));
  return {reply};
}

Client::~Client() {
  if (!isClosed) {
    close();
  }
}
void Client::close() {
  if (isStarted) {
    sendMessage("end", 4);
    isClosed = true;
    isStarted = false;
  }
}

