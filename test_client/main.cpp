// STL includes
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <sstream>

// BOOST includes
#include <boost/foreach.hpp>

// OpcUa includes
#include <sugus/Client.h>
#include <sugus/EndpointContainer.h>
#include <sugus/Endpoint.h>
#include <sugus/Types.h>
#include <sugus/Value.h>



std::string
ToString(Sugus::MessageSecurityMode msm)
{
    switch(msm) {
    case Sugus::MessageSecurityMode::Invalid:        return "Invalid";
    case Sugus::MessageSecurityMode::None:           return "None";
    case Sugus::MessageSecurityMode::Sign:           return "Sign";
    case Sugus::MessageSecurityMode::SignAndEncrypt: return "SignAndEncrypt";
    }
}

std::string
ToString(Sugus::ApplicationType type)
{
    switch( type ) {
    case Sugus::ApplicationType::Client:          return "Client";
    case Sugus::ApplicationType::Server:          return "Server";
    case Sugus::ApplicationType::ClientAndServer: return "ClientAndServer";
    case Sugus::ApplicationType::DiscoveryServer: return "DiscoveryServer";
    }
}

std::ostream&
operator<<(std::ostream& os, const std::vector<uint8_t>& input)
{
    std::ios::fmtflags flags( os.flags() );
    os << std::hex << std::noshowbase;
    bool isFirst = true;
    BOOST_FOREACH(uint8_t element, input) {
        if( isFirst ) isFirst = false;
        else os << ":";
        os << (int)element;
    }
    os.flags( flags );
    return os;
}

std::ostream&
operator<<(std::ostream& os, const std::vector<std::string>& input)
{
    bool isFirst = true;
    BOOST_FOREACH(const std::string& element, input) {
        if( isFirst ) isFirst = false;
        else
            os << ", ";
        os << element;
    }
    return os;
}

std::ostream&
operator<<(std::ostream& os, const Sugus::ApplicationDescription& description)
{
    os << "appUri=" << description.applicationUri
       << ", productUri=" << description.productUri
       << ", appName=" << description.applicationName
       << ", appType=" << ToString(description.applicationType)
       << ", gatewayServerUri=" << description.gatewayServerUri
       << ", discoveryProfileUri=" << description.discoveryProfileUri
       << ", discoveryUrls=(" << description.discoveryUrls << ")";
    return os;
}

std::ostream&
operator<<(std::ostream& os, Sugus::UserTokenType token)
{
    switch( token ) {
    case Sugus::UserTokenType::Anonymous:   return os << "Anonymous";
    case Sugus::UserTokenType::UserName:    return os << "UserName";
    case Sugus::UserTokenType::Certificate: return os << "Certificate";
    case Sugus::UserTokenType::IssuedToken: return os << "IssuedToken";
    default: return os << "<ERROR>";
    }
}

std::ostream&
operator<<(std::ostream& os, const Sugus::UserTokenPolicy& policy)
{
    os << "policyId=" << policy.policyId
       << ", tokenType=" << policy.tokenType
       << ", issuedTokenType=" << policy.issuedTokenType
       << ", issuerEndpointUrl=" << policy.issuerEndpointUrl
       << ", securityPolicyUri=" << policy.securityPolicyUri;
    return os;
}

std::ostream&
operator<<(std::ostream& os, const Sugus::UserTokenPolicyContainer& policies)
{
    bool isFirst = true;
    BOOST_FOREACH(const Sugus::UserTokenPolicy& policy, policies) {
        if( isFirst ) isFirst = false;
        else os << ", ";
        os << "(" << policy << ")";
    }
    return os;
}

std::ostream&
operator<<(std::ostream& os, const Sugus::Endpoint& endpoint)
{
    os << "url=" << endpoint.url
       << ", server=(" << endpoint.server << ")"
       << ", serverCertificate=(" << endpoint.serverCertificate << ")"
       << ", securityMode=" << ToString(endpoint.securityMode)
       << ", securityPorlicyUri=" << endpoint.securityPolicyUri
       << ", userIdentityTokens=(" << endpoint.userIdentityTokens << ")"
       << ", transportProfileUri=" << endpoint.transportProfileUri
       << ", securityLevel=" << endpoint.securityLevel;

    return os;
}

std::ostream&
operator<<(std::ostream& os, const Sugus::Value& value)
{
    os << "data=(" << value.data << ")"
       << ", statusCode=" << value.statusCode
       << ", sourceTimestamp=" << value.sourceTimestamp
       << ", serverTimestamp=" << value.serverTimestamp
       << ", sourcePicoseconds=" << value.sourcePicoseconds
       << ", serverPicoseconds=" << value.serverPicoseconds;
    return os;
}

void
Print(const Sugus::EndpointContainer& endpoints)
{
    for(const auto& endpoint: endpoints) {
        std::cout << "Endpoint=(" << endpoint << ")\n";
    }
}

int
LocalServer()
{
    Sugus::Client client;
    if( !client.Connect("opc.tcp://localhost:4840",
                        Sugus::SecurityPolicy::None,
                        Sugus::MessageSecurityMode::None
            )
        ) {
        std::cout << "Connect failed\n";
        return 1;
    }
    else
        std::cout << "Connect successful\n";

    Sugus::EndpointContainer endpoints;
    if( !client.GetEndpoints(endpoints) ) {
        std::cout << "Endpoints failed\n";
        return 1;
    }
    Print(endpoints);

    if( !client.CreateSession("opc.tcp://localhost:4840", "Nano_Server") ) {
        std::cout << "Creating session failed\n";
        return 1;
    }
    else
        std::cout << "Creating session successful\n";

    if( !client.ActivateSessionAnonymous("0") ) {
        std::cout << "Activate session failed\n";
        return 1;
    }
    else
        std::cout << "Activate session successful\n";

    Sugus::Value value;
    if( !client.ReadNode(2258, value) ) {
        std::cout << "Reading node failed\n";
        return 1;
    }
    else
        std::cout << "Reading node successful: value=(" << value << ")\n";


    return 0;
}

int
RemoteServer()
{
    Sugus::Client client;
    if( !client.Connect("opc.tcp://opcua.demo-this.com:51210/UA/SampleServer",
                        Sugus::SecurityPolicy::None,
                        Sugus::MessageSecurityMode::None
            )
        ) {
        std::cout << "Connect failed\n";
        return 1;
    }
    else
        std::cout << "Connect successful\n";

    Sugus::EndpointContainer endpoints;
    if( !client.GetEndpoints(endpoints) ) {
        std::cout << "Endpoints failed\n";
        return 1;
    }
    Print(endpoints);

    if( !client.CreateSession("opc.tcp://opcua.demo-this.com:51210/UA/SampleServer", "urn:opcua.demo-this.com:UA Sample Server") ) {
        std::cout << "Creating session failed\n";
        return 1;
    }
    else
        std::cout << "Creating session successful\n";

    if( !client.ActivateSessionAnonymous("0") ) {
        std::cout << "Activate session failed\n";
        return 1;
    }
    else
        std::cout << "Activate session successful\n";

    Sugus::Value value;
    if( !client.ReadNode(2261, value) ) {
        std::cout << "Reading node failed\n";
        return 1;
    }
    else
        std::cout << "Reading node successful: value=(" << value << ")\n";


    // if( !client.Connect("opc.tcp://opcua.demo-this.com:51210/UA/SampleServer",
    //                     Sugus::SecurityPolicy::Basic256,
    //                     Sugus::MessageSecurityMode::Sign
    //         )
    //     ) {
    //     std::cout << "Connection(2) failed\n";
    //     return 1;
    // }

    return 0;
}


int
Do(const std::string& job)
{
    if( job == "local" )
        return LocalServer();
    else if( job == "remote" )
        return RemoteServer();
    else {
        std::cerr << "Job parameter invalid\n";
        return 1;
    }
}

int
main(int argc, char* argv[])
{
    if( argc != 2 ) {
        std::cerr << "Invalid number of parameters!\n";
        return 1;
    }

    try {
        return Do( argv[1] );
    }
    catch( std::exception& e ) {
        std::cerr << e.what() << "\n";
        return 1;
    }
}
