#ifndef SUGUS_DETAIL_HANDLERARRAY_H
#define SUGUS_DETAIL_HANDLERARRAY_H

namespace Sugus {
namespace detail {


template<class T, class Policy>
class HandlerArray
{
  public:
    HandlerArray()
        : m_size( 0 )
        , m_array( NULL )
    {}

    ~HandlerArray() {
        for(int i=0; i<m_size; ++i)
            Policy::Destroy( m_array[i] );
    }

  public:
    OpcUa_Int32* GetSizePtr()  const { return const_cast<OpcUa_Int32*>(&m_size); }
    T**          GetArrayPtr() const { return const_cast<T**>(&m_array); }

  public:
    int GetSize() const { return m_size; }
    T* Get() const { return m_array; }
    T& operator[](size_t index) const { return m_array[index]; }

  private:
    OpcUa_Int32 m_size;
    T* m_array;
};

#define HandlerArrayTypedef(T)                  \
    struct T##Policy {                          \
        static void Destroy(OpcUa_##T & p) { OpcUa_##T##_Clear(&p); }   \
    };                                                                  \
    typedef HandlerArray<OpcUa_##T, T##Policy> T##Container;

} // End namespace detail
} // End namespace Sugus

#endif  // SUGUS_DETAIL_HANDLERARRAY_H
