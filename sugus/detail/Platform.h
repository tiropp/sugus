#ifndef SUGUS_DETAIL_PLATFORM_H
#define SUGUS_DETAIL_PLATFORM_H

// OpcUa includes
#include <opcua_platformdefs.h>



namespace Sugus {
namespace detail {


class Platform
{
  public:
    Platform();
    ~Platform();

  public:
    OpcUa_Handle GetHandle() const { return m_handle; }

  private:
    OpcUa_Handle  m_handle;
};


} // End namespace detail
} // End namespace Sugus

#endif  // SUGUS_DETAIL_PLATFORM_H
