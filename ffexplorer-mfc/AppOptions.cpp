#include "stdafx.h"
#include "AppOptions.h"

CAppOptions theAppOptions;



CAppOptions::CAppOptions()
{
}


CAppOptions::~CAppOptions()
{
}

void CAppOptions::LoadOptions()
{
}

void CAppOptions::SaveOptions()
{
}

void CAppOptions::SetLocalization(LCID Loc_)
{
}

LCID CAppOptions::GetLocalization()
{
    return LCID();
}

CAppOptions * CAppOptions::GetInstance()
{
    return &theAppOptions;
}

void CAppOptions::write(LPCTSTR Key_, const int & Data_)
{
}

void CAppOptions::write(LPCTSTR Key_, const CString & Data_)
{
}

void CAppOptions::read(LPCTSTR Key_, int & Data_)
{
}

void CAppOptions::read(LPCTSTR Key_, CString & Data_)
{
}
