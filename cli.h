#pragma once
#include <string>
#include <vector>

class CLI {
public:
    CLI(int argc, char* argv[]);
    void run();
private:
    std::vector<std::string> args;
    bool interactive = true;

    //system commands implementation 
    void showHelp();
    void showVersion();
    void showInfo();
    void showUsage();
    void showHealth();
    void showScan();
    void showAll();
    void showIntegrity(const std::vector<std::string>& tokens);
    void interactiveMode();
    static std::vector<std::string> tokenize(const std::string& line);
};
