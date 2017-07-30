
// DlgMain.cpp : implementation file
//

#include "stdafx.h"
#include "ffexplorer-mfc.h"
#include "DlgMain.h"
#include "afxdialogex.h"
#include "DlgOptions.h"
#include "DlgLoading.h"
#include "TaskDecompression.h"
#include "Localization.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CDlgMain::CDlgMain(CWnd* pParent /*=NULL*/)
    : CDialogEx(IDD_FFEXPLORERMFC_DIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDlgMain::localizeDialog()
{
    this->SetWindowText(L(IDS_FFEXPLORER));
}

void CDlgMain::localizeMenu()
{
    CLocalization::TDictionary dict;
    dict[L"IDS_FILE"] = IDS_FILE;
    dict[L"IDS_OPEN"] = IDS_OPEN;
    dict[L"IDS_OPTIONS"] = IDS_OPTIONS;
    dict[L"IDS_QUIT"] = IDS_QUIT;
    CLocalization::GetInstance()->LocalizeMenu(GetMenu(), dict);
}

void CDlgMain::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDlgMain, CDialogEx)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_COMMAND(IDC_MENU_FILE_OPTIONS, &CDlgMain::OnMenuFileOptions)
    ON_COMMAND(IDC_MENU_FILE_QUIT, &CDlgMain::OnMenuFileQuit)
    ON_COMMAND(IDC_MENU_FILE_OPEN, &CDlgMain::OnMenuFileOpen)
END_MESSAGE_MAP()


// CDlgMain message handlers

BOOL CDlgMain::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);			// Set big icon
    SetIcon(m_hIcon, FALSE);		// Set small icon

    // TODO: Add extra initialization here
    localizeMenu();
    localizeDialog();

    return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDlgMain::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDlgMain::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}



void CDlgMain::OnMenuFileOptions()
{
    CDlgOptions dlgOptions;
    if (dlgOptions.DoModal() == IDOK)
    {
        AfxMessageBox(L"Preferences saved");
    }
}


void CDlgMain::OnMenuFileQuit()
{
    AfxGetMainWnd()->SendMessage(WM_CLOSE);
}

void CDlgMain::OnMenuFileOpen()
{
    // TODO: localize filter
    CFileDialog& dlgOpenFile = CFileDialog(TRUE, NULL, NULL, 6UL, L"Fastfile (*.ff)");
    if (dlgOpenFile.DoModal() != IDOK)
        return;

    CString& ffName = dlgOpenFile.GetFileName();

    CTaskDecompression taskDecompression;
    CDlgLoading dlgLoading(&taskDecompression);
    dlgLoading.DoModal();
}
