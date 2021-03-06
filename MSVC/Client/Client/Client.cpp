// SocketClient.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "ClientNet.h"

#define HOST "127.0.0.1"
#define PORT 15000

using namespace std;

int main()
{
	WORD wdResult;
	CHAR pBuf[BUF_SIZE];
	ClientNet client;
	string msg;
	//memset(msg, 0, sizeof(msg));

	//连接到127.0.0.1（即本地）,端口号为8888的服务端
	printf("connecting.....\n");
	wdResult = client.ClientConnect(HOST, PORT);

	if (wdResult == 0) // socket连接成功
	{
		//发送消息
		printf("	connect successfully. input 'exit' to quit\n");
		printf("----------------------------------------------\n");
		while (1)
		{
			//printf("msg input: ");
			getline(cin, msg);
			//cout << msg << endl;
			if (msg == "exit" || msg == "EXIT")
			{
				break;
			}
			else
			{
				wdResult = client.ClientSend(msg.c_str(), msg.length());
				
				wdResult = client.ClientRecv(pBuf, sizeof(pBuf));
				printf("%s", pBuf);
			}

		}


		// 关闭socket
		printf("closing socket.....\n");
		client.ClientClose();


	}

	system("pause");

	return 0;

}
