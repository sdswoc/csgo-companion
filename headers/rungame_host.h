#include<iostream>
#include<fstream>
#include<windows.h>
using namespace std;
void rungame_host()
{
	cout<<"Starting the game"<<endl;
	system("copy ..\\csgo\\cfg\\autoexec.cfg original_autoexec.cfg > dustbin");
	fstream file;
	file.open("..\\csgo\\cfg\\autoexec.cfg",ios::app);
	file<<"\nsv_lan \"1\"";
	file.close();
	file.open("..\\csgo\\cfg\\config.cfg",ios::app);
	file<<"map \"de_dust2\"";
	file.close();
	cout<<"Map is de_dust2\nDont close this window directly after coming back from game."<<endl;
	cout<<"Game is running in  3..";
	Sleep(1000);
	cout<<"2..";
	Sleep(1000);
	cout<<"1..\n";
	Sleep(1000);
	system("start ..\\loader.exe");
	//system("copy original_autoexec.cfg ..\\csgo\\cfg\\autoexec.cfg > dustbin");
	
}
