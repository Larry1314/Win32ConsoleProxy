#pragma once
#include<stdio.h>
#include<windows.h>
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")
#define BUF_SIZE 4096
class ClientNet
{
public:
	ClientNet();
	~ClientNet();

	// ����ָ���ķ�����
	int ClientConnect(const char* address, int port);
	// ������Ϣ
	int ClientSend(const char* msg, int len);
	// ������Ϣ
	int ClientRecv(PCHAR msg);
	// �ر�����
	void ClientClose();

private:
	SOCKET m_sock;
	
};

