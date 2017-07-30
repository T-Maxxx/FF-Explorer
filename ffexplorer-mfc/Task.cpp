#include "stdafx.h"
#include "Task.h"
#include "WindowMessages.h"


CTask::CTask()
{
    m_LastError.Empty();
    m_NotifyWindow = NULL;
}

CTask::CTask(const HWND & Window_) : CTask()
{
    SetNotifyWindow(Window_);
}

CTask::~CTask()
{
    m_LastError.Empty();
}

void CTask::SetNotifyWindow(const HWND& Window_)
{
    m_NotifyWindow = Window_;
}

void CTask::GetError(CString & Out_)
{
    Out_ = m_LastError;
}

void CTask::setError(const CString & Error_)
{
    m_LastError = Error_;
}

void CTask::ReportProgress(unsigned int Value_)
{
    if (Value_ > 100)
        Value_ = 100;

    PostMessage(m_NotifyWindow, CWM_TASK_PROGRESS, 0, Value_);
}
