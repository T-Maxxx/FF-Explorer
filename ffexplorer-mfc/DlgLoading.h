#pragma once
#include "Task.h"
#include <vector>
#include "LocalizableDialog.h"

class CDlgLoading : public CLocalizableDialog
{
    DECLARE_DYNAMIC(CDlgLoading)

public:
    CDlgLoading(std::vector<CTask*>& vTasks_, CWnd* pParent_ = NULL);
    virtual ~CDlgLoading();

    DECLARE_MESSAGE_MAP()

    virtual BOOL OnInitDialog();
    long GetTasksCount() const;
    CTask* GetTaskByIndex(const unsigned int Idx_) const;

private:
    static UINT __cdecl workerFunc(LPVOID pParam);
    void setBarValue(CProgressCtrl& ProgressBar_, long Value_);

    CStatic m_TextBatch;
    CStatic m_TextStep;
    CProgressCtrl m_ProgressBatch;
    CProgressCtrl m_ProgressStep;
    HANDLE m_WorkerThread;
    std::vector<CTask*>& m_Tasks;
protected:
    afx_msg LRESULT OnTasksBatchEnd(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnTaskProgress(WPARAM wParam, LPARAM lParam);
    virtual void LocalizeDialog();
public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
    afx_msg LRESULT OnNextTask(WPARAM wParam, LPARAM lParam);

    // Happens when one of tasks just ended.
    // wParam is index of task.
    // lParam is return value.
    afx_msg LRESULT OnTaskEnd(WPARAM wParam, LPARAM lParam);
};
