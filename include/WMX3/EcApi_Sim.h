// EcApi_Sim.h
// WMX3 EtherCAT API Header-only wrapper for VS2012 compatibility
// Part of WMX3Api_Sim.h - provides wmx3Api::ecApi namespace interface
//
// Usage:
//   Include via WMX3Api_Sim.h (not directly)
//   Link with WMXBroker.lib

#ifndef ECAPI_SIM_H
#define ECAPI_SIM_H

#include "WMX3BrokerC.h"

namespace wmx3Api
{
    namespace ecApi
    {
        //=====================================================================
        // EtherCAT Constants
        //=====================================================================
        namespace constants
        {
            static const int maxMasters = 2;
            static const int maxSlaves = 256;
            static const int maxSlaveAxes = 16;
            static const int maxEniFilePathLen = 256;
            static const int maxSdoInfoNameLen = 64;
            static const int maxSdoInfoODListSize = 450;
            static const int maxSdoInfoEDListSize = 50;
        }

        //=====================================================================
        // EtherCAT Enums
        //=====================================================================
        class EcStateMachine
        {
        public:
            enum T
            {
                None = 0x00,
                Init = 0x01,
                Preop = 0x02,
                Boot = 0x03,
                Safeop = 0x04,
                Op = 0x08
            };
        };

        class EcSdoType
        {
        public:
            enum T
            {
                Expedited = 0x00,
                Normal = 0x01
            };
        };

        class EcHotconnectState
        {
        public:
            enum T
            {
                Idle = 0x00,
                Running,
                Abort,
                Unknown
            };
        };

        class EcHotconnectAbortCode
        {
        public:
            enum T
            {
                None = 0x00,
                PortOpenError,
                Timeout,
                ScanNetworkFailed,
                ApplyNewTopologyError,
                InitNewSlavesError,
                RecalculateDcError,
                ClearDLEventError,
                Unknown
            };
        };

        class EcOperationMode
        {
        public:
            enum T
            {
                NONE = 0x00,
                PP = 0x01,
                VL = 0x02,
                PV = 0x03,
                TQ = 0x04,
                HM = 0x06,
                IP = 0x07,
                CSP = 0x08,
                CSV = 0x09,
                CST = 0x0a,
                CSTCA = 0x0b,
                Unknown
            };
        };

        class EcMasterMode
        {
        public:
            enum T
            {
                CyclicMode,
                PPMode
            };
        };

        class EcErrorCode : public ErrorCode
        {
        public:
            enum
            {
                EcError = 0x00002000,
                ScanNetworkFailed,
                HotconnectFailed,
                SharedMemoryNull,
                SlaveStateChangeError,
                SlaveStateBelowPreop,
                SlaveInvalidAddressingMode,
                SlaveInEmergencyState,
                SlaveMailboxInUse,
                SlaveSdoDownloadError,
                SlaveSdoUploadError,
                SlaveSdoInfoGetODListError,
                SlaveSdoInfoGetODError,
                SlaveSdoInfoGetEDError,
                SlaveActualSizeLargerThanBufferSize,
                SlaveRegWriteError,
                SlaveRegReadError,
                SlaveSIIWriteError,
                SlaveSIIWriteFailedToSetChecksum,
                SlaveSIIReadError,
                SlavePdoReadWriteNotAllowed,
                SlavePdoReadWriteTimeout,
                SlavePdoNotMapped,
                SlaveTxPdoWriteNotAllowed,
                SlaveFoENotInBootState,
                SlaveFoEFileOpenError,
                SlaveFoEReadError,
                SlaveFoEWriteError,
                SlaveFoEFilePathTooLong,
                SlaveFoEFileNameTooLong,
                SlaveAoEReadError,
                SlaveAoEWriteError,
                SlaveSoEReadError,
                SlaveSoEWriteError,
                SlaveVoEReadError,
                SlaveVoEWriteError,
                AxisNotServoOn,
                NotInPPMode,
                NotInHMMode,
                NotInPVMode,
                NotInTQMode,
                PdoNotMapped,
                SlaveNotSupportVirtualSerial,
                OpenComFailed,
                CreateComProcessThreadFailed
            };

            static int ConvertEcErrorCode(int errCode);
        };

        //=====================================================================
        // EtherCAT Data Structures
        //=====================================================================
        class EcSlavePdo
        {
        public:
            EcSlavePdo() : enable(false), size(0), offset(0) {}
            bool enable;
            unsigned char size;
            unsigned short offset;
        };

        class EcSlavePdoInfo
        {
        public:
            EcSlavePdoInfo()
            {
                memset(this, 0, sizeof(EcSlavePdoInfo));
            }
            EcSlavePdo statusWord;
            EcSlavePdo modesOfOperationDisplay;
            EcSlavePdo positionActualValue;
            EcSlavePdo velocityActualValue;
            EcSlavePdo torqueActualValue;
            EcSlavePdo errorCode;
            EcSlavePdo touchProbeStatus;
            EcSlavePdo touchProbePositionPos1;
            EcSlavePdo touchProbePositionPos2;
            EcSlavePdo followingError;
            EcSlavePdo digitalInput;

            EcSlavePdo controlWord;
            EcSlavePdo modesOfOperation;
            EcSlavePdo targetPosition;
            EcSlavePdo targetVelocity;
            EcSlavePdo targetTorque;
            EcSlavePdo maxTorque;
            EcSlavePdo positiveTorqueLimit;
            EcSlavePdo negativeTorqueLimit;
            EcSlavePdo touchProbeFunction;
            EcSlavePdo velocityOffset;
            EcSlavePdo torqueOffset;
            EcSlavePdo maxMotorSpeed;
            EcSlavePdo digitalOutput;
        };

        class EcSlaveAxisInfo
        {
        public:
            EcSlaveAxisInfo()
            {
                memset(this, 0, sizeof(EcSlaveAxisInfo));
                operationMode = EcOperationMode::NONE;
            }
            int axisIndex;
            short digitalInputAddr;
            unsigned short digitalInputSize;
            short digitalOutputAddr;
            unsigned short digitalOutputSize;
            EcSlavePdoInfo pdoInfo;
            EcOperationMode::T operationMode;
            unsigned char targetReached;
            unsigned char followingError;
            unsigned char homingError;
            unsigned char homingAttained;
            unsigned char halt;
        };

        class EcSlaveInfo
        {
        public:
            EcSlaveInfo()
            {
                memset(this, 0, sizeof(EcSlaveInfo));
                state = EcStateMachine::None;
            }
            int id;
            short position;
            short address;
            unsigned int vendorId;
            unsigned int productCode;
            unsigned int revisionNo;
            unsigned int serialNo;
            unsigned int alias;
            unsigned int numOfAxes;
            EcSlaveAxisInfo axisInfo[constants::maxSlaveAxes];
            EcStateMachine::T state;
            unsigned short alStatusCode;
            unsigned char offline;
            unsigned char inaccessible;
            unsigned char newSlave;
            unsigned char reverseSlave;
            unsigned char dcSupport;
            unsigned char dcWidth;
            unsigned char portState[4];
            int neighbor[4];
            unsigned int propagaDelay;
            unsigned long long systemTime;
            unsigned long long systemTimeOffset;
            unsigned long long startTime;
            unsigned short inputAddr;
            unsigned short inputSize;
            unsigned short outputAddr;
            unsigned short outputSize;
            unsigned int rxLogicAddr;
            unsigned int rxPhyAddr;
            unsigned int rxSize;
            unsigned int txLogicAddr;
            unsigned int txPhyAddr;
            unsigned int txSize;
        };

        class EcMasterStatisticsInfo
        {
        public:
            EcMasterStatisticsInfo()
            {
                memset(this, 0, sizeof(EcMasterStatisticsInfo));
                hcState = EcHotconnectState::Idle;
                hcAbortCode = EcHotconnectAbortCode::None;
            }
            long commPeriod;
            long long cycleCounter;
            double interruptIntervalRatio[9];
            double cycleProcessTimeRatio[6];
            double processTimeRatio[6];
            double commandProcessTimeRatio[6];
            double feedbackProcessTimeRatio[6];
            double communicateProcessTimeRatio[6];
            unsigned int txDelay;
            unsigned int minTxDelay;
            unsigned int maxTxDelay;
            unsigned int packetLoss;
            unsigned int packetTimeout;
            unsigned int packetLossMode[4];
            unsigned int packetTimeoutMode[4];
            unsigned long long minRefClockInterval;
            unsigned long long maxRefClockInterval;
            unsigned long long avgRefClockInterval;
            unsigned long long curRefClock;
            unsigned long long nextDcClock;
            int diffFromNextDcClock;
            int minDiffFromNextDcClock;
            int maxDiffFromNextDcClock;
            unsigned int totalAxesNum;
            unsigned int totalRxPdoSize;
            unsigned int totalTxPdoSize;
            unsigned int totalInputSize;
            unsigned int totalOutputSize;
            unsigned int overCycle;
            unsigned int ringNum;
            unsigned int numOfCyclicFrames;
            EcHotconnectState::T hcState;
            EcHotconnectAbortCode::T hcAbortCode;
            long hcErrorCode;
        };

        class EcMasterInfo
        {
        public:
            EcMasterInfo()
            {
                memset(this, 0, sizeof(EcMasterInfo));
                state = EcStateMachine::None;
                mode = EcMasterMode::CyclicMode;
            }
            int id;
            EcStateMachine::T state;
            EcMasterMode::T mode;
            unsigned int numOfSlaves;
            EcSlaveInfo slaves[constants::maxSlaves];
            EcMasterStatisticsInfo statisticsInfo;

            int GetOnlineSlaveCount()
            {
                int count = 0;
                for (unsigned int i = 0; i < numOfSlaves; i++)
                {
                    if (!slaves[i].offline)
                        count++;
                }
                return count;
            }

            int GetOfflineSlaveCount()
            {
                int count = 0;
                for (unsigned int i = 0; i < numOfSlaves; i++)
                {
                    if (slaves[i].offline)
                        count++;
                }
                return count;
            }

            int GetInaccessibleSlaveCount()
            {
                int count = 0;
                for (unsigned int i = 0; i < numOfSlaves; i++)
                {
                    if (slaves[i].inaccessible)
                        count++;
                }
                return count;
            }
        };

        //=====================================================================
        // Ecat class - EtherCAT operations
        //=====================================================================
        class Ecat
        {
        private:
            WMX3Api *m_wmx3Api;

        public:
            Ecat(WMX3Api *wmx3Api) : m_wmx3Api(wmx3Api) {}
            Ecat() : m_wmx3Api(NULL) {}
            ~Ecat() {}

            // Static methods
            static long ErrorToString(int errCode, char *pString, unsigned int size)
            {
                return WMX3Broker_Ecat_ErrorToString(errCode, pString, size);
            }

            static long ErrorToString(int errCode, wchar_t *pString, unsigned int size)
            {
                return WMX3Broker_Ecat_ErrorToStringW(errCode, pString, size);
            }

            // Copy constructor and assignment operator
            Ecat(const Ecat &src) : m_wmx3Api(src.m_wmx3Api) {}
            Ecat &operator=(const Ecat &src)
            {
                if (this != &src)
                {
                    m_wmx3Api = src.m_wmx3Api;
                }
                return *this;
            }

            //=================================================================
            // Master Information
            //=================================================================
            long GetMasterInfo(EcMasterInfo *pMaster)
            {
                return WMX3Broker_Ecat_GetMasterInfo(pMaster);
            }

            //=================================================================
            // Network Control
            //=================================================================
            long ScanNetwork()
            {
                return WMX3Broker_Ecat_ScanNetwork();
            }

            long StartHotconnect()
            {
                return WMX3Broker_Ecat_StartHotconnect();
            }

            long ChangeSlaveState(int slaveId, EcStateMachine::T state, int *pErrorCode)
            {
                return WMX3Broker_Ecat_ChangeSlaveState(slaveId, static_cast<int>(state), pErrorCode);
            }

            bool IsDeviceValid()
            {
                return WMX3Broker_Ecat_IsDeviceValid() != 0;
            }

            long ResetTransmitStatisticsInfo()
            {
                return WMX3Broker_Ecat_ResetTransmitStatisticsInfo();
            }

            //=================================================================
            // SDO Communication
            //=================================================================
            long SdoDownload(int slaveId, int index, int subindex, int sdoDataSize,
                             unsigned char *sdoData, unsigned int *errCode, unsigned int waitTime = 0)
            {
                return WMX3Broker_Ecat_SdoDownload(slaveId, index, subindex,
                                                   sdoDataSize, sdoData, errCode, waitTime);
            }

            long SdoUpload(int slaveId, int index, int subindex, int sdoBuffSize,
                           unsigned char *sdoBuff, unsigned int *actualSize, unsigned int *errCode,
                           unsigned int waitTime = 0)
            {
                return WMX3Broker_Ecat_SdoUpload(slaveId, index, subindex,
                                                 sdoBuffSize, sdoBuff, actualSize, errCode, waitTime);
            }

            long SdoUpload(int slaveId, int index, int subindex, EcSdoType::T sdoType,
                           int sdoBuffSize, unsigned char *sdoBuff, unsigned int *actualSize,
                           unsigned int *errCode, unsigned int waitTime = 0)
            {
                return WMX3Broker_Ecat_SdoUploadWithType(slaveId, index, subindex,
                                                         static_cast<int>(sdoType),
                                                         sdoBuffSize, sdoBuff, actualSize, errCode, waitTime);
            }

            //=================================================================
            // Register Read/Write
            //=================================================================
            long RegisterWrite(int slaveId, int regAddr, int len, unsigned char *data)
            {
                return WMX3Broker_Ecat_RegisterWrite(slaveId, regAddr, len, data);
            }

            long RegisterRead(int slaveId, int regAddr, int len, unsigned char *buff)
            {
                return WMX3Broker_Ecat_RegisterRead(slaveId, regAddr, len, buff);
            }

            //=================================================================
            // PDO Read/Write
            //=================================================================
            long TxPdoWrite(int slaveId, int index, int subindex, int pdoDataSize,
                            unsigned char *pdoData, unsigned int mask = 0)
            {
                return WMX3Broker_Ecat_TxPdoWrite(slaveId, index, subindex,
                                                  pdoDataSize, pdoData);
            }

            long PdoRead(int slaveId, int index, int subindex, int pdoBuffSize,
                         unsigned char *pdoBuff, unsigned int *actualSize)
            {
                return WMX3Broker_Ecat_PdoRead(slaveId, index, subindex,
                                               pdoBuffSize, pdoBuff, actualSize);
            }

            //=================================================================
            // Slave I/O (Digital)
            //=================================================================
            long SetOutputBit(int slaveId, int byte, int bit, unsigned char data)
            {
                return WMX3Broker_Ecat_SetOutputBit(slaveId, byte, bit, data);
            }

            long SetOutputByte(int slaveId, int byte, unsigned char data)
            {
                return WMX3Broker_Ecat_SetOutputByte(slaveId, byte, data);
            }

            long SetOutputBytes(int slaveId, int byte, int size, unsigned char *pData)
            {
                return WMX3Broker_Ecat_SetOutputBytes(slaveId, byte, size, pData);
            }

            long GetInputBit(int slaveId, int byte, int bit, unsigned char *pData)
            {
                return WMX3Broker_Ecat_GetInputBit(slaveId, byte, bit, pData);
            }

            long GetInputByte(int slaveId, int byte, unsigned char *pData)
            {
                return WMX3Broker_Ecat_GetInputByte(slaveId, byte, pData);
            }

            long GetInputBytes(int slaveId, int byte, int size, unsigned char *pData)
            {
                return WMX3Broker_Ecat_GetInputBytes(slaveId, byte, size, pData);
            }

            //=================================================================
            // SII (Slave Information Interface) Read/Write
            //=================================================================
            long SIIWrite(int slaveId, int siiAddr, int len, unsigned char *data, bool checkSum = false)
            {
                return WMX3Broker_Ecat_SIIWrite(slaveId, siiAddr, len, data, checkSum ? 1 : 0);
            }

            long SIIRead(int slaveId, int siiAddr, int len, unsigned char *buff)
            {
                return WMX3Broker_Ecat_SIIRead(slaveId, siiAddr, len, buff);
            }
        };

    } // namespace ecApi
} // namespace wmx3Api

#endif // ECAT_SIM_H
