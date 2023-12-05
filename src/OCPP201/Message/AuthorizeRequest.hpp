//
// Created by 杨帆 on 2023/12/3.
//

#ifndef ECHOOCPP_AUTHORIZEREQUEST_HPP
#define ECHOOCPP_AUTHORIZEREQUEST_HPP
#include "MessageCall.hpp"

namespace OCPP201{
class AuthorizeRequest : public MessageCall {
private:
  std::string certificate;
  std::string idToken;
  nlohmann::json iso15118CertificateHashData;

public:
  AuthorizeRequest(const std::string& certificate, const std::string& idToken, const nlohmann::json& iso15118CertificateHashData)
      : certificate(certificate), idToken(idToken), iso15118CertificateHashData(iso15118CertificateHashData) {
    mAction = "AuthorizeRequest";
    mMessageId = generateMessageId();
    buildPayload();
  }

private:
  void buildPayload() {
    mPayload["certificate"] = certificate;
    mPayload["idToken"] = idToken;
    mPayload["iso15118CertificateHashData"] = iso15118CertificateHashData;
  }
};

}

#endif // ECHOOCPP_AUTHORIZEREQUEST_HPP
