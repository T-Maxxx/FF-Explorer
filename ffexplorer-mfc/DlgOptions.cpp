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
END_MESSAGE_MAP()


BOOL CDlgOptions::OnInitDialog()
{
    m_cbLanguage.SubclassDlgItem(IDC_CB_LANGUAGE, this);
    m_cbLanguage.SetCurSel(0);

    return CLocalizableDialog::OnInitDialog();
}

void CDlgOptions::OnClose()
{
}

void CDlgOptions::LocalizeDialog()
{
    CLocalization* pLoc = CLocalization::GetInstance();
    // Language:
    SetDlgItemText(IDC_LBL_LANGUAGE, L(IDS_LANGUAGE));
    for (UINT i = 0; i < pLoc->GetLocalizationCount(); ++i)
    {
        const int langIdx = m_cbLanguage.AddString(pLoc->GetLanguageName(i));
        m_cbLanguage.SetItemData(langIdx, i);
    }

    // Control buttons:
    SetDlgItemText(IDOK, L(IDS_APPLY));
    SetDlgItemText(IDCANCEL, L(IDS_CANCEL));
}

void CDlgOptions::OnSize(UINT nType, int cx, int cy)
{
    if (!IsDialogInitialized())
        return;

    CLocalizableDialog::OnSize(nType, cx, cy);
}
