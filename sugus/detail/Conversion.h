#ifndef SUGUS_DETAIL_CONVERSION_H
#define SUGUS_DETAIL_CONVERSION_H

// OpcUa includes
#include <opcua.h>
#include <opcua_string.h>
#include <opcua_p_types.h>

// Sugus includes
#include <sugus/Types.h>
#include <sugus/UserTokenPolicy.h>
#include <sugus/detail/String.h>

// Fwd declarations
namespace Sugus {
    class EndpointContainer;
    class ApplicationDescription;
    class Value;
    namespace detail { class EndpointContainer; }
}



namespace Sugus {
namespace detail {


String ToString(SecurityPolicy secPolicy);
std::string ToString(const OpcUa_String& string);

MessageSecurityMode       ToSecurityMode(OpcUa_MessageSecurityMode mode);
OpcUa_MessageSecurityMode ToSecurityMode(MessageSecurityMode mode);

ApplicationType ToApplicationType(OpcUa_ApplicationType type);
ApplicationDescription ToApplicationDescription(const OpcUa_ApplicationDescription& in);

Sugus::EndpointContainer ToEndpointContainer(const Sugus::detail::EndpointContainer& endpoints);

Data ToData(const OpcUa_ByteString& data);

UserTokenType ToUserTokenType(OpcUa_UserTokenType type);
UserTokenPolicy ToUserTokenPolicy(const OpcUa_UserTokenPolicy& policy);
UserTokenPolicyContainer ToUserTokenPolicyContainer(OpcUa_UserTokenPolicy* policies, int size);

uint64_t ToUint64(const OpcUa_DateTime& dt);
Data ToData(const OpcUa_Guid& guid);
Data ToData(const OpcUa_ByteString& string);
Value ToValue(const OpcUa_DataValue& value);

} // End namespace detail
} // End namespace Sugus

#endif  // SUGUS_DETAIL_CONVERSION_H
