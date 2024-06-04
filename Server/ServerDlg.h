
// ServerDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "ListenSocket.h"
#include "mysql.h"
#include<map>
using namespace std;

// CServerDlg ��ȭ ����
class CServerDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CServerDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERVER_DIALOG };
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
	CEdit m_ctrlEdit;
	CListenSocket* m_pListenSocket;
	virtual BOOL DestroyWindow();
	MYSQL m_mysql;
	void SignUp(CString id, CString password, UINT port);
	void Login(CString id, CString password, UINT port);
	map<UINT, CString> m_usermap;
	void Ready(int isready, CString username, CString msg);
	map<CString, int> m_ready;
	map<CString, int> m_mapScore;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int m_numlogged;
	CString m_prevword;
//	CString m_isfirst;
	int m_isfirst;
};
