#include<iostream>
#include<fstream>
#include<winsock2.h>
#include "..\\headers\\lobby.h"
using namespace std;
static BOOL WINAPI console_ctrl_handler(DWORD dwCtrlType)
{
  system("copy original_autoexec.cfg ..\\csgo\\cfg\\autoexec.cfg > dustbin");
  return TRUE;
}
int main()
{
	SetConsoleCtrlHandler(console_ctrl_handler, TRUE);	
	WSADATA data;
	
	char name[50];
	fstream file;
	file.open("rev",ios::in|ios::binary);
	file.read((char*)&name, sizeof(name));
	file.close();
	
	if(WSAStartup(MAKEWORD(2,2),&data)==0)
	{
		lobby(name);	
	}
	else
	{
		cout<<"Unexpected Error! Please restart the application";
	}
	WSACleanup();
}
