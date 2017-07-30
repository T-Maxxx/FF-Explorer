// DlgOptions.cpp : implementation file
//

#include "stdafx.h"
#include "ffexplorer-mfc.h"
#include "DlgOptions.h"
#include "Localization.h"
#include "afxdialogex.h"


// CDlgOptions dialog

IMPLEMENT_DYNAMIC(CDlgOptions, CDialogEx)

CDlgOptions::CDlgOptions(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLGOPTIONS, pParent)
{

}

CDlgOptions::~CDlgOptions()
{
}


BEGIN_MESSAGE_MAP(CDlgOptions, CDialogEx)
END_MESSAGE_MAP()


BOOL CDlgOptions::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    m_cbLanguage.SubclassDlgItem(IDC_CB_LANGUAGE, this);
    localizeDialog();
    m_cbLanguage.SetCurSel(0);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgOptions::OnClose()
{
}

void CDlgOptions::localizeDialog()
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
    SetDlgItemText(IDOK,        L(IDS_APPLY));
    SetDlgItemText(IDCANCEL,    L(IDS_CANCEL));
}
