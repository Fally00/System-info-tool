#define UNICODE
#include "systemInfo.h"
#include <windows.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <intrin.h>
#include <winreg.h>

// Implementation of SystemInfo functions for Windows
namespace SystemInfo {

    // Returns the operating system name
    std::string getOSName() {
        HKEY hKey;
        if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
            char buffer[256];
            DWORD size = sizeof(buffer);
            if (RegQueryValueEx(hKey, "ProductName", NULL, NULL, (LPBYTE)buffer, &size) == ERROR_SUCCESS) {
                RegCloseKey(hKey);
                return std::string(buffer);
            }
            RegCloseKey(hKey);
        }
        return "Windows";
    }

    // Returns the CPU model name
    std::string getCPUModel() {
        int cpuInfo[4] = {-1};
        char brand[49] = {0};
        __cpuid(cpuInfo, 0x80000002);
        memcpy(brand, cpuInfo, sizeof(cpuInfo));
        __cpuid(cpuInfo, 0x80000003);
        memcpy(brand + 16, cpuInfo, sizeof(cpuInfo));
        __cpuid(cpuInfo, 0x80000004);
        memcpy(brand + 32, cpuInfo, sizeof(cpuInfo));
        return std::string(brand);
    }

    // Returns the ram size in GB
    std::string getRam() {
        MEMORYSTATUSEX memInfo;
        memInfo.dwLength = sizeof(MEMORYSTATUSEX);
        GlobalMemoryStatusEx(&memInfo);
        double ramGB = memInfo.ullTotalPhys / (1024.0 * 1024.0 * 1024.0);
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << ramGB << " GB";
        return oss.str();
    }

    // Returns the total physical disk size in GB
    uint64_t getDisk() {
        ULARGE_INTEGER totalBytes;
        if (GetDiskFreeSpaceExA("C:\\", NULL, &totalBytes, NULL)) {
            return totalBytes.QuadPart / (1024LL * 1024 * 1024);
        }
        return 0;
    }

    // Returns the uptime in seconds
    int getUptime() {
        return static_cast<int>(GetTickCount64() / 1000);
    }

    // Returns the current user name
    std::string getUserName() {
        char buffer[256];
        DWORD size = sizeof(buffer);
        if (GetUserNameA(buffer, &size)) {
            return std::string(buffer);
        }
        return "Unknown";
    }

}
