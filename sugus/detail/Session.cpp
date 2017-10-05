#include "Session.h"

// OpcUa includes
#include <opcua.h>
#include <opcua_core.h>
#include <opcua_clientapi.h>

// Sugus includes
#include <sugus/Value.h>
#include <sugus/detail/String.h>
#include <sugus/detail/EndpointContainer.h>
#include <sugus/detail/Channel.h>
#include <sugus/detail/Conversion.h>



namespace Sugus {
namespace detail {

Session::Session(const Channel& channel)
    : m_channel( channel )
{
}

bool
Session::Create(
    const std::string& endpointUrl,
    const std::string& applicationUri
    )
{
    RequestHeader reqHeader;
    reqHeader->TimeoutHint = 60000;
    reqHeader->Timestamp = OpcUa_DateTime_UtcNow();

    ResponseHeader rspHeader;
    ApplicationDescription clientDescription;
    clientDescription->ApplicationType      = OpcUa_ApplicationType_Client;
    OpcUa_String_AttachReadOnly(&clientDescription->ApplicationName.Text, "Sugus.Client");
    OpcUa_String_AttachReadOnly(&clientDescription->ApplicationUri,       "urn:Sugus:Client");
    OpcUa_String_AttachReadOnly(&clientDescription->ProductUri,           "http://sugus.org/Client");

    String sApplicationUri(applicationUri);
    String sEndpointUrl(endpointUrl);
    ByteString clientNonce;
    ByteString clientCertificate;
    OpcUa_Double requestedSessionTimeout = 60000;
    OpcUa_UInt32 maxResponseMessageSize = 1024*1024;

    NodeId sessionId;
    OpcUa_Double revisedSessionTimeout;
    ByteString   serverNonce;
    ByteString   serverCertificate;
    OpcUa_Int32  noOfServerEndpoints;
    EndpointContainer serverEndpoints;
    SignedSoftwareCertificateContainer softwareCertificates;
    SignatureData m_signatureData;
    OpcUa_UInt32 maxRequestMessageSize = 0;

    OpcUa_StatusCode status = OpcUa_ClientApi_CreateSession(
        *m_channel,
        reqHeader.Get(),
        clientDescription.Get(),
        sApplicationUri.Get(),
        sEndpointUrl.Get(),
        &clientDescription->ApplicationName.Text,
        clientNonce.Get(),
        clientCertificate.Get(),
        requestedSessionTimeout,
        maxResponseMessageSize,
        rspHeader.Get(),
        sessionId.Get(),
        m_authenticationToken.Get(),
        &revisedSessionTimeout,
        serverNonce.Get(),
        serverCertificate.Get(),
        serverEndpoints.GetSizePtr(),
        serverEndpoints.GetArrayPtr(),
        softwareCertificates.GetSizePtr(),
        softwareCertificates.GetArrayPtr(),
        m_signatureData.Get(),
        &maxResponseMessageSize
        );
    if( OpcUa_IsBad(status) )
        return false;
    if( OpcUa_IsBad(rspHeader->ServiceResult) )
        return false;

    return true;
}

bool
Session::ActivateAnonymous(const std::string& policyId)
{
    RequestHeader reqHeader;
    reqHeader->TimeoutHint = 60000;
    reqHeader->Timestamp   = OpcUa_DateTime_UtcNow();
    OpcUa_StatusCode status = OpcUa_NodeId_CopyTo(m_authenticationToken.Get(), &reqHeader->AuthenticationToken);
    if( OpcUa_IsBad(status) )
        return false;

    SignatureData clientSignature;
    SignedSoftwareCertificateContainer clientCertificates;

    ExtensionObject identityToken;
    OpcUa_AnonymousIdentityToken* body = (OpcUa_AnonymousIdentityToken*)
        OpcUa_ExtensionObject_CreateFromType(identityToken.Get(),
                                             &OpcUa_AnonymousIdentityToken_EncodeableType
            );
    if( !body )
        return false;
    String sPolicyId( policyId );
    status = OpcUa_String_CopyTo(sPolicyId.Get(), &body->PolicyId);
    if( OpcUa_IsBad(status) )
        return false;

    SignatureData identityTokenSignature;
    ResponseHeader rspHeader;
    ByteString revisedNonce;
    StatusCodeContainer results;
    DiagnosticInfoContainer diagnosticInfos;

    status = OpcUa_ClientApi_ActivateSession(
        *m_channel,
        reqHeader.Get(),
        clientSignature.Get(),
        clientCertificates.GetSize(), clientCertificates.Get(),
        0, NULL,
        identityToken.Get(),
        identityTokenSignature.Get(),
        rspHeader.Get(),
        revisedNonce.Get(),
        results.GetSizePtr(), results.GetArrayPtr(),
        diagnosticInfos.GetSizePtr(), diagnosticInfos.GetArrayPtr()
        );
    if( OpcUa_IsBad(status) )
        return false;
    if( OpcUa_IsBad(rspHeader->ServiceResult) )
        return false;

    return true;
}

bool
Session::ReadNode(int nodeId, Value& value)
{
    RequestHeader reqHeader;
    reqHeader->TimeoutHint = 60000;
    reqHeader->Timestamp = OpcUa_DateTime_UtcNow();
    OpcUa_StatusCode status = OpcUa_NodeId_CopyTo(m_authenticationToken.Get(), &reqHeader->AuthenticationToken);
    if( OpcUa_IsBad(status) )
        return false;

    ReadValueId nodesToRead;
    nodesToRead->NodeId.Identifier.Numeric = nodeId;
    nodesToRead->NodeId.IdentifierType = OpcUa_IdentifierType_Numeric;
    nodesToRead->NodeId.NamespaceIndex = 0;
    nodesToRead->AttributeId = OpcUa_Attributes_Value;

    ResponseHeader rspHeader;
    DataValueContainer results;
    DiagnosticInfoContainer diagnosticInfos;

    status = OpcUa_ClientApi_Read(
        *m_channel,
        reqHeader.Get(),
        36000, // 10 seconds
        OpcUa_TimestampsToReturn_Both,
        1,
        nodesToRead.Get(),
        rspHeader.Get(),
        results.GetSizePtr(), results.GetArrayPtr(),
        diagnosticInfos.GetSizePtr(), diagnosticInfos.GetArrayPtr()
        );

    if( OpcUa_IsBad(status) )
        return false;

    if( OpcUa_IsBad(rspHeader->ServiceResult) )
        return false;

    if( !results.GetSize() || (results[0].StatusCode != OpcUa_Good) )
        return false;

    value = ToValue(results[0]);
    return true;
}



} // End namespace detail
} // End namespace Sugus
