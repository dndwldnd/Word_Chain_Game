
// ServerDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Server.h"
#include "ServerDlg.h"
#include "afxdialogex.h"
#include "ChildSocket.h"


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


// CServerDlg ��ȭ ����



CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_numlogged = 0;
	m_prevword = _T("");
	//  m_isfirst = _T("");
	m_isfirst = 1;
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_ctrlEdit);
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CServerDlg �޽��� ó����

BOOL CServerDlg::OnInitDialog()
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

	//db ����
	mysql_init(&m_mysql);
	MYSQL *conn = mysql_real_connect(&m_mysql, "127.0.0.1", "gaeun", "1203", "testdb", 3306, (char*)NULL, 0);
	if (conn == NULL) {
		AfxMessageBox((LPCTSTR)mysql_error(&m_mysql));
		::PostQuitMessage(0); 
		return FALSE;
	}
	this->m_ctrlEdit.ReplaceSel(_T("MySQL ������ ����Ǿ����ϴ�\r\n"));
	mysql_set_character_set(&m_mysql, "euckr");


	//���� ����
	m_pListenSocket = new CListenSocket;
	if (m_pListenSocket->Create(21000, SOCK_STREAM)) {
		if (m_pListenSocket->Listen()) {
			m_ctrlEdit.ReplaceSel(_T("[����] Port(21000)�� Listen �������� ���Ƚ��ϴ�.\r\n"));
		}
		else AfxMessageBox(_T("ERROR: Failed to create a listen socket"));
	}


	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CServerDlg::OnPaint()
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
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CServerDlg::DestroyWindow()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	//db
	mysql_close(&m_mysql);

	//����
	POSITION pos = m_pListenSocket->m_pChildSocketList.GetHeadPosition();
	CChildSocket* pChild = NULL;
	while (pos != NULL) {
		pChild = (CChildSocket*)(m_pListenSocket->m_pChildSocketList.GetNext(pos));
		if (pChild != NULL) {
			pChild->ShutDown(); pChild->Close(); delete pChild;
		}
	}
	m_pListenSocket->ShutDown();
	m_pListenSocket->Close();
	delete m_pListenSocket;
	return CDialogEx::DestroyWindow();
}



void CServerDlg::SignUp(CString id, CString password, UINT port)
{
	//ȸ������
	CString query;
	query.Format(_T("insert into member (id,pw) values ('%s',password('%s'))"), id, password);
	int status = mysql_query(&m_mysql, query);
	int UserNo = mysql_insert_id(&m_mysql);
	CString str;
	str.Format(_T("0 %s \r\n"), id);
	CServerDlg* pMain = (CServerDlg*)AfxGetMainWnd();
	pMain->m_ctrlEdit.ReplaceSel(str);
	//map ����
	m_usermap.insert(pair<UINT, CString>(port, id));
	m_ready.insert(pair<CString, int>(id, 0));
	m_mapScore.insert(pair<CString, int>(id, 0));

	m_pListenSocket->Broadcast(str);
}


void CServerDlg::Login(CString id, CString password, UINT port)
{
	//�α���
	CString query;
	query.Format(_T("select * from member where id='%s' and pw=password('%s')"), id, password);
	int status = mysql_query(&m_mysql, query);
	MYSQL_RES *result = mysql_store_result(&m_mysql);
	int nRowCount = mysql_num_rows(result);

	if (m_numlogged >= 2) {
		nRowCount = 0;	//2�� �̻� �α��� �Ϸ��� �� �� ���з� �����
	}
	if (nRowCount > 0) {
		MYSQL_ROW row = mysql_fetch_row(result);
		int UserNo = atoi(row[0]);
		CString str;
		str.Format(_T("1 %s \r\n"), id);
		CServerDlg* pMain = (CServerDlg*)AfxGetMainWnd();
		pMain->m_ctrlEdit.ReplaceSel(str);
		//map ����
		m_usermap.insert(pair<UINT, CString>(port, id));
		m_ready.insert(pair<CString, int>(id, 0));
		m_mapScore.insert(pair<CString, int>(id, 0));
		m_numlogged++;	//�α��� �� ��� �� +1

		m_pListenSocket->Broadcast(str);
	}
	else {
		AfxMessageBox("����");
	}

}


void CServerDlg::Ready(int isready, CString username, CString msg)
{
	if (isready == 1) {
		//�غ�
		m_pListenSocket->Broadcast(msg);
		m_ready[username] = 1;
	}
	else {
		//�غ� ����
		m_pListenSocket->Broadcast(msg);
		m_ready[username] = 0;
	}

	//�غ� Ȯ��
	int result = 1;
	for (auto it = m_ready.begin(); it != m_ready.end(); it++) {

		if (it->second == 0) result = 0;
	}
	if (result == 1 && m_ready.size()==2) {
		//��� �غ� �� 2�� �α���-> ���� ����

		for (auto it = m_ready.begin(); it != m_ready.end(); it++) {
			it->second = 0;	//�غ� �������·� map ����
		}
		

		CString query;
		query.Append(_T("9 \r\n"));
		Sleep(1000);	//�����̰� ������ Client �ܿ��� �ΰ��� ���̾�αװ� �������� �ʴ´�!!
		m_pListenSocket->Broadcast(query);
		m_ctrlEdit.ReplaceSel(query);


		CString turn, myscore, otherscore, time, name1, name2;
		CString temp;
		turn = m_usermap.begin()->second;	//���� �α����� ����� ����
		Sleep(500);

		//���� �ϱ� ���� �� �ֱ�
		time.Format(_T("10000"));	//���۽� �ִ� �ð� ms
		query.Format(_T("5 %s %s "), turn, time);
		for (auto it = m_mapScore.begin(); it != m_mapScore.end(); it++) {
			temp.Format(_T("%s %d "), it->first, it->second);
			query.Append(temp);
		}
		temp.Format(_T("0 1 40000 "));	//Ÿ�Ӿƿ��� ���� �� ����(�ֱ�)�ƴϴ�, ���� �����϶� 1, �� ���� �ð�
		query.Append(temp);
		temp.Format(_T("\r\n"));
		query.Append(temp);
		
		m_pListenSocket->Broadcast(query);

		m_ctrlEdit.ReplaceSel(query);

		query.Format(_T("���� ����\r\n"));
		m_ctrlEdit.ReplaceSel(query);

		//server timer start
		SetTimer(1, 40000, NULL);	//�� ���ӽð� ���� �Ʒ� �Ѵ� �ٲٱ�
	}
	
}


void CServerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	if (nIDEvent == 1) {

		//���� ����
		CString query, temp;
		int h_score = -1;
		CString winner;
		query.Format(_T("7 "));
		for (auto it = m_mapScore.begin(); it != m_mapScore.end(); it++) {
			temp.Format(_T("%s %d "), it->first, it->second);
			query.Append(temp);
			if (h_score < it->second) {	//���� �ǰ�
				h_score = it->second;
				winner = it->first;
			}
			else if (h_score == it->second) {	//���, ���߿� ������ ����� �̱��, 2��° iteration�̹Ƿ� 2��°�� winner
				winner = it->first;
			}
		}
		temp.Format(_T("%s "), winner);
		query.Append(temp);
		
		temp.Format(_T("\r\n"));
		query.Append(temp);

		m_pListenSocket->Broadcast(query);
		m_ctrlEdit.ReplaceSel(query);

		//DB ����
		CString  str;
		for (auto it = m_mapScore.begin(); it != m_mapScore.end(); it++) {
			//�� ��������
			CString prev_score;
			int iprev_score;
			query.Format(_T("select point from member where id = '%s'"), it->first);
			int status = mysql_query(&m_mysql, query);
			MYSQL_RES *result = mysql_store_result(&m_mysql);

			if (result) {
				int nFieldCount = mysql_num_fields(result);
				MYSQL_FIELD *fields = mysql_fetch_field(result);
				MYSQL_ROW row;
				while ((row = mysql_fetch_row(result))) {
					prev_score = row[0];
					iprev_score = _ttoi(prev_score);
					break;

				}
			}
			if (iprev_score < it->second & it->first == winner) {	//�ְ����� ���Ž�, ������ ��
				query.Format(_T("update member set point = %d where id = '%s'"), it->second, it->first);
				int status = mysql_query(&m_mysql, query);
			}

		}
		str.Format(_T("DB ������Ʈ\r\n"));
		m_ctrlEdit.ReplaceSel(str);
		//�������� �������� �޽��� ������

		query.Format(_T("select * from member order by point desc"));
		int status = mysql_query(&m_mysql, query);
		MYSQL_RES *result = mysql_store_result(&m_mysql);
		if (result) {
			str.Format(_T("4 "));
			CString temp;
			CString name, point;
			int nFieldCount = mysql_num_fields(result);
			MYSQL_FIELD *fields = mysql_fetch_field(result);
			MYSQL_ROW row;

			int i = 0;
			while ((row = mysql_fetch_row(result))) {
				i++;
				name = row[1];
				point = row[3];
				temp = str;
				str.Format(_T("%s%s %s "), temp, name, point);
				if (i == 5) break;	//5����� ��������
			}
			m_ctrlEdit.ReplaceSel(str);

			temp = str;
			str.Format(_T("%s%s"), temp, _T("\r\n"));

			m_pListenSocket->Broadcast(str);	//db �޽��� ������

		}
		//map�� ����� ���� 0���� �ʱ�ȭ
		for (auto it = m_mapScore.begin(); it != m_mapScore.end(); it++) {
			m_mapScore.at(it->first) = 0;
			query.Append(temp);
		}

		//���� ��� �����ߴ��� ���� �ʱ�ȭ, ���� �ܾ� �ʱ�ȭ
		CChildSocket* pChild= (CChildSocket*)AfxGetMainWnd();
		m_isfirst = 1;
		m_prevword.Format(_T(""));

		str.Format(_T("���� ����\r\n"));
		m_ctrlEdit.ReplaceSel(str);

		// Ÿ�̸� ����
		KillTimer(1);
	}

	CDialogEx::OnTimer(nIDEvent);
}
