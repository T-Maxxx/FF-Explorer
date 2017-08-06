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
    static UINT discardChanges(CDlgLoading* self, long lastTaskIdx_);

    void setBarValue(CProgressCtrl& ProgressBar_, long Value_);

    CStatic m_TextBatch;
    CProgressCtrl m_ProgressStep;
    HANDLE m_WorkerThread;
    UINT m_TasksCount;
    std::vector<CTask*>& m_Tasks;
protected:
    afx_msg LRESULT OnTasksBatchEnd(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnTaskProgress(WPARAM wParam, LPARAM lParam);
    virtual void LocalizeDialog();
public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
    afx_msg LRESULT OnNextTask(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnTaskEnd(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnSetTasksCount(WPARAM wParam, LPARAM lParam);
};
