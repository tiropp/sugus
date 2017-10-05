#ifndef SUGUS_EXCEPTIONS_H
#define SUGUS_EXCEPTIONS_H

// STL includes
#include <sstream>

// Sugus includes
#include <sugus/Exception.h>



namespace Sugus {

namespace detail {

template<typename T>
std::string
ToHexString(T value)
{
    std::stringstream ss;
    ss << std::showbase << std::hex << value;
    return ss.str();
}

} // End namespace detail
    
class PlatformInitFailed: public Exception
{
  public:
    PlatformInitFailed(OpcUa_StatusCode error)
        : Exception("Initialization of platform failed: " + detail::ToHexString(error))
    {}
};

class ProxyStubInitFailed: public Exception
{
  public:
    ProxyStubInitFailed(OpcUa_StatusCode error)
        : Exception("Initialization of proxy stub failed: " + detail::ToHexString(error))
    {}
};

class CreateChannelFailed: public Exception
{
  public:
    CreateChannelFailed(OpcUa_StatusCode error)
        : Exception("Creation of channel failed: " + detail::ToHexString(error))
    {}
};

class StringCreationFailed: public Exception
{
  public:
    StringCreationFailed(OpcUa_StatusCode error)
        : Exception("Creation of string failed: " + detail::ToHexString(error))
    {}
};

class InvalidSecurityPolicy: public Exception
{
  public:
    InvalidSecurityPolicy()
        : Exception("Security policy is invalid")
    {}
};

class InvalidMessageSecurityMode: public Exception
{
  public:
    InvalidMessageSecurityMode()
        : Exception("Message security mode is invalid")
    {}
};

class InvalidApplicationType: public Exception
{
  public:
    InvalidApplicationType()
        : Exception("Application type is invalid")
    {}
};

class InvalidUserTokenType: public Exception
{
  public:
    InvalidUserTokenType()
        : Exception("User token type is invalid")
    {}
};


} // End namespace Sugus

#endif  // SUGUS_EXCEPTIONS_H
