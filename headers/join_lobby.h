#include<iostream>
#include<winsock2.h>
#include "rungame_client.h"
void join_lobby(char ip[16] , char name[50])
{
	if(ip!=NULL){
	
		char msg[1024];
		sockaddr_in servAdr;
		servAdr.sin_family=AF_INET;
		servAdr.sin_port=htons(11022);
		servAdr.sin_addr.S_un.S_addr=inet_addr(ip);
		SOCKET new_client=socket(AF_INET,SOCK_STREAM,IPPROTO_IP);
		SOCKET last_client=socket(AF_INET,SOCK_STREAM,IPPROTO_IP);
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
			rungame_client(ip);
			connect(last_client,(sockaddr*)&servAdr,sizeof(servAdr));
			memset(msg,0,sizeof(msg));
			strcpy(msg,"L");												//Send "J" query to join the specified server
			send(last_client,(char*)&msg,sizeof(msg),0);
			send(last_client,(char*)&name,sizeof(name),0);
			cout<<"You Left."<<endl;
			system("pause");
		}
		else
		{
			cout<<ip<<"== Server Shutdown"<<endl;
		}
	}
}
