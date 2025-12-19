#include "systemInfo.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <iomanip>
#include <cstdlib>

namespace SystemInfo {

    std::string getOSName() {
        std::ifstream file("/etc/os-release");
        std::string line;
        while (std::getline(file, line)) {
            if (line.find("PRETTY_NAME") != std::string::npos) {
                size_t equal = line.find('=');
                if (equal != std::string::npos) {
                    std::string value = line.substr(equal + 1);
                    if (!value.empty() && value[0] == '"') {
                        value = value.substr(1, value.size() - 2);
                    }
                    return value;
                }
            }
        }
        return "Linux";
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
        try {
            auto space = std::filesystem::space("/");
            return space.capacity / (1024 * 1024 * 1024);
        } catch (...) {
            return 0;
        }
    }

    int getUptime() {
        std::ifstream file("/proc/uptime");
        double uptime_seconds;
        file >> uptime_seconds;
        return static_cast<int>(uptime_seconds);
    }

    std::string getUserName() {
        char* username = getenv("USER");
        if (username) {
            return std::string(username);
        }
        return "Unknown";
    }

}
