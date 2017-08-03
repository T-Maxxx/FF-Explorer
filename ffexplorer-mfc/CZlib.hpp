#pragma once
#include "include/zlib-1211/zlib.h"
#include "include/zlib-1211/zutil.h"
#include "CDynArray.hpp"
#include <string>

typedef unsigned int uint;
typedef unsigned char byte;

class CZlib
{
public:
    CZlib();
    ~CZlib();

    // Compress memory block as complete zlib chunk.
    uint Compress(const void* const Data_, const uint Size_);

    // Decompress memory block as complete zlib chunk.
    uint Decompress(const void* const Data_, const uint Size_);

    // Copies (de-)compression result to array. Returns number of bytes written.
    uint Result(void* const Out_, const uint OutSize_);

    // Returns true if some data still available to export from class.
    bool IsBufferEmpty();

    // Compress block of memory. You can call it sequently few times.
    uint CompressBlock(const void* const Data_, const uint Size_, bool IsLastBlock_);

    // Decompress block of memory. You can call it sequently few times.
    uint DecompressBlock(const void* const Data_, const uint Size_);

    // Finishes compression\decompression operations.
    // Returns count of processed bytes in last operation.
    uint Finish();

private:
    enum CZlibLastOperation
    {
        // C - ZLO. Kappa
        CZLO_COMPRESSION = 0,
        CZLO_DECOMPRESSION,
        CZLO_NOOP
    };

    z_stream m_ZS;
    CDynArray m_DynArray;
    CZlibLastOperation m_LastOp;
};
