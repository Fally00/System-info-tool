#include "systemInfo.h"
#include <iostream>
using namespace std;


int main() {
    cout << "System Information Tool" << endl;
    cout << "       To Start the System Info tool Press {1}" << endl;
    cout << "=============================================="<< endl;

    //System Info Tool Start
    int choice;
    cin >> choice;
    if (choice == 1) {
        cout << "OS Name: " << SystemInfo::getOSName() << endl;
        cout << "CPU Model: " << SystemInfo::getCPUModel() << endl;
        cout << "RAM: " << SystemInfo::getRam() << endl;
        cout << "Disk Size: " << SystemInfo::getDisk() << " GB" << endl;
        cout << "Uptime: " << SystemInfo::getUptime() << " seconds" << endl;
        cout << "User Name: " << SystemInfo::getUserName() << endl;
    }




    return 0;
}
