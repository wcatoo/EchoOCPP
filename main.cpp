
#include "src/OCPP201/Message/MessageRequest.hpp"
#include "src/OCPP201/Message/MessageRespone.hpp"
#include <iostream>

using namespace OCPP201;

std::string getMessage(MessageCall &messageCallBase) {
  return messageCallBase.serializeMessage();
}

int main(void) {
  AuthorizeRequest authorizeRequest("a", "b", "c");

  std::cout << getMessage(authorizeRequest) << std::endl;
}