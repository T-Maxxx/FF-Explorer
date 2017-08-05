#pragma once
#include "LocalizableDialog.h"

// CDlgOptions dialog

class CDlgOptions : public CLocalizableDialog
{
    DECLARE_DYNAMIC(CDlgOptions)

public:
    CDlgOptions(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDlgOptions();

    virtual BOOL OnInitDialog();
    virtual void OnClose();
    virtual void OnOK();

protected:
    DECLARE_MESSAGE_MAP()
    virtual void LocalizeDialog();

private:
    void OnLanguageChanged();
    CComboBox m_cbLanguage;
public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
//    virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};
