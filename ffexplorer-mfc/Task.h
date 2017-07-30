#pragma once
class CTask
{
public:
    CTask();
    CTask(const HWND& Window_);
    virtual ~CTask();

    virtual int RunTask() = 0;
    void SetNotifyWindow(const HWND& Window_);
    void GetError(CString& Out_);


protected: 
    void setError(const CString& Error_);
    void ReportProgress(unsigned int Value_);

private:
    CString m_LastError;
    HWND m_NotifyWindow;
};

