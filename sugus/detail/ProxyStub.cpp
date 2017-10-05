#include "ProxyStub.h"

// OpcUa includes
#include <opcua_proxystub.h>
#include <opcua_trace.h>

// Sugus includes
#include <sugus/detail/Platform.h>
#include <sugus/Exceptions.h>



namespace Sugus {
namespace detail {


ProxyStub::ProxyStub(const Platform& platform)
{
    OpcUa_ProxyStubConfiguration config;
    config.bProxyStub_Trace_Enabled              = OpcUa_True;   //to deactivate Tracer set this variable Opc Ua Falseconfig.
    config.uProxyStub_Trace_Level                = OPCUA_TRACE_LEVEL_DEBUG;
    config.iSerializer_MaxAlloc                  = -1;
    config.iSerializer_MaxStringLength           = -1;
    config.iSerializer_MaxByteStringLength       = -1;
    config.iSerializer_MaxArrayLength            = -1;
    config.iSerializer_MaxMessageSize            = -1;
    config.iSerializer_MaxRecursionDepth         = -1;
    config.bSecureListener_ThreadPool_Enabled    = OpcUa_False;
    config.iSecureListener_ThreadPool_MinThreads = -1;
    config.iSecureListener_ThreadPool_MaxThreads = -1;
    config.iSecureListener_ThreadPool_MaxJobs    = -1;
    config.bSecureListener_ThreadPool_BlockOnAdd = OpcUa_True;
    config.uSecureListener_ThreadPool_Timeout    = OPCUA_INFINITE;
    config.bTcpListener_ClientThreadsEnabled     = OpcUa_False;
    config.iTcpListener_DefaultChunkSize         = -1;
    config.iTcpConnection_DefaultChunkSize       = -1;
    config.iTcpTransport_MaxMessageLength        = -1;
    config.iTcpTransport_MaxChunkCount           = -1;
    config.bTcpStream_ExpectWriteToBlock         = OpcUa_True;

    OpcUa_StatusCode status = OpcUa_ProxyStub_Initialize(platform.GetHandle(),
                                                         &config);
    if( OpcUa_IsBad(status) )
        throw ProxyStubInitFailed(status);
}

ProxyStub::~ProxyStub()
{
    OpcUa_ProxyStub_Clear();
}


} // End namespace detail
} // End namespace Sugus
