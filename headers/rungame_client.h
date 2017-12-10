#include<iostream>
#include<fstream>
#include<windows.h>
using namespace std;
void rungame_client( char x[16] )
{
	fstream file;
	file.open("..\\..\\csgo\\cfg\\config.cfg",ios::app);
	file<<"connect \""<<x<<":27015\"";
	file.close();
	cout<<"Game is running in  3..";
	Sleep(1000);
	cout<<"2..";
	Sleep(1000);
	cout<<"1..\n";
	Sleep(1000);
	system("..\\..\\loader.exe");
	system("pause");
}
