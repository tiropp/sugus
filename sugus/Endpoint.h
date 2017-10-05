#ifndef SUGUS_ENDPOINT_H
#define SUGUS_ENDPOINT_H

// STL includes
#include <string>

// Sugus includes
#include <sugus/Types.h>
#include <sugus/ApplicationDescription.h>
#include <sugus/UserTokenPolicy.h>



namespace Sugus {

class Endpoint
{
  public:
    Endpoint(const std::string&              url_,
             const ApplicationDescription&   server_,
             const Data&                     serverCertificate_,
             MessageSecurityMode             securityMode_,
             const std::string&              securityPolicyUri_,
             const UserTokenPolicyContainer& userIdentityTokens_,
             const std::string&              transportProfileUri_,
             int                             securityLevel_
        )
        : url                ( url_ )
        , server             ( server_ )
        , serverCertificate  ( serverCertificate_ )
        , securityMode       ( securityMode_ )
        , securityPolicyUri  ( securityPolicyUri_ )
        , userIdentityTokens ( userIdentityTokens_ )
        , transportProfileUri( transportProfileUri_ )
        , securityLevel      ( securityLevel_ )
    {}

  public:
    std::string                  url;
    ApplicationDescription       server;
    Data                         serverCertificate;
    MessageSecurityMode          securityMode;
    std::string                  securityPolicyUri;
    UserTokenPolicyContainer     userIdentityTokens;
    std::string                  transportProfileUri;
    int                          securityLevel;
};

} // End namespace Sugus

#endif  // SUGUS_ENDPOINT_H
