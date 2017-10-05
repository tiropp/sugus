#include "Conversion.h"

// BOOST includes
#include <boost/foreach.hpp>

// OpcUa includes
#include <opcua_guid.h>

// Sugus includes
#include <sugus/Exceptions.h>
#include <sugus/EndpointContainer.h>
#include <sugus/Value.h>
#include <sugus/detail/EndpointContainer.h>



namespace Sugus {
namespace detail {


String
ToString(SecurityPolicy secPolicy)
{
    switch( secPolicy ) {
    case SecurityPolicy::None:           return OpcUa_SecurityPolicy_None;
    case SecurityPolicy::Basic128Rsa15:  return OpcUa_SecurityPolicy_Basic128Rsa15;
    case SecurityPolicy::Basic256:       return OpcUa_SecurityPolicy_Basic256;
    case SecurityPolicy::Basic256Sha256: return OpcUa_SecurityPolicy_Basic256Sha256;
    default:                             throw InvalidSecurityPolicy();
    }
}

std::string
ToString(const OpcUa_String& string)
{
    std::string result;
    const char* p = OpcUa_String_GetRawString( &string );
    if( p )
        result.assign( p );
    return result;
}

MessageSecurityMode
ToSecurityMode(OpcUa_MessageSecurityMode mode)
{
    switch( mode ) {
    case OpcUa_MessageSecurityMode_Invalid:        return MessageSecurityMode::Invalid;
    case OpcUa_MessageSecurityMode_None:           return MessageSecurityMode::None;
    case OpcUa_MessageSecurityMode_Sign:           return MessageSecurityMode::Sign;
    case OpcUa_MessageSecurityMode_SignAndEncrypt: return MessageSecurityMode::SignAndEncrypt;
    default: throw InvalidMessageSecurityMode();
    }
}

OpcUa_MessageSecurityMode
ToSecurityMode(MessageSecurityMode mode)
{
    switch( mode ) {
    case MessageSecurityMode::Invalid:        return OpcUa_MessageSecurityMode_Invalid;
    case MessageSecurityMode::None:           return OpcUa_MessageSecurityMode_None;
    case MessageSecurityMode::Sign:           return OpcUa_MessageSecurityMode_Sign;
    case MessageSecurityMode::SignAndEncrypt: return OpcUa_MessageSecurityMode_SignAndEncrypt;
    default: throw InvalidMessageSecurityMode();
    }

}

Sugus::EndpointContainer
ToEndpointContainer(const Sugus::detail::EndpointContainer& in)
{
    Sugus::EndpointContainer out;
    BOOST_FOREACH(const Endpoint& ep, in)
        out.Add( ep );
    return out;
}

ApplicationType
ToApplicationType(OpcUa_ApplicationType type)
{
    switch( type ) {
    case OpcUa_ApplicationType_Server:          return ApplicationType::Server;
    case OpcUa_ApplicationType_Client:          return ApplicationType::Client;
    case OpcUa_ApplicationType_ClientAndServer: return ApplicationType::ClientAndServer;
    case OpcUa_ApplicationType_DiscoveryServer: return ApplicationType::DiscoveryServer;
    default: throw InvalidApplicationType();
    }
}

ApplicationDescription
ToApplicationDescription(const OpcUa_ApplicationDescription& in)
{
    Sugus::ApplicationDescription out;

    out.applicationUri      = ToString         (in.ApplicationUri);
    out.productUri          = ToString         (in.ProductUri);
    out.applicationName     = ToString         (in.ApplicationName.Text);
    out.applicationType     = ToApplicationType(in.ApplicationType);
    out.gatewayServerUri    = ToString         (in.GatewayServerUri);
    out.discoveryProfileUri = ToString         (in.DiscoveryProfileUri);
    for(int i=0; i<in.NoOfDiscoveryUrls; ++i)
        out.discoveryUrls.push_back( ToString(in.DiscoveryUrls[i]) );

    return out;
}

Data
ToData(const OpcUa_ByteString& data)
{
    Data result;
    if( !data.Length || (data.Length==-1) )
        return result;

    result.resize( data.Length );
    std::copy(data.Data, data.Data+data.Length, result.begin());
    return result;
}

UserTokenPolicyContainer
ToUserTokenPolicyContainer(OpcUa_UserTokenPolicy* policies, int size)
{
    UserTokenPolicyContainer result;
    for(int i=0; i<size; ++i)
        result.push_back( ToUserTokenPolicy(policies[i]) );
    return result;
}

UserTokenPolicy
ToUserTokenPolicy(const OpcUa_UserTokenPolicy& policy)
{
    UserTokenPolicy result;
    result.policyId          = ToString       (policy.PolicyId);
    result.tokenType         = ToUserTokenType(policy.TokenType);
    result.issuedTokenType   = ToString       (policy.IssuedTokenType);
    result.issuerEndpointUrl = ToString       (policy.IssuerEndpointUrl);
    result.securityPolicyUri = ToString       (policy.SecurityPolicyUri);
    return result;
}

UserTokenType
ToUserTokenType(OpcUa_UserTokenType type)
{
    switch( type ) {
    case OpcUa_UserTokenType_Anonymous:   return UserTokenType::Anonymous;
    case OpcUa_UserTokenType_UserName:    return UserTokenType::UserName;
    case OpcUa_UserTokenType_Certificate: return UserTokenType::Certificate;
    case OpcUa_UserTokenType_IssuedToken: return UserTokenType::IssuedToken;
    default: throw InvalidUserTokenType();
    }
}

uint64_t
ToUint64(const OpcUa_DateTime& dt)
{
    uint64_t result = dt.dwHighDateTime;
    result <<=32;
    result += dt.dwLowDateTime;
    return result;
}

Data
ToData(const OpcUa_Guid& guid)
{
    char g[OPCUA_GUID_LEXICAL_LENGTH];
    OpcUa_Guid_ToStringA(const_cast<OpcUa_Guid*>(&guid), g);

    Data data;
    data.assign(g, g+OPCUA_GUID_LEXICAL_LENGTH);
    return data;
}

namespace {
template <typename T>
Data
ToData(T& value)
{
    Data data;
    data.assign((uint8_t*)&value, (uint8_t*)(&value+1));
    return data;
}
} // End unnamed namespace

Value
ToValue(const OpcUa_DataValue& value)
{
    Value result;
    result.statusCode        = value.StatusCode;
    result.sourceTimestamp   = ToUint64(value.SourceTimestamp);
    result.serverTimestamp   = ToUint64(value.ServerTimestamp);
    result.sourcePicoseconds = value.SourcePicoseconds;
    result.serverPicoseconds = value.ServerPicoseconds;
    const OpcUa_VariantUnion& v = value.Value.Value;
    switch( value.Value.Datatype ) {
    case OpcUaType_Null:
        break;
    case OpcUaType_Boolean:
        result.data.push_back(v.Boolean);
        break;
    case OpcUaType_SByte:
        result.data.push_back(v.SByte);
        break;
    case OpcUaType_Byte:
        result.data.push_back(v.Byte);
        break;
    case OpcUaType_Int16:
        result.data = ToData(v.Int16);
        break;
    case OpcUaType_UInt16:
        result.data = ToData(v.UInt16);
        break;
    case OpcUaType_Int32:
        result.data = ToData(v.Int32);
        break;
    case OpcUaType_UInt32:
        result.data = ToData(v.UInt32);
        break;
    case OpcUaType_Int64:
        result.data = ToData(v.Int64);
        break;
    case OpcUaType_UInt64:
        result.data = ToData(v.UInt64);
        break;
    case OpcUaType_Float:
        result.data = ToData(v.Float);
        break;
    case OpcUaType_Double:
        result.data = ToData(v.Double);
        break;
    case OpcUaType_String:
    {
        String s(v.String);
        const std::string& ss = s.Str();
        result.data.assign(ss.begin(), ss.end());
        break;
    }
    case OpcUaType_DateTime:
    {
        uint64_t dt = ToUint64(v.DateTime);
        result.data = ToData( dt );
        break;
    }
    case OpcUaType_Guid:
        result.data = ToData(v.Guid);
        break;
    case OpcUaType_ByteString:
        result.data = ToData( v.ByteString );
        break;
    case OpcUaType_XmlElement:
        result.data = ToData( v.XmlElement );
        break;
    case OpcUaType_NodeId:
        // not supported
        break;
    case OpcUaType_ExpandedNodeId:
        // not supported
        break;
    case OpcUaType_StatusCode:
        result.data = ToData(v.StatusCode);
        break;
    case OpcUaType_QualifiedName:
        // not supported
        break;
    case OpcUaType_LocalizedText:
        // not supported
        break;
    case OpcUaType_ExtensionObject:
        // not supported
        break;
    case OpcUaType_DataValue:
        // not supported
        break;
    case OpcUaType_Variant:
        // not supported
        break;
    case OpcUaType_DiagnosticInfo:
        // not supported
        break;
    }
    return result;
}

} // End namespace detail
} // End namespace Sugus
