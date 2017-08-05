#pragma once
/////////////////////////////////////////////////////////////////////////////
// This file is managed to make access to main application classes easier. //
/////////////////////////////////////////////////////////////////////////////

#include "FFExplorerApp.h"
#include <Windows.h>

inline CAppOptions* GetAppOptions()
{
    return theApp.GetAppOptions();
}

inline CLocalization* GetAppLocalization()
{
    return theApp.GetAppLocalization();
}

// Return localized string for current localization.
inline LPCTSTR L(UINT StrID_)
{
    return GetAppLocalization()->Localize(StrID_);
}
