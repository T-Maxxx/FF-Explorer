#include "stdafx.h"
#include "TaskDecompression.h"


CTaskDecompression::CTaskDecompression()
{
}


CTaskDecompression::~CTaskDecompression()
{
}

int CTaskDecompression::RunTask()
{
    Sleep(1000);
    this->ReportProgress(33);
    Sleep(1000);
    this->ReportProgress(66);
    Sleep(1000);
    this->ReportProgress(100);
    Sleep(1000);
    return 0;
}

int CTaskDecompression::DiscardChanges()
{
    return 0;
}
