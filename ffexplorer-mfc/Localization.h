#pragma once
#include <vector>
#include <map>

// Return localized string for current localization.
LPCTSTR L(UINT StrID_);

class CLocalization
{
public:
    CLocalization();
    ~CLocalization();

    UINT GetLocalizationCount() const;
    LPCTSTR Localize(UINT StrIdx_);
    void SetLocalization(UINT LocalizationIdx_);
    LPCTSTR GetLanguageName(UINT LocalizationIdx_);

    typedef std::map<CString, UINT> TDictionary;
    void LocalizeMenu(CMenu* pMenu_, const TDictionary& Dictionary_);

    static CLocalization* GetInstance();

    
private:
    struct SLanguageInfo;
    void loadLanguages();

    LCID m_CurrentLoc;
    CString m_LastLoadedString;
    std::vector<SLanguageInfo> m_Languages;
};

struct CLocalization::SLanguageInfo
{
    SLanguageInfo() : Index(0), LocalizationIndex(0) {}
    SLanguageInfo(const LCID Index_, const UINT LocalizationIndex_) :
        Index(Index_), LocalizationIndex(LocalizationIndex_) {}

    LCID Index;
    UINT LocalizationIndex;
};
