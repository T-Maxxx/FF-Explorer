// DlgOptions.cpp : implementation file
//

#include "stdafx.h"
#include "FFExplorerApp.h"
#include "DlgOptions.h"
#include "Localization.h"
#include "afxdialogex.h"


// CDlgOptions dialog

IMPLEMENT_DYNAMIC(CDlgOptions, CLocalizableDialog)

CDlgOptions::CDlgOptions(CWnd* pParent /*=NULL*/)
	: CLocalizableDialog(IDD_DLGOPTIONS, pParent)
{

}

CDlgOptions::~CDlgOptions()
{
}


BEGIN_MESSAGE_MAP(CDlgOptions, CLocalizableDialog)
    ON_WM_SIZE()
    ON_CBN_SELENDOK(IDC_CB_LANGUAGE, &CDlgOptions::OnLanguageChanged)
END_MESSAGE_MAP()


BOOL CDlgOptions::OnInitDialog()
{
    m_cbLanguage.SubclassDlgItem(IDC_CB_LANGUAGE, this);
    CLocalization* pLoc = GetAppLocalization();
    for (UINT i = 0; i < pLoc->GetLocalizationCount(); ++i)
    {
        const int idx = m_cbLanguage.AddString(pLoc->GetLanguageNameByIdx(i));
        m_cbLanguage.SetItemData(idx, pLoc->GetLCIDByIndex(i));
    }
    int curSel = pLoc->GetIndexForLCID(GetAppOptions()->GetLocalization());
    assert(curSel != -1); // Not supported language. HOW?
    m_cbLanguage.SetCurSel(curSel);

    return CLocalizableDialog::OnInitDialog();
}

void CDlgOptions::OnClose()
{
    GetAppOptions()->LoadOptions();
    CLocalizableDialog::OnCancel();
}

void CDlgOptions::OnOK()
{
    GetAppOptions()->SaveOptions();
    CLocalizableDialog::OnOK();
}

void CDlgOptions::LocalizeDialog()
{
    CLocalization* pLoc = GetAppLocalization();
    // Language:
    SetDlgItemText(IDC_LBL_LANGUAGE, L(IDS_LANGUAGE));
    /*for (UINT i = 0; i < pLoc->GetLocalizationCount(); ++i)
    {
        const int langIdx = m_cbLanguage.AddString(pLoc->GetLanguageNameByIdx(i));
        m_cbLanguage.SetItemData(langIdx, i);
    }*/

    // Control buttons:
    SetDlgItemText(IDOK, L(IDS_APPLY));
    SetDlgItemText(IDCANCEL, L(IDS_CANCEL));
    SetWindowText(L(IDS_OPTIONS));
}

void CDlgOptions::OnLanguageChanged()
{
    int cur = m_cbLanguage.GetCurSel();
    GetAppOptions()->SetLocalization(m_cbLanguage.GetItemData(cur));
}

void CDlgOptions::OnSize(UINT nType, int cx, int cy)
{
    if (!IsDialogInitialized())
        return;

    CLocalizableDialog::OnSize(nType, cx, cy);
}


//BOOL CDlgOptions::OnCommand(WPARAM wParam, LPARAM lParam)
//{
//    // TODO: Add your specialized code here and/or call the base class
//
//    return CLocalizableDialog::OnCommand(wParam, lParam);
//}
