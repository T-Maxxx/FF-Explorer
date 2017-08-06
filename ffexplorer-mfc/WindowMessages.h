#pragma once
#include <Windows.h>

enum ECustomWindowMessage : unsigned short int
{
    CWM_START = WM_USER,
    CWM_TASK_CURRENT,
    CWM_TASK_PROGRESS,
    CWM_TASK_END,
    CWM_TASKSBATCH_END,
    CWM_TASKSBATCH_SET_COUNT,
    CWM_COUNT
};
