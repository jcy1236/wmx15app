// StatusMapper.cpp
// WMX3 CoreMotionStatus to WMX 1.5 WMX_STATUS conversion

#include "StatusMapper.h"
#include "CoreMotionApi.h"
#include "IOApi.h"

void StatusMapper::MapStatus(const wmx3Api::CoreMotionStatus& src, wmx3Api::Io* io, WMX_STATUS* dst)
{
    if (!dst) return;

    // Initialize structure
    memset(dst, 0, sizeof(WMX_STATUS));

    // Map engine status
    MapEngineStatus(src, dst);

    // Map axis status (up to 64 axes)
    int axisCount = (MAX_ALLAXES < wmx3Api::constants::maxAxes) ? MAX_ALLAXES : wmx3Api::constants::maxAxes;
    MapAxisStatus(src, dst, axisCount);

    // Map I/O status
    if (io) {
        MapIoStatus(io, dst);
    }
}

void StatusMapper::MapEngineStatus(const wmx3Api::CoreMotionStatus& src, WMX_STATUS* dst)
{
    // Engine state conversion
    // WMX3: EngineState::T { Idle, Running, Communicating, Shutdown, Unknown }
    // WMX1.5: WMX_PE_STATE { WMX_PE_ST_IDLE, WMX_PE_ST_RUNNING, WMX_PE_ST_COMMUNICATING, ... }
    switch (src.engineState) {
        case wmx3Api::EngineState::Idle:
            dst->EngineStatus = WMX_PE_ST_IDLE;
            break;
        case wmx3Api::EngineState::Running:
            dst->EngineStatus = WMX_PE_ST_RUNNING;
            break;
        case wmx3Api::EngineState::Communicating:
            dst->EngineStatus = WMX_PE_ST_COMMUNICATING;
            break;
        case wmx3Api::EngineState::Shutdown:
            dst->EngineStatus = WMX_PE_ST_SHUTDOWN;
            break;
        default:
            dst->EngineStatus = WMX_PE_ST_IDLE;
            break;
    }

    // License error
    dst->InvalidLicenseError = src.invalidLicenseError ? 1 : 0;
}

void StatusMapper::MapAxisStatus(const wmx3Api::CoreMotionStatus& src, WMX_STATUS* dst, int axisCount)
{
    for (int i = 0; i < axisCount; i++) {
        const wmx3Api::CoreMotionAxisStatus& axisSrc = src.axesStatus[i];

        // Servo status
        dst->ServoOn[i] = axisSrc.servoOn ? 1 : 0;

        // Alarm
        dst->AmpAlarm[i] = axisSrc.ampAlarm ? 1 : 0;
        dst->AmpAlarmCode[i] = axisSrc.ampAlarmCode;

        // Master axis
        dst->MasterAxis[i] = (short)axisSrc.masterAxis;

        // Position
        dst->ActualPosition[i] = axisSrc.actualPos;
        dst->PositionCommand[i] = axisSrc.posCmd;
        dst->RawPositionCommand[i] = axisSrc.compPosCmd;
        dst->RawFeedback[i] = axisSrc.compActualPos;

        // Encoder
        dst->EncoderValue[i] = axisSrc.encoderFeedback;

        // Velocity
        dst->ActualAxisVelocity[i] = axisSrc.actualVelocity;
        dst->VelocityCommand[i] = axisSrc.velocityCmd;
        dst->VelocityLag[i] = axisSrc.velocityLag;

        // Torque
        dst->ActualTorque[i] = axisSrc.actualTorque;

        // Profile time (ms)
        dst->ProfileTotalCycleTime[i] = (int)axisSrc.profileTotalMilliseconds;
        dst->ProfileAccCycleTime[i] = (int)axisSrc.profileAccMilliseconds;
        dst->ProfileCruiseCycleTime[i] = (int)axisSrc.profileCruiseMilliseconds;
        dst->ProfileDecCycleTime[i] = (int)axisSrc.profileDecMilliseconds;

        // Limit switches
        dst->HardPLS[i] = axisSrc.positiveLS ? 1 : 0;
        dst->HardNLS[i] = axisSrc.negativeLS ? 1 : 0;
        dst->NearPLS[i] = axisSrc.nearPositiveLS ? 1 : 0;
        dst->NearNLS[i] = axisSrc.nearNegativeLS ? 1 : 0;
        dst->ExtPLS[i] = axisSrc.externalPositiveLS ? 1 : 0;
        dst->ExtNLS[i] = axisSrc.externalNegativeLS ? 1 : 0;
        dst->PositiveLimitSwitch[i] = axisSrc.positiveLS ? 1 : 0;
        dst->NegativeLimitSwitch[i] = axisSrc.negativeLS ? 1 : 0;
        dst->PositiveSoftLimit[i] = axisSrc.positiveSoftLimit ? 1 : 0;
        dst->NegativeSoftLimit[i] = axisSrc.negativeSoftLimit ? 1 : 0;

        // In-position
        dst->InPosition[i] = axisSrc.inPos ? 1 : 0;
        dst->InPosition2[i] = axisSrc.inPos2 ? 1 : 0;
        dst->InPosition3[i] = axisSrc.inPos3 ? 1 : 0;
        dst->InPosition4[i] = axisSrc.inPos4 ? 1 : 0;
        dst->InPosition5[i] = axisSrc.inPos5 ? 1 : 0;

        // Flags
        dst->DenFlag[i] = axisSrc.cmdDistributionEnd ? 1 : 0;
        dst->PsetFlag[i] = axisSrc.posSet ? 1 : 0;
        dst->DPsetFlag[i] = axisSrc.delayedPosSet ? 1 : 0;
        dst->DenDPsetDiff[i] = axisSrc.cmdDistributionEndDelayedPosSetDiff;

        // Home
        dst->HomeSwitch[i] = axisSrc.homeSwitch ? 1 : 0;
        dst->HomeDone[i] = axisSrc.homeDone ? 1 : 0;
        dst->HomePaused[i] = axisSrc.homePaused ? 1 : 0;

        // Home state conversion
        // WMX3 HomeState::T has many states, WMX1.5 WMX_HOME_STATE also has many states
        // Map directly where possible
        switch (axisSrc.homeState) {
            case wmx3Api::HomeState::Idle:
                dst->HomeState[i] = WMX_HOME_STATE_IDLE;
                break;
            case wmx3Api::HomeState::ZPulseSearch:
                dst->HomeState[i] = WMX_HOME_STATE_ZP_SEARCH;
                break;
            case wmx3Api::HomeState::ZPulseSearchReverse:
                dst->HomeState[i] = WMX_HOME_STATE_ZP_SEARCH_REV;
                break;
            case wmx3Api::HomeState::ZPulseSearchPauseReverse:
                dst->HomeState[i] = WMX_HOME_STATE_ZP_SEARCH_REV_PAUSE;
                break;
            case wmx3Api::HomeState::HSSearch:
                dst->HomeState[i] = WMX_HOME_STATE_HS_SEARCH;
                break;
            case wmx3Api::HomeState::HSSearchPause:
                dst->HomeState[i] = WMX_HOME_STATE_HS_SEARCH_PAUSE;
                break;
            case wmx3Api::HomeState::HSAndZPulseSearch:
                dst->HomeState[i] = WMX_HOME_STATE_HS_AND_ZP_SEARCH;
                break;
            case wmx3Api::HomeState::HSAndZPulseSearchPause:
                dst->HomeState[i] = WMX_HOME_STATE_HS_AND_ZP_SEARCH_PAUSE;
                break;
            case wmx3Api::HomeState::LSSearch:
                dst->HomeState[i] = WMX_HOME_STATE_LS_SEARCH;
                break;
            case wmx3Api::HomeState::LSSearchPause:
                dst->HomeState[i] = WMX_HOME_STATE_LS_SEARCH_PAUSE;
                break;
            case wmx3Api::HomeState::HSClearReverse:
                dst->HomeState[i] = WMX_HOME_STATE_HS_CLEAR_REV;
                break;
            case wmx3Api::HomeState::HSClearReversePause:
                dst->HomeState[i] = WMX_HOME_STATE_HS_CLEAR_REV_PAUSE;
                break;
            case wmx3Api::HomeState::HomeShift:
                dst->HomeState[i] = WMX_HOME_STATE_HOME_SHIFT;
                break;
            case wmx3Api::HomeState::HomeShiftPause:
                dst->HomeState[i] = WMX_HOME_STATE_HOME_SHIFT_PAUSE;
                break;
            case wmx3Api::HomeState::Cancel:
                dst->HomeState[i] = WMX_HOME_STATE_CANCEL;
                break;
            default:
                dst->HomeState[i] = WMX_HOME_STATE_OTHER;
                break;
        }

        // Acc/Dec flags
        dst->AxisAccFlag[i] = axisSrc.accFlag ? 1 : 0;
        dst->AxisDecFlag[i] = axisSrc.decFlag ? 1 : 0;

        // Following error
        dst->FollowingErrorAlarm[i] = axisSrc.followingErrorAlarm ? 1 : 0;

        // Operation state conversion
        // WMX3: OperationState::T { Idle, Pos, Jog, Home, Sync, GantryHome, Stop, Intpl, Velocity, ... }
        // WMX1.5: WMX_OPSTATE { WMX_OPSTATE_IDLE, WMX_OPSTATE_POS, WMX_OPSTATE_JOG, WMX_OPSTATE_HOME, ... }
        switch (axisSrc.opState) {
            case wmx3Api::OperationState::Idle:
                dst->OpState[i] = WMX_OPSTATE_IDLE;
                break;
            case wmx3Api::OperationState::Pos:
                dst->OpState[i] = WMX_OPSTATE_POS;
                break;
            case wmx3Api::OperationState::Jog:
                dst->OpState[i] = WMX_OPSTATE_JOG;
                break;
            case wmx3Api::OperationState::Home:
                dst->OpState[i] = WMX_OPSTATE_HOME;
                break;
            case wmx3Api::OperationState::Sync:
            case wmx3Api::OperationState::SyncCatchUp:
                dst->OpState[i] = WMX_OPSTATE_SYNC;
                break;
            case wmx3Api::OperationState::GantryHome:
                dst->OpState[i] = WMX_OPSTATE_GANTRY_HOME;
                break;
            case wmx3Api::OperationState::Stop:
                dst->OpState[i] = WMX_OPSTATE_STOPPING;
                break;
            case wmx3Api::OperationState::Intpl:
                dst->OpState[i] = WMX_OPSTATE_INTPL;
                break;
            case wmx3Api::OperationState::Velocity:
            case wmx3Api::OperationState::ConstLinearVelocity:
                dst->OpState[i] = WMX_OPSTATE_CLV;
                break;
            case wmx3Api::OperationState::Trq:
            case wmx3Api::OperationState::DancerControl:
                dst->OpState[i] = WMX_OPSTATE_TRQ;
                break;
            case wmx3Api::OperationState::DirectControl:
                dst->OpState[i] = WMX_OPSTATE_DIRECT_CONTROL;
                break;
            case wmx3Api::OperationState::PVT:
                dst->OpState[i] = WMX_OPSTATE_PVT;
                break;
            default:
                dst->OpState[i] = WMX_OPSTATE_IDLE;
                break;
        }

        // Axis command mode conversion
        // WMX3: AxisCommandMode::T { Position, Velocity, Torque }
        // WMX1.5: WMX_AXIS_COMMAND_MODE { WMX_AXIS_COMMAND_MODE_POSITION, WMX_AXIS_COMMAND_MODE_VELOCITY, WMX_AXIS_COMMAND_MODE_TORQUE }
        switch (axisSrc.axisCommandMode) {
            case wmx3Api::AxisCommandMode::Position:
                dst->AxisCommandMode[i] = WMX_AXIS_COMMAND_MODE_POSITION;
                break;
            case wmx3Api::AxisCommandMode::Velocity:
                dst->AxisCommandMode[i] = WMX_AXIS_COMMAND_MODE_VELOCITY;
                break;
            case wmx3Api::AxisCommandMode::Torque:
                dst->AxisCommandMode[i] = WMX_AXIS_COMMAND_MODE_TORQUE;
                break;
            default:
                dst->AxisCommandMode[i] = WMX_AXIS_COMMAND_MODE_POSITION;
                break;
        }

        // Sync mode conversion
        // WMX3: AxisSyncMode::T { NoSync, NoOffset, VelocityOffset, SymmetricVelocityOffset }
        // WMX1.5: WMX_AXIS_SYNC_MODE { WMX_AXIS_SYNC_MODE_NOT_SYNC, WMX_AXIS_SYNC_MODE_SYNC_NO_OFFSET,
        //                              WMX_AXIS_SYNC_MODE_SYNC_VELOCITY_OFFSET, WMX_AXIS_SYNC_MODE_SYNC_POSITION_OFFSET }
        switch (axisSrc.axisSyncMode) {
            case wmx3Api::AxisSyncMode::NoSync:
                dst->AxisSyncMode[i] = WMX_AXIS_SYNC_MODE_NOT_SYNC;
                break;
            case wmx3Api::AxisSyncMode::NoOffset:
                dst->AxisSyncMode[i] = WMX_AXIS_SYNC_MODE_SYNC_NO_OFFSET;
                break;
            case wmx3Api::AxisSyncMode::VelocityOffset:
                dst->AxisSyncMode[i] = WMX_AXIS_SYNC_MODE_SYNC_VELOCITY_OFFSET;
                break;
            case wmx3Api::AxisSyncMode::SymmetricVelocityOffset:
                dst->AxisSyncMode[i] = WMX_AXIS_SYNC_MODE_SYNC_POSITION_OFFSET;
                break;
            default:
                dst->AxisSyncMode[i] = WMX_AXIS_SYNC_MODE_NOT_SYNC;
                break;
        }

        // Command ready
        dst->CmdReadyFlag[i] = axisSrc.commandReady ? 1 : 0;

        // Compensation
        dst->Compensation[i].PitchErrorCompensation = axisSrc.compensation.pitchErrorCompensation;
    }
}

void StatusMapper::MapIoStatus(wmx3Api::Io* io, WMX_STATUS* dst)
{
    if (!io) return;

    // Read input I/O
    int inSize = (MAX_IOINSIZE < wmx3Api::constants::maxIoInSize) ? MAX_IOINSIZE : wmx3Api::constants::maxIoInSize;
    io->GetInBytes(0, inSize, dst->GenIn);

    // Read output I/O
    int outSize = (MAX_IOOUTSIZE < wmx3Api::constants::maxIoOutSize) ? MAX_IOOUTSIZE : wmx3Api::constants::maxIoOutSize;
    io->GetOutBytes(0, outSize, dst->GenOut);
}
