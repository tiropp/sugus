#ifndef SUGUS_DETAIL_SESSION_H
#define SUGUS_DETAIL_SESSION_H

// STL includes
#include <string>

// Sugus includes
#include <sugus/detail/Handlers.h>

// Fwd declarations
namespace Sugus {
    class Value;
    namespace detail { class Channel; }
}



namespace Sugus {
namespace detail {

class Session
{
  public:
    Session(const Channel& channel);

  public:
    bool Create(
        const std::string& endpointUrl,
        const std::string& applicationUri
        );
    bool ActivateAnonymous(const std::string& policyId);
    bool ReadNode(int nodeId, Value& value);

  private:
    const Channel& m_channel;
    NodeId m_authenticationToken;
};

} // End namespace detail
} // End namespace Sugus

#endif  // SUGUS_DETAIL_SESSION_H
