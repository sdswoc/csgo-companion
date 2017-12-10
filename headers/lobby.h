#include<iostream>
#include<winsock2.h>
using namespace std;
void lobby(char name[50])
{
		char server_name[100];
		char msg[1024];
		bool flag=true;
	
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
}
