#include "Xen.h"

/*
Check for process list
*/

BOOL xen_process()
{
	TCHAR *szProcesses[] = {
		_T("xenservice.exe"),
	};

	WORD iLength = sizeof(szProcesses) / sizeof(szProcesses[0]);
	for (int i = 0; i < iLength; i++)
	{
		TCHAR msg[256] = _T("");
		_stprintf_s(msg, sizeof(msg) / sizeof(TCHAR), _T("Checking Citrix Xen process: "), szProcesses[i]);
		if (GetProcessIdFromName(szProcesses[i]))
			return print_results(TRUE, msg);
		else
			return print_results(FALSE, msg);
	}
}
