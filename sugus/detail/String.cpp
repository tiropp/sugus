#include "String.h"

// Sugus includes
#include <sugus/Exceptions.h>



namespace Sugus {
namespace detail {


String::String()
{
    OpcUa_String_Initialize( &m_string );
}

String::String(OpcUa_StringA other)
{
    CopyToMe(other);
}

String::String(const std::string& other)
{
    CopyToMe( other.c_str() );
}

void
String::CopyToMe(const char* other)
{
    OpcUa_StatusCode status = OpcUa_String_AttachToString(const_cast<OpcUa_StringA>(other),
                                                          OPCUA_STRINGLENZEROTERMINATED,
                                                          0,
                                                          OpcUa_True,
                                                          OpcUa_True,
                                                          &m_string);
    if( OpcUa_IsBad(status) )
        throw StringCreationFailed(status);
}

String::String(const OpcUa_String& other)
{
    OpcUa_String_StrnCpy(&m_string, &other, OPCUA_STRING_LENDONTCARE);
}

String::String(const String& other)
{
    OpcUa_String_StrnCpy(&m_string, &other.m_string, OPCUA_STRING_LENDONTCARE);
}

String::~String()
{
    OpcUa_String_Clear( &m_string );
}

String&
String::operator=(const String& other)
{
    OpcUa_String_StrnCpy(&m_string, &other.m_string, OPCUA_STRING_LENDONTCARE);
    return *this;
}

String&
String::operator=(const std::string& other)
{
    String s(other);
    OpcUa_String_StrnCpy(&m_string, &s.m_string, OPCUA_STRING_LENDONTCARE);
    return *this;
}

bool
String::operator==(const String& other) const
{
    return OpcUa_String_StrnCmp(&m_string,
                                &other.m_string,
                                OPCUA_STRING_LENDONTCARE,
                                OpcUa_False) == 0;
}


} // End namespace detail
} // End namespace Sugus
