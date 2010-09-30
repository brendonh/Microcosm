#include "ClientEndpoint.hpp"

using namespace Microcosm::Server;

ClientEndpoint::ClientEndpoint(Reckoner::Network::ENetEndpoint& client,
                               std::string name)
  : mClient(client),
    mName(name),
    mIdentifier(client.getIdentifier() + " [" + name + "]") {

  LOG("Logged in");

#define ATTACH(MSG, METHOD)     \
  client.registerHandler(MSG,                \
                         std::bind(&ClientEndpoint::METHOD, *this,  \
                                   std::placeholders::_1,       \
                                   std::placeholders::_2))
  
  ATTACH("Reckoner.ProtoBufs.Login", handle_repeatedLogin);
  ATTACH("Reckoner.ProtoBufs.ControlObject", handle_controlObject);

#undef ATTACH

  Reckoner::ProtoBufs::LoggedIn msg;
  client.send(&msg, ENET_PACKET_FLAG_RELIABLE);
}


void ClientEndpoint::handle_repeatedLogin(
        Reckoner::Network::ENetEndpoint& UNUSED(endpoint), 
        const google::protobuf::MessageLite& UNUSED(message)) {
  LOG("Ignoring repeated login");
}

void ClientEndpoint::handle_controlObject(
        Reckoner::Network::ENetEndpoint& UNUSED(endpoint), 
        const google::protobuf::MessageLite& message) {

  const Reckoner::ProtoBufs::ControlObject* controlObj = 
    static_cast<const Reckoner::ProtoBufs::ControlObject*>(&message);

  LOG("Controlling ID " << controlObj->objectid());
}
