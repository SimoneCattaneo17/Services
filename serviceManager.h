#include <iostream>
#include <Windows.h>
#include <winsvc.h>
#include <winnetwk.h>
#include <filesystem>
#include <string.h>
#include <string>
#include <fstream>

using namespace std;

//just started, this is everything but final

//local computer, all access - test purpose
SC_HANDLE connectLocalComputer(SC_HANDLE schSCManager) {

    schSCManager = OpenSCManager( 
        NULL,
        NULL,
        SC_MANAGER_ALL_ACCESS
    );

    return schSCManager;
}

//remote computer - idk
/*
SC_HANDLE connectRemoteComputer(SC_HANDLE schSCManager) {

    NETRESOURCE nr;

    nr.dwScope = RESOURCE_GLOBALNET;
    nr.dwType = RESOURCETYPE_ANY;
    nr.dwUsage = RESOURCEUSAGE_CONNECTABLE;
    nr.lpLocalName = "".c_str();
    nr.lpRemoteName = "\\\\Ad_022\\IPC$";
    nr.lpProvider = "";

    DWORD dwTest = WNetAddConnection2( &nr, "test", "Administrator", 0 );

    SC_HANDLE hSCManager = OpenSCManager( "Ad_022", NULL, SC_MANAGER_ALL_ACCESS );

    schSCManager = OpenSCManager( 
        NULL,
        NULL,
        SC_MANAGER_CONNECT
    );

    return schSCManager;
}
*/