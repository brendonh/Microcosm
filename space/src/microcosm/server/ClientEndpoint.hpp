#ifndef __MICROCOSM_SERVER_CLIENTENDPOINT
#define __MICROCOSM_SERVER_CLIENTENDPOINT

#include "reckoner/common/ENetEndpoint.hpp"

namespace Microcosm {
  namespace Server {
    
    class ClientEndpoint {
    public:
      ClientEndpoint(Reckoner::Network::ENetEndpoint& client,
                     std::string name);

      void handle_repeatedLogin(Reckoner::Network::ENetEndpoint& endpoint, 
                                const google::protobuf::MessageLite& message);

      void handle_controlObject(Reckoner::Network::ENetEndpoint& endpoint, 
                                const google::protobuf::MessageLite& message);

    private:
      Reckoner::Network::ENetEndpoint& mClient;
      std::string mName;
      std::string mIdentifier;
    };

  }
}


#endif
