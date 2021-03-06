#include "VirtualPC.h"

/*
Check for process list
*/

BOOL virtual_pc_process()
{
	TCHAR *szProcesses[] = {
		_T("VMSrvc.exe"),
		_T("VMUSrvc.exe"),
	};

	WORD iLength = sizeof(szProcesses) / sizeof(szProcesses[0]);
	for (int i = 0; i < iLength; i++)
	{
		TCHAR msg[256] = _T("");
		_stprintf_s(msg, sizeof(msg) / sizeof(TCHAR), _T("Checking Virtual PC processes %s: "), szProcesses[i]);
		if (GetProcessIdFromName(szProcesses[i]))
			return print_results(TRUE, msg);
		else
			return print_results(FALSE, msg);
	}
}