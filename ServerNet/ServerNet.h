#pragma once

#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include <stdio.h> 
#include <strsafe.h>
#include <iostream>
#include <string>
#include "Console.h"
#pragma comment(lib, "Ws2_32.lib")
#define SOCKET_BUFSIZE 4096
#define PIPE_BUFSIZE 4096
using namespace std;
class ServerNet
{

public:
	ServerNet();
	~ServerNet();
	//  ��ʼ��������
	int ServerInit(const char* address, int port);

	// ��������
	DWORD ServerRun();

private:
	SOCKET m_sock;
	Console m_console;
};