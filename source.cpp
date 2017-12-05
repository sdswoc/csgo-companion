//CS:GO Companion
//Keep 1102 port ready
#include<iostream>
#include<fstream>
#include<string>
#include<winsock2.h>
#include<thread>
using namespace std;
char name[50];
char path[10000];
void intro();
void firstTimeSetup();
void change();
class host
{
	public:
	SOCKET listener;
	SOCKET client[32];
	char client_name[32][50];
	sockaddr_in servAdr;
	int gametype;
	char sname[50];
	char password[50];
	int i;
	host()
	{
		i=1;
		cout<<"##########################################################################################################"<<endl;
		cout<<"Enter the server's name>>";
		cin.getline(sname,50);
		cout<<"Enter the type of game you want to play>>"<<endl;
		cout<<"1. Classic Casual"<<endl;
		cout<<"2. Classic Competetive"<<endl;
		cout<<"3. Arms Race"<<endl;
		cout<<"4. Demolition"<<endl;
		cout<<"5. Deathmatch"<<endl;
		cout<<"Enter choice>>";
		cin>>gametype;
		cout<<"Enter the password for your server>>";
		cin.getline(password,50);
		servAdr.sin_family=AF_INET;
		servAdr.sin_addr.S_un.S_addr=INADDR_ANY;
		servAdr.sin_port=htons(1102);
		listener=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
		bind(listener, (sockaddr*)&servAdr,sizeof(servAdr));
		listen(listener,SOMAXCONN);
		cout<<"Waiting for clients....(Press enter to start the game at any time)";
		thread t1(&host::ac,0);
		cin.get();
		notify();//Send all clients msg that game is about to run by sending "R" 
		rungame();//run the game
		//TODO:close everything
	}
	void ac(int x)
	{
		char msg[5];
		while(i<32)
		{
			SOCKET temp =accept(listener,NULL, NULL);
			recv(temp,(char*)&msg,sizeof(msg),0);
			if(!strcmp(msg,"C"))		//recieved when client searcher for game
			{
				send(temp,(char*)&sname,sizeof(sname),0);
				send(temp,(char*)&i,sizeof(i),0);
				send(temp,(char*)&gametype,sizeof(gametype),0);
			}
			else if(!strcmp(msg,"J"))
			{
				client[i]=temp;
				//TODO:recieve clients name
				cout<<client_name[i]<<" joined!!"<<endl;
				//TODO:send number of clients
				i++;
				//TODO:Send names of all clients
				//TODO:Tell all clients that new client has joined 
			}
			
		}
	}
	void notify()
	{
		
	}
	void rungame()
	{
		
	}
};
class join
{
	public:
	join()
	{
		cout<<"##########################################################################################################"<<endl;
		cout<<"Select from the following ongoing games:"<<endl;
		//TODO: connect with all posible games found. For each game connected, send "C" as buffer to gain info from server. Store info of all servers in a array
		cout<<"Select the game to connect>>";
		cin>>ch;
		//TODO:connect to given choice
		//TODO:Send "J" as a buffer to tell server that you are joining.
		//TODO:Recieve all names of all other clients and print them
		//TODO:Recieve any further names of clients joined until "R" is sent
		//TODO:Run the game
		//TODO:Close everything and exit
	}
};
int main()
{
	char ch;
	fstream file;
	file.open("rev",ios::in|ios::binary);
	intro();
	WSAStartup(MAKEWORD(2,0),NULL);
	if(!file){
		firstTimeSetup();
		file.close();
		file.open("rev",ios::in|ios::binary);
	}
	file.read((char*)&name, sizeof(name));		
	
	cout<<"##########################################################################################################"<<endl;
	cout<<"                                       CS:GO COMPANION                                                    "<<endl;
	cout<<"##########################################################################################################"<<endl<<endl<<endl;
	cout<<"                                  Welcome "<<name<<"! Choose an option-"<<endl;
	cout<<"                                       1. Host                                                            "<<endl;
	cout<<"                                       2. Join                                                            "<<endl;
	cout<<"                                       3. Change Name"<<endl;
	cout<<"                                       4. Exit"<<endl;
	cout<<"Choice>>";
	cin>>ch;
	while(ch>'4'||ch<'1')
	{
		cout<<"Invalid Choice. Enter again>>";
		cin>>ch;	
	}
	system("cls");	
	switch(ch)
	{
		case '1': host g1();break;
		case '2': /*join g2();*/break;
		case '3': change();break;
		case '4': break;
	}
	WSACleanup();
	
}
void firstTimeSetup()
{
	cout<<"##########################################################################################################"<<endl;
	cout<<"##########################################################################################################"<<endl;
	cout<<"Welcome to CS:GO Companion app!"<<endl;
	cout<<"This must be your first time in this app."<<endl;
	cout<<"Please enter your username(Please keep it unique)>>";
	cin.getline(name,50);
	fstream file("rev",ios::out|ios::binary);
	file.write((char*)&name,sizeof(name));
	cout<<"Thank you! ";
	file.close();
	cin.get();
	system("cls");
}
void intro()
{
	cout<<"##########################################################################################################"<<endl;
	cout<<"##########################################################################################################"<<endl;
	cout<<endl<<endl<<endl<<endl<<endl;
	cout<<"                                        CS:GO Companion App!"<<endl;
	cout<<endl<<endl<<endl<<endl<<endl;
	system("pause");
	system("cls");
}
void change()
{
	cout<<"##########################################################################################################"<<endl;
	cout<<"Please enter your new username(Please keep it unique)>>";
	cin.getline(name,50);
	fstream file("rev",ios::out|ios::binary);
	file.write((char*)&name,sizeof(name));
	file.close();
	system("cls");
}
