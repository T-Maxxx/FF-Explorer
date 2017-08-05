#include "stdafx.h"
#include "Localization.h"
#include "resource.h"

using namespace std;

CLocalization::CLocalization()
{
    loadLanguages();
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
    LANGID langid = LANGIDFROMLCID(GetAppOptions()->GetLocalization());
    if (m_LastLoadedString.LoadString(nullptr, StrIdx_, langid) != TRUE)
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

LCID CLocalization::GetLCIDByIndex(UINT Idx_)
{
    assert(Idx_ < m_Languages.size());
    return m_Languages[Idx_].Index;
}

LPCTSTR CLocalization::GetLanguageNameByIdx(UINT Idx_)
{
    assert(Idx_ < m_Languages.size());
    return Localize(m_Languages[Idx_].LanguageNameStrIdx);
}

int CLocalization::GetIndexForLCID(LCID LocalizationID_) const
{
    for (int i = 0; i < (int)m_Languages.size(); ++i)
        if (m_Languages[i].Index == LocalizationID_)
            return i;
    return -1;
}

void CLocalization::loadLanguages()
{
    m_Languages.reserve(2);
    m_Languages.push_back(SLanguageInfo(MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), IDS_ENGLISH));
    m_Languages.push_back(SLanguageInfo(MAKELANGID(LANG_RUSSIAN, SUBLANG_DEFAULT), IDS_RUSSIAN));
}
