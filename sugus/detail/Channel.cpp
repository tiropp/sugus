#include "Channel.h"

// BOOST includes
#include <boost/scoped_array.hpp>

// Sugus includes
#include <sugus/Exceptions.h>
#include <sugus/detail/String.h>
#include <sugus/detail/Conversion.h>



namespace {

OpcUa_StatusCode
CallbackConnectStateChanged(
    OpcUa_Channel       channel,
    OpcUa_Void*         callbackData,
    OpcUa_Channel_Event event,
    OpcUa_StatusCode    status
    )
{
OpcUa_InitializeStatus(OpcUa_Module_Client, "ChannelCallback");

    OpcUa_ReferenceParameter(channel);
    OpcUa_ReferenceParameter(callbackData);
    OpcUa_ReferenceParameter(status);

    switch( event )
    {
        case eOpcUa_Channel_Event_Connected:
        {
            OpcUa_Trace(OPCUA_TRACE_LEVEL_SYSTEM, "Publisher_ChannelCallback: Channel has been established.\n");
            break;
        }

        case eOpcUa_Channel_Event_Disconnected:
        {
            OpcUa_Trace(OPCUA_TRACE_LEVEL_SYSTEM, "Publisher_ChannelCallback: Channel has been lost.\n");
            break;
        }

        default:
        {
            OpcUa_Trace(OPCUA_TRACE_LEVEL_SYSTEM, "Publisher_ChannelCallback: Unknown event %d.\n", event);
            break;
        }
    }

OpcUa_ReturnStatusCode;
OpcUa_BeginErrorHandling;
OpcUa_FinishErrorHandling;
}

} // End unnamed namespace



namespace Sugus {
namespace detail {


Channel::Channel()
    : m_connected( false )
{
    OpcUa_StatusCode status = OpcUa_Channel_Create(&m_channel,
                                                   OpcUa_Channel_SerializerType_Binary
        );
    if( OpcUa_IsBad(status) )
        throw CreateChannelFailed(status);
}

bool
Channel::Connect(
    const std::string&  url,
    SecurityPolicy      secPolicy,
    MessageSecurityMode msgSecMode
    )
{
    if( IsConnected() )
        Disconnect();

    boost::scoped_array<OpcUa_CharA> urlArray( new OpcUa_CharA[url.length()+1] );
    std::copy(url.begin(), url.end(), urlArray.get());
    urlArray[url.length()] = '\0';

    OpcUa_ByteString certificate                      = OPCUA_BYTESTRING_STATICINITIALIZER;
    OpcUa_ByteString privateKey                       = OPCUA_BYTESTRING_STATICINITIALIZER;
    OpcUa_ByteString serverCertificate                = OPCUA_BYTESTRING_STATICINITIALIZER;
    OpcUa_P_OpenSSL_CertificateStore_Config pkiConfig = {OpcUa_NO_PKI, OpcUa_Null, OpcUa_Null,OpcUa_Null, 0, OpcUa_Null};
    String securityPolicy = ToString(secPolicy);

    OpcUa_StatusCode status = OpcUa_Channel_Connect(
        m_channel,
        urlArray.get(),
        CallbackConnectStateChanged,
        OpcUa_Null,
        &certificate,
        &privateKey,
        &serverCertificate,
        &pkiConfig,
        securityPolicy.Get(),
        OPCUA_SECURITYTOKEN_LIFETIME_MAX,
        ToSecurityMode(msgSecMode),
        OPCUA_INFINITE);
    if( OpcUa_IsBad(status) )
        return false;

    m_connected = true;
    return true;


    // OpcUa_P_OpenSSL_CertificateStore_Config pkiConfig;
    // pkiConfig.PkiType = OpcUa_OpenSSL_PKI;
    // pkiConfig.Flags   = OPCUA_P_PKI_OPENSSL_ADD_UNTRUSTED_LIST_TO_ROOT_CERTIFICATES |
    //                     OPCUA_P_PKI_OPENSSL_REQUIRE_CHAIN_CERTIFICATE_IN_TRUST_LIST |
    //                     OPCUA_P_PKI_OPENSSL_CHECK_REVOCATION_ALL;
    // pkiConfig.CertificateTrustListLocation
}

bool
Channel::Disconnect()
{
    OpcUa_Channel_Disconnect( m_channel );
    m_connected = false;
    return true;
}


Channel::~Channel()
{
    OpcUa_Channel_Delete( &m_channel );
}

} // End namespace detail
} // End namespace Sugus
