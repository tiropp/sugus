#ifndef SUGUS_DETAIL_CHANNEL_H
#define SUGUS_DETAIL_CHANNEL_H

// STL includes
#include <string>

// OpcUa includes
#include <opcua.h>
#include <opcua_channel.h>

// Sugus includes
#include <sugus/Types.h>



namespace Sugus {
namespace detail {

class Channel
{
  public:
    Channel();
    ~Channel();

  public:
    bool Connect(
        const std::string&  url,
        SecurityPolicy      secPolicy,
        MessageSecurityMode msgSecMode
        );
    bool Disconnect();

  public:
    OpcUa_Channel operator*() const { return m_channel; }
    bool IsConnected() const { return m_connected;}

  private:
    OpcUa_Channel m_channel;

    /// \brief Flag indicates connection status
    bool m_connected;
};

} // End namespace detail
} // End namespace Sugus

#endif  // SUGUS_DETAIL_CHANNEL_H
