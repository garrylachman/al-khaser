#include "dll_main.h"
#include "Shared\Main.h"
#include <algorithm>
#include <functional>

namespace AlKhaser
{
	Detector *Detector::m_self = nullptr;

	bool Detector::Check()
	{
		if (m_self == nullptr)
		{
			m_self = new Detector();
		}
		return m_self->RunCheck(m_self->checkers_AntiDebug);
	}

	Detector::Detector()
	{
		checkers_AntiDebug.assign({
			&IsDebuggerPresentAPI,
			&IsDebuggerPresentPEB,
			&CheckRemoteDebuggerPresentAPI,
			&NtGlobalFlag,
			&HeapFlags,
			&HeapForceFlags,
			&NtQueryInformationProcess_ProcessDebugPort,
			&NtQueryInformationProcess_ProcessDebugFlags,
			&NtQueryInformationProcess_ProcessDebugObject,
			&NtSetInformationThread_ThreadHideFromDebugger,
			&CloseHandle_InvalideHandle,
			&UnhandledExcepFilterTest,
			&OutputDebugStringAPI,
			&HardwareBreakpoints,
			&SoftwareBreakpoints,
			&Interrupt_0x2d,
			&Interrupt_3,
			&MemoryBreakpoints_PageGuard,
			&IsParentExplorerExe,
			&CanOpenCsrss,
			&NtQueryObject_ObjectTypeInformation,
			&NtQueryObject_ObjectAllTypesInformation,
			&NtYieldExecutionAPI,
			&SetHandleInformatiom_ProtectedHandle,
			&NtQuerySystemInformation_SystemKernelDebuggerInformation,
			&SharedUserData_KernelDebugger,
			&ProcessJob,
			&VirtualAlloc_WriteWatch_BufferOnly,
			&VirtualAlloc_WriteWatch_APICalls,
			&VirtualAlloc_WriteWatch_IsDebuggerPresent,
			&VirtualAlloc_WriteWatch_CodeWrite
		});
	}

	Detector::~Detector()
	{
	}

	bool Detector::RunCheck(std::vector<int(*)()> list)
	{
		bool isFail = false;

		std::for_each(list.begin(), list.end(), [&isFail](int(*callback)()) {
			int result = callback();
			printf("checker result: %i\n", result);
			if (result)
			{
				isFail = true;
				return;
			}
		});

		return isFail;
	}
}
