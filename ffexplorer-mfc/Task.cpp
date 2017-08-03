#include "stdafx.h"
#include "Task.h"
#include "WindowMessages.h"


CTask::CTask()
{
    m_LastError = 0;
    m_NotifyWindow = NULL;
}

CTask::CTask(const HWND & Window_) : CTask()
{
    SetNotifyWindow(Window_);
}

CTask::~CTask()
{
}

void CTask::SetNotifyWindow(const HWND& Window_)
{
    m_NotifyWindow = Window_;
}

UINT CTask::GetError() const
{
    return m_LastError;
}

void CTask::setError(UINT StrErrorIdx_)
{
    m_LastError = StrErrorIdx_;
}

void CTask::ReportProgress(unsigned int Value_)
{
    if (Value_ > 100)
        Value_ = 100;

    PostMessage(m_NotifyWindow, CWM_TASK_PROGRESS, 0, Value_);
}
