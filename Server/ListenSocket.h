#pragma once

// CListenSocket ��� ����Դϴ�.

class CListenSocket : public CAsyncSocket
{
public:
	CListenSocket();
	virtual ~CListenSocket();
	CPtrList m_pChildSocketList;
	virtual void OnAccept(int nErrorCode);
	void Broadcast(CString strMessage);
//	MYSQL m_mysql;
};


