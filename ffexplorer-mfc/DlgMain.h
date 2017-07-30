#pragma once

class CDlgMain : public CDialogEx
{
public:
    CDlgMain(CWnd* pParent = NULL);

private:
    void localizeDialog();
    void localizeMenu();

protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnMenuFileOptions();
    afx_msg void OnMenuFileQuit();
    afx_msg void OnMenuFileOpen();
};
