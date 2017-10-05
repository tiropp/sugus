#ifndef SUGUS_DATAVALUE_H
#define SUGUS_DATAVALUE_H

// STL includes
#include <cstdint>

// Sugus includes
#include <sugus/Types.h>



namespace Sugus {

struct Value
{
    Data     data;
    int      statusCode;
    uint64_t sourceTimestamp;
    uint64_t serverTimestamp;
    uint16_t sourcePicoseconds;
    uint16_t serverPicoseconds;
};

} // End namespace Sugus
#endif  // SUGUS_DATAVALUE_H
