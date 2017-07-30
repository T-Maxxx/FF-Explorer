// DlgLoading.cpp : implementation file
//

#include "stdafx.h"
#include "ffexplorer-mfc.h"
#include "DlgLoading.h"
#include "afxdialogex.h"
#include "WindowMessages.h"

// CDlgLoading dialog

IMPLEMENT_DYNAMIC(CDlgLoading, CDialogEx)

CDlgLoading::CDlgLoading(CTask* pTask_, CWnd* pParent_ /*= NULL*/) :
    CDialogEx(IDD_LOADING, pParent_)
{
    m_Tasks.push_back(pTask_);
}

CDlgLoading::~CDlgLoading()
{
}

BEGIN_MESSAGE_MAP(CDlgLoading, CDialogEx)
    ON_MESSAGE(CWM_TASKSBATCH_END, &CDlgLoading::OnTasksBatchEnd)
    ON_MESSAGE(CWM_TASK_PROGRESS, &CDlgLoading::OnTaskProgress)
END_MESSAGE_MAP()


// CDlgLoading message handlers


BOOL CDlgLoading::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    m_Progress.SubclassDlgItem(IDC_PROGRESSBAR, this);
    m_Progress.SetRange(0, 100);
    m_Progress.SetPos(0);
    m_WorkerThread = AfxBeginThread(workerFunc, this, 0, 0, 0, 0);

    return TRUE;
}

long CDlgLoading::GetTasksCount() const
{
    return m_Tasks.size();
}

CTask * CDlgLoading::GetTaskByIndex(const unsigned int Idx_) const
{
    if (Idx_ >= m_Tasks.size())
        return nullptr;

    return m_Tasks[Idx_];
}

UINT __cdecl CDlgLoading::workerFunc(LPVOID pParam)
{
    CDlgLoading* self = reinterpret_cast<CDlgLoading*>(pParam);
    long tasksCount = self->GetTasksCount();
    HWND selfHWND = self->GetSafeHwnd();

    ::PostMessage(selfHWND, CWM_TASKSBATCH_BEGIN, 0, tasksCount);
    for (long i = 0; i < tasksCount; ++i)
    {
        ::PostMessage(selfHWND, CWM_TASK_CURRENT, 0, i);
        CTask* pTask = self->GetTaskByIndex(i);
        pTask->SetNotifyWindow(selfHWND);
        long result = pTask->RunTask();
        ::PostMessage(selfHWND, CWM_TASK_END, 0, result);
    }
    ::PostMessage(selfHWND, CWM_TASKSBATCH_END, 0, tasksCount);

    return 0;
}


afx_msg LRESULT CDlgLoading::OnTasksBatchEnd(WPARAM wParam, LPARAM lParam)
{
    this->PostMessage(WM_CLOSE);
    return 0;
}


afx_msg LRESULT CDlgLoading::OnTaskProgress(WPARAM wParam, LPARAM lParam)
{
    if (lParam == 100)
        m_Progress.SetRange(0, 101);

    m_Progress.SetPos(lParam + 1);
    m_Progress.SetPos(lParam);

    if (lParam == 100)
        m_Progress.SetRange(0, 100);
    return 0;
}
