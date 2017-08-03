#pragma once
#include "Task.h"
#include "CZlib.hpp"

class CTaskDecompression : public CTask
{
public:
    CTaskDecompression();
    ~CTaskDecompression();
    virtual int RunTask();
    virtual int DiscardChanges();
};

