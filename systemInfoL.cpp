#include "systemInfo.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/statvfs.h>
#include <pwd.h>
#include <iomanip>

namespace SystemInfo {
tat
    std::string getOSName() {
        struct utsname buffer;
        if (uname(&buffer) != 0) {
            return "Unknown";
        }
        return std::string(buffer.sysname) + " " + std::string(buffer.release);
    }

    std::string getCPUModel() {
        std::ifstream file("/proc/cpuinfo");
        std::string line;
        while (std::getline(file, line)) {
            if (line.find("model name") != std::string::npos) {
                size_t colon = line.find(':');
                if (colon != std::string::npos) {
                    return line.substr(colon + 2);
                }
            }
        }
        return "Unknown";
    }

    std::string getRam() {
        std::ifstream file("/proc/meminfo");
        std::string line;
        while (std::getline(file, line)) {
            if (line.find("MemTotal") != std::string::npos) {
                std::istringstream iss(line);
                std::string key, value, unit;
                iss >> key >> value >> unit;
                long mem_kb = std::stol(value);
                double mem_gb = mem_kb / (1024.0 * 1024.0);
                std::ostringstream oss;
                oss << std::fixed << std::setprecision(2) << mem_gb << " GB";
                return oss.str();
            }
        }
        return "Unknown";
    }

    uint64_t getDisk() {
        struct statvfs stat;
        if (statvfs("/", &stat) != 0) {
            return 0;
        }
        uint64_t total_bytes = stat.f_blocks * stat.f_frsize;
        uint64_t total_gb = total_bytes / (1024 * 1024 * 1024);
        return total_gb;
    }

    int getUptime() {
        std::ifstream file("/proc/uptime");
        double uptime_seconds;
        file >> uptime_seconds;
        return static_cast<int>(uptime_seconds);
    }

    std::string getUserName() {
        char* username = getlogin();
        if (username) {
            return std::string(username);
        }
        // Fallback to environment variable
        username = getenv("USER");
        if (username) {
            return std::string(username);
        }
        // Another fallback using getpwuid
        struct passwd* pw = getpwuid(getuid());
        if (pw) {
            return std::string(pw->pw_name);
        }
        return "Unknown";
    }

}
