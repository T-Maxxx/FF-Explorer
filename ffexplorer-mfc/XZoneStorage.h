#pragma once
struct XBlock
{
    XBlock() : Data(nullptr), Size(0) {}
    ~XBlock() { Clear(); };

    void Clear();
    void InitStream(unsigned int Size_);

    char* Data;
    unsigned int Size;
};

class XZoneStorage
{
public:
    XZoneStorage() {};
    ~XZoneStorage() { Clear(); };

    void Clear();
    XBlock& GetBlockByIdx(int Idx_);
    void InitStreams(const int* const Sizes_);

private:
    XBlock m_Blocks[11];
};

