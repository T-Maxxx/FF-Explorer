#include "stdafx.h"
#include <cstring>
#include <cassert>
#include "CDynArray.hpp"

CDynArray::CDynArray(const uint allocationSize)
{
    m_AllocationSize = allocationSize;
    m_TotalSize = 0;
}

CDynArray::~CDynArray()
{
    Clear();
}

uint CDynArray::Size()
{
    return m_TotalSize;
}

bool CDynArray::Add(const void * const ptr, const uint size)
{
    if (!size)
        return NULL;

    if (!m_Handler.size())
    {
        SElement e;
        e.ptr = new byte[m_AllocationSize]();
        assert(e.ptr);
        m_Handler.push_back(e);
    }
    
    const void* pUnreadData = ptr;
    uint toCopy = size;
    while(toCopy)
    {
        std::vector<SElement>::iterator last = --(m_Handler.end());
        const uint lastLeft = m_AllocationSize - last->used;
        uint copyCount = toCopy < lastLeft ? toCopy : lastLeft;

        memcpy(last->ptr + last->used, pUnreadData, copyCount);

        toCopy -= copyCount;
        pUnreadData = reinterpret_cast<const void*>(reinterpret_cast<uint>(pUnreadData) + copyCount);
        last->used += copyCount;

        // Need to store more bytes -> create new vector buffer.
        if (last->used == m_AllocationSize)
        {
            SElement e;
            e.ptr = new byte[m_AllocationSize];
            if (!e.ptr)
                return false;
            e.used = 0;
            m_Handler.push_back(e);
        }
    }

    m_TotalSize += size;
    return true;
}

uint CDynArray::Get(void *const ptr, const uint size)
{
    uint readCount = 0;
    void* nextUnwritten = ptr;
    while(m_Handler.size() && readCount < size)
    {
        std::vector<SElement>::iterator first = m_Handler.begin();
        const uint max = first->used - first->next;
        const uint toRead = size < max ? size : max;
        memcpy(nextUnwritten, first->ptr + first->next, toRead);
        first->next += toRead;
        readCount += toRead;
        nextUnwritten = reinterpret_cast<void*>(reinterpret_cast<uint>(nextUnwritten) + toRead);

        if (first->next == first->used)
        {
            delete[] first->ptr;
            m_Handler.erase(first);
        }
    }
    m_TotalSize -= readCount;
    return readCount;
}

void CDynArray::Clear()
{
    m_Handler.clear();
    m_TotalSize = 0;
}
