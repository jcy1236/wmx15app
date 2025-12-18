// WMX3BrokerC.cpp
// WMX3 Native API C-style interface implementation
// Uses WMX3ContextManager for shared WMX3 context

#include "WMX3BrokerC.h"
#include "WMX3ContextManager.h"

// WMX3 headers
#include "WMX3Api.h"
#include "CoreMotionApi.h"
#include "IOApi.h"
#include "EcApi.h"
#include "EventApi.h"

#include <cstring>

// Reference counting for WMX3Broker C API
static int g_wmx3RefCount = 0;
static CRITICAL_SECTION g_wmx3Cs;
static bool g_wmx3CsInitialized = false;

//=============================================================================
// Internal Helper Functions
//=============================================================================
static void EnsureCsInitialized()
{
    if (!g_wmx3CsInitialized)
    {
        InitializeCriticalSection(&g_wmx3Cs);
        g_wmx3CsInitialized = true;
    }
}

//=============================================================================
// Initialization APIs
//=============================================================================
long __stdcall WMX3Broker_Initialize(void)
{
    EnsureCsInitialized();
    EnterCriticalSection(&g_wmx3Cs);
    g_wmx3RefCount++;
    LeaveCriticalSection(&g_wmx3Cs);
    return 0;
}

long __stdcall WMX3Broker_Uninitialize(void)
{
    EnsureCsInitialized();
    EnterCriticalSection(&g_wmx3Cs);
    if (g_wmx3RefCount > 0)
    {
        g_wmx3RefCount--;
    }
    LeaveCriticalSection(&g_wmx3Cs);
    return 0;
}

//=============================================================================
// WMX3Api System APIs
//=============================================================================
long __stdcall WMX3Broker_GetIMDllVersion(int* pVersion, int* pRevision)
{
    return wmx3Api::WMX3Api::GetIMDllVersion(pVersion, pRevision);
}

long __stdcall WMX3Broker_GetEngineStatus(void* pStatus)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::WMX3Api* wmx3 = ctx->GetWMX3();
    if (!wmx3 || !pStatus) return -1;
    return wmx3->GetEngineStatus(static_cast<wmx3Api::EngineStatus*>(pStatus));
}

long __stdcall WMX3Broker_CreateDevice(const char* path, int deviceType)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    return ctx->AcquireDevice();
}

long __stdcall WMX3Broker_CreateDeviceW(const wchar_t* path, int deviceType)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    return ctx->AcquireDevice();
}

long __stdcall WMX3Broker_CloseDevice(void)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    ctx->ReleaseDevice();
    return 0;
}

long __stdcall WMX3Broker_StartCommunication(unsigned int waitTimeMilliseconds)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::WMX3Api* wmx3 = ctx->GetWMX3();
    if (!wmx3) return -1;
    return wmx3->StartCommunication(waitTimeMilliseconds);
}

long __stdcall WMX3Broker_StopCommunication(unsigned int waitTimeMilliseconds)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::WMX3Api* wmx3 = ctx->GetWMX3();
    if (!wmx3) return -1;
    return wmx3->StopCommunication(waitTimeMilliseconds);
}

long __stdcall WMX3Broker_GetDeviceID(int* pId)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::WMX3Api* wmx3 = ctx->GetWMX3();
    if (!wmx3 || !pId) return -1;
    return wmx3->GetDeviceID(pId);
}

long __stdcall WMX3Broker_SetDeviceName(const char* name)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::WMX3Api* wmx3 = ctx->GetWMX3();
    if (!wmx3 || !name) return -1;
    return wmx3->SetDeviceName(const_cast<char*>(name));
}

long __stdcall WMX3Broker_SetDeviceNameW(const wchar_t* name)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::WMX3Api* wmx3 = ctx->GetWMX3();
    if (!wmx3 || !name) return -1;
    return wmx3->SetDeviceName(const_cast<wchar_t*>(name));
}

//=============================================================================
// CoreMotion Status APIs
//=============================================================================
long __stdcall WMX3Broker_CoreMotion_GetStatus(void* pStatus)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion || !pStatus) return -1;
    return coreMotion->GetStatus(static_cast<wmx3Api::CoreMotionStatus*>(pStatus));
}

//=============================================================================
// CoreMotion::AxisControl APIs
//=============================================================================
long __stdcall WMX3Broker_AxisControl_SetServoOn(int axis, int newStatus)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion) return -1;
    return coreMotion->axisControl->SetServoOn(axis, newStatus);
}

long __stdcall WMX3Broker_AxisControl_ClearAmpAlarm(int axis)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion) return -1;
    return coreMotion->axisControl->ClearAmpAlarm(axis);
}

long __stdcall WMX3Broker_AxisControl_ClearAxisAlarm(int axis)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion) return -1;
    return coreMotion->axisControl->ClearAxisAlarm(axis);
}

long __stdcall WMX3Broker_AxisControl_SetAxisCommandMode(int axis, int mode)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion) return -1;
    return coreMotion->axisControl->SetAxisCommandMode(axis, static_cast<wmx3Api::AxisCommandMode::T>(mode));
}

long __stdcall WMX3Broker_AxisControl_GetAxisCommandMode(int axis, int* pMode)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion || !pMode) return -1;
    wmx3Api::AxisCommandMode::T mode;
    long ret = coreMotion->axisControl->GetAxisCommandMode(axis, &mode);
    if (ret == 0) *pMode = static_cast<int>(mode);
    return ret;
}

long __stdcall WMX3Broker_AxisControl_GetPosCommand(int axis, double* pPosition)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion || !pPosition) return -1;
    return coreMotion->axisControl->GetPosCommand(axis, pPosition);
}

long __stdcall WMX3Broker_AxisControl_GetPosFeedback(int axis, double* pPosition)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion || !pPosition) return -1;
    return coreMotion->axisControl->GetPosFeedback(axis, pPosition);
}

long __stdcall WMX3Broker_AxisControl_GetVelCommand(int axis, double* pVelocity)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion || !pVelocity) return -1;
    return coreMotion->axisControl->GetVelCommand(axis, pVelocity);
}

long __stdcall WMX3Broker_AxisControl_GetVelFeedback(int axis, double* pVelocity)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion || !pVelocity) return -1;
    return coreMotion->axisControl->GetVelFeedback(axis, pVelocity);
}

//=============================================================================
// CoreMotion::Motion APIs
//=============================================================================
long __stdcall WMX3Broker_Motion_StartPos(int axis, double target,
    int profileType, double velocity, double acc, double dec,
    double jerkAccRatio, double jerkDecRatio, double startingVelocity, double endVelocity)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion) return -1;

    wmx3Api::Motion::PosCommand posCmd;
    posCmd.axis = axis;
    posCmd.target = target;
    posCmd.profile.type = static_cast<wmx3Api::ProfileType::T>(profileType);
    posCmd.profile.velocity = velocity;
    posCmd.profile.acc = acc;
    posCmd.profile.dec = dec;
    posCmd.profile.jerkAccRatio = jerkAccRatio;
    posCmd.profile.jerkDecRatio = jerkDecRatio;
    posCmd.profile.startingVelocity = startingVelocity;
    posCmd.profile.endVelocity = endVelocity;

    return coreMotion->motion->StartPos(&posCmd);
}

long __stdcall WMX3Broker_Motion_StartMov(int axis, double target,
    int profileType, double velocity, double acc, double dec,
    double jerkAccRatio, double jerkDecRatio, double startingVelocity, double endVelocity)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion) return -1;

    wmx3Api::Motion::PosCommand posCmd;
    posCmd.axis = axis;
    posCmd.target = target;
    posCmd.profile.type = static_cast<wmx3Api::ProfileType::T>(profileType);
    posCmd.profile.velocity = velocity;
    posCmd.profile.acc = acc;
    posCmd.profile.dec = dec;
    posCmd.profile.jerkAccRatio = jerkAccRatio;
    posCmd.profile.jerkDecRatio = jerkDecRatio;
    posCmd.profile.startingVelocity = startingVelocity;
    posCmd.profile.endVelocity = endVelocity;

    return coreMotion->motion->StartMov(&posCmd);
}

long __stdcall WMX3Broker_Motion_StartJog(int axis,
    int profileType, double velocity, double acc, double jerkAccRatio)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion) return -1;

    wmx3Api::Motion::JogCommand jogCmd;
    jogCmd.axis = axis;
    jogCmd.profile.type = static_cast<wmx3Api::ProfileType::T>(profileType);
    jogCmd.profile.velocity = velocity;
    jogCmd.profile.acc = acc;
    jogCmd.profile.jerkAccRatio = jerkAccRatio;

    return coreMotion->motion->StartJog(&jogCmd);
}

long __stdcall WMX3Broker_Motion_Stop(int axis)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion) return -1;
    return coreMotion->motion->Stop(axis);
}

long __stdcall WMX3Broker_Motion_ExecQuickStop(int axis)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion) return -1;
    return coreMotion->motion->ExecQuickStop(axis);
}

long __stdcall WMX3Broker_Motion_ExecTimedStop(int axis, double timeMilliseconds)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion) return -1;
    return coreMotion->motion->ExecTimedStop(axis, timeMilliseconds);
}

// Adapter API: Wait is not directly available in WMX3, implement via polling
long __stdcall WMX3Broker_Motion_Wait(int axis)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion) return -1;

    wmx3Api::CoreMotionStatus status;
    while (true)
    {
        long ret = coreMotion->GetStatus(&status);
        if (ret != 0) return ret;

        // Check if axis is in Idle state (motion complete)
        if (status.axesStatus[axis].opState == wmx3Api::OperationState::Idle)
        {
            break;
        }
        Sleep(1);  // 1ms polling interval
    }
    return 0;
}

long __stdcall WMX3Broker_Motion_Pause(int axis)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion) return -1;
    return coreMotion->motion->Pause(axis);
}

long __stdcall WMX3Broker_Motion_Resume(int axis)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion) return -1;
    return coreMotion->motion->Resume(axis);
}

long __stdcall WMX3Broker_Motion_StartLinearIntplPos(
    int axisCount, int* axes, double* targets,
    double* maxVelocities, double* maxAccs, double* maxDecs,
    int profileType, double velocity, double acc, double dec,
    double jerkAccRatio, double jerkDecRatio, double startingVelocity, double endVelocity)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion || !axes || !targets) return -1;

    wmx3Api::Motion::LinearIntplCommand linearCmd;
    linearCmd.axisCount = axisCount;
    for (int i = 0; i < axisCount && i < wmx3Api::constants::maxAxes; i++)
    {
        linearCmd.axis[i] = axes[i];
        linearCmd.target[i] = targets[i];
        linearCmd.maxVelocity[i] = maxVelocities ? maxVelocities[i] : 0;
        linearCmd.maxAcc[i] = maxAccs ? maxAccs[i] : 0;
        linearCmd.maxDec[i] = maxDecs ? maxDecs[i] : 0;
    }
    linearCmd.profile.type = static_cast<wmx3Api::ProfileType::T>(profileType);
    linearCmd.profile.velocity = velocity;
    linearCmd.profile.acc = acc;
    linearCmd.profile.dec = dec;
    linearCmd.profile.jerkAccRatio = jerkAccRatio;
    linearCmd.profile.jerkDecRatio = jerkDecRatio;
    linearCmd.profile.startingVelocity = startingVelocity;
    linearCmd.profile.endVelocity = endVelocity;

    return coreMotion->motion->StartLinearIntplPos(&linearCmd);
}

//=============================================================================
// CoreMotion::Home APIs
//=============================================================================
long __stdcall WMX3Broker_Home_StartHome(int axis)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion) return -1;
    return coreMotion->home->StartHome(axis);
}

long __stdcall WMX3Broker_Home_Continue(int axis)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion) return -1;
    return coreMotion->home->Continue(axis);
}

long __stdcall WMX3Broker_Home_Cancel(int axis)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion) return -1;
    return coreMotion->home->Cancel(axis);
}

long __stdcall WMX3Broker_Home_SetCommandPos(int axis, double position)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion) return -1;
    return coreMotion->home->SetCommandPos(axis, position);
}

long __stdcall WMX3Broker_Home_SetFeedbackPos(int axis, double position)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion) return -1;
    return coreMotion->home->SetFeedbackPos(axis, position);
}

long __stdcall WMX3Broker_Home_SetCommandPosToFeedbackPos(int axis, double posChangePerCycle)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion) return -1;
    return coreMotion->home->SetCommandPosToFeedbackPos(axis, posChangePerCycle);
}

long __stdcall WMX3Broker_Home_GetHomeData(void* pHomeData)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion || !pHomeData) return -1;
    return coreMotion->home->GetHomeData(static_cast<wmx3Api::Home::HomeData*>(pHomeData));
}

//=============================================================================
// CoreMotion::Velocity APIs
//=============================================================================
long __stdcall WMX3Broker_Velocity_StartVel(int axis,
    int profileType, double velocity, double acc, double dec,
    double jerkAccRatio, double jerkDecRatio)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion) return -1;

    wmx3Api::Velocity::VelCommand velCmd;
    velCmd.axis = axis;
    velCmd.profile.type = static_cast<wmx3Api::ProfileType::T>(profileType);
    velCmd.profile.velocity = velocity;
    velCmd.profile.acc = acc;
    velCmd.profile.dec = dec;
    velCmd.profile.jerkAccRatio = jerkAccRatio;
    velCmd.profile.jerkDecRatio = jerkDecRatio;

    return coreMotion->velocity->StartVel(&velCmd);
}

long __stdcall WMX3Broker_Velocity_Stop(int axis)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion) return -1;
    return coreMotion->velocity->Stop(axis);
}

long __stdcall WMX3Broker_Velocity_ExecQuickStop(int axis)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion) return -1;
    return coreMotion->velocity->ExecQuickStop(axis);
}

long __stdcall WMX3Broker_Velocity_ExecTimedStop(int axis, double timeMilliseconds)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion) return -1;
    return coreMotion->velocity->ExecTimedStop(axis, timeMilliseconds);
}

long __stdcall WMX3Broker_Velocity_OverrideVel(int axis,
    int profileType, double velocity, double acc, double dec,
    double jerkAccRatio, double jerkDecRatio)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion) return -1;

    wmx3Api::Velocity::VelCommand velCmd;
    velCmd.axis = axis;
    velCmd.profile.type = static_cast<wmx3Api::ProfileType::T>(profileType);
    velCmd.profile.velocity = velocity;
    velCmd.profile.acc = acc;
    velCmd.profile.dec = dec;
    velCmd.profile.jerkAccRatio = jerkAccRatio;
    velCmd.profile.jerkDecRatio = jerkDecRatio;

    return coreMotion->velocity->OverrideVel(&velCmd);
}

//=============================================================================
// CoreMotion::Torque APIs
//=============================================================================
long __stdcall WMX3Broker_Torque_SetMaxTrqLimit(int axis, double torque)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion) return -1;
    return coreMotion->torque->SetMaxTrqLimit(axis, torque);
}

long __stdcall WMX3Broker_Torque_GetMaxTrqLimit(int axis, double* pTorque)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion || !pTorque) return -1;
    return coreMotion->torque->GetMaxTrqLimit(axis, pTorque);
}

long __stdcall WMX3Broker_Torque_SetPositiveTrqLimit(int axis, double torque)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion) return -1;
    return coreMotion->torque->SetPositiveTrqLimit(axis, torque);
}

long __stdcall WMX3Broker_Torque_GetPositiveTrqLimit(int axis, double* pTorque)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion || !pTorque) return -1;
    return coreMotion->torque->GetPositiveTrqLimit(axis, pTorque);
}

long __stdcall WMX3Broker_Torque_SetNegativeTrqLimit(int axis, double torque)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion) return -1;
    return coreMotion->torque->SetNegativeTrqLimit(axis, torque);
}

long __stdcall WMX3Broker_Torque_GetNegativeTrqLimit(int axis, double* pTorque)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion || !pTorque) return -1;
    return coreMotion->torque->GetNegativeTrqLimit(axis, pTorque);
}

long __stdcall WMX3Broker_Torque_StartTrq(int axis, double torque)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion) return -1;

    wmx3Api::Torque::TrqCommand trqCmd;
    trqCmd.axis = axis;
    trqCmd.torque = torque;

    return coreMotion->torque->StartTrq(&trqCmd);
}

long __stdcall WMX3Broker_Torque_StartTrqWithMaxSpeed(int axis, double torque, double maxMotorSpeed)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion) return -1;

    wmx3Api::Torque::TrqCommand trqCmd;
    trqCmd.axis = axis;
    trqCmd.torque = torque;

    return coreMotion->torque->StartTrq(&trqCmd, maxMotorSpeed);
}

long __stdcall WMX3Broker_Torque_StopTrq(int axis)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion) return -1;
    return coreMotion->torque->StopTrq(axis);
}

//=============================================================================
// CoreMotion::Config APIs
//=============================================================================
long __stdcall WMX3Broker_Config_SetHomeParam(int axis, void* pParam)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion || !pParam) return -1;
    return coreMotion->config->SetHomeParam(axis, static_cast<wmx3Api::Config::HomeParam*>(pParam));
}

long __stdcall WMX3Broker_Config_GetHomeParam(int axis, void* pParam)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion || !pParam) return -1;
    return coreMotion->config->GetHomeParam(axis, static_cast<wmx3Api::Config::HomeParam*>(pParam));
}

long __stdcall WMX3Broker_Config_SetFeedbackParam(int axis, void* pParam)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion || !pParam) return -1;
    return coreMotion->config->SetFeedbackParam(axis, static_cast<wmx3Api::Config::FeedbackParam*>(pParam));
}

long __stdcall WMX3Broker_Config_GetFeedbackParam(int axis, void* pParam)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion || !pParam) return -1;
    return coreMotion->config->GetFeedbackParam(axis, static_cast<wmx3Api::Config::FeedbackParam*>(pParam));
}

long __stdcall WMX3Broker_Config_SetLimitParam(int axis, void* pParam)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion || !pParam) return -1;
    return coreMotion->config->SetLimitParam(axis, static_cast<wmx3Api::Config::LimitParam*>(pParam));
}

long __stdcall WMX3Broker_Config_GetLimitParam(int axis, void* pParam)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion || !pParam) return -1;
    return coreMotion->config->GetLimitParam(axis, static_cast<wmx3Api::Config::LimitParam*>(pParam));
}

long __stdcall WMX3Broker_Config_SetMotionParam(int axis, void* pParam)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion || !pParam) return -1;
    return coreMotion->config->SetMotionParam(axis, static_cast<wmx3Api::Config::MotionParam*>(pParam));
}

long __stdcall WMX3Broker_Config_GetMotionParam(int axis, void* pParam)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion || !pParam) return -1;
    return coreMotion->config->GetMotionParam(axis, static_cast<wmx3Api::Config::MotionParam*>(pParam));
}

long __stdcall WMX3Broker_Config_SetAlarmParam(int axis, void* pParam)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion || !pParam) return -1;
    return coreMotion->config->SetAlarmParam(axis, static_cast<wmx3Api::Config::AlarmParam*>(pParam));
}

long __stdcall WMX3Broker_Config_GetAlarmParam(int axis, void* pParam)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion || !pParam) return -1;
    return coreMotion->config->GetAlarmParam(axis, static_cast<wmx3Api::Config::AlarmParam*>(pParam));
}

long __stdcall WMX3Broker_Config_SetGearRatio(int axis, double numerator, double denominator)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion) return -1;
    return coreMotion->config->SetGearRatio(axis, numerator, denominator);
}

long __stdcall WMX3Broker_Config_GetGearRatio(int axis, double* pNumerator, double* pDenominator)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion || !pNumerator || !pDenominator) return -1;
    return coreMotion->config->GetGearRatio(axis, pNumerator, pDenominator);
}

long __stdcall WMX3Broker_Config_SetSingleTurn(int axis, int enable, unsigned int encoderCount)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion) return -1;
    return coreMotion->config->SetSingleTurn(axis, enable != 0, encoderCount);
}

long __stdcall WMX3Broker_Config_GetSingleTurn(int axis, int* pEnable, unsigned int* pEncoderCount)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion || !pEnable || !pEncoderCount) return -1;
    bool enable;
    long ret = coreMotion->config->GetSingleTurn(axis, &enable, pEncoderCount);
    if (ret == 0) *pEnable = enable ? 1 : 0;
    return ret;
}

long __stdcall WMX3Broker_Config_SetVelocityFeedforwardGain(int axis, double gain)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion) return -1;
    return coreMotion->config->SetVelocityFeedforwardGain(axis, gain);
}

long __stdcall WMX3Broker_Config_GetVelocityFeedforwardGain(int axis, double* pGain)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::CoreMotion* coreMotion = ctx->GetCoreMotion();
    if (!coreMotion || !pGain) return -1;
    return coreMotion->config->GetVelocityFeedforwardGain(axis, pGain);
}

//=============================================================================
// Io APIs
//=============================================================================
long __stdcall WMX3Broker_Io_SetOutBit(int addr, int bit, unsigned char data)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::Io* io = ctx->GetIo();
    if (!io) return -1;
    return io->SetOutBit(addr, bit, data);
}

long __stdcall WMX3Broker_Io_SetOutByte(int addr, unsigned char data)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::Io* io = ctx->GetIo();
    if (!io) return -1;
    return io->SetOutByte(addr, data);
}

long __stdcall WMX3Broker_Io_SetOutBytes(int addr, int size, unsigned char* pData)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::Io* io = ctx->GetIo();
    if (!io || !pData) return -1;
    return io->SetOutBytes(addr, size, pData);
}

long __stdcall WMX3Broker_Io_GetInBit(int addr, int bit, unsigned char* pData)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::Io* io = ctx->GetIo();
    if (!io || !pData) return -1;
    return io->GetInBit(addr, bit, pData);
}

long __stdcall WMX3Broker_Io_GetInByte(int addr, unsigned char* pData)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::Io* io = ctx->GetIo();
    if (!io || !pData) return -1;
    return io->GetInByte(addr, pData);
}

long __stdcall WMX3Broker_Io_GetInBytes(int addr, int size, unsigned char* pData)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::Io* io = ctx->GetIo();
    if (!io || !pData) return -1;
    return io->GetInBytes(addr, size, pData);
}

long __stdcall WMX3Broker_Io_GetOutBit(int addr, int bit, unsigned char* pData)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::Io* io = ctx->GetIo();
    if (!io || !pData) return -1;
    return io->GetOutBit(addr, bit, pData);
}

long __stdcall WMX3Broker_Io_GetOutByte(int addr, unsigned char* pData)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::Io* io = ctx->GetIo();
    if (!io || !pData) return -1;
    return io->GetOutByte(addr, pData);
}

long __stdcall WMX3Broker_Io_GetOutBytes(int addr, int size, unsigned char* pData)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::Io* io = ctx->GetIo();
    if (!io || !pData) return -1;
    return io->GetOutBytes(addr, size, pData);
}

long __stdcall WMX3Broker_Io_SetOutAnalogDataShort(int addr, short analogData)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::Io* io = ctx->GetIo();
    if (!io) return -1;
    return io->SetOutAnalogDataShort(addr, analogData);
}

long __stdcall WMX3Broker_Io_GetInAnalogDataShort(int addr, short* pAnalogData)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::Io* io = ctx->GetIo();
    if (!io || !pAnalogData) return -1;
    return io->GetInAnalogDataShort(addr, pAnalogData);
}

long __stdcall WMX3Broker_Io_SetOutAnalogDataInt(int addr, int analogData)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::Io* io = ctx->GetIo();
    if (!io) return -1;
    return io->SetOutAnalogDataInt(addr, analogData);
}

long __stdcall WMX3Broker_Io_GetInAnalogDataInt(int addr, int* pAnalogData)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::Io* io = ctx->GetIo();
    if (!io || !pAnalogData) return -1;
    return io->GetInAnalogDataInt(addr, pAnalogData);
}

long __stdcall WMX3Broker_Io_GetInBytesEx(int addr, int size, unsigned char* pData)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::Io* io = ctx->GetIo();
    if (!io || !pData) return -1;
    return io->GetInBytesEx(addr, size, pData);
}

long __stdcall WMX3Broker_Io_GetOutBytesEx(int addr, int size, unsigned char* pData)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::Io* io = ctx->GetIo();
    if (!io || !pData) return -1;
    return io->GetOutBytesEx(addr, size, pData);
}

//=============================================================================
// Ecat APIs
//=============================================================================
long __stdcall WMX3Broker_Ecat_ErrorToString(int errCode, char* pString, unsigned int size)
{
    return wmx3Api::ecApi::Ecat::ErrorToString(errCode, pString, size);
}

long __stdcall WMX3Broker_Ecat_ErrorToStringW(int errCode, wchar_t* pString, unsigned int size)
{
    return wmx3Api::ecApi::Ecat::ErrorToString(errCode, pString, size);
}

long __stdcall WMX3Broker_Ecat_GetMasterInfo(void* pMaster)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::ecApi::Ecat* ecat = ctx->GetEcat();
    if (!ecat || !pMaster) return -1;
    return ecat->GetMasterInfo(static_cast<wmx3Api::ecApi::EcMasterInfo*>(pMaster));
}

long __stdcall WMX3Broker_Ecat_ScanNetwork(void)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::ecApi::Ecat* ecat = ctx->GetEcat();
    if (!ecat) return -1;
    return ecat->ScanNetwork();
}

long __stdcall WMX3Broker_Ecat_StartHotconnect(void)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::ecApi::Ecat* ecat = ctx->GetEcat();
    if (!ecat) return -1;
    return ecat->StartHotconnect();
}

long __stdcall WMX3Broker_Ecat_ChangeSlaveState(int slaveId, int state, int* pErrorCode)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::ecApi::Ecat* ecat = ctx->GetEcat();
    if (!ecat) return -1;
    return ecat->ChangeSlaveState(slaveId, static_cast<wmx3Api::ecApi::EcStateMachine::T>(state), pErrorCode);
}

long __stdcall WMX3Broker_Ecat_SdoDownload(int slaveId, int index, int subindex,
    int sdoDataSize, unsigned char* sdoData, unsigned int* errCode, unsigned int waitTime)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::ecApi::Ecat* ecat = ctx->GetEcat();
    if (!ecat || !sdoData) return -1;
    return ecat->SdoDownload(slaveId, index, subindex, sdoDataSize, sdoData, errCode, waitTime);
}

long __stdcall WMX3Broker_Ecat_SdoUpload(int slaveId, int index, int subindex,
    int sdoBuffSize, unsigned char* sdoBuff, unsigned int* actualSize, unsigned int* errCode, unsigned int waitTime)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::ecApi::Ecat* ecat = ctx->GetEcat();
    if (!ecat || !sdoBuff) return -1;
    return ecat->SdoUpload(slaveId, index, subindex, sdoBuffSize, sdoBuff, actualSize, errCode, waitTime);
}

long __stdcall WMX3Broker_Ecat_RegisterWrite(int slaveId, int regAddr, int len, unsigned char* data)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::ecApi::Ecat* ecat = ctx->GetEcat();
    if (!ecat || !data) return -1;
    return ecat->RegisterWrite(slaveId, regAddr, len, data);
}

long __stdcall WMX3Broker_Ecat_RegisterRead(int slaveId, int regAddr, int len, unsigned char* buff)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::ecApi::Ecat* ecat = ctx->GetEcat();
    if (!ecat || !buff) return -1;
    return ecat->RegisterRead(slaveId, regAddr, len, buff);
}

long __stdcall WMX3Broker_Ecat_TxPdoWrite(int slaveId, int index, int subindex,
    int pdoDataSize, unsigned char* pdoData)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::ecApi::Ecat* ecat = ctx->GetEcat();
    if (!ecat || !pdoData) return -1;
    return ecat->TxPdoWrite(slaveId, index, subindex, pdoDataSize, pdoData);
}

long __stdcall WMX3Broker_Ecat_PdoRead(int slaveId, int index, int subindex,
    int pdoBuffSize, unsigned char* pdoBuff, unsigned int* actualSize)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::ecApi::Ecat* ecat = ctx->GetEcat();
    if (!ecat || !pdoBuff) return -1;
    return ecat->PdoRead(slaveId, index, subindex, pdoBuffSize, pdoBuff, actualSize);
}

long __stdcall WMX3Broker_Ecat_SetOutputBit(int slaveId, int byte, int bit, unsigned char data)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::ecApi::Ecat* ecat = ctx->GetEcat();
    if (!ecat) return -1;
    return ecat->SetOutputBit(slaveId, byte, bit, data);
}

long __stdcall WMX3Broker_Ecat_SetOutputByte(int slaveId, int byte, unsigned char data)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::ecApi::Ecat* ecat = ctx->GetEcat();
    if (!ecat) return -1;
    return ecat->SetOutputByte(slaveId, byte, data);
}

long __stdcall WMX3Broker_Ecat_SetOutputBytes(int slaveId, int byte, int size, unsigned char* pData)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::ecApi::Ecat* ecat = ctx->GetEcat();
    if (!ecat || !pData) return -1;
    return ecat->SetOutputBytes(slaveId, byte, size, pData);
}

long __stdcall WMX3Broker_Ecat_GetInputBit(int slaveId, int byte, int bit, unsigned char* pData)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::ecApi::Ecat* ecat = ctx->GetEcat();
    if (!ecat || !pData) return -1;
    return ecat->GetInputBit(slaveId, byte, bit, pData);
}

long __stdcall WMX3Broker_Ecat_GetInputByte(int slaveId, int byte, unsigned char* pData)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::ecApi::Ecat* ecat = ctx->GetEcat();
    if (!ecat || !pData) return -1;
    return ecat->GetInputByte(slaveId, byte, pData);
}

long __stdcall WMX3Broker_Ecat_GetInputBytes(int slaveId, int byte, int size, unsigned char* pData)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::ecApi::Ecat* ecat = ctx->GetEcat();
    if (!ecat || !pData) return -1;
    return ecat->GetInputBytes(slaveId, byte, size, pData);
}

//=============================================================================
// EventControl APIs
//=============================================================================
long __stdcall WMX3Broker_Event_EnableEvent(int id, unsigned char enable)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::EventControl* eventCtrl = ctx->GetEventControl();
    if (!eventCtrl) return -1;
    return eventCtrl->EnableEvent(id, enable != 0);
}

long __stdcall WMX3Broker_Event_RemoveEvent(int id)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::EventControl* eventCtrl = ctx->GetEventControl();
    if (!eventCtrl) return -1;
    return eventCtrl->RemoveEvent(id);
}

long __stdcall WMX3Broker_Event_ClearAllEvent(void)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::EventControl* eventCtrl = ctx->GetEventControl();
    if (!eventCtrl) return -1;
    return eventCtrl->ClearAllEvent();
}

long __stdcall WMX3Broker_Event_GetAllEventID(void* pEventIdData, int filterInputModuleId, int filterOutputModuleId)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::EventControl* eventCtrl = ctx->GetEventControl();
    if (!eventCtrl || !pEventIdData) return -1;
    return eventCtrl->GetAllEventID(static_cast<wmx3Api::AllEventID*>(pEventIdData),
        filterInputModuleId, filterOutputModuleId);
}

//=============================================================================
// EventControl - Software Touch Probe APIs
//=============================================================================
long __stdcall WMX3Broker_Event_SetSoftwareTouchProbe(unsigned int channel,
    unsigned char enable, int axis, int byteAddrs, int bitOffset, unsigned char logic, int mode)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::EventControl* eventCtrl = ctx->GetEventControl();
    if (!eventCtrl) return -1;
    return eventCtrl->SetSoftwareTouchProbe(channel, enable != 0, axis, byteAddrs, bitOffset,
        logic != 0, static_cast<wmx3Api::EventControl::TouchProbeMode::T>(mode));
}

long __stdcall WMX3Broker_Event_EnableSoftwareTouchProbe(unsigned int channel, unsigned char enable)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::EventControl* eventCtrl = ctx->GetEventControl();
    if (!eventCtrl) return -1;
    return eventCtrl->EnableSoftwareTouchProbe(channel, enable != 0);
}

long __stdcall WMX3Broker_Event_GetSoftwareTouchProbe(unsigned int channel,
    unsigned char* pEnabled, int* pAxis, int* pByteAddrs, int* pBitOffset,
    unsigned char* pLogic, int* pMode)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::EventControl* eventCtrl = ctx->GetEventControl();
    if (!eventCtrl) return -1;

    unsigned char enabled = 0;
    unsigned char logic = 0;
    wmx3Api::EventControl::TouchProbeMode::T mode;

    long ret = eventCtrl->GetSoftwareTouchProbe(channel, &enabled, pAxis, pByteAddrs, pBitOffset, &logic, &mode);
    if (ret == 0) {
        if (pEnabled) *pEnabled = enabled;
        if (pLogic) *pLogic = logic;
        if (pMode) *pMode = static_cast<int>(mode);
    }
    return ret;
}

long __stdcall WMX3Broker_Event_IsSoftwareTouchProbeLatched(unsigned int channel, unsigned char* pLatched)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::EventControl* eventCtrl = ctx->GetEventControl();
    if (!eventCtrl || !pLatched) return -1;
    return eventCtrl->IsSoftwareTouchProbeLatched(channel, pLatched);
}

long __stdcall WMX3Broker_Event_GetSoftwareTouchProbeCounterValue(unsigned int channel,
    unsigned char* pLatched, double* pCounterValue)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::EventControl* eventCtrl = ctx->GetEventControl();
    if (!eventCtrl || !pCounterValue) return -1;
    return eventCtrl->GetSoftwareTouchProbeCounterValue(channel, pLatched, pCounterValue);
}

//=============================================================================
// EventControl - Hardware Touch Probe APIs
//=============================================================================
long __stdcall WMX3Broker_Event_SetHardwareTouchProbe(int axis, unsigned char enable,
    int mode, int triggerSource, unsigned int channel)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::EventControl* eventCtrl = ctx->GetEventControl();
    if (!eventCtrl) return -1;
    return eventCtrl->SetHardwareTouchProbe(axis, enable != 0,
        static_cast<wmx3Api::EventControl::TouchProbeMode::T>(mode),
        static_cast<wmx3Api::EventControl::TouchProbeSource::T>(triggerSource), channel);
}

long __stdcall WMX3Broker_Event_GetHardwareTouchProbeStatus(int axis, void* pStatus)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::EventControl* eventCtrl = ctx->GetEventControl();
    if (!eventCtrl || !pStatus) return -1;
    return eventCtrl->GetHardwareTouchProbeStatus(axis,
        static_cast<wmx3Api::EventControl::HardwareTouchProbeStatus*>(pStatus));
}

long __stdcall WMX3Broker_Event_EnableHardwareTouchProbe(int axis, unsigned char enable)
{
    WMX3ContextManager* ctx = WMX3ContextManager::GetInstance();
    wmx3Api::EventControl* eventCtrl = ctx->GetEventControl();
    if (!eventCtrl) return -1;
    return eventCtrl->EnableHardwareTouchProbe(axis, enable != 0);
}
