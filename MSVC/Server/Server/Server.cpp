// Server.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>  
#include <winsock2.h> // 必须包含windwos.h之前
#include <Windows.h>
#include "ServerNet.h"

#pragma comment(lib,"ws2_32.lib") 
#define HOST "127.0.0.1"
#define PORT 15000

int main(int argc, char * argv[])
{
	ServerNet serverNet;
	int iRlt = serverNet.ServerInit(HOST, PORT);
	if (iRlt == 0)
	{
		printf("servr init successful.\n");
		serverNet.ServerRun();
	}
	else
	{
		printf("server init failed with error: %d\n", iRlt);
	}

	system("pause");

}
