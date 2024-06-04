
// WordChainGameDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "WordChainGame.h"
#include "WordChainGameDlg.h"
#include "afxdialogex.h"
#pragma comment(lib, "winmm");
#include <mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWordChainGameDlg ��ȭ ����



CWordChainGameDlg::CWordChainGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_WORDCHAINGAME_DIALOG, pParent)
	, m_strAddress(_T("127.0.0.1"))	//IP �ʱⰪ
	, m_nPort(21000)		//Port �ʱⰪ
	, m_strID(_T(""))
	, m_strPASSWORD(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_cnt = 0;
	m_totaltimecount = 0;
}

void CWordChainGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strAddress);
	DDX_Text(pDX, IDC_EDIT2, m_nPort);
	DDX_Control(pDX, IDC_EDIT3, m_ctrlEdit);
	DDX_Text(pDX, IDC_EDIT4, m_strID);
	DDX_Text(pDX, IDC_EDIT5, m_strPASSWORD);
	DDX_Control(pDX, IDC_EDIT6, m_ctrlLeaderBoard);
	DDX_Control(pDX, IDC_EDIT8, m_MyWord);
	DDX_Control(pDX, IDC_EDIT9, m_OtherWord);
	DDX_Control(pDX, IDC_EDIT7, m_ctrlArchive);

}

BEGIN_MESSAGE_MAP(CWordChainGameDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CWordChainGameDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CWordChainGameDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CWordChainGameDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CWordChainGameDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDOK, &CWordChainGameDlg::OnBnClickedOk)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON5, &CWordChainGameDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CWordChainGameDlg �޽��� ó����

BOOL CWordChainGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.


	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CWordChainGameDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CWordChainGameDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CWordChainGameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWordChainGameDlg::OnBnClickedButton1()
{
	m_pClientSocket = new CClientSocket;
	m_pClientSocket->Create();
	CString str; str.Format(_T("[��] ����(%s:%d)�� ����!\r\n"), m_strAddress, m_nPort);
	m_ctrlEdit.ReplaceSel(str);
	this->UpdateData(TRUE);	// ��Ʈ�ѿ� �Էµ� ������ ��������� �ִ´�.
	bool success = m_pClientSocket->Connect(m_strAddress, m_nPort);
	if (!success) m_ctrlEdit.ReplaceSel(_T("[error] ���� ���� ����!\r\n"));
}



BOOL CWordChainGameDlg::DestroyWindow()
{
	m_pClientSocket->ShutDown();
	m_pClientSocket->Close();
	delete m_pClientSocket;
	return CDialogEx::DestroyWindow();
}


void CWordChainGameDlg::OnBnClickedButton2()
{
	//ȸ������ ��ư
	this->UpdateData(TRUE);
	CString msg;	//���� ����
	msg.Append(_T("0 "));
	msg.Append(m_strID);
	msg.Append(_T(" "));
	msg.Append(m_strPASSWORD);
	msg.Append(_T("\r\n"));
	m_pClientSocket->Send(msg, msg.GetLength());

	this->UpdateData(FALSE);
}


void CWordChainGameDlg::OnBnClickedButton3()
{
	//�α��� ��ư
	this->UpdateData(TRUE);
	CString msg;	//���� ����
	msg.Append(_T("1 "));
	msg.Append(m_strID);
	msg.Append(_T(" "));
	msg.Append(m_strPASSWORD);
	msg.Append(_T("\r\n"));
	m_pClientSocket->Send(msg, msg.GetLength());

	this->UpdateData(FALSE);
}


void CWordChainGameDlg::OnBnClickedButton4()
{
	//�غ� ��ư
	CString strButton4;
	CString msg;
	GetDlgItemText(IDC_BUTTON4, strButton4);
	if (!strButton4.Compare(_T("�غ�"))) {
		msg.Append(_T("2 ready \r\n"));
		m_pClientSocket->Send(msg, msg.GetLength());
		SetDlgItemText(IDC_BUTTON4, _T("�غ�����"));
	}
	else {
		msg.Append(_T("2 notready \r\n"));
		m_pClientSocket->Send(msg, msg.GetLength());
		SetDlgItemText(IDC_BUTTON4, _T("�غ�"));
	}
}


void CWordChainGameDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString msg;
	CString word;
	this->UpdateData(TRUE);
	GetDlgItemText(IDC_EDIT8, word);
	msg.Format(_T("6 %s \r\n"), word);
	m_pClientSocket->Send(msg, msg.GetLength());
	SetDlgItemText(IDC_EDIT8, _T(""));
	GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
	this->UpdateData(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);

	//CDialogEx::OnOK();
}


void CWordChainGameDlg::OnTimer(UINT_PTR nIDEvent)
{

	CString msg;
	if (nIDEvent == 1) {	//����

		CString s_time;
		s_time.Format(_T("%d"), m_cnt);
		SetDlgItemText(IDC_STATIC20, s_time);
		SetDlgItemText(IDC_STATIC19, _T(""));

		m_cnt--;
		this->UpdateData(FALSE);
		if (m_cnt < 0) {	//timeout
			GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
			SetDlgItemText(IDC_EDIT8, _T(""));
			msg.Format(_T("5 0 \r\n"));
			m_pClientSocket->Send(msg, msg.GetLength());
			KillTimer(1);
		}
		else {	//time left

		}

	}
	else if(nIDEvent == 2) {	//�����

		CString s_time;
		s_time.Format(_T("%d"), m_cnt);
		SetDlgItemText(IDC_STATIC19, s_time);
		SetDlgItemText(IDC_STATIC20, _T(""));
		m_cnt--;
		this->UpdateData(FALSE);
		if (m_cnt < 0) {	//timeout
			//��밡 Ÿ�� �ƿ� �Ǵ��� �޽����� ������ ����
			SetDlgItemText(IDC_EDIT9, _T(""));
			KillTimer(2);
		}
		else {	//time left

		}
	}
	else {	//��ü�ð� Ÿ�̸�
		msg.Format(_T("�����ð�: %d��"), m_totaltimecount);
		SetDlgItemText(IDC_STATIC23, msg);
		m_totaltimecount--;
		this->UpdateData(FALSE);
		if (m_totaltimecount < 0) {

			KillTimer(3);
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CWordChainGameDlg::OnBnClickedButton5()
{
	//ȿ���� ����ϱ�
	PlaySound("C:\\Users\\�̰���\\source\\repos\\�����ձ�\\WordChainGame\\clock.wav", 
		AfxGetInstanceHandle(), SND_ASYNC | SND_LOOP);
}
