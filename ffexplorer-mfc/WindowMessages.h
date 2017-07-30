#pragma once
#include <Windows.h>

enum ECustomWindowMessage : unsigned short int
{
    CWM_START = WM_USER,
    CWM_TASKSBATCH_BEGIN,
    CWM_TASK_CURRENT,
    CWM_TASK_PROGRESS,
    CWM_TASK_END,
    CWM_TASKSBATCH_END,
    CWM_COUNT
};
