#ifndef SUGUS_ENDPOINTCONTAINER_H
#define SUGUS_ENDPOINTCONTAINER_H

// STL includes
#include <vector>

// Sugus includes
#include <sugus/Endpoint.h>



namespace Sugus {


class EndpointContainer
{
  private:
    typedef std::vector<Endpoint> container_type;
  public:
    typedef container_type::const_iterator const_iterator;

  public:
    void Add(const Endpoint& endpoint) { m_endpoints.push_back(endpoint); }

  public:
    const_iterator begin() const { return m_endpoints.begin(); }
    const_iterator end  () const { return m_endpoints.end  (); }

  private:
    container_type m_endpoints;
};


} // End namespace Sugus

#endif  // SUGUS_ENDPOINTCONTAINER_H
