// ListenSocket.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Server.h"
#include "ListenSocket.h"
#include "ChildSocket.h"
#include "ServerDlg.h"

// CListenSocket

CListenSocket::CListenSocket()
{
}

CListenSocket::~CListenSocket()
{
}


// CListenSocket ��� �Լ�


void CListenSocket::OnAccept(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	//���� ���� ���
	CChildSocket* pChild = new CChildSocket;
	BOOL check = Accept(*pChild);
	if (check == FALSE) {
		delete pChild;
		return;
	}
	m_pChildSocketList.AddTail(pChild);
	CString strSocketName; UINT uPort;
	pChild->GetPeerName(strSocketName, uPort);
	CString str;
	str.Format(_T("3 [%s:%u] ���������� �����մϴ� \r\n"), strSocketName, uPort);
	CServerDlg* pMain = (CServerDlg*)AfxGetMainWnd();
	pMain->m_ctrlEdit.ReplaceSel(str);
	pChild->Send(str.GetBuffer(), str.GetLength());

	//LeaderBoard ��������
	CString query;
	query.Format(_T("select * from member order by point desc"));
	int status = mysql_query(&pMain->m_mysql, query);
	MYSQL_RES *result = mysql_store_result(&pMain->m_mysql);
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
		pMain->m_ctrlEdit.ReplaceSel(str);

		temp = str;
		str.Format(_T("%s%s"), temp, _T("\r\n"));
		pChild->Send(str.GetBuffer(), str.GetLength());

	}

	pChild->m_pListenSocket = this;

	CAsyncSocket::OnAccept(nErrorCode);
}


void CListenSocket::Broadcast(CString strMessage)
{
	POSITION pos = m_pChildSocketList.GetHeadPosition();
	while (pos != NULL) {
		CChildSocket* pChild = (CChildSocket*)m_pChildSocketList.GetNext(pos);
		if (pChild != NULL) pChild->Send(strMessage.GetBuffer(), strMessage.GetLength());
	}
}
