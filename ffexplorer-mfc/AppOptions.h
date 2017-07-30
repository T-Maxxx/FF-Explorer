#pragma once

class CAppOptions
{
public:
    CAppOptions();
    ~CAppOptions();

    void LoadOptions();
    void SaveOptions();

    void SetLocalization(LCID Loc_);
    LCID GetLocalization();

    static CAppOptions* GetInstance();
private:
    void write(LPCTSTR Key_, const int& Data_);
    void write(LPCTSTR Key_, const CString& Data_);
    template <class T>
    void write(LPCTSTR Key_, const T& Data);

    void read(LPCTSTR Key_, int& Data_);
    void read(LPCTSTR Key_, CString& Data_);
    template <class T>
    void read(LPCTSTR Key_, T& Data_);

    LCID m_CurrentLoc;
};

template<class T>
inline void CAppOptions::write(LPCTSTR Key_, const T & Data)
{
}

template<class T>
inline void CAppOptions::read(LPCTSTR Key_, T & Data_)
{
}
