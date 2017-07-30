#pragma once
#include "Task.h"

class CTaskDecompression : public CTask
{
public:
    CTaskDecompression();
    ~CTaskDecompression();
    virtual int RunTask();
};

