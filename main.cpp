// WMX 1.5 Application using WMX3 Broker
#include <iostream>
#include <cstdio>
#include <windows.h>
#include <tchar.h>
#include "WMXBroker.h"

using namespace std;
using namespace wmxAPI;

int main()
{
    cout << "=== WMX 1.5 Application (via WMX3 Broker) ===" << endl;

    // WMXLIB instance (now using WMXBroker)
    WMXLIB wmx;

    // Create device (Simulation Engine)
    // WMX_SIM_ENGINE: Simulation mode
    // WMX_RTEX_ENGINE: Real-time EtherCAT mode
    TCHAR path[MAX_PATH] = _T("C:\\Program Files\\SoftServo\\WMX3");
    long result = wmx.CreateDevice(path, WMX_SIM_ENGINE);
    if (result != 0)
    {
        cout << "CreateDevice failed. Error code: " << result << endl;
        cout << "Please check if WMX engine is running." << endl;
        return -1;
    }
    cout << "CreateDevice successful!" << endl;

    // Start communication
    result = wmx.StartCommunication();
    if (result != 0)
    {
        cout << "StartCommunication failed. Error code: " << result << endl;
        wmx.CloseDevice();
        return -1;
    }
    cout << "StartCommunication successful!" << endl;

    // Get device status
    WMX_STATUS status;
    result = wmx.GetStatus(&status);
    if (result == 0)
    {
        cout << "Device Status retrieved successfully." << endl;
        cout << "Engine Status: " << status.EngineStatus << endl;
    }

    // Stop communication and close device
    wmx.StopCommunication();
    cout << "StopCommunication done." << endl;

    wmx.CloseDevice();
    cout << "CloseDevice done." << endl;

    cout << "Press Enter to exit..." << endl;
    cin.get();

    return 0;
}
