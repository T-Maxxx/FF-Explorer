#pragma once
class CTask
{
public:
    CTask();
    CTask(const HWND& Window_);
    virtual ~CTask();

    virtual int RunTask() = 0;
    virtual int DiscardChanges() = 0;
    void SetNotifyWindow(const HWND& Window_);
    UINT GetError() const;


protected: 
    void setError(UINT StrErrorIdx_);
    void ReportProgress(unsigned int Value_);

private:
    UINT m_LastError;
    HWND m_NotifyWindow;
};

