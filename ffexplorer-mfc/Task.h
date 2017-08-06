#pragma once
class CTask
{
public:
    CTask();
    CTask(const HWND& Window_);
    virtual ~CTask();

    virtual UINT RunTask() = 0;
    virtual UINT DiscardChanges() = 0;
    void SetNotifyWindow(const HWND& Window_);
    UINT GetError() const;


protected: 
    void setError(UINT StrErrorIdx_);
    void ReportProgress(unsigned int Value_);

private:
    UINT m_LastError;
    HWND m_NotifyWindow;
};

