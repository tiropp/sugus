#ifndef SUGUS_EXCEPTION_H
#define SUGUS_EXCEPTION_H

// STL includes
#include <stdexcept>



namespace Sugus {


class Exception: public std::exception
{
  public:
    Exception(const std::string& message)
        : m_message( message )
    {}

    const char* what() const noexcept { return m_message.c_str(); }

  private:
    std::string m_message;
};


} // End namespace Sugus

#endif  // SUGUS_EXCEPTION_H
