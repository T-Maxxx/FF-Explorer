#include "stdafx.h"
#include "Localization.h"
#include "resource.h"

using namespace std;

CLocalization g_Localization;

CLocalization* CLocalization::GetInstance()
{
    return &g_Localization;
}

LPCTSTR L(UINT StrID_)
{
    return g_Localization.Localize(StrID_);
}

CLocalization::CLocalization()
{
    loadLanguages();
    m_CurrentLoc = m_Languages[0].Index;
}

CLocalization::~CLocalization()
{
    m_Languages.clear();
}

UINT CLocalization::GetLocalizationCount() const
{
    return m_Languages.size();
}

LPCTSTR CLocalization::Localize(UINT StrIdx_)
{
    if (m_LastLoadedString.LoadString(nullptr, StrIdx_, LANGIDFROMLCID(m_CurrentLoc)) != TRUE)
        m_LastLoadedString.Format(L"Unlocalized: %d", StrIdx_);
    return m_LastLoadedString.GetString();
}

void CLocalization::LocalizeMenu(CMenu * pMenu_, const TDictionary& Dictionary_)
{
    if (!pMenu_)
        return;

    for (int i = 0; i < pMenu_->GetMenuItemCount(); ++i)
    {
        // Localize item's submenu.
        LocalizeMenu(pMenu_->GetSubMenu(i), Dictionary_);

        // Localize menu item itself.
        CString key;
        pMenu_->GetMenuString(i, key, MF_BYPOSITION);
        if (key.IsEmpty())
            continue;

        MENUITEMINFO info;
        info.cbSize = sizeof(MENUITEMINFO);
        info.fMask = MIIM_ID;
        pMenu_->GetMenuItemInfo(i, &info, TRUE);

        auto it = Dictionary_.find(key);
        if (it != Dictionary_.end())
            pMenu_->ModifyMenu(info.wID, MF_BYCOMMAND | MF_STRING, info.wID, Localize(it->second));
    }
}

void CLocalization::SetLocalization(UINT LocalizationIdx_)
{
    assert(LocalizationIdx_ < GetLocalizationCount());
    m_CurrentLoc = m_Languages[LocalizationIdx_].Index;
}

LPCTSTR CLocalization::GetLanguageName(UINT LocalizationIdx_)
{
    assert(LocalizationIdx_ < GetLocalizationCount());
    return Localize(m_Languages[LocalizationIdx_].LocalizationIndex);
}

void CLocalization::loadLanguages()
{
    m_Languages.reserve(2);
    m_Languages.push_back(SLanguageInfo(MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), IDS_ENGLISH));
    m_Languages.push_back(SLanguageInfo(MAKELANGID(LANG_RUSSIAN, SUBLANG_DEFAULT), IDS_RUSSIAN));
}
