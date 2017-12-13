//CS:GO Companion
//Keep 11022 port ready
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
char name[50];
void intro();
void firstTimeSetup();
void change();
void menu();
void fetch_info();
int main()
{
	system("title CS:GO COMPANION");
	system("color 02");
	intro();
	fetch_info();
	menu();
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
void menu()
{
	char ch;
	do{
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
	cin.ignore();
	while(ch>'4'||ch<'1')
	{
		cout<<"Invalid Choice. Enter again>>";
		cin>>ch;	
	}
	system("cls");
	switch(ch)
	{
		case '1': system("cls");system("bin\\host.exe");break;
		case '2': system("cls");system("bin\\join.exe");break;
		case '3': change();break;
		case '4': break;
	}
    } while(ch!='4');
}
void fetch_info()
{
	fstream file;
	file.open("rev",ios::in|ios::binary);
	if(!file){
		firstTimeSetup();
		file.close();
		file.open("rev",ios::in|ios::binary);
	}
	file.read((char*)&name, sizeof(name));		
	file.close();
}
