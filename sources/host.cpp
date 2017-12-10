#include<iostream>
#include<fstream>
#include<winsock2.h>
#include "..\\headers\\rungame_host.h"
#include "..\\headers\\lobby.h"
using namespace std;
int main()
{
	
	WSADATA data;
	
	char name[50];
	fstream file;
	file.open("rev",ios::in|ios::binary);
	file.read((char*)&name, sizeof(name));
	file.close();
	
	if(WSAStartup(MAKEWORD(2,2),&data)==0)
	{
		lobby(name);
		rungame_host();
		
	}
	else
	{
		cout<<"Unexpected Error! Please restart the application";
	}
	WSACleanup();
}
