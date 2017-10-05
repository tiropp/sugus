#ifndef SUGUS_APPLICATIONDESCRIPTION_H
#define SUGUS_APPLICATIONDESCRIPTION_H

// STL includes
#include <string>
#include <vector>

// Sugus includes
#include <sugus/Types.h>



namespace Sugus {

struct ApplicationDescription
{
    std::string              applicationUri;
    std::string              productUri;
    std::string              applicationName;
    ApplicationType          applicationType;
    std::string              gatewayServerUri;
    std::string              discoveryProfileUri;
    std::vector<std::string> discoveryUrls;
};

} // End namespace Sugus

#endif  // SUGUS_APPLICATIONDESCRIPTION_H
