#include<iostream>
#include<fstream>
#include<windows.h>
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
		servAdr.sin_port=htons(11022);
		SOCKET server= socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
		bind(server, (sockaddr*)&servAdr,sizeof(servAdr));
		cout<<"Waiting for connections..."<<endl;
		listen(server,1);
		sockaddr_in clientAdr;
		int len=sizeof(clientAdr);
		
		SOCKET client;
		while(flag)
		{
			client=accept(server,(sockaddr*)&clientAdr,&len);
			recv(client,(char*)&msg,sizeof(msg),0);
			if(!strcmp(msg,"C"))							//If sent query is "C" then send the server name
			{
				send(client,(char*)&server_name,sizeof(server_name),0);
				closesocket(client);
			}
			else if(!strcmp(msg,"J"))						//If sent query is "J" then connect with the client and run the game
			{
				recv(client,(char*)&msg,sizeof(msg),0);
				cout<<msg<<" joined"<<endl;
				send(client, (char*)&name,sizeof(name),0);
				flag=false;
			}
		}
		cout<<"Starting the game"<<endl;
		rungame();
		
	}
	WSACleanup();
	system("source.exe");
}
void rungame()
{
	system("copy csgo\\cfg\\autoexec.cfg original_autoexec.cfg > dustbin");
	fstream file;
	file.open("csgo\\cfg\\autoexec.cfg",ios::app);
	file<<"sv_lan \"1\"";
	file.close();
	file.open("csgo\\cfg\\config.cfg",ios::app);
	file<<"map \"de_dust2\"";
	file.close();
	cout<<"Map is de_dust2\nDont close this window directly after coming back from game."<<endl;
	cout<<"Game is running in  3..";
	Sleep(1000);
	cout<<"2..";
	Sleep(1000);
	cout<<"1..\n";
	Sleep(1000);
	system("loader.exe");
	system("pause");
	system("copy original_autoexec.cfg csgo\\cfg\\autoexec.cfg > dustbin");
}
