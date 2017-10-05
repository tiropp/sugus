#ifndef SUGUS_DETAIL_STRING_H
#define SUGUS_DETAIL_STRING_H

// STL includes
#include <string>

// OpcUa includes
#include <opcua.h>
#include <opcua_string.h>



namespace Sugus {
namespace detail {


class String
{
  public:
    String();
    String(const OpcUa_StringA other);
    String(const std::string& other);
    String(const OpcUa_String& other);
    String(const String& other);
    ~String();

  public:
    String& operator=(const String& other);
    String& operator=(const std::string& other);

  public:
    bool operator==(const String& other) const;
    OpcUa_String* Get() const { return const_cast<OpcUa_String*>(&m_string); }
    std::string Str() const { return std::string(OpcUa_String_GetRawString(&m_string)); }

  private:
    void CopyToMe(const char* other);

  private:
    OpcUa_String m_string;
};


} // End namespace detail
} // End namespace Sugus

#endif  // SUGUS_DETAIL_STRING_H
