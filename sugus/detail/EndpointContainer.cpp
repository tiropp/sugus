#include "EndpointContainer.h"

// Sugus includes
#include <sugus/detail/Conversion.h>



namespace Sugus {
namespace detail {



void
EndpointContainer::Update() const
{
    if( m_array.GetSize() == m_endpoints.size() )
        return;

    for(int i = 0; i < m_array.GetSize(); ++i) {
        const OpcUa_EndpointDescription& ep = m_array[i];
        m_endpoints.push_back(
            Endpoint(ToString(ep.EndpointUrl),
                     ToApplicationDescription(ep.Server),
                     ToData(ep.ServerCertificate),
                     ToSecurityMode(ep.SecurityMode),
                     ToString(ep.SecurityPolicyUri),
                     ToUserTokenPolicyContainer(ep.UserIdentityTokens, ep.NoOfUserIdentityTokens),
                     ToString(ep.TransportProfileUri),
                     ep.SecurityLevel
                )
            );
    }
}


} // End namespace detail
} // End namespace Sugus
