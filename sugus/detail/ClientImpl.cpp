#include "ClientImpl.h"

// OpcUa includes
#include <opcua_core.h>
#include <opcua_clientapi.h>
#include <opcua_trace.h>

// Sugus includes
#include <sugus/Exceptions.h>
#include <sugus/detail/String.h>
#include <sugus/detail/Handlers.h>
#include <sugus/detail/EndpointContainer.h>
#include <sugus/detail/Conversion.h>



namespace Sugus {
namespace detail {



ClientImpl::ClientImpl()
    : m_platform()
    , m_proxyStub( m_platform )
    , m_session( m_channel )
{
}

bool
ClientImpl::Connect(
    const std::string&  url,
    SecurityPolicy      secPolicy,
    MessageSecurityMode msgSecMode
    )
{
    if( !m_channel.Connect(url, secPolicy, msgSecMode) )
        return false;

    m_url = url;
    return true;
}

bool
ClientImpl::Disconnect()
{
    return m_channel.Disconnect();
}


bool
ClientImpl::GetEndpoints(EndpointContainer& endpoints)
{
    if( !m_channel.IsConnected() )
        return false;

    RequestHeader reqHeader;
    ResponseHeader rspHeader;
    String endpointUrl( m_url );

    OpcUa_StatusCode status = OpcUa_ClientApi_GetEndpoints(
        *m_channel,
        reqHeader.Get(),
        endpointUrl.Get(),
        0, OpcUa_Null,
        0, OpcUa_Null,
        rspHeader.Get(),
        endpoints.GetSizePtr(),
        endpoints.GetArrayPtr());
    if( OpcUa_IsBad(status) )
        return false;

    return true;
}

bool
ClientImpl::CreateSession(
    const std::string& endpointUrl,
    const std::string& applicationUri
    )
{
    return m_session.Create(endpointUrl, applicationUri);
}

bool
ClientImpl::ActivateSessionAnonymous(const std::string& policyId)
{
    return m_session.ActivateAnonymous(policyId);
}

bool
ClientImpl::ReadNode(int nodeId, Value& value)
{
    return m_session.ReadNode(nodeId, value);
}


// bool
// ClientImpl::ChooseAppropriateEndpoint(
//     SecurityPolicy           secPolicy,
//     MessageSecurityMode      msgSecMode,
//     const EndpointContainer& endpoints,
//     Endpoint&                ep
//     )
// {
//     EndpointContainer::const_iterator it = endpoints.begin();
//     EndpointContainer::const_iterator itEnd = endpoints.end();
//     BOOST_FOREACH(const Endpoint& endpoint, endpoints) {
//         if( (endpoint.securityMode      == msgSecMode)           &&
//             (endpoint.securityPolicyUri == ToString(secPolicy))  ) {
//             ep = endpoint;
//             return true;
//         }
//     }

//     return false;
// }




} // End namespace detail
} // End namespace Sugus
