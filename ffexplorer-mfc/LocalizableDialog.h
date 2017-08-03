#pragma once
#include "afxdialogex.h"
class CLocalizableDialog : public CDialogEx
{
public:
    CLocalizableDialog(UINT nIDTemplate, CWnd *pParent = NULL);
    virtual ~CLocalizableDialog();

    // Must be called in child overload to apply localization in return.
    virtual BOOL OnInitDialog();

protected:
    // Returns current dialog localization state.
    bool IsDialogInitialized() const;

    // Overload this function to localize dialog items. [Required]
    virtual void LocalizeDialog() = 0;

    // Overload this method to localize dialog's menu. [Optional]
    virtual void LocalizeMenu();
    
private:
    bool m_IsDialogInitialized;
public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
};

