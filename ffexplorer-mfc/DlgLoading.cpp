// DlgLoading.cpp : implementation file
//

#include "stdafx.h"
#include "FFExplorerApp.h"
#include "DlgLoading.h"
#include "afxdialogex.h"
#include "WindowMessages.h"
#include "Localization.h"

using namespace std;

// CDlgLoading dialog

IMPLEMENT_DYNAMIC(CDlgLoading, CLocalizableDialog)

CDlgLoading::CDlgLoading(vector<CTask*>& vTasks_, CWnd* pParent_ /*= NULL*/) :
    CLocalizableDialog(IDD_LOADING, pParent_),
    m_Tasks(vTasks_)
{
    m_TasksCount = 0;
}

CDlgLoading::~CDlgLoading()
{
}

BEGIN_MESSAGE_MAP(CDlgLoading, CLocalizableDialog)
    ON_MESSAGE(CWM_TASKSBATCH_END, &CDlgLoading::OnTasksBatchEnd)
    ON_MESSAGE(CWM_TASK_PROGRESS, &CDlgLoading::OnTaskProgress)
    ON_WM_SIZE()
    ON_MESSAGE(CWM_TASK_CURRENT, &CDlgLoading::OnNextTask)
    ON_MESSAGE(CWM_TASK_END, &CDlgLoading::OnTaskEnd)
    ON_MESSAGE(CWM_TASKSBATCH_SET_COUNT, &CDlgLoading::OnSetTasksCount)
END_MESSAGE_MAP()


// CDlgLoading message handlers


BOOL CDlgLoading::OnInitDialog()
{
    m_ProgressStep.SubclassDlgItem(IDC_PB_STEP, this);
    m_ProgressStep.SetRange(0, 100);
    m_ProgressStep.SetPos(0);

    m_TextBatch.SubclassDlgItem(IDC_ST_PROGRESS_BATCH, this);

    m_WorkerThread = AfxBeginThread(workerFunc, this, 0, 0, 0, 0);

    return CLocalizableDialog::OnInitDialog();
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

UINT CDlgLoading::discardChanges(CDlgLoading* self, long lastTaskIdx_)
{
    HWND selfHWND = self->GetSafeHwnd();
    ::PostMessage(selfHWND, CWM_TASKSBATCH_SET_COUNT, 0, lastTaskIdx_ + 1);
    for (long j = lastTaskIdx_; j >= 0; --j)
    {
        ::PostMessage(selfHWND, CWM_TASK_CURRENT, 0, lastTaskIdx_ - j);
        CTask* pTask = self->GetTaskByIndex(j);
        UINT discardResult = pTask->DiscardChanges();
        if (discardResult)
            return discardResult;
    }

    ::PostMessage(selfHWND, CWM_TASKSBATCH_END, 0, 0);
    return 0;
}

UINT __cdecl CDlgLoading::workerFunc(LPVOID pParam)
{
    CDlgLoading* self = reinterpret_cast<CDlgLoading*>(pParam);
    long tasksCount = self->GetTasksCount();
    HWND selfHWND = self->GetSafeHwnd();
    ::PostMessage(selfHWND, CWM_TASKSBATCH_SET_COUNT, 0, tasksCount);

    for (long i = 0; i < tasksCount; ++i)
    {
        ::PostMessage(selfHWND, CWM_TASK_CURRENT, 0, i);
        CTask* pTask = self->GetTaskByIndex(i);
        pTask->SetNotifyWindow(selfHWND);
        UINT result = pTask->RunTask();
        ::PostMessage(selfHWND, CWM_TASK_END, i, result);
        if (result)
            return discardChanges(self, i);
    }

    ::PostMessage(selfHWND, CWM_TASKSBATCH_END, 0, 0);
    return 0;
}


afx_msg LRESULT CDlgLoading::OnTasksBatchEnd(WPARAM wParam, LPARAM lParam)
{
    this->PostMessage(WM_CLOSE);
    return 0;
}


afx_msg LRESULT CDlgLoading::OnTaskProgress(WPARAM wParam, LPARAM lParam)
{
    setBarValue(m_ProgressStep, lParam);
    return 0;
}

void CDlgLoading::LocalizeDialog()
{
    SetWindowText(L(IDS_LOADING));
    m_TextBatch.SetWindowText(L"");
}


void CDlgLoading::OnSize(UINT nType, int cx, int cy)
{
    if (!IsDialogInitialized())
        return;

    const int margin = 4;
    const int elemWidth = cx - 2 * margin;
    const int elemHeight = 30;

    m_TextBatch.MoveWindow(margin, margin, elemWidth, elemHeight);
    m_ProgressStep.MoveWindow(margin, margin * 2 + elemHeight, elemWidth, elemHeight);
}

void CDlgLoading::setBarValue(CProgressCtrl& ProgressBar_, long Value_)
{
    if (Value_ == 100)
        ProgressBar_.SetRange(0, 101);

    ProgressBar_.SetPos(Value_ + 1);
    ProgressBar_.SetPos(Value_);

    if (Value_ == 100)
        ProgressBar_.SetRange(0, 100);
}


afx_msg LRESULT CDlgLoading::OnNextTask(WPARAM wParam, LPARAM lParam)
{
    CString text;
    text.Format(L(IDS_PROGRESS_BATCH), lParam, m_TasksCount);
    m_TextBatch.SetWindowTextW(text.GetString());
    m_ProgressStep.SetPos(0);
    return 0;
}

afx_msg LRESULT CDlgLoading::OnTaskEnd(WPARAM wParam, LPARAM lParam)
{
    // Return if no error happened.
    if (lParam == 0)
        return 0;

    ::MessageBox(this->GetSafeHwnd(), L(IDS_TASK_EXECUTION_ERROR), L(m_Tasks[wParam]->GetError()), MB_OK);
    return 0;
}

afx_msg LRESULT CDlgLoading::OnSetTasksCount(WPARAM wParam, LPARAM lParam)
{
    m_TasksCount = lParam;
    return 0;
}
