#include <iostream>
#include <Windows.h>
#include <winsvc.h>
#include <filesystem>
#include <string.h>
#include <string>
#include <fstream>

#include "./services.h"

using namespace std;

/*

#ifdef UNICODE
#define ServiceString   std::wstring
#else
#define ServiceString   std::string
#endif

struct ServiceStatusProcess
{
    ServiceString ServiceName;
    ServiceString DisplayName;
    SERVICE_STATUS_PROCESS Status;
};

enum class ServiceType
{
   KernelDriver       = SERVICE_KERNEL_DRIVER,
   FileSystemDriver   = SERVICE_FILE_SYSTEM_DRIVER,
   Adapter            = SERVICE_ADAPTER,
   RecognizerDriver   = SERVICE_RECOGNIZER_DRIVER,
   Win32OwnProcess    = SERVICE_WIN32_OWN_PROCESS,
   Win32ShareProcess  = SERVICE_WIN32_SHARE_PROCESS,
   InteractiveDriver  = SERVICE_INTERACTIVE_PROCESS,
   Driver             = SERVICE_DRIVER,
   Win32              = SERVICE_WIN32,
   All                = SERVICE_TYPE_ALL
};

enum class ServiceState
{
   Active   = SERVICE_ACTIVE,
   Inactive = SERVICE_INACTIVE,
   All      = SERVICE_STATE_ALL
};

class ServiceHandle
{
   SC_HANDLE _handle = nullptr;

   void Close()
   {
      if (_handle != nullptr)
         ::CloseServiceHandle(_handle);
   }
   
public:
   ServiceHandle(SC_HANDLE const handle = nullptr) noexcept :_handle(handle) {}

   ServiceHandle(ServiceHandle&& other) noexcept : _handle(std::move(other._handle)) {}

   ServiceHandle& operator=(SC_HANDLE const handle)
   {
      if (_handle != handle)
      {
         Close();

         _handle = handle;
      }

      return *this;
   }

   ServiceHandle& operator=(ServiceHandle&& other)
   {
      if (this != &other)
      {
         _handle = std::move(other._handle);
         other._handle = nullptr;
      }

      return *this;
   }

   operator SC_HANDLE() const noexcept { return _handle; }

   explicit operator bool() const noexcept { return _handle != nullptr; }
   
   ~ServiceHandle() 
   {
      Close();
   }
};

class ServiceEnumerator
{
public:
    static std::vector<ServiceStatusProcess> EnumerateServices(
        ServiceType const type = ServiceType::All,
        ServiceState const state = ServiceState::All,
        ServiceString const *machine = nullptr,
        ServiceString const *dbname = nullptr,
        ServiceString const *groupName = nullptr) {

        std::vector<ServiceStatusProcess> ssps;

        auto scHandle = ServiceHandle{
            ::OpenSCManager(
                machine == nullptr ? nullptr : machine->c_str(),
                dbname == nullptr ? nullptr : dbname->c_str(),
                SC_MANAGER_ENUMERATE_SERVICE)};
        auto bytesNeeded = DWORD{0};
        auto servicesReturnedCount = DWORD{0};
        auto resumeHandle = DWORD{0};

        do {
            if (!EnumServicesStatusEx(
                    scHandle,
                    SC_ENUM_PROCESS_INFO,
                    static_cast<DWORD>(type),
                    static_cast<DWORD>(state),
                    nullptr,
                    0,
                    &bytesNeeded,
                    &servicesReturnedCount,
                    &resumeHandle,
                    groupName == nullptr ? nullptr : groupName->c_str()))
            {
                if (ERROR_MORE_DATA == ::GetLastError()) {
                    std::vector<unsigned char> buffer(bytesNeeded, 0);

                    if (EnumServicesStatusEx(
                            scHandle,
                            SC_ENUM_PROCESS_INFO,
                            static_cast<DWORD>(type),
                            static_cast<DWORD>(state),
                            reinterpret_cast<LPBYTE>(buffer.data()),
                            bytesNeeded,
                            &bytesNeeded,
                            &servicesReturnedCount,
                            nullptr,
                            groupName == nullptr ? nullptr : groupName->c_str())) 
                    {
                        auto essp = reinterpret_cast<LPENUM_SERVICE_STATUS_PROCESS>(buffer.data());

                        for (auto i = DWORD{0}; i < servicesReturnedCount; ++i) {
                            auto ssp = ServiceStatusProcess{};
                            ssp.ServiceName = essp[i].lpServiceName;
                            ssp.DisplayName = essp[i].lpDisplayName;
                            ssp.Status = essp[i].ServiceStatusProcess;

                            ssps.push_back(ssp);
                        }
                    }
                    else
                        break;
                }
                else
                    break;
            }
        } while (resumeHandle != 0);
            
        return ssps;
    }
};

*/

int main(int argc, char *argv[]) {
/*    
    if(argc != 2) {
        //return 0;     //will be used to know wich file needs to be used
    }
*/
    string path;
    ifstream file;
    file.open("./path.txt");
    getline(file, path);
    file.close();
/*
    //used for test purposes
    if(std::filesystem::exists(path)) {
        cout << "File trovato\n";

        SC_HANDLE schSCManager = connectLocalComputer(schSCManager);
        //SC_HANDLE schService;

        if(schSCManager == NULL) {
            cout << "OpenSCManager failed\n";
            cout << GetLastError() << "\n";
        }
        else {
            cout << "OpenSCManager successfull\n";
        }
    }
    else {
        cout << "File non trovato\n";
    }
*/

    fileTransfer();

    //system("pause");

    return 0;
}