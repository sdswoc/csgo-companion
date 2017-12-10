#include<iostream>
#include<fstream>
#include<winsock2.h>
//#include "..\\headers\\rungame_client.h">
#include "..\\headers\\search_games.h"
#include "..\\headers\\join_lobby.h"
using namespace std;
int main()
{
	char ip[16];
	
	char name[50];
	fstream file;
	file.open("rev",ios::in|ios::binary);
	file.read((char*)&name, sizeof(name));
	file.close();
	
	WSADATA data;
	if(WSAStartup(MAKEWORD(2,2),&data)==0)
	{
		strcpy(ip,search_games());
		join_lobby(ip,name);
	}
	else
	{
		cout<<"Unexpected Error! Please restart the application";
	}
	WSACleanup();
	
}
