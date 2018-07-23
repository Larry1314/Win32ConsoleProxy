#include "stdafx.h"
#include "ServerNet.h"

ServerNet::ServerNet() {

}

ServerNet::~ServerNet() {

	closesocket(m_sock);
}

int ServerNet::ServerInit(const char* address, int port)
{
	int rlt = 0;
	int iErrorMsg;
		
	WSAData wsaData;
	iErrorMsg = WSAStartup(MAKEWORD(1, 1), &wsaData); //��ʼ��WinSock  

	if (iErrorMsg != NO_ERROR)//��ʼ��WinSockʧ��  
	{
		printf("server wsastartup failed with error : %d\n", iErrorMsg);
		rlt = 1;
		return rlt;
	}
	
	m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // ������������socket  
	if (m_sock == INVALID_SOCKET)// ����socket�������쳣  
	{
		printf("server socket failed with error: %d\n", WSAGetLastError());
		rlt = 2;
		return rlt;
	}

	SOCKADDR_IN servaddr;
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = port;
	servaddr.sin_addr.s_addr = inet_addr(address);
		
	iErrorMsg = bind(m_sock, (SOCKADDR*)&servaddr, sizeof(servaddr)); //��  
	if (iErrorMsg < 0) //��ʧ��  
	{		
		printf("bind failed with error : %d\n", iErrorMsg);
		rlt = 3;
		return rlt;
	}

	iErrorMsg = m_console.CreateChildProcess();
	if ( !iErrorMsg )
	{
		printf("CreateChildProcess Failed.");
	}
	return rlt;
}

DWORD ServerNet::ServerRun()
{	
	CHAR buff[PIPE_BUFSIZE];
	string msg;
	SOCKADDR_IN tcpAddr;
	int len = sizeof(sockaddr);
	SOCKET newSocket;
	int rval = TRUE;
	BOOL bSuccess;
	
	listen(m_sock, 5); // ��ʼ����ָ���˿�
	
	do
	{		
		newSocket = accept(m_sock, (sockaddr*)&tcpAddr, &len);	// ������Ϣ  
		if (newSocket == INVALID_SOCKET)						// �ǿ���socket  
		{
			printf("invalid socket occured.\n");
		}
		else													// ���õ���socket����  
		{			
			printf("new socket connect: %lld\n", newSocket);

						
			do															// ��Ϣ����  
			{			
				rval = recv(newSocket, buff, sizeof(buff), NULL);		// �������� 
				
				if (rval == SOCKET_ERROR)								// ���쳣ͨ��������δcloseSocket���˳�ʱ  
				{
					printf("recv socket error.\n");
					break;
				}

				else if (rval == 0)										// 0��ʾ�����˳�  
				{
					printf("socket %lld connect end.\n", newSocket);
				}
				else													// ��ʾ���յ�������  
				{
					if (!m_console.Write(buff, strlen(buff))) 
					{
						printf("%s:[%d] write failed. \r\n", __FILE__, __LINE__);
					}

					printf("%s", buff);

					if (!m_console.Read(buff, sizeof(buff)))
					{
						printf("%s:[%d] Read failed. \r\n", __FILE__, __LINE__);
					}

					send(newSocket, buff, strlen(buff), NULL);

					printf("%s", buff);
				}
				
			} while (rval != 0);

			closesocket(newSocket); // �رս��յ�socket  
		}
	} while (1);

	// �ر�����socket  
	//closesocket(m_sock);
}
