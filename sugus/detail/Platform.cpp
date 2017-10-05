#include "Platform.h"

// OpcUa includes
#include <opcua.h>

// Sugus includes
#include <sugus/Exceptions.h>



namespace Sugus {
namespace detail {


Platform::Platform()
{
    OpcUa_StatusCode status = OpcUa_P_Initialize( &m_handle );
    if( OpcUa_IsBad(status) )
        throw PlatformInitFailed( status );
}

Platform::~Platform()
{
    OpcUa_P_Clean( &m_handle );
}


} // End namespace detail
} // End namespace Sugus
