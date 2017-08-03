#pragma once

class CAppOptions
{
public:
    CAppOptions();
    ~CAppOptions();

    // No copy class.
    CAppOptions(const CAppOptions&) = delete;
    void operator=(const CAppOptions&) = delete;

    void LoadOptions();
    void SaveOptions();

    void SetLocalization(LCID Loc_);
    LCID GetLocalization() const;

private: // Methods.
    void write(LPCTSTR Key_, const int& Data_);
    void write(LPCTSTR Key_, const CString& Data_);
    template <class T>
    void write(LPCTSTR Key_, const T& Data);

    void read(LPCTSTR Key_, int& Data_);
    void read(LPCTSTR Key_, CString& Data_);
    template <class T>
    void read(LPCTSTR Key_, T& Data_);

private: // Members.
    LCID m_CurrentLoc;

private: // Maintenance.
    CWinApp* m_App;
    bool m_IsSaveRequired;
    static LPCTSTR m_SectionName;
};

template<class T>
inline void CAppOptions::write(LPCTSTR Key_, const T & Data_)
{
    m_App->WriteProfileBinary(m_SectionName, Key_, reinterpret_cast<LPBYTE>(const_cast<T*>(&Data_)), sizeof(T));
}

template<class T>
inline void CAppOptions::read(LPCTSTR Key_, T & Data_)
{
    UINT readCount = 0;
    T* dataRead = nullptr;
    m_App->GetProfileBinary(m_SectionName, Key_, reinterpret_cast<LPBYTE*>(&dataRead), &readCount);
    if (readCount == sizeof(T))
    {
        memcpy_s(&Data_, sizeof(T), dataRead, sizeof(T));
        delete[] dataRead;
        return;
    }

    if (readCount)
        delete[] dataRead;

    CString dbgMsg;
    dbgMsg.Format(L"[REGISTER] Key mismatch: '%s', size read: %d\n", Key_, readCount);
    OutputDebugString(dbgMsg.GetString());
}
