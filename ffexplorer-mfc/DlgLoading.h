#pragma once
#include "Task.h"
#include <vector>

class CDlgLoading : public CDialogEx
{
    DECLARE_DYNAMIC(CDlgLoading)

public:
    CDlgLoading(CTask* pTask_, CWnd* pParent_ = NULL);
    virtual ~CDlgLoading();

    DECLARE_MESSAGE_MAP()

    virtual BOOL OnInitDialog();
    long GetTasksCount() const;
    CTask* GetTaskByIndex(const unsigned int Idx_) const;

private:
    static UINT __cdecl workerFunc(LPVOID pParam);

    CProgressCtrl m_Progress;
    HANDLE m_WorkerThread;
    std::vector<CTask*> m_Tasks; 
protected:
    afx_msg LRESULT OnTasksBatchEnd(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnTaskProgress(WPARAM wParam, LPARAM lParam);
};
