#ifndef SUGUS_USERTOKENPOLICY_H
#define SUGUS_USERTOKENPOLICY_H

// STL includes
#include <string>
#include <vector>

// Sugus includes
#include <sugus/Types.h>



namespace Sugus {

struct UserTokenPolicy
{
    std::string   policyId;
    UserTokenType tokenType;
    std::string   issuedTokenType;
    std::string   issuerEndpointUrl;
    std::string   securityPolicyUri;
};

typedef std::vector<UserTokenPolicy> UserTokenPolicyContainer;

} // End namespace Sugus

#endif  // SUGUS_USERTOKENPOLICY_H
