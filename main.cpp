// WMX 1.5 Application using WMX3 Broker
#include <iostream>
#include <cstdio>
#include <windows.h>
#include <tchar.h>
//#include "WMXBroker.h"    // for c++
#include "WMXLIB_Sim.h"  // for vs2012 compatibility

using namespace std;
using namespace wmxAPI;

void test1_ioread(WMXLIB& wmx, WMX_STATUS& status);
void test2_position(WMXLIB& wmx, WMX_STATUS& status);
void test3_servo(WMXLIB& wmx, WMX_STATUS& status);
void test4_limit(WMXLIB& wmx, WMX_STATUS& status);
void test5_inposition(WMXLIB& wmx, WMX_STATUS& status);
void test6_opstate(WMXLIB& wmx, WMX_STATUS& status);
void test7_home(WMXLIB& wmx, WMX_STATUS& status);
void test8_engine(WMXLIB& wmx, WMX_STATUS& status);
void test9_profile(WMXLIB& wmx, WMX_STATUS& status);

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

    // Test: Sample GenIn/GenOut for 60 seconds at 1 second intervals
	//test1(wmx, status);
	test4_limit(wmx, status);

    // Stop communication and close device
    wmx.StopCommunication();
    cout << "StopCommunication done." << endl;

    wmx.CloseDevice();
    cout << "CloseDevice done." << endl;

    cout << "Press Enter to exit..." << endl;
    //cin.get();

    return 0;
}

void test1_ioread(WMXLIB& wmx, WMX_STATUS& status)
{
    cout << endl << "=== GenIn/GenOut Sampling Test (60 seconds) ===" << endl;
    cout << "Sampling GenIn/GenOut every 1 second..." << endl << endl;

    long result = -1;;

    for (int i = 0; i < 60; i++)
    {
        result = wmx.GetStatus(&status);
        if (result == 0)
        {
            cout << "[" << (i + 1) << "/60] ";

            // Print first 8 bytes of GenIn
            cout << "GenIn[0-7]: ";
            for (int j = 0; j < 8; j++)
            {
                printf("%02X ", status.GenIn[j]);
            }

            // Print first 8 bytes of GenOut
            cout << " | GenOut[0-7]: ";
            for (int j = 0; j < 8; j++)
            {
                printf("%02X ", status.GenOut[j]);
            }
            cout << endl;
        }
        else
        {
            cout << "[" << (i + 1) << "/60] GetStatus failed. Error: " << result << endl;
        }

        Sleep(1000);  // 1 second interval
    }

    cout << endl << "=== Sampling Complete ===" << endl << endl;
}

void test2_position(WMXLIB& wmx, WMX_STATUS& status)
{
    cout << endl << "=== Position/Velocity Test (60 seconds) ===" << endl;
    cout << "Sampling ActualPosition, PositionCommand, Velocity for Axis 0-3..." << endl << endl;

    long result = -1;

    for (int i = 0; i < 60; i++)
    {
        result = wmx.GetStatus(&status);
        if (result == 0)
        {
            cout << "[" << (i + 1) << "/60]" << endl;
            for (int axis = 0; axis < 4; axis++)
            {
                printf("  Axis%d: ActPos=%.3f, PosCmd=%.3f, ActVel=%.3f, VelCmd=%.3f\n",
                    axis,
                    status.ActualPosition[axis],
                    status.PositionCommand[axis],
                    status.ActualAxisVelocity[axis],
                    status.VelocityCommand[axis]);
            }
        }
        else
        {
            cout << "[" << (i + 1) << "/60] GetStatus failed. Error: " << result << endl;
        }
        Sleep(1000);
    }

    cout << endl << "=== Position/Velocity Test Complete ===" << endl << endl;
}

void test3_servo(WMXLIB& wmx, WMX_STATUS& status)
{
    cout << endl << "=== Servo Status Test (60 seconds) ===" << endl;
    cout << "Sampling ServoOn, AmpAlarm, AmpAlarmCode for Axis 0-3..." << endl << endl;

    long result = -1;

    for (int i = 0; i < 60; i++)
    {
        result = wmx.GetStatus(&status);
        if (result == 0)
        {
            cout << "[" << (i + 1) << "/60]" << endl;
            for (int axis = 0; axis < 4; axis++)
            {
                printf("  Axis%d: ServoOn=%d, AmpAlarm=%d, AmpAlarmCode=%d\n",
                    axis,
                    status.ServoOn[axis],
                    status.AmpAlarm[axis],
                    status.AmpAlarmCode[axis]);
            }
        }
        else
        {
            cout << "[" << (i + 1) << "/60] GetStatus failed. Error: " << result << endl;
        }
        Sleep(1000);
    }

    cout << endl << "=== Servo Status Test Complete ===" << endl << endl;
}

void test4_limit(WMXLIB& wmx, WMX_STATUS& status)
{
    cout << endl << "=== Limit Switch Test (60 seconds) ===" << endl;
    cout << "Sampling HardPLS/NLS, NearPLS/NLS, SoftLimit for Axis 0-3..." << endl << endl;

    long result = -1;

    for (int i = 0; i < 60; i++)
    {
        result = wmx.GetStatus(&status);
        if (result == 0)
        {
            cout << "[" << (i + 1) << "/60]" << endl;
            for (int axis = 0; axis < 4; axis++)
            {
                printf("  Axis%d: HardPLS=%d, HardNLS=%d, NearPLS=%d, NearNLS=%d, SoftPLS=%d, SoftNLS=%d\n",
                    axis,
                    status.HardPLS[axis],
                    status.HardNLS[axis],
                    status.NearPLS[axis],
                    status.NearNLS[axis],
                    status.PositiveSoftLimit[axis],
                    status.NegativeSoftLimit[axis]);
            }
        }
        else
        {
            cout << "[" << (i + 1) << "/60] GetStatus failed. Error: " << result << endl;
        }
        Sleep(1000);
    }

    cout << endl << "=== Limit Switch Test Complete ===" << endl << endl;
}

void test5_inposition(WMXLIB& wmx, WMX_STATUS& status)
{
    cout << endl << "=== In-Position Test (60 seconds) ===" << endl;
    cout << "Sampling InPosition 1-5 for Axis 0-3..." << endl << endl;

    long result = -1;

    for (int i = 0; i < 60; i++)
    {
        result = wmx.GetStatus(&status);
        if (result == 0)
        {
            cout << "[" << (i + 1) << "/60]" << endl;
            for (int axis = 0; axis < 4; axis++)
            {
                printf("  Axis%d: InPos=%d, InPos2=%d, InPos3=%d, InPos4=%d, InPos5=%d\n",
                    axis,
                    status.InPosition[axis],
                    status.InPosition2[axis],
                    status.InPosition3[axis],
                    status.InPosition4[axis],
                    status.InPosition5[axis]);
            }
        }
        else
        {
            cout << "[" << (i + 1) << "/60] GetStatus failed. Error: " << result << endl;
        }
        Sleep(1000);
    }

    cout << endl << "=== In-Position Test Complete ===" << endl << endl;
}

void test6_opstate(WMXLIB& wmx, WMX_STATUS& status)
{
    cout << endl << "=== Operation State Test (60 seconds) ===" << endl;
    cout << "Sampling OpState, AxisCommandMode, AxisSyncMode for Axis 0-3..." << endl << endl;

    long result = -1;

    for (int i = 0; i < 60; i++)
    {
        result = wmx.GetStatus(&status);
        if (result == 0)
        {
            cout << "[" << (i + 1) << "/60]" << endl;
            for (int axis = 0; axis < 4; axis++)
            {
                printf("  Axis%d: OpState=%d, CmdMode=%d, SyncMode=%d\n",
                    axis,
                    status.OpState[axis],
                    status.AxisCommandMode[axis],
                    status.AxisSyncMode[axis]);
            }
        }
        else
        {
            cout << "[" << (i + 1) << "/60] GetStatus failed. Error: " << result << endl;
        }
        Sleep(1000);
    }

    cout << endl << "=== Operation State Test Complete ===" << endl << endl;
}

void test7_home(WMXLIB& wmx, WMX_STATUS& status)
{
    cout << endl << "=== Home Status Test (60 seconds) ===" << endl;
    cout << "Sampling HomeSwitch, HomeDone, HomeState, HomePaused for Axis 0-3..." << endl << endl;

    long result = -1;

    for (int i = 0; i < 60; i++)
    {
        result = wmx.GetStatus(&status);
        if (result == 0)
        {
            cout << "[" << (i + 1) << "/60]" << endl;
            for (int axis = 0; axis < 4; axis++)
            {
                printf("  Axis%d: HomeSwitch=%d, HomeDone=%d, HomeState=%d, HomePaused=%d\n",
                    axis,
                    status.HomeSwitch[axis],
                    status.HomeDone[axis],
                    status.HomeState[axis],
                    status.HomePaused[axis]);
            }
        }
        else
        {
            cout << "[" << (i + 1) << "/60] GetStatus failed. Error: " << result << endl;
        }
        Sleep(1000);
    }

    cout << endl << "=== Home Status Test Complete ===" << endl << endl;
}

void test8_engine(WMXLIB& wmx, WMX_STATUS& status)
{
    cout << endl << "=== Engine Status Test (60 seconds) ===" << endl;
    cout << "Sampling EngineStatus, InvalidLicenseError..." << endl << endl;

    long result = -1;

    for (int i = 0; i < 60; i++)
    {
        result = wmx.GetStatus(&status);
        if (result == 0)
        {
            printf("[%d/60] EngineStatus=%d, InvalidLicenseError=%d\n",
                (i + 1),
                status.EngineStatus,
                status.InvalidLicenseError);
        }
        else
        {
            cout << "[" << (i + 1) << "/60] GetStatus failed. Error: " << result << endl;
        }
        Sleep(1000);
    }

    cout << endl << "=== Engine Status Test Complete ===" << endl << endl;
}

void test9_profile(WMXLIB& wmx, WMX_STATUS& status)
{
    cout << endl << "=== Profile Timing Test (60 seconds) ===" << endl;
    cout << "Sampling ProfileTotalCycleTime, Acc, Cruise, Dec for Axis 0-3..." << endl << endl;

    long result = -1;

    for (int i = 0; i < 60; i++)
    {
        result = wmx.GetStatus(&status);
        if (result == 0)
        {
            cout << "[" << (i + 1) << "/60]" << endl;
            for (int axis = 0; axis < 4; axis++)
            {
                printf("  Axis%d: Total=%d, Acc=%d, Cruise=%d, Dec=%d\n",
                    axis,
                    status.ProfileTotalCycleTime[axis],
                    status.ProfileAccCycleTime[axis],
                    status.ProfileCruiseCycleTime[axis],
                    status.ProfileDecCycleTime[axis]);
            }
        }
        else
        {
            cout << "[" << (i + 1) << "/60] GetStatus failed. Error: " << result << endl;
        }
        Sleep(1000);
    }

    cout << endl << "=== Profile Timing Test Complete ===" << endl << endl;
}
