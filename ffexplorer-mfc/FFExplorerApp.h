
// ffexplorer-mfc.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "AppOptions.h"
#include "Localization.h"


class CFFExplorerApp : public CWinApp
{
public:
    CFFExplorerApp();

    virtual BOOL InitInstance();

    CAppOptions* GetAppOptions();
    CLocalization* GetAppLocalization();

    DECLARE_MESSAGE_MAP()

private:
    CAppOptions m_AppOptions;
    CLocalization m_AppLocalization;
};

extern CFFExplorerApp theApp;