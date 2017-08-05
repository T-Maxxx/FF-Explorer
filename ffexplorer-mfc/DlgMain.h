#pragma once
#include "LocalizableDialog.h"

class CDlgMain : public CLocalizableDialog
{
public:
    CDlgMain(CWnd* pParent = NULL);

protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    virtual void OnSize(UINT nType, int cx, int cy);
    virtual BOOL OnInitDialog();
    virtual void LocalizeDialog();
    virtual void LocalizeMenu();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnMenuFileOptions();
    afx_msg void OnMenuFileQuit();
    afx_msg void OnMenuFileOpen();

private:
    // May be moved to CLocalizableDialog if needed in more than one menu.
    CMenu m_Menu;
    virtual void OnCancel();
};
