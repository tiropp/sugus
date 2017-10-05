#ifndef SUGUS_DETAIL_ENDPOINTCONTAINER_H
#define SUGUS_DETAIL_ENDPOINTCONTAINER_H

// STL includes
#include <vector>

// OpcUa includes
#include <opcua.h>

// Sugus includes
#include <sugus/Endpoint.h>
#include <sugus/detail/HandlerArray.h>



namespace Sugus {
namespace detail {


class EndpointContainer
{
  public:
    OpcUa_Int32*                GetSizePtr() const  { return m_array.GetSizePtr(); }
    OpcUa_EndpointDescription** GetArrayPtr() const { return m_array.GetArrayPtr(); }

  private:
    HandlerArrayTypedef(EndpointDescription);
    typedef EndpointDescriptionContainer array_type;
    typedef std::vector<Endpoint> container_type;
  public:
    typedef container_type::const_iterator const_iterator;

  public:
    size_t GetSize() const { Update(); return m_endpoints.size(); }

    const_iterator begin() const { Update(); return m_endpoints.begin(); }
    const_iterator end  () const { Update(); return m_endpoints.end  (); }

  private:
    void Update() const;

  private:
    array_type m_array;
    mutable std::vector<Endpoint> m_endpoints;
};


} // End namespace detail
} // End namespace Sugus

#endif  // SUGUS_DETAIL_ENDPOINTCONTAINER_H
