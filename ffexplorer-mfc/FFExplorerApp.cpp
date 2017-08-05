
// ffexplorer-mfc.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "FFExplorerApp.h"
#include "DlgMain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CFFExplorerApp, CWinApp)
    ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


CFFExplorerApp::CFFExplorerApp()
{
}

CFFExplorerApp theApp;


BOOL CFFExplorerApp::InitInstance()
{
    // InitCommonControlsEx() is required on Windows XP if an application
    // manifest specifies use of ComCtl32.dll version 6 or later to enable
    // visual styles.  Otherwise, any window creation will fail.
    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof(InitCtrls);
    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&InitCtrls);

    CWinApp::InitInstance();
    
    AfxEnableControlContainer();

    CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

    SetRegistryKey(_T("FFExplorer"));
    m_AppOptions.LoadOptions();

    CDlgMain dlg;
    m_pMainWnd = &dlg;
    INT_PTR nResponse = dlg.DoModal();
    if (nResponse == -1)
    {
        TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
        TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
    }

    m_AppOptions.SaveOptions();

    return FALSE;
}

CAppOptions* CFFExplorerApp::GetAppOptions()
{
    return &m_AppOptions;
}

CLocalization* CFFExplorerApp::GetAppLocalization()
{
    return &m_AppLocalization;
}

