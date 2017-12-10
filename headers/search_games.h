#include<iostream>
#include<winsock2.h>
using namespace std;
char* search_games()
{
	int idx=0;
	int ch;
	char msg[1024];
	char* active[16];
	SOCKET client= socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	sockaddr_in servAdr;
	servAdr.sin_family=AF_INET;
	servAdr.sin_port=htons(11022);
	cout<<"Select from the following active servers>>"<<endl;	
	int i,j,k;
	char temp[3];
	char ip[16];
	for(i=0;i<256;i++)
	for(j=0;j<256;j++)
	for(k=0;k<256;k++)
	{
		strcpy(ip,"172.");
		itoa(i,temp,10);
		strcat(ip,temp);
		strcat(ip,".");
		itoa(j,temp,10);
		strcat(ip,temp);
		strcat(ip,".");
		itoa(k,temp,10);
		strcat(ip,temp);
		servAdr.sin_addr.S_un.S_addr=inet_addr(ip);
		if(connect(client,(sockaddr*)&servAdr,sizeof(servAdr))==0)
		{
			
			memset(msg,0,sizeof(msg));
			strcpy(msg,"C");											//Send "C" query to fetch server name to display the list of games
			send(client,(char*)&msg,sizeof(msg),0);
			memset(msg,0,sizeof(msg));
			recv(client,(char*)&msg,sizeof(msg),0);
			strcpy(active[idx],ip);
			cout<<(idx++)<<")"<<ip<<" == "<<msg<<endl;
		}
	}
	if(idx)
	{
		cout<<idx<<" games found."<<endl;
		cout<<"Enter the serial number of an active server to join>>";
		cin>>ch;
		return active[ch];
	}
	else
	{
		cout<<"No Availible Games :( \n";
		return NULL;
	}
}
