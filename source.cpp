#include "stdio.h"
#include "windows.h"
#include "iostream"

using namespace std;
#define IOCTL_MOU_MOV  CTL_CODE(FILE_DEVICE_UNKNOWN, 0x775, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
const WCHAR UserLandPath[] = L"\\\\.\\moumovdriver";

int x = 0;
int y = 0;
unsigned short btn = 0;
int main(int argc, char **argv)
{
	printf("Hi. Welcome to mouse to move test program.\n");
	
	printf("Please input position like <X Y btn>. \n");
	HANDLE h = CreateFile(UserLandPath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (h == INVALID_HANDLE_VALUE) {
		int nn = GetLastError();
		printf("Can not open mouse control.");
		return 0;
	}
	while (1)
	{
		cin >> x >> y >> btn;

		int inputbuff[10];
		int outputbuff[10];
		DWORD dwRead;
		inputbuff[0] = x; inputbuff[1] = y; inputbuff[2] = btn;
		int status = DeviceIoControl(h, IOCTL_MOU_MOV, inputbuff, sizeof(int) * 3, outputbuff, sizeof(int) * 10, &dwRead, 0);
		if (status == FALSE) {
			int nError = GetLastError();
			printf("Error number : %x, Read=%d", nError, dwRead);
			break;
		}
		if (btn == 99)
			break;
	}
	CloseHandle(h);
	return 0;
}

//https://community.osr.com/discussion/12253/named-pipes-in-kernelmode
//https://community.osr.com/discussion/71108/named-pipes-kernel-mode-help-needed-newbie
//https://community.osr.com/discussion/84676/how-to-create-a-named-pipe-in-kernela
//https://www.winvistatips.com/threads/is-it-possible-to-use-named-pipes-in-a-kernel-mode-device-driver.184370/
//https://groups.google.com/g/microsoft.public.win32.programmer.kernel/c/Nh0jnC6XzaI?pli=1
//https://stackoverflow.com/questions/26561604/create-named-pipe-c-windows
//https://groups.google.com/g/microsoft.public.win32.programmer.kernel/c/Nh0jnC6XzaI

//Can communicate by File Operation.
//https://www.unknowncheats.me/forum/c-and-c-/351894-kernel-driver-pid-process-name.html
//https://www.unknowncheats.me/forum/anti-cheat-bypass/489641-pid-kernel.html
//https://stackoverflow.com/questions/50654093/can-kernel-mode-driver-do-readprocessmemory-on-any-process
/*NTSTATUS
MmCopyVirtualMemory(
  IN  PEPROCESS FromProcess,
  IN  CONST VOID *FromAddress,
  IN  PEPROCESS ToProcess,
  OUT PVOID ToAddress,
  IN  SIZE_T BufferSize,
  IN  KPROCESSOR_MODE PreviousMode,
  OUT PSIZE_T NumberOfBytesCopied
  );*/
//https://github.com/AYIDouble/Kernel-Memory-Reading-Writing
//MmCopyVirtualMemory examplc
//https://github.com/Zer0Mem0ry/KernelReadWriteMemory/blob/master/ReadWrite.c
//https://github.com/340211173/hf-2011/tree/master/Technology/rookit/sys
//https://github.com/BuddyBoi/KernelMoveMouse/blob/master/kernelMoveMouse/includes.hpp