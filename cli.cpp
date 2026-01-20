#include "systemInfo.h"
#include "health.h"
#include "cli.h"
#include <string>
#include <vector>
#include <iostream>

// ANSI color codes
#define RESET       "\033[0m"
#define BOLD        "\033[1m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"
#define PURPLE      "\033[95m"
#define ORANGE      "\033[38;5;208m"
#define COFFEE     "\033[38;5;94m"

CLI::CLI(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        args.push_back(argv[i]);
    }
    if (!args.empty()) {
        interactive = false;
    }
}

void CLI::run() {
    if (interactive) {
        interactiveMode();
    } else {
        if (args[0] == "--help" || args[0] == "-h" || args[0] == "help") {
            showHelp();
        } else if (args[0] == "--version" || args[0] == "-v" || args[0] == "version") {
            showVersion();
        } else if (args[0] == "info") {
            showInfo();
        } else if (args[0] == "usage") {
            showUsage();
        } else if (args[0] == "health") {
            showHealth();
        } else if (args[0] == "scan") {
            showScan();
        } else if (args[0] == "all") {
            showAll();
        } else {
            std::cout << RED << "Unknown command. Use --help for usage." << RESET << std::endl;
        }
    }
}

void CLI::showHelp() {
    std::cout << YELLOW << BOLD << "System Insight Toolkit Commands" << RESET << std::endl;
    std::cout << WHITE << std::endl;
    std::cout << COFFEE << "Commands:" << std::endl;
    std::cout << WHITE << "  info     Show basic system information" << std::endl;
    std::cout << WHITE << "  usage    Show system resource usage" << std::endl;
    std::cout << WHITE << "  health   Show system health status" << std::endl;
    std::cout << WHITE << "  scan     Scan for common system problems" << std::endl;
    std::cout << WHITE << "  all      Show all information" << std::endl;
    std::cout << GREEN << "  help     Show this help message" << std::endl;
    std::cout << GREEN << "  version  Show version information" << std::endl;
    std::cout << RED << "  << exit >>    Exit the tool" << std::endl;
    std::cout << WHITE << std::endl;
}

void CLI::showVersion() {
    std::cout << YELLOW << "System Insight Toolkit v1.2.0" << std::endl;
}

void CLI::showInfo() {
    std::cout << YELLOW << BOLD << "---------- System Basic Info ----------" << RESET << std::endl;
    std::cout << "OS Name: " << SystemInfo::getOSName() << std::endl;
    std::cout << "CPU Model: " << SystemInfo::getCPUModel() << std::endl;
    std::cout << "RAM: " << SystemInfo::getRam() << std::endl;
    std::cout << "Disk Size: " << SystemInfo::getDisk() << " GB" << std::endl;
    std::cout << "Uptime: " << SystemInfo::getUptime() << " seconds" << std::endl;
    std::cout << "User Name: " << SystemInfo::getUserName() << std::endl;
    std::cout << COFFEE << "==============================================" << RESET << std::endl;
}

void CLI::showUsage() {
    std::cout << YELLOW << BOLD << "---------- System Usage Info ----------" << RESET << std::endl;
    double cpu = SystemInfo::getCPUusage();
    double ram = SystemInfo::getRamUsage();
    double disk = SystemInfo::getDiskUsage();
    std::cout << "CPU Usage: " << cpu << " %" << std::endl;
    std::cout << "RAM Usage: " << ram << " %" << std::endl;
    std::cout << "Disk Usage: " << disk << " %" << std::endl;
    std::cout << COFFEE << "==============================================" << RESET << std::endl;
}

void CLI::showHealth() {
    std::cout << YELLOW<< BOLD << "---------- System Health Info ----------" << RESET << std::endl;
    double cpu = SystemInfo::getCPUusage();
    double ram = SystemInfo::getRamUsage();
    double disk = SystemInfo::getDiskUsage();
    std::cout << "CPU Health: " << Health::CPUhp(cpu) << std::endl;
    std::cout << "RAM Health: " << Health::RAMhp(ram) << std::endl;
    std::cout << "Disk Health: " << Health::Diskhp(disk) << std::endl;
    std::cout << "Overall Health Score: " << Health::overallScore(cpu, ram, disk) << "/100" << std::endl;
    std::cout << COFFEE << "==============================================" << RESET << std::endl;
}

void CLI::showAll() {
    showInfo();
    showUsage();
    showHealth();
    showScan();
}

void CLI::showScan() {
    struct Issue {
        std::string severity;
        std::string message;
        std::string tip;
    };

    std::vector<Issue> issues;
    double cpu = SystemInfo::getCPUusage();
    double ram = SystemInfo::getRamUsage();
    int uptimeSeconds = SystemInfo::getUptime();
    double tempC = SystemInfo::getCpuTemperatureC();

    if (cpu >= 85.0) {
        issues.push_back({"CRITICAL", "High CPU usage (" + std::to_string((int)cpu) + "%)", "Close heavy apps or check background processes."});
    } else if (cpu >= 70.0) {
        issues.push_back({"WARNING", "Elevated CPU usage (" + std::to_string((int)cpu) + "%)", "Check for apps using unusual CPU."});
    }

    if (ram >= 85.0) {
        issues.push_back({"CRITICAL", "High RAM usage (" + std::to_string((int)ram) + "%)", "Close apps or upgrade memory if needed."});
    } else if (ram >= 75.0) {
        issues.push_back({"WARNING", "Elevated RAM usage (" + std::to_string((int)ram) + "%)", "Close unused apps and browser tabs."});
    }

    int uptimeDays = uptimeSeconds / (60 * 60 * 24);
    if (uptimeDays >= 30) {
        issues.push_back({"CRITICAL", "Long uptime (" + std::to_string(uptimeDays) + " days)", "Reboot to clear leaks and apply updates."});
    } else if (uptimeDays >= 7) {
        issues.push_back({"WARNING", "Long uptime (" + std::to_string(uptimeDays) + " days)", "Consider a reboot if issues appear."});
    }

    if (tempC >= 0.0) {
        if (tempC >= 85.0) {
            issues.push_back({"CRITICAL", "High CPU temperature (" + std::to_string((int)tempC) + " C)", "Check cooling, fans, and airflow."});
        } else if (tempC >= 75.0) {
            issues.push_back({"WARNING", "Elevated CPU temperature (" + std::to_string((int)tempC) + " C)", "Clean dust and ensure good airflow."});
        }
    }

    std::cout << YELLOW << BOLD << "---------- System Problem Scan ----------" << RESET << std::endl;
    if (issues.empty()) {
        std::cout << GREEN << "No problems detected." << RESET << std::endl;
    } else {
        for (const auto& issue : issues) {
            std::cout << RED << "[" << issue.severity << "] " << RESET
                      << issue.message << " | Tip: " << issue.tip << std::endl;
        }
    }
    std::cout << COFFEE << "==============================================" << RESET << std::endl;
}

void CLI::interactiveMode() {
    const std::string logo = R"(
   _____ __________ 
  / ___//  _/_  __/
  \__ \ / /  / /   
 ___/ // /  / /    
/____/___/ /_/     
                    )";

    std::cout << YELLOW  << BOLD << logo << RESET << std::endl;
    std::cout << COFFEE << "==============================================" << RESET << std::endl;
    std::cout << YELLOW << BOLD << "System Insight Toolkit v1.2.0" << RESET << std::endl;
    std::cout << "Type 'help' for commands or 'exit' to quit." << std::endl;
    std::cout << COFFEE << "==============================================" << RESET << std::endl;

    std::string command;
    while (true) {
        std::cout << "sysinfo> ";
        std::getline(std::cin, command);
        if (!std::cin) {
            std::cout << RED << "Input closed. Exiting System Insight Toolkit." << RESET << std::endl;
            break;
        }
        if (command == "exit" || command == "quit") {
            std::cout << RED << "Exiting System Insight Toolkit." << RESET << std::endl;
            break;
        } else if (command == "help") {
            showHelp();
        } else if (command == "version") {
            showVersion();
        } else if (command == "info") {
            showInfo();
        } else if (command == "usage") {
            showUsage();
        } else if (command == "health") {
            showHealth();
        } else if (command == "scan") {
            showScan();
        } else if (command == "all") {
            showAll();
        } else if (command.empty()) {
            continue;
        } else {
            std::cout << RED << "Unknown command. Type 'help' for available commands." << RESET << std::endl;
        }
    }
}
