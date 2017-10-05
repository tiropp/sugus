#ifndef SUGUS_CLIENT_H
#define SUGUS_CLIENT_H

// STL includes
#include <string>

// BOOST includes
#include <boost/scoped_ptr.hpp>

// Sugus includes
#include <sugus/Types.h>

// Fwd declarations
namespace Sugus {
    class EndpointContainer;
    class Value;
    namespace detail { class ClientImpl; }
}



namespace Sugus {


class Client
{
  public:
    Client();
    ~Client();

  public:
    /// \brief Connect to server with URL \a url
    ///
    /// \return True on successful connection, false for error
    bool Connect(const std::string&  url,
                 SecurityPolicy      secPolicy,
                 MessageSecurityMode msgSecMode
        );

    /// \brief Return endpoints for the URL connected with
    ///
    /// \param[out] endpoints The returned endpoints offered by URL \a url
    ///
    /// The client needs to be connected already otherwise this operation fails.
    bool GetEndpoints(EndpointContainer& endpoints);

    /// \brief Disconnect from server
    bool Disconnect();

    bool CreateSession(const std::string& endpointUrl,
                       const std::string& applicationUri
        );

    bool ActivateSessionAnonymous(const std::string& policyId);

    bool ReadNode(int nodeId, Value& value);

  private:
    boost::scoped_ptr<detail::ClientImpl> m_impl;
};

} // End namespace Sugus

#endif  // SUGUS_CLIENT_H
