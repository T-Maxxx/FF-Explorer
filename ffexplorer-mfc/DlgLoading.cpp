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
END_MESSAGE_MAP()


// CDlgLoading message handlers


BOOL CDlgLoading::OnInitDialog()
{
    CLocalizableDialog::OnInitDialog();

    m_ProgressBatch.SubclassDlgItem(IDC_PB_BATCH, this);
    m_ProgressBatch.SetRange(0, (short)m_Tasks.size());
    m_ProgressBatch.SetPos(0);

    m_ProgressStep.SubclassDlgItem(IDC_PB_STEP, this);
    m_ProgressStep.SetRange(0, 100);
    m_ProgressStep.SetPos(0);

    m_TextBatch.SubclassDlgItem(IDC_ST_PROGRESS_BATCH, this);
    m_TextStep.SubclassDlgItem(IDC_ST_PROGRESS_STEP, this);

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

    for (long i = 0; i < tasksCount; ++i)
    {
        ::PostMessage(selfHWND, CWM_TASK_CURRENT, 0, i);
        CTask* pTask = self->GetTaskByIndex(i);
        pTask->SetNotifyWindow(selfHWND);
        long result = pTask->RunTask();
        ::PostMessage(selfHWND, CWM_TASK_END, i, result);
        if (result)
            return 0;
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
    setBarValue(m_ProgressStep, lParam);
    return 0;
}

void CDlgLoading::LocalizeDialog()
{
}


void CDlgLoading::OnSize(UINT nType, int cx, int cy)
{
    if (!IsDialogInitialized())
        return;

    const int margin = 4;
    const int elemWidth = cx - 2 * margin;
    const int elemHeight = 30;

    m_TextBatch.MoveWindow(margin, margin, elemWidth, elemHeight);
    m_ProgressBatch.MoveWindow(margin, margin * 2 + elemHeight, elemWidth, elemHeight);
    m_TextStep.MoveWindow(margin, margin * 3 + 2 * elemHeight, elemWidth, elemHeight);
    m_ProgressStep.MoveWindow(margin, margin * 4 + 3 * elemHeight, elemWidth, elemHeight);
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
    m_ProgressBatch.SetPos(lParam);
    return 0;
}

afx_msg LRESULT CDlgLoading::OnTaskEnd(WPARAM wParam, LPARAM lParam)
{
    // Return if no error happened.
    if (lParam == 0)
        return 0;

    ::MessageBox(this->GetSafeHwnd(), L(IDS_TASK_EXECUTION_ERROR), L(m_Tasks[wParam]->GetError()), MB_OK);

    // TODO: discard changes in thread?
    for (int i = wParam; i >= 0; --i)
        m_Tasks[i]->DiscardChanges();

    this->SendMessage(WM_CLOSE);
    return 0;
}
