#pragma once
#include <vector>
#include <map>

class CLocalization
{
public:
    CLocalization();
    ~CLocalization();

    LPCTSTR Localize(UINT StrIdx_);
    UINT GetLocalizationCount() const;
    LCID GetLCIDByIndex(UINT Idx_);
    LPCTSTR GetLanguageNameByIdx(UINT Idx_);
    int GetIndexForLCID(LCID LocalizationID_) const;

    typedef std::map<CString, UINT> TDictionary;
    void LocalizeMenu(CMenu* pMenu_, const TDictionary& Dictionary_);

private:
    struct SLanguageInfo;

    void loadLanguages();
    std::vector<SLanguageInfo> m_Languages;

    CString m_LastLoadedString;
};

struct CLocalization::SLanguageInfo
{
    SLanguageInfo() : Index(0), LanguageNameStrIdx(0) {}
    SLanguageInfo(const LCID Index_, const UINT LanguageNameStrIdx_) :
        Index(Index_), LanguageNameStrIdx(LanguageNameStrIdx_) {}

    LCID Index;
    UINT LanguageNameStrIdx;
};
