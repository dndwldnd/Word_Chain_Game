// ClientSocket.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "WordChainGame.h"
#include "ClientSocket.h"
#include "WordChainGameDlg.h"
#include "InGameDlg.h"

// CClientSocket

CClientSocket::CClientSocket()
{
	m_turn = _T("");
	m_ID = _T("");
	m_MyScore = _T("");
	m_OtherScore = _T("");
	m_itime = 0;
	m_MyLastInput = _T("");
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket ��� �Լ�


void CClientSocket::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	this->ShutDown();
	this->Close();
	AfxMessageBox(_T("������ ������ �����Ͽ����ϴ�"));
	::PostQuitMessage(0);
	CSocket::OnClose(nErrorCode);
}


void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	TCHAR szBuff[1024];
	int nRead = Receive(szBuff, sizeof(szBuff));
	switch (nRead) {
	case 0: this->Close(); break;
	case SOCKET_ERROR: if (GetLastError() != WSAEWOULDBLOCK) {
		AfxMessageBox(_T("Error occured"));
		this->Close();
	}break;
	default: 
		szBuff[nRead] = _T('\0');
		CWordChainGameDlg* pMain = (CWordChainGameDlg*)AfxGetMainWnd();

		if (szBuff[0] == '0') {	//ȸ������
			CString name;
			CString msg;
			AfxExtractSubString(name, szBuff, 1, ' ');
			msg.Format(_T("%s ���� ȸ������ �ϼ̽��ϴ�\r\n"), name);
			pMain->m_ctrlEdit.ReplaceSel(msg);

			if (pMain->m_strID == name) {	//���� ȸ������
				m_ID = pMain->m_strID;
				pMain->m_strID = _T("");
				pMain->m_strPASSWORD = _T("");
				pMain->UpdateData(FALSE);
				CString text;
				text.Format(_T("%s �� �ȳ��ϼ���!!"), name);
				pMain->SetDlgItemText(IDC_STATIC11, text);
				//��Ȱ��ȭ �� Ȱ��ȭ
				pMain->GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);
				pMain->GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
				pMain->GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
				pMain->GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
				pMain->GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
			}
		}
		else if (szBuff[0] == '1') {	//�α���
			CString name;
			CString msg;
			AfxExtractSubString(name, szBuff, 1, ' ');
			msg.Format(_T("%s ���� �α��� �ϼ̽��ϴ�\r\n"), name);
			pMain->m_ctrlEdit.ReplaceSel(msg);

			if (pMain->m_strID == name) {	//���� �α���
				m_ID = pMain->m_strID;
				pMain->m_strID = _T("");
				pMain->m_strPASSWORD = _T("");
				pMain->UpdateData(FALSE);
				CString text;
				text.Format(_T("%s �� �ȳ��ϼ���!!"), name);
				pMain->SetDlgItemText(IDC_STATIC11, text);
				//��Ȱ��ȭ �� Ȱ��ȭ
				pMain->GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);
				pMain->GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
				pMain->GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
				pMain->GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
				pMain->GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);

			}
		}
		else if(szBuff[0] == '2'){	//�غ� ���� �޽���
			CString name;
			CString ready;
			CString msg;
			AfxExtractSubString(name, szBuff, 1, ' ');
			AfxExtractSubString(ready, szBuff, 2, ' ');
			if (ready == 'y') {
				msg.Format(_T("%s ���� �غ� �Ͽ����ϴ� \r\n"), name);
			}
			else {
				msg.Format(_T("%s ���� �غ���� �Ͽ����ϴ� \r\n"), name);
			}
			pMain->m_ctrlEdit.ReplaceSel(msg);
		}
		else if (szBuff[0] == '3') {	//���� ���� ���
			CString str1;
			CString str2;
			CString str3;
			CString msg;
			AfxExtractSubString(str1, szBuff, 1, ' ');
			AfxExtractSubString(str2, szBuff, 2, ' ');
			AfxExtractSubString(str3, szBuff, 3, ' ');
			msg.Format(_T("%s %s %s \r\n"), str1, str2, str3);
			pMain->m_ctrlEdit.ReplaceSel(msg);
			//EditControl ��Ȱ�� �� Ȱ��ȭ
			pMain->GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
			pMain->GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
			pMain->GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
			pMain->GetDlgItem(IDC_EDIT4)->EnableWindow(TRUE);
			pMain->GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
			pMain->GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
			pMain->GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);

		}
		else if (szBuff[0] == '4') {	//LeaderBoard ���
			CString name, score;
			CString msg;
			pMain->SetDlgItemTextA(IDC_EDIT6, _T(""));
			for (int i = 0; i < 10; i+=2) {
				AfxExtractSubString(name, szBuff, i+1, ' ');
				AfxExtractSubString(score, szBuff, i+2, ' ');
				msg.Format(_T("%s\t\t%s \r\n"), name, score);
				pMain->m_ctrlLeaderBoard.ReplaceSel(msg);
			}

		}
		else if (szBuff[0] == '5') {	//���� or �����
			CString turn, time;
			CString name1, name2;
			CString timeout, start;
			CString total_time;
			int itotal_time;
			int istart;
			int itimeout;
			AfxExtractSubString(turn, szBuff, 1, ' ');
			AfxExtractSubString(time, szBuff, 2, ' ');
			AfxExtractSubString(name1, szBuff, 3, ' ');
			AfxExtractSubString(name2, szBuff, 5, ' ');
			AfxExtractSubString(timeout, szBuff, 7, ' ');
			AfxExtractSubString(start, szBuff, 8, ' ');

			istart = _ttoi(start);
			m_itime = _ttoi(time);
			itimeout = _ttoi(timeout);
			
			if (istart == 1) {	//���� ���� �϶�
				itimeout = _ttoi(timeout);
				AfxExtractSubString(total_time, szBuff, 9, ' ');
				itotal_time = _ttoi(total_time);
				pMain->m_totaltimecount = itotal_time / 1000;
				pMain->SetTimer(3, 1000, NULL);	//1�ʹٴ� ����
			}


			
			//total timer �� ���� Ÿ�̸� �ð� �� �� ������ ���ϱ�
			if (m_itime/1000 > pMain->m_totaltimecount) {
				pMain->m_cnt = pMain->m_totaltimecount;
			}
			else {
				pMain->m_cnt = m_itime / 1000;
			}
			

			if (name1 == m_ID) {
				AfxExtractSubString(m_MyScore, szBuff, 4, ' ');
				pMain->SetDlgItemText(IDC_STATIC15, m_MyScore);
				AfxExtractSubString(m_OtherScore, szBuff, 6, ' ');
				pMain->SetDlgItemText(IDC_STATIC14, m_OtherScore);
			}
			else {
				AfxExtractSubString(m_MyScore, szBuff, 6, ' ');
				pMain->SetDlgItemText(IDC_STATIC15, m_MyScore);
				AfxExtractSubString(m_OtherScore, szBuff, 4, ' ');
				pMain->SetDlgItemText(IDC_STATIC14, m_OtherScore);

			}
			
			m_turn = turn;
			
			CString text;
			CString msg;

			if (m_turn == m_ID) {	//����
				if (itimeout == 1) {	//Ÿ�Ӿƿ��� ���� �� ������ �� ���� �� ���ڸ� �̾�� �Ѵ�
					pMain->SetDlgItemText(IDC_EDIT9, m_MyLastInput);	//���� ���������� �Է��� ���ڸ� �־��ش�
					msg.Format(_T("��밡 �Է����� ���Ͽ����ϴ� \r\n"));
					pMain->m_ctrlArchive.ReplaceSel(msg);
				}
				pMain->GetDlgItem(IDOK)->EnableWindow(TRUE);
				pMain->GetDlgItem(IDC_EDIT8)->EnableWindow(TRUE);
				text.Format(_T("���� �Դϴ�!!"));
				pMain->SetDlgItemText(IDC_STATIC18, text);
				pMain->KillTimer(2);

				pMain->SetTimer(1, 1000, NULL);	//1�ʸ���

			}
			else {	//�����
				pMain->GetDlgItem(IDOK)->EnableWindow(FALSE);
				text.Format(_T("����� �Դϴ�!!"));
				pMain->SetDlgItemText(IDC_STATIC18, text);
				pMain->KillTimer(1);

				pMain->SetTimer(2, 1000, NULL);	//1�ʸ���

			}
			
		}
		else if (szBuff[0] == '6') {	//�ܾ� ����
			pMain->UpdateData(TRUE);
			CString word, correct, msg;
			AfxExtractSubString(word, szBuff, 1, ' ');
			AfxExtractSubString(correct, szBuff, 2, ' ');

			if (m_turn == m_ID) {	//����
				
				if (correct == '1') {	//�ùٸ� �ܾ�
					m_MyLastInput.Format(word);
					pMain->SetDlgItemText(IDC_EDIT9, _T(""));
					msg.Format(_T("��: %s \r\n"), word);
					pMain->m_ctrlArchive.ReplaceSel(msg);

				}
				else {	//Ʋ�� �ܾ�
					pMain->GetDlgItem(IDC_EDIT8)->EnableWindow(TRUE);
					pMain->SetDlgItemText(IDC_EDIT8, _T(""));
					msg.Format(_T("��: Ʋ���ܾ� �Է�! \r\n"));
					pMain->m_ctrlArchive.ReplaceSel(msg);
					pMain->GetDlgItem(IDOK)->EnableWindow(TRUE);
				}
			}
			else {	//�����
				pMain->SetDlgItemText(IDC_EDIT9, word);
				if (correct == '1') {	//�ùٸ� �ܾ�
					msg.Format(_T("���: %s \r\n"), word);
					pMain->m_ctrlArchive.ReplaceSel(msg);
	

				}
				else {	//Ʋ�� �ܾ�
					msg.Format(_T("���: Ʋ���ܾ� �Է�! \r\n"));
					pMain->m_ctrlArchive.ReplaceSel(msg);
				}
			}
			pMain->UpdateData(FALSE);
		}
		else if (szBuff[0] == '7') {	//���� ����
			//Ÿ�̸� ����
			pMain->KillTimer(1);
			pMain -> KillTimer(2);

			CString name1, name2, winner;

			AfxExtractSubString(name1, szBuff, 1, ' ');
			AfxExtractSubString(name2, szBuff, 3, ' ');
			AfxExtractSubString(winner, szBuff, 5, ' ');

			if (name1 == m_ID) {
				AfxExtractSubString(m_MyScore, szBuff, 2, ' ');
				AfxExtractSubString(m_OtherScore, szBuff, 4, ' ');
			}
			else {
				AfxExtractSubString(m_MyScore, szBuff, 4, ' ');
				AfxExtractSubString(m_OtherScore, szBuff, 2, ' ');
			}

			//���̾�α� �ʱ�ȭ
			pMain->GetDlgItem(IDOK)->EnableWindow(FALSE);

			pMain->SetDlgItemText(IDC_EDIT7, _T(""));
			pMain->SetDlgItemText(IDC_EDIT8, _T(""));
			pMain->SetDlgItemText(IDC_EDIT9, _T(""));

			pMain->SetDlgItemTextA(IDC_STATIC14, _T("0"));
			pMain->SetDlgItemTextA(IDC_STATIC15, _T("0"));
			pMain->SetDlgItemTextA(IDC_STATIC18, _T("��ٸ�����!"));
			pMain->SetDlgItemTextA(IDC_STATIC19, _T("0"));
			pMain->SetDlgItemTextA(IDC_STATIC20, _T("0"));

			pMain->GetDlgItem(IDC_EDIT7)->EnableWindow(FALSE);
			pMain->GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
			pMain->GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);

			//�غ� Ȱ��ȭ
			pMain->GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
			
			//��� ���
			CString msg, temp;
			if (winner == m_ID) {
				temp.Format(_T("�¸��ϼ̽��ϴ�! "));
			}
			else {
				temp.Format(_T("�й��ϼ̽��ϴ�! "));
			}
			msg.Format(_T(" %s \n ����: %s \n �� ����: %s \n ��� ����: %s"), temp, winner, m_MyScore, m_OtherScore);

			AfxMessageBox(msg);
			pMain->GetDlgItem(IDOK)->EnableWindow(FALSE);
			pMain->UpdateData(FALSE);

		}

		else {	//���� ����

			//â Ȱ��ȭ
			pMain->GetDlgItem(IDC_EDIT7)->EnableWindow(TRUE);
			
			pMain->GetDlgItem(IDC_EDIT9)->EnableWindow(TRUE);
			

			//�غ� ��Ȱ��ȭ
			pMain->SetDlgItemText(IDC_BUTTON4, _T("�غ�"));
			pMain->GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);

			
		}
	}
	CSocket::OnReceive(nErrorCode);
}
