#pragma once


// CDlgOptions dialog

class CDlgOptions : public CDialogEx
{
    DECLARE_DYNAMIC(CDlgOptions)

public:
    CDlgOptions(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDlgOptions();

    virtual BOOL OnInitDialog();
    virtual void OnClose();

protected:
    DECLARE_MESSAGE_MAP()

private:
    void localizeDialog();

    CComboBox m_cbLanguage;
};
