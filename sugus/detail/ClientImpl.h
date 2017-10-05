#ifndef SUGUS_DETAIL_CLIENTIMPL_H
#define SUGUS_DETAIL_CLIENTIMPL_H

// STL includes
#include <string>

// OpcUa includes
#include <opcua.h>

// Sugus includes
#include <sugus/Types.h>
#include <sugus/detail/Platform.h>
#include <sugus/detail/ProxyStub.h>
#include <sugus/detail/Channel.h>
#include <sugus/detail/Session.h>

// Fwd declarations
namespace Sugus {
    class Valuie;
    namespace detail { class EndpointContainer;}
}



namespace Sugus {
namespace detail {


class ClientImpl
{
  public:
    ClientImpl();

  public:
    bool Connect(const std::string&  url,
                 SecurityPolicy      secPolicy,
                 MessageSecurityMode msgSecMode
        );
    bool Disconnect();
    bool GetEndpoints(EndpointContainer& endpoints);
    bool CreateSession(
        const std::string& endpointUrl,
        const std::string& applicationUri
        );
    bool ActivateSessionAnonymous(const std::string& policyId);
    bool ReadNode(int nodeId, Value& value);

  private:
    Platform m_platform;
    ProxyStub m_proxyStub;
    Channel m_channel;
    Session m_session;

    /// \brief The URL of the server we are connected with
    std::string m_url;
};


} // End namespace detail
} // End namespace Sugus

#endif  // SUGUS_DETAIL_CLIENTIMPL_H
