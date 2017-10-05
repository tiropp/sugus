#include "Client.h"

// Sugus includes
#include <sugus/EndpointContainer.h>
#include <sugus/detail/ClientImpl.h>
#include <sugus/detail/EndpointContainer.h>
#include <sugus/detail/Conversion.h>



namespace Sugus {


Client::Client()
    : m_impl( new detail::ClientImpl() )
{
}

Client::~Client()
{}

bool
Client::Connect(
    const std::string& url,
    SecurityPolicy secPolicy,
    MessageSecurityMode msgSecMode
    )
{
    return m_impl->Connect(url, secPolicy, msgSecMode);
}

bool
Client::GetEndpoints(EndpointContainer& endpoints)
{
    detail::EndpointContainer eps;
    if( !m_impl->GetEndpoints(eps) )
        return false;

    endpoints = ToEndpointContainer(eps);
    return true;
}

bool
Client::Disconnect()
{
    return m_impl->Disconnect();
}

bool
Client::CreateSession(
    const std::string& endpointUrl,
    const std::string& applicationUri
    )
{
    return m_impl->CreateSession(endpointUrl, applicationUri);
}

bool
Client::ActivateSessionAnonymous(const std::string& policyId)
{
    return m_impl->ActivateSessionAnonymous(policyId);
}

bool
Client::ReadNode(int nodeId, Value& value)
{
    return m_impl->ReadNode(nodeId, value);
}


} // End namespace Sugus
