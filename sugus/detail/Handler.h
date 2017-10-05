#ifndef SUGUS_DETAIL_HANDLER_H
#define SUGUS_DETAIL_HANDLER_H

// OpcUa includes
#include <opcua.h>



namespace Sugus {
namespace detail {


template<class T, class Policy>
class Handler
{
  public:
    typedef Handler<T, Policy> this_type;

  public:
    Handler() {
        Policy::Initialize(m_handlee);
    }
    ~Handler() {
        Policy::Destroy(m_handlee);
    }
    Handler(const this_type& other) {
        Policy::Copy(other.m_handlee, m_handlee);
    }

  public:
    Handler& operator=(const this_type& other) {
        Policy::Copy(other.m_handlee, m_handlee);
        return *this;
    }
  public:
    T* Get() const { return const_cast<T*>(&m_handlee); }
    T* operator->() const { return Get(); }

  private:
    T m_handlee;
};

#define HandlerTypedef(T)                                               \
    struct T##Policy {                                                  \
        typedef OpcUa_##T type;                                         \
        static void Initialize(type& p) { OpcUa_##T##_Initialize(&p); } \
        static void Destroy   (type& p) { OpcUa_##T##_Clear(&p); }      \
      private:                                                          \
        static void Copy      (type& dst, type& src);                   \
    };                                                                  \
    typedef Handler<OpcUa_##T, T##Policy> T;

#define HandlerCopyableTypedef(T)                                       \
    struct T##Policy {                                                  \
        typedef OpcUa_##T type;                                         \
        static void Initialize(type& p) { OpcUa_##T##_Initialize(&p); } \
        static void Destroy   (type& p) { OpcUa_##T##_Clear(&p); }      \
        static void Copy      (const type& src, type& dst) { OpcUa_##T##_CopyTo(&src, &dst); } \
    };                                                                  \
    typedef Handler<OpcUa_##T, T##Policy> T;

} // End namespace detail
} // End namespace Sugus

#endif  // SUGUS_DETAIL_HANDLER_H
