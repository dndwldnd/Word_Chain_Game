#pragma once


// CInGameDlg ��ȭ �����Դϴ�.

class CInGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInGameDlg)

public:
	CInGameDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CInGameDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INGAME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAddBtn1();
	afx_msg void OnBnClickedAddBtn2();
	CListBox m_chat_list1;
	CListBox m_chat_list2;
};
