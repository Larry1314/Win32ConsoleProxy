// ConsoleProxy.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Console.h"
#define MAX_BUFFER_SIZE 4096
int main()
{
	Console cmdConsole;
	if (cmdConsole.CreateChildProcess())
	{
		DWORD dw;
		string msg;
		CHAR buff[MAX_BUFFER_SIZE];
		while (TRUE) 
		{
			getline(cin, msg);
			if (msg == "exit" || msg == "EXIT")
			{
				break;
			}
			//printf("%s\r\n", msg.c_str());
			if ( !cmdConsole.Write(msg.c_str(), msg.length()) ) 
			{
				printf("%s:[%d] write failed. \r\n", __FILE__, __LINE__);
				dw = GetLastError();
				printf("GetLastError-->%u\n", GetLastError());
				ExitProcess(dw);				
			}

			if ( !cmdConsole.Read(buff, sizeof(buff)) ) 
			{
				printf("%s:[%d] write failed. \r\n", __FILE__, __LINE__);
				dw = GetLastError();
				printf("GetLastError-->%u\n", dw);
				ExitProcess(dw);
			}
			printf("%s", buff);
		}
	}
	system("pause");
    return 0;
}

