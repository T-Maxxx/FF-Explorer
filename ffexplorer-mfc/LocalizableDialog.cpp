#include "stdafx.h"
#include "LocalizableDialog.h"


CLocalizableDialog::CLocalizableDialog(UINT nIDTemplate, CWnd * pParent) : 
    CDialogEx(nIDTemplate, pParent)
{
    m_IsDialogInitialized = false;
}


CLocalizableDialog::~CLocalizableDialog()
{
}

BOOL CLocalizableDialog::OnInitDialog()
{
    LocalizeDialog();
    LocalizeMenu();
    m_IsDialogInitialized = true;

    return CDialogEx::OnInitDialog();
}

void CLocalizableDialog::LocalizeMenu()
{
}

bool CLocalizableDialog::IsDialogInitialized() const
{
    return m_IsDialogInitialized;
}


BOOL CLocalizableDialog::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN)
        if (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)
            return TRUE;


    return CDialogEx::PreTranslateMessage(pMsg);
}
