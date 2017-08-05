#include "stdafx.h"
#include "AppOptions.h"

// Macro to simplify read operation call.
#define _READ(paramName) read(L#paramName, m_##paramName)
// Macro to simplify write operation call.
#define _WRITE(paramName) write(L#paramName, m_##paramName)

LPCTSTR CAppOptions::m_SectionName = L"Settings";

CAppOptions::CAppOptions()
{
    m_App = AfxGetApp();
    m_IsSaveRequired = false;

    m_CurrentLoc = 0;
}


CAppOptions::~CAppOptions()
{
    m_IsSaveRequired = false;
}

void CAppOptions::LoadOptions()
{
    if (m_IsSaveRequired)
        return;

    _READ(CurrentLoc);
    
    m_IsSaveRequired = false;
}

void CAppOptions::SaveOptions()
{
    if (!m_IsSaveRequired)
        return;

    _WRITE(CurrentLoc);

    m_IsSaveRequired = false;
}
/*
bool CAppOptions::IsSaveRequired() const
{
    return m_IsSaveRequired;
}*/

void CAppOptions::SetLocalization(LCID Loc_)
{
    m_CurrentLoc = Loc_;
    m_IsSaveRequired = true;
}

LCID CAppOptions::GetLocalization() const
{
    return m_CurrentLoc;
}

void CAppOptions::write(LPCTSTR Key_, const int & Data_)
{
    m_App->WriteProfileInt(m_SectionName, Key_, Data_);
}

void CAppOptions::write(LPCTSTR Key_, const CString & Data_)
{
    m_App->WriteProfileString(m_SectionName, Key_, Data_.GetString());
}

void CAppOptions::read(LPCTSTR Key_, int & Data_)
{
    m_App->GetProfileInt(m_SectionName, Key_, 0);
}

void CAppOptions::read(LPCTSTR Key_, CString & Data_)
{
    Data_ = m_App->GetProfileString(_T("Settings"), Key_);
}
