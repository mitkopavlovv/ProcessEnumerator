#include<stdio.h>
#include<Windows.h>	
#include<psapi.h>
#include<tchar.h>
#include<WtsApi32.h>

#pragma comment(lib, "Wtsapi32.lib")

void ListProcesses() {
	int pid = 0;
	WTS_PROCESS_INFOA* procInfo;
	DWORD procCount;

	if (!WTSEnumerateProcessesA(WTS_CURRENT_SERVER_HANDLE, 0, 1, &procInfo, &procCount)) {
		printf("[!] Problem with WTSEnumerateProcessesA function procname searched -> error num %i\n", GetLastError);
	}

	for (int i = 0; i < procCount; i++) {
		printf("[-->]PID: %lu (Name %s)\n", procInfo[i].ProcessId, procInfo[i].pProcessName);
	}
}

int FindProcess(char* procname) {
	int pid = 0;
	WTS_PROCESS_INFOA* procInfo;
	DWORD procCount;

	if (!WTSEnumerateProcessesA(WTS_CURRENT_SERVER_HANDLE, 0, 1, &procInfo, &procCount)) {
		printf("[!] Problem with WTSEnumerateProcessesA function procname searched -> error num %i\n", GetLastError);
		return -1;
	}

	for (int i = 0; i < procCount; i++) {
		if (lstrcmpiA(procname, procInfo[i].pProcessName) == 0) {
			printf("[*] Found PID %lu with name %s\n", procInfo[i].ProcessId, procInfo[i].pProcessName);
			return pid;
		}
	}
	printf("[*] No PID found with name %s\n", procname);
	return 0;
}


int main(int argc, char* argv[]) {
	//ListProcesses();
	FindProcess((char*)"lsass.exe");
	return 0;
}