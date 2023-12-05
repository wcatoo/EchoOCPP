
#include <iostream>
#include "src/OCPP201/Message/AuthorizeRequest.hpp"

using namespace OCPP201;

std::string getMessage(MessageCall &messageCallBase) {
  return messageCallBase.messageSerialize();
}

int main(void) {
  AuthorizeRequest authorizeRequest("a", "b", "c");

  std::cout << getMessage(authorizeRequest) << std::endl;
}