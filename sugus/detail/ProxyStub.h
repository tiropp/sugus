#ifndef SUGUS_DETAIL_PROXYSTUB_H
#define SUGUS_DETAIL_PROXYSTUB_H

// Fwd declarations
namespace Sugus { namespace detail { class Platform; } }



namespace Sugus {
namespace detail {


class ProxyStub
{
  public:
    ProxyStub(const Platform& platform);
    ~ProxyStub();
};


} // End namespace detail
} // End namespace Sugus

#endif  // SUGUS_DETAIL_PROXYSTUB_H
