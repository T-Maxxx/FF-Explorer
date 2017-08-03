#include "stdafx.h"
#include "XZoneStorage.h"

void XBlock::Clear()
{
    if (Data)
        delete[] Data;
}

void XBlock::InitStream(unsigned int Size_)
{
    Size = Size_;
    Data = new char[Size_]; // TODO: alloc type switch?
}

void XZoneStorage::Clear()
{
    for (int i = 0; i < 11; ++i)
        m_Blocks[i].Clear();
}

XBlock & XZoneStorage::GetBlockByIdx(int Idx_)
{
    assert(Idx_ >= 0 && Idx_ < 11);
    return m_Blocks[Idx_];
}

void XZoneStorage::InitStreams(const int * const Sizes_)
{
    for (int i = 0; i < 11; ++i)
        m_Blocks[i].InitStream(Sizes_[i]);
}
