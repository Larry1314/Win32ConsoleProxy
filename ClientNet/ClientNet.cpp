#include "stdafx.h"
#include "ClientNet.h"

ClientNet::ClientNet()
{
}


ClientNet::~ClientNet()
{
}

/*�ͻ���Socket����*/
int ClientNet::ClientConnect(const char* address, int port)
{
	int rlt = 0;   //connectflag  0-success 1-WSAStartfailed 2-socketfailed 3-connectfailed

	// ��¼������Ϣ
	int iErrMsg;
	// ����WinSock
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(1, 1);
	iErrMsg = WSAStartup(wVersionRequested, &wsaData);
	if (iErrMsg != NO_ERROR) // WSAStartup�����˴���
	{
		printf("failed with WSAStartup error: %d\n", iErrMsg);
		rlt = 1;
		return rlt;
	}

	// ����Socket
	m_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (m_sock == INVALID_SOCKET) // socket�����˴���
	{
		printf("failed with socket error: %d\n", WSAGetLastError());
		rlt = 2;
		return rlt;
	}


	// Ŀ�����������
	SOCKADDR_IN servaddr;
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = port;
	servaddr.sin_addr.s_addr = inet_addr(address);

	// sock��Ŀ�����������
	iErrMsg = connect(m_sock, (SOCKADDR*)&servaddr, sizeof(servaddr));
	if (iErrMsg != NO_ERROR)
	{
		printf("failed with connect error: %d\n", iErrMsg);
		rlt = 3;
		return rlt;
	}

	// success
	return rlt;

}

/*�ͻ��˷�����Ϣ*/
int ClientNet::ClientSend(const char* msg, int len)
{
	int rlt = 0;

	int iErrMsg = 0;
	int bufSize = len + 3 + 2; // ���з�+�س���+NULL�ַ�
	char * buf = (char *)malloc(bufSize);
		
	ZeroMemory(buf, bufSize);
	// windows�����Ի��Żس�����
	sprintf_s(buf, bufSize, "%s\r\n", msg);
	
	// ָ��sock������Ϣ
	iErrMsg = send(m_sock, buf, bufSize, 0);
	if (iErrMsg < 0)// ����ʧ��
	{
		printf("send msg failed with error: %d\n", iErrMsg);
		rlt = 1;
	}
	else
	{
		//printf("send msg successfully\n");
		//
	}
	
	free(buf);
	
	return rlt;
}
int ClientNet::ClientRecv(PCHAR msg)
{
	int rlt = 0;

	int iErrMsg = 0;

	// ָ��sock������Ϣ
	iErrMsg = recv(m_sock, msg, BUF_SIZE, 0);
	if (iErrMsg < 0)// ����ʧ��
	{
		printf("recv msg failed with error: %d\n", iErrMsg);
		rlt = 1;
		return rlt;
	}
	//printf("recv msg successfully\n");
	return rlt;
}

/*�ͻ��˹ر�Socket*/
void ClientNet::ClientClose()
{
	closesocket(m_sock);
}