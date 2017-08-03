#include <vector>

typedef unsigned char byte;
typedef unsigned int uint;

class CDynArray
{
public:
    CDynArray(const uint allocationSize = 4096);
    ~CDynArray();

    // No copy class.
    CDynArray(const CDynArray&) = delete;
    void operator = (const CDynArray&) = delete;

    // Returns total allocated memory size.
    uint Size();

    // Adds memory block to array.
    // Returns true if added successfully.
    bool Add(const void* const ptr, const uint size);

    // Extracts memory from array.
    // Returns number of extracted bytes.
    uint Get(void* const ptr, const uint size);

    // Frees all allocated memory.
    void Clear();

private:
    struct SElement
    {
        SElement(): ptr(0), used(0), next(0) {}
        ~SElement() { if (ptr) delete[] ptr; }

        byte* ptr;
        uint used;
        uint next;
    };

    std::vector<CDynArray::SElement> m_Handler;
    uint m_AllocationSize;
    uint m_TotalSize;
};
