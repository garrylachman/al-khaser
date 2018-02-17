#include <Windows.h>
#include <tchar.h>
#include <ShlObj.h>
#include <strsafe.h>
#include <Shlwapi.h>
#include <Wbemidl.h>

# pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "Mpr.lib")

#include "../Shared/Common.h"
#include "../Shared/Utils.h"




BOOL vbox_reg_key_value();
BOOL vbox_reg_keys();
BOOL vbox_files();
BOOL vbox_dir();

BOOL vbox_check_mac();
BOOL vbox_devices();
BOOL vbox_window_class();
BOOL vbox_network_share();
BOOL vbox_processes();
BOOL vbox_devices_wmi();
BOOL vbox_mac_wmi();
BOOL vbox_eventlogfile_wmi();
