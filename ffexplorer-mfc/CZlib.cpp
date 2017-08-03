#include "stdafx.h"
#include "CZlib.hpp"
#include <fstream>

using namespace std;

CZlib::CZlib()
{
    memset(&m_ZS, 0, sizeof(m_ZS));
    m_LastOp = CZLO_NOOP;
}

CZlib::~CZlib()
{
    this->Finish();
}

uint CZlib::Compress(const void* const Data_, const uint Size_)
{
    this->CompressBlock(Data_, Size_, true);
    return this->Finish();
}

uint CZlib::CompressBlock(const void* const Data_, const uint Size_, bool IsLastBlock_)
{
    // Do not change case order (drop down).
    switch(m_LastOp)
    {
        case CZLO_DECOMPRESSION: // Drop down.
            // Must inflateEnd and deflateInit and clear m_DynArray.
            inflateEnd(&m_ZS);
        case CZLO_NOOP:
            // Must deflateInit and clear m_DynArray.
            memset(&m_ZS, 0, sizeof(z_stream));
            deflateInit(&m_ZS, Z_BEST_COMPRESSION);

            if (m_DynArray.Size())
                m_DynArray.Clear();
        case CZLO_COMPRESSION:
            // All ok.
            break;
        default: break;
    }

    m_LastOp = CZLO_COMPRESSION;
    int flushMode = IsLastBlock_? Z_FINISH : Z_SYNC_FLUSH;
    m_ZS.next_in = reinterpret_cast<Bytef*>(const_cast<void*>(Data_));
    m_ZS.avail_in = Size_;

    // Compress until input ends.
    while(m_ZS.avail_in)
    {
        byte buff[4096] = {'\0'};
        m_ZS.next_out = buff;
        m_ZS.avail_out = sizeof(buff);

        deflate(&m_ZS, flushMode);

        m_DynArray.Add(buff, sizeof(buff) - m_ZS.avail_out);
    }


    return m_DynArray.Size();
}

uint CZlib::Decompress(const void* const Data_, const uint Size_)
{
    this->DecompressBlock(Data_, Size_);
    return this->Finish();
}

uint CZlib::DecompressBlock(const void* const Data_, const uint Size_)
{
    // Do not change case order (drop down)
    switch(m_LastOp)
    {

        case CZLO_COMPRESSION: // Drop down.
            // Must deflateEnd and inflateInit and clear m_DynArray.
            deflateEnd(&m_ZS);
        case CZLO_NOOP: // Drop down.
            // Must inflateInit and clear m_DynArray.
            memset(&m_ZS, 0, sizeof(z_stream));
            inflateInit(&m_ZS);

            if (m_DynArray.Size())
                m_DynArray.Clear();
        case CZLO_DECOMPRESSION:
            // All ok.
            break;
        // No default.
    }

    m_LastOp = CZLO_DECOMPRESSION;
    m_ZS.next_in = reinterpret_cast<Bytef*>(const_cast<void*>(Data_));
    m_ZS.avail_in = Size_;

    // Decompress until input ends.
    while(m_ZS.avail_in)
    {
        byte buff[4096] = {'\0'};
        m_ZS.next_out = buff;
        m_ZS.avail_out = sizeof(buff);

        inflate(&m_ZS, Z_SYNC_FLUSH);

        m_DynArray.Add(buff, sizeof(buff) - m_ZS.avail_out);
    }

    return m_DynArray.Size();
}

uint CZlib::Finish()
{
    switch(m_LastOp)
    {
        case CZLO_COMPRESSION:
            deflateEnd(&m_ZS);
            break;
        case CZLO_DECOMPRESSION:
            inflateEnd(&m_ZS);
            break;
        //case CZLO_NOOP:
    }
    m_LastOp = CZLO_NOOP;
    return m_DynArray.Size();
}

uint CZlib::Result(void* const Out_, const uint OutSize_)
{
    return m_DynArray.Get(Out_, OutSize_);
}

bool CZlib::IsBufferEmpty()
{
    return m_DynArray.Size() == 0;
}


