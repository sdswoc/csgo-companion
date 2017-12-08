#include<iostream>
#include<fstream>
#include<winsock2.h>
using namespace std;
char ip[][16]={"127.0.0.1","192.168.1.136"};			//Contains all possible ips in lan
int ipn=2;												//No of ips
void rungame(int);
int main()
{
	int ch;
	char msg[1024];
	char name[50];
	fstream file;
	file.open("rev",ios::in|ios::binary);
	file.read((char*)&name, sizeof(name));
	file.close();
	
	WSADATA data;
	if(WSAStartup(MAKEWORD(2,2),&data)==0)
	{
		cout<<"Winsock started succesfully..."<<endl;   //debug
		SOCKET client= socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
		sockaddr_in servAdr;
		servAdr.sin_family=AF_INET;
		//servAdr.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
		servAdr.sin_port=htons(11022);
		cout<<"Select from the following active servers>>"<<endl;
		for(int i=0;i<ipn;i++)
		{
			servAdr.sin_addr.S_un.S_addr=inet_addr(ip[i]);
			if(connect(client,(sockaddr*)&servAdr,sizeof(servAdr))==0)
			{
				memset(msg,0,sizeof(msg));
				strcpy(msg,"C");											//Send "C" query to fetch server name to display the list of games
				send(client,(char*)&msg,sizeof(msg),0);
				memset(msg,0,sizeof(msg));
				recv(client,(char*)&msg,sizeof(msg),0);
				cout<<i<<")"<<ip[i]<<" == "<<msg<<endl;
			}
			else
			{
				cout<<i<<")"<<ip[i]<<" == (inactive)"<<endl;
			}
		}
		cout<<"Enter the serial number of an active server to join>>";
		cin>>ch;
		servAdr.sin_addr.S_un.S_addr=inet_addr(ip[ch]);
		SOCKET new_client=socket(AF_INET,SOCK_STREAM,IPPROTO_IP);
		if(connect(new_client,(sockaddr*)&servAdr,sizeof(servAdr))==0)
		{
			memset(msg,0,sizeof(msg));
			strcpy(msg,"J");												//Send "J" query to join the specified server
			send(new_client,(char*)&msg,sizeof(msg),0);
			memset(msg,0,sizeof(msg));
			send(new_client,(char*)&name,sizeof(name),0);
			recv(new_client,(char*)&msg,sizeof(msg),0);
			cout<<msg<<" is the admin"<<endl;
			cout<<"Game is going to run";
			rungame(ch);
		}
		else
		{
			cout<<ip[ch]<<"== Server Shutdown"<<endl;
		}
	}
	WSACleanup();
	system("source.exe");
	
}
void rungame(int ch)
{
	fstream file;
	file.open("csgo\\cfg\\config.cfg",ios::app);
	file<<"connect \""<<ip[ch]<<":27015\"";
	file.close();
	cout<<"Game is running in  3..";
	Sleep(1000);
	cout<<"2..";
	Sleep(1000);
	cout<<"1..\n";
	Sleep(1000);
	system("loader.exe");
	system("pause");
}
