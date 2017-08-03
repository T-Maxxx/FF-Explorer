#pragma once
#include "XZoneLoader.h"
#include "XZoneStorage.h"

class XZone
{
public:
    XZone();
    ~XZone();

private:
    XZoneLoader m_Loader;
    XZoneStorage m_Storage;
};

