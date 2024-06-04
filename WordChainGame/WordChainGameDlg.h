
// WordChainGameDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "ClientSocket.h"

// CWordChainGameDlg ��ȭ ����
class CWordChainGameDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CWordChainGameDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WORDCHAINGAME_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
//	afx_msg void OnStnClickedStatic2();
	CString m_strAddress;
	int m_nPort;
	CEdit m_ctrlEdit;
	CClientSocket* m_pClientSocket;
	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedButton2();
	CString m_strID;
	CString m_strPASSWORD;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
//	CString m_strLeaderBoard;
//	CEdit m_editLeaderBoard;
	CEdit m_ctrlLeaderBoard;
	CEdit m_ctrlWho;
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int m_cnt;
	CEdit m_MyWord;
	CEdit m_OtherWord;
	CEdit m_ctrlArchive;
//	CEdit m_ctrlTotalTime;
	int m_totaltimecount;
	afx_msg void OnBnClickedButton5();
};
