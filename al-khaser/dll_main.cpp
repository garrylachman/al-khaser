#include "dll_main.h"
#include "Shared\Main.h"
#include <algorithm>
#include <functional>

namespace AlKhaser
{
	Detector *Detector::m_self = nullptr;
	
	BOOL Detector::Check(Detector::CHECKERS _checker)
	{
		if (m_self == nullptr)
		{
			m_self = new Detector();
		}
		switch (_checker)
		{
		case CHECKERS::ANALYSIS:
			return m_self->RunCheck(m_self->checkers_AntiAnalysis);
			break;

		case CHECKERS::DEBUG:
			return m_self->RunCheck(m_self->checkers_AntiDebug);
			break;

		case CHECKERS::VM:
			return m_self->RunCheck(m_self->checkers_AntiVM);
			break;

		case CHECKERS::DUMP:
			return m_self->RunCheck(m_self->checkers_AntiDump);
			break;

		case CHECKERS::ALL:
			BOOL ret = (m_self->RunCheck(m_self->checkers_AntiAnalysis)
				&& m_self->RunCheck(m_self->checkers_AntiDebug)
				&& m_self->RunCheck(m_self->checkers_AntiVM)
				&& m_self->RunCheck(m_self->checkers_AntiDump));
			return ret;
			break;
		}
		return TRUE;
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

		checkers_AntiVM.assign({
			&loaded_dlls,
			&NumberOfProcessors,
			&idt_trick,
			&ldt_trick,
			&gdt_trick,
			&str_trick,
			&number_cores_wmi,
			&disk_size_wmi,
			&dizk_size_deviceiocontrol,
			&setupdi_diskdrive,
			&mouse_movement,
			&memory_space,
			&disk_size_getdiskfreespace,
			&cpuid_is_hypervisor,
			&cpuid_hypervisor_vendor,
			&FirmwareSMBIOS,
			&FirmwareACPI,
			&accelerated_sleep,
			&VMDriverServices,
			&vbox_reg_key_value,
			&vbox_dir,
			&vbox_files,
			&vbox_reg_keys,
			&vbox_check_mac,
			&vbox_devices,
			&vbox_window_class,
			&vbox_network_share,
			&vbox_processes,
			&vbox_devices_wmi,
			&vbox_mac_wmi,
			&vbox_eventlogfile_wmi,
			&vmware_reg_key_value,
			&vmware_reg_keys,
			&vmware_files,
			&vmware_mac,
			&vmware_adapter_name,
			&vmware_devices,
			&vmware_dir,
			&virtual_pc_process,
			&qemu_reg_key_value,
			&xen_process,
			&wine_exports,
			&wine_reg_keys,
			&parallels_process
		});

		checkers_AntiAnalysis.assign({
			&analysis_tools_process
		});

		checkers_AntiDump.assign({
			&ErasePEHeaderFromMemory,
			&SizeOfImage
		});
	}

	Detector::~Detector()
	{
	}

	BOOL Detector::RunCheck(std::vector<int(*)()> list)
	{
		BOOL isFail = FALSE;

		std::for_each(list.begin(), list.end(), [&isFail](int(*callback)()) {
			int result = callback();
			printf("checker result: %i\n", result);
			if (result)
			{
				isFail = TRUE;
				return;
			}
		});

		return isFail;
	}
}
