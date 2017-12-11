#include<iostream>
#include<winsock2.h>
#include "rungame_host.h"
using namespace std;
void lobby(char name[50])
{
		char server_name[100];
		char msg[1024];
		int i=1;
	
		cout<<"Enter the name of the server>>";
		cin.getline(server_name,100);
		rungame_host();
		sockaddr_in servAdr;
		servAdr.sin_family=AF_INET;
		servAdr.sin_addr.S_un.S_addr=INADDR_ANY;
		servAdr.sin_port=htons(11022);
		SOCKET server= socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
		bind(server, (sockaddr*)&servAdr,sizeof(servAdr));
		cout<<"Waiting for connections..."<<endl;
		listen(server,5);
		sockaddr_in clientAdr;
		int len=sizeof(clientAdr);
		
		SOCKET client;
		while(1)
		{
			client=accept(server,(sockaddr*)&clientAdr,&len);
			recv(client,(char*)&msg,sizeof(msg),0);
			if(!strcmp(msg,"C"))							//If sent query is "C" then send the server name
			{
				strcpy(msg,server_name);
				if(i==32)
					strcat(msg,"(SERVER FULL)");
				send(client,(char*)&msg,sizeof(msg),0);
				closesocket(client);
			}
			else if(!strcmp(msg,"J"))						//If sent query is "J" then connect with the client and run the game
			{
				recv(client,(char*)&msg,sizeof(msg),0);
				cout<<msg<<" joined"<<endl;
				send(client, (char*)&name,sizeof(name),0);
				i++;
			}
			else if(!strcmp(msg,"L"))
			{
				recv(client,(char*)&msg,sizeof(msg),0);
				cout<<msg<<" left"<<endl;
				i--;
			}
		}
}
