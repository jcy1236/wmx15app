// LogApi_Sim.h
// WMX3 Log API Header-only wrapper for VS2012 compatibility
// Part of WMX3Api_Sim.h - provides wmx3Api::Log interface
//
// Usage:
//   Include via WMX3Api_Sim.h (not directly)
//   Link with WMXBroker.lib

#ifndef LOGAPI_SIM_H
#define LOGAPI_SIM_H

#include "WMX3BrokerC.h"

namespace wmx3Api
{
    //=========================================================================
    // Log Constants
    //=========================================================================
    namespace constants
    {
        static const unsigned int maxLogBufferSize = ((unsigned int)2048 * 1024);
        static const int maxLogBufferSampleSize = 80;
        static const int maxLogChannel = 8;
        static const int maxLogHeaderBytes = 4096;
        static const int maxLogHeaderLines = 2048;
        static const int maxLogDirSize = 260;
        static const int maxLogFileNameSize = 260;
        static const int maxLogDataSize = (32 * 1024);
        static const int maxLogDelimiterSize = 8;
        static const int maxLogPrecision = 20;

        static const int maxMemLogBufferSize = 1024;
        static const int maxMemLogChannel = 8;
        static const int maxMemLogAxesSize = 8;
        static const int maxMemLogDataSize = 100;
        static const int maxMemLogIoInputByteSize = 128;
        static const int maxMemLogIoOutputByteSize = 128;
        static const int maxMemLogMDataByteSize = 128;
        static const int maxMemLogTriggerEventSize = 32;

        static const int moduleLen = 64;
    }

    //=========================================================================
    // Log Error Codes
    //=========================================================================
    class LogErrorCode : public ErrorCode
    {
    public:
        enum
        {
            LogTimeIsZero = 0x00011000,
            LogBufferIsNotOpened,
            LogBufferAlreadyOpened,
            LogBufferAlreadyClosed,
            LogBufferOpenFailed,
            LogBufferIsNull,
            LockLogBufferFailed,
            SetLogIsNotFinished,
            LogBufferDataNotFound,
            CurrentlyCollectingLogData,
            CurrentlyNotCollectingLogData,
            LengthOutOfRange,
            FilePathStringTooLarge,
            FileNameNotSpecified,
            FileDirectoryNotSpecified,
            PrecisionOutOfRange,
            InvalidFilePath,
            TriggerEventCountOutOfRange,
            TriggerEventIDOutOfRange,
            SamplingPeriodOutOfRange,
            MaxLogFileCountSetButNotMaxLogFileSize,
            IOFormatCountOutOfRange,
            UserMemoryFormatCountOutOfRange,
            DataSourceModuleNotLoaded,
            NoMoreLogData
        };
    };

    //=========================================================================
    // Log Enums
    //=========================================================================
    class LogState
    {
    public:
        enum T
        {
            Idle,
            Running,
            WriteFail,
            BufferOverflow,
            Finished
        };
    };

    class DetailLogState
    {
    public:
        enum T
        {
            Idle,
            WaitingForTrigger,
            Running,
            Pause,
            Stop,
            WriteFail,
            BufferOverflow,
            Finished
        };
    };

    class ApiLogState
    {
    public:
        enum T
        {
            Stopped,
            Stopping,
            Running,
            Error,
            Unknown
        };
    };

    class FormatType
    {
    public:
        enum T
        {
            Binary,
            Decimal,
            Hexadecimal
        };
    };

    //=========================================================================
    // Log Status class
    //=========================================================================
    class LogStatus
    {
    public:
        LogStatus()
            : bufferOpened(false), logState(LogState::Idle),
              samplesToCollect(0), samplesCollected(0), samplesWritten(0),
              millisecondsToCollect(0), millisecondsCollected(0), millisecondsWritten(0) {}

        bool bufferOpened;
        LogState::T logState;
        unsigned int samplesToCollect;
        unsigned int samplesCollected;
        unsigned int samplesWritten;
        double millisecondsToCollect;
        double millisecondsCollected;
        double millisecondsWritten;
    };

    //=========================================================================
    // Log Options class
    //=========================================================================
    class LogOptions
    {
    public:
        LogOptions()
            : commandPos(0), feedbackPos(0), compCommandPos(0), compFeedbackPos(0),
              encoderCommandPos(0), encoderFeedbackPos(0), commandVelocity(0), feedbackVelocity(0),
              encoderCommandVelocity(0), encoderFeedbackVelocity(0), commandTrq(0), feedbackTrq(0),
              encoderCommandTrq(0), encoderFeedbackTrq(0), followingError(0), homeOffset(0),
              inPosFlag(0), inPosFlag2(0), inPosFlag3(0), inPosFlag4(0), inPosFlag5(0),
              commandDistributionEndFlag(0), posSetFlag(0), delayedPosSetFlag(0),
              opState(0), detailOpState(0), userOffsetCommandPos(0), userOffsetFeedbackPos(0),
              triggerOnCommandChange(0), triggerOnEvent(0), triggerEventID(0) {}

        unsigned char commandPos;
        unsigned char feedbackPos;
        unsigned char compCommandPos;
        unsigned char compFeedbackPos;
        unsigned char encoderCommandPos;
        unsigned char encoderFeedbackPos;
        unsigned char commandVelocity;
        unsigned char feedbackVelocity;
        unsigned char encoderCommandVelocity;
        unsigned char encoderFeedbackVelocity;
        unsigned char commandTrq;
        unsigned char feedbackTrq;
        unsigned char encoderCommandTrq;
        unsigned char encoderFeedbackTrq;
        unsigned char followingError;
        unsigned char homeOffset;
        unsigned char inPosFlag;
        unsigned char inPosFlag2;
        unsigned char inPosFlag3;
        unsigned char inPosFlag4;
        unsigned char inPosFlag5;
        unsigned char commandDistributionEndFlag;
        unsigned char posSetFlag;
        unsigned char delayedPosSetFlag;
        unsigned char opState;
        unsigned char detailOpState;
        unsigned char userOffsetCommandPos;
        unsigned char userOffsetFeedbackPos;
        unsigned char triggerOnCommandChange;
        unsigned char triggerOnEvent;
        unsigned int triggerEventID;
    };

    //=========================================================================
    // Log Channel Options class
    //=========================================================================
    class LogChannelOptions
    {
    public:
        LogChannelOptions()
            : maxLogFileSize(0), maxLogFileCount(0), samplingTimeMilliseconds(0),
              isRotateFile(false), stopLoggingOnBufferOverflow(false),
              samplingPeriodInCycles(0), precision(0), isDelimInLastCol(false),
              triggerOnCondition(0), triggerOnEvent(0), triggerEventID(0)
        {
            memset(delimiter, 0, sizeof(delimiter));
        }

        unsigned int maxLogFileSize;
        unsigned int maxLogFileCount;
        unsigned int samplingTimeMilliseconds;
        bool isRotateFile;
        bool stopLoggingOnBufferOverflow;
        unsigned int samplingPeriodInCycles;
        unsigned int precision;
        bool isDelimInLastCol;
        char delimiter[constants::maxLogDelimiterSize];
        unsigned char triggerOnCondition;
        unsigned char triggerOnEvent;
        unsigned int triggerEventID;
    };

    //=========================================================================
    // Log File Path classes
    //=========================================================================
    class LogFilePathA
    {
    public:
        LogFilePathA()
        {
            memset(dirPath, 0, sizeof(dirPath));
            memset(fileName, 0, sizeof(fileName));
        }

        char dirPath[constants::maxLogDirSize];
        char fileName[constants::maxLogFileNameSize];
    };

    class LogFilePathW
    {
    public:
        LogFilePathW()
        {
            memset(dirPath, 0, sizeof(dirPath));
            memset(fileName, 0, sizeof(fileName));
        }

        wchar_t dirPath[constants::maxLogDirSize];
        wchar_t fileName[constants::maxLogFileNameSize];
    };

    //=========================================================================
    // Detail Log Status classes
    //=========================================================================
    class DetailLogBufferStatus
    {
    public:
        DetailLogBufferStatus()
            : opened(0), samplesToCollect(0), samplesCollected(0),
              millisecondsToCollect(0), millisecondsCollected(0) {}

        unsigned char opened;
        unsigned int samplesToCollect;
        unsigned int samplesCollected;
        double millisecondsToCollect;
        double millisecondsCollected;
    };

    class DetailLogStatus
    {
    public:
        DetailLogStatus()
            : state(DetailLogState::Idle), interruptPeriod(0), logFileCount(0),
              samplesWrittenSize(0), samplesWritten(0), millisecondsWritten(0) {}

        DetailLogState::T state;
        DetailLogBufferStatus buffer;
        double interruptPeriod;
        unsigned int logFileCount;
        unsigned int samplesWrittenSize;
        unsigned int samplesWritten;
        double millisecondsWritten;
    };

    class DetailLogMemoryStatus
    {
    public:
        DetailLogMemoryStatus()
            : state(DetailLogState::Idle), usageRate(0), overflowFlag(0) {}

        DetailLogState::T state;
        DetailLogBufferStatus buffer;
        double usageRate;
        unsigned char overflowFlag;
    };

    //=========================================================================
    // Memory Log classes
    //=========================================================================
    class MemoryLogStatus
    {
    public:
        MemoryLogStatus()
            : bufferOpened(false), logState(LogState::Idle),
              samplesToCollect(0), samplesCollected(0), usageRate(0),
              overflowFlag(0), interruptPeriod(0) {}

        bool bufferOpened;
        LogState::T logState;
        unsigned int samplesToCollect;
        unsigned int samplesCollected;
        double usageRate;
        unsigned char overflowFlag;
        double interruptPeriod;
    };

    class MemoryLogAxisData
    {
    public:
        MemoryLogAxisData()
            : commandPos(0), feedbackPos(0), compCommandPos(0), compFeedbackPos(0),
              encoderCommandPos(0), encoderFeedbackPos(0), commandVelocity(0), feedbackVelocity(0),
              encoderCommandVelocity(0), encoderFeedbackVelocity(0), commandTrq(0), feedbackTrq(0),
              encoderCommandTrq(0), encoderFeedbackTrq(0), followingError(0), homeOffset(0),
              inPosFlag(0), inPosFlag2(0), inPosFlag3(0), inPosFlag4(0), inPosFlag5(0),
              commandDistributionEndFlag(0), posSetFlag(0), delayedPosSetFlag(0),
              opState(0), detailOpState(0), userOffsetCommandPos(0), userOffsetFeedbackPos(0) {}

        double commandPos;
        double feedbackPos;
        double compCommandPos;
        double compFeedbackPos;
        int encoderCommandPos;
        int encoderFeedbackPos;
        double commandVelocity;
        double feedbackVelocity;
        int encoderCommandVelocity;
        int encoderFeedbackVelocity;
        double commandTrq;
        double feedbackTrq;
        int encoderCommandTrq;
        int encoderFeedbackTrq;
        double followingError;
        double homeOffset;
        unsigned char inPosFlag;
        unsigned char inPosFlag2;
        unsigned char inPosFlag3;
        unsigned char inPosFlag4;
        unsigned char inPosFlag5;
        unsigned char commandDistributionEndFlag;
        unsigned char posSetFlag;
        unsigned char delayedPosSetFlag;
        int opState;
        int detailOpState;
        double userOffsetCommandPos;
        double userOffsetFeedbackPos;
    };

    class MemoryLogIOData
    {
    public:
        MemoryLogIOData()
        {
            memset(input, 0, sizeof(input));
            memset(output, 0, sizeof(output));
        }

        char input[constants::maxMemLogIoInputByteSize];
        char output[constants::maxMemLogIoOutputByteSize];
    };

    class MemoryLogMData
    {
    public:
        MemoryLogMData()
        {
            memset(data, 0, sizeof(data));
        }

        char data[constants::maxMemLogMDataByteSize];
    };

    class MemoryLogOptions
    {
    public:
        MemoryLogOptions() : triggerEventCount(0)
        {
            memset(triggerEventID, 0, sizeof(triggerEventID));
        }

        unsigned char triggerEventCount;
        unsigned int triggerEventID[constants::maxMemLogTriggerEventSize];
    };

    class MemoryLogDatas
    {
    public:
        MemoryLogDatas() : cycleCounter(0) {}

        long long cycleCounter;
        MemoryLogAxisData logAxisData[constants::maxMemLogAxesSize];
        MemoryLogIOData logIOData;
        MemoryLogMData logMData;
    };

    class MemoryLogData
    {
    public:
        MemoryLogData() : count(0), overflowFlag(0) {}

        unsigned int count;
        unsigned char overflowFlag;
        MemoryLogDatas logData[constants::maxMemLogDataSize];
    };

    //=========================================================================
    // Api Log classes
    //=========================================================================
    class ApiLogInfo
    {
    public:
        enum LogType
        {
            Command,
            Response
        };

        ApiLogInfo()
            : majorVer(0), minorVer(0), revision(0), devId(0), moduleId(0),
              mode(0), type(Command), dataLen(0), logId(0) {}

        int majorVer;
        int minorVer;
        int revision;
        int devId;
        int moduleId;
        int mode;
        LogType type;
        unsigned int dataLen;
        unsigned short logId;
    };

    class ApiLogOptions
    {
    public:
        ApiLogOptions() : sizePerFile(0)
        {
            memset(deviceExcluded, 0, sizeof(deviceExcluded));
            memset(moduleExcluded, 0, sizeof(moduleExcluded));
            memset(moduleResp, 0, sizeof(moduleResp));
        }

        unsigned int sizePerFile;
        unsigned char deviceExcluded[constants::maxDevices];
        unsigned char moduleExcluded[constants::moduleLen];
        unsigned char moduleResp[constants::moduleLen];
    };

    class ApiLogStatus
    {
    public:
        ApiLogStatus()
            : state(ApiLogState::Unknown), queueSize(0), dataSize(0), errorCode(0) {}

        ApiLogState::T state;
        unsigned int queueSize;
        unsigned int dataSize;
        int errorCode;
    };

    //=========================================================================
    // Log class - Logging functionality
    //=========================================================================
    class Log
    {
    private:
        WMX3Api *m_wmx3Api;

    public:
        Log(WMX3Api *wmx3Api) : m_wmx3Api(wmx3Api) {}
        Log() : m_wmx3Api(NULL) {}
        ~Log() {}

        // Copy constructor and assignment operator
        Log(const Log &src) : m_wmx3Api(src.m_wmx3Api) {}
        Log &operator=(const Log &src)
        {
            if (this != &src)
            {
                m_wmx3Api = src.m_wmx3Api;
            }
            return *this;
        }

        //=====================================================================
        // Static methods
        //=====================================================================
        static long GetLibVersion(int *pMajorVersion, int *pMinorVersion,
                                  int *pRevisionVersion, int *pFixVersion)
        {
            return WMX3Broker_Log_GetLibVersion(pMajorVersion, pMinorVersion,
                                                pRevisionVersion, pFixVersion);
        }

        //=====================================================================
        // Version
        //=====================================================================
        long GetVersion(int *pMajorVersion, int *pMinorVersion,
                        int *pRevisionVersion, int *pFixVersion)
        {
            return WMX3Broker_Log_GetVersion(pMajorVersion, pMinorVersion,
                                             pRevisionVersion, pFixVersion);
        }

        //=====================================================================
        // File Log Control
        //=====================================================================
        long StartLog(unsigned int channel)
        {
            return WMX3Broker_Log_StartLog(channel);
        }

        long StopLog(unsigned int channel)
        {
            return WMX3Broker_Log_StopLog(channel);
        }

        long ResetLog(unsigned int channel)
        {
            return WMX3Broker_Log_ResetLog(channel);
        }

        //=====================================================================
        // Log Options
        //=====================================================================
        long SetLogOption(unsigned int channel, LogChannelOptions *pOption)
        {
            return WMX3Broker_Log_SetLogOption(channel, pOption);
        }

        long GetLogOption(unsigned int channel, LogChannelOptions *pOption)
        {
            return WMX3Broker_Log_GetLogOption(channel, pOption);
        }

        //=====================================================================
        // Log File Path
        //=====================================================================
        long SetLogFilePath(unsigned int channel, LogFilePathA *pPath)
        {
            return WMX3Broker_Log_SetLogFilePath(channel, pPath);
        }

        long GetLogFilePath(unsigned int channel, LogFilePathA *pPath)
        {
            return WMX3Broker_Log_GetLogFilePath(channel, pPath);
        }

        long SetLogFilePath(unsigned int channel, LogFilePathW *pPath)
        {
            return WMX3Broker_Log_SetLogFilePathW(channel, pPath);
        }

        long GetLogFilePath(unsigned int channel, LogFilePathW *pPath)
        {
            return WMX3Broker_Log_GetLogFilePathW(channel, pPath);
        }

        //=====================================================================
        // Log Status
        //=====================================================================
        long GetLogStatus(unsigned int channel, LogStatus *pStatus)
        {
            return WMX3Broker_Log_GetLogStatus(channel, pStatus);
        }

        long GetDetailLogStatus(unsigned int channel, DetailLogStatus *pStatus)
        {
            return WMX3Broker_Log_GetDetailLogStatus(channel, pStatus);
        }

        //=====================================================================
        // Memory Log
        //=====================================================================
        long OpenMemoryLogBuffer(unsigned int channel)
        {
            return WMX3Broker_Log_OpenMemoryLogBuffer(channel);
        }

        long CloseMemoryLogBuffer(unsigned int channel)
        {
            return WMX3Broker_Log_CloseMemoryLogBuffer(channel);
        }

        long SetMemoryLog(unsigned int channel, AxisSelection *pAxisSelection, MemoryLogOptions *pOption)
        {
            return WMX3Broker_Log_SetMemoryLog(channel, pAxisSelection, pOption);
        }

        long StartMemoryLog(unsigned int channel)
        {
            return WMX3Broker_Log_StartMemoryLog(channel);
        }

        long StopMemoryLog(unsigned int channel)
        {
            return WMX3Broker_Log_StopMemoryLog(channel);
        }

        long GetMemoryLogStatus(unsigned int channel, MemoryLogStatus *pStatus)
        {
            return WMX3Broker_Log_GetMemoryLogStatus(channel, pStatus);
        }

        long GetMemoryLogData(unsigned int channel, MemoryLogData *pData)
        {
            return WMX3Broker_Log_GetMemoryLogData(channel, pData);
        }

        //=====================================================================
        // Api Log
        //=====================================================================
        long SetApiLog(char *pPath, ApiLogOptions *pOptions = NULL, unsigned int buffSize = 16777216)
        {
            return WMX3Broker_Log_SetApiLog(pPath, pOptions, buffSize);
        }

        long SetApiLog(wchar_t *pPath, ApiLogOptions *pOptions = NULL, unsigned int buffSize = 16777216)
        {
            return WMX3Broker_Log_SetApiLogW(pPath, pOptions, buffSize);
        }

        long StartApiLog()
        {
            return WMX3Broker_Log_StartApiLog();
        }

        long StopApiLog()
        {
            return WMX3Broker_Log_StopApiLog();
        }

        long GetApiLogStatus(ApiLogStatus *pStatus)
        {
            return WMX3Broker_Log_GetApiLogStatus(pStatus);
        }

        static long ErrorToString(int errCode, char *pString, unsigned int size)
        {
            return WMX3Broker_Log_ErrorToString(errCode, pString, size);
        }

        static long ErrorToString(int errCode, wchar_t *pString, unsigned int size)
        {
            return WMX3Broker_Log_ErrorToStringW(errCode, pString, size);
        }
    };

} // namespace wmx3Api

#endif // LOGAPI_SIM_H
