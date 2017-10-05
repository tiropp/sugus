#ifndef SUGUS_TYEPS_H
#define SUGUS_TYEPS_H

// STL includes
#include <vector>
#include <cstdint>

// BOOST includes
#include <boost/core/scoped_enum.hpp>



namespace Sugus {

typedef std::vector<uint8_t> Data;

BOOST_SCOPED_ENUM_DECLARE_BEGIN(SecurityPolicy)
{
    None,
    Basic128Rsa15,
    Basic256,
    Basic256Sha256
}
BOOST_SCOPED_ENUM_DECLARE_END(SecurityPolicy)

BOOST_SCOPED_ENUM_DECLARE_BEGIN(MessageSecurityMode)
{
    Invalid,
    None,
    Sign,
    SignAndEncrypt
}
BOOST_SCOPED_ENUM_DECLARE_END(MessageSecurityMode)

BOOST_SCOPED_ENUM_DECLARE_BEGIN(ApplicationType)
{
    Server,
    Client,
    ClientAndServer,
    DiscoveryServer
}
BOOST_SCOPED_ENUM_DECLARE_END(ApplicationType)

BOOST_SCOPED_ENUM_DECLARE_BEGIN(UserTokenType)
{
    Anonymous,
    UserName,
    Certificate,
    IssuedToken
}
BOOST_SCOPED_ENUM_DECLARE_END(UserTokenType)


} // End namespace Sugus

#endif  // SUGUS_TYEPS_H
