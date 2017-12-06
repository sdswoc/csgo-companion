#include<iostream>
#include<fstream>
#include<winsock2.h>
using namespace std;
void rungame();
int main()
{
	char server_name[100];
	char msg[1024];
	WSADATA data;
	bool flag=true;
	
	char name[50];
	fstream file;
	file.open("rev",ios::in|ios::binary);
	file.read((char*)&name, sizeof(name));
	file.close();
	
	if(WSAStartup(MAKEWORD(2,2),&data)==0)
	{
		cout<<"Winsock started successfully.."<<endl;   //debug
		cout<<"Enter the name of the server>>";
		cin.getline(server_name,100);
		sockaddr_in servAdr;
		servAdr.sin_family=AF_INET;
		servAdr.sin_addr.S_un.S_addr=INADDR_ANY;
		servAdr.sin_port=htons(1102);
		SOCKET server= socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
		bind(server, (sockaddr*)&servAdr,sizeof(servAdr));
		cout<<"Waiting for connections..."<<endl;
		//listen(server,SOMAXCONN);
		sockaddr_in clientAdr;
		int len=sizeof(clientAdr);
		
		SOCKET client;
		while(flag)
		{
			listen(server,SOMAXCONN);
			client=accept(server,(sockaddr*)&clientAdr,&len);
			recv(client,(char*)&msg,sizeof(msg),0);
			if(!strcmp(msg,"C"))
			{
				send(client,(char*)&server_name,sizeof(server_name),0);
			}
			else if(!strcmp(msg,"J"))
			{
				recv(client,(char*)&msg,sizeof(msg),0);
				cout<<msg<<" joined"<<endl;
				send(client, (char*)&name,sizeof(name),0);
				flag=false;
			}
		}
		cout<<"Starting the game";
		rungame();
		
	}
}
void rungame()
{
	cin.get();
}
