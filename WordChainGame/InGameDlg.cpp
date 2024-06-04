// InGameDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "WordChainGame.h"
#include "InGameDlg.h"
#include "afxdialogex.h"


// CInGameDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CInGameDlg, CDialogEx)

CInGameDlg::CInGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_INGAME, pParent)
{

}

CInGameDlg::~CInGameDlg()
{
}

void CInGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHAT_LIST1, m_chat_list1);
	DDX_Control(pDX, IDC_CHAT_LIST2, m_chat_list2);
}


BEGIN_MESSAGE_MAP(CInGameDlg, CDialogEx)
	ON_BN_CLICKED(IDC_ADD_BTN1, &CInGameDlg::OnBnClickedAddBtn1)
	ON_BN_CLICKED(IDC_ADD_BTN2, &CInGameDlg::OnBnClickedAddBtn2)
END_MESSAGE_MAP()


// CInGameDlg �޽��� ó�����Դϴ�.


void CInGameDlg::OnBnClickedAddBtn1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString str;
	GetDlgItemText(IDC_CHAT_EDIT1, str);
	CInGameDlg::OnBnClickedAddBtn2();

}


void CInGameDlg::OnBnClickedAddBtn2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString str;
	GetDlgItemText(IDC_CHAT_EDIT2, str);
	CInGameDlg::OnBnClickedAddBtn2();
}
