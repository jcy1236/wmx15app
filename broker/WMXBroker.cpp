// WMXBroker.cpp
// WMX 1.5 API를 WMX3 API로 변환하는 Broker 구현

#include "WMXBroker.h"
#include "StatusMapper.h"

// WMX3 헤더
#include "WMX3Api.h"
#include "CoreMotionApi.h"
#include "IOApi.h"

namespace wmxAPI {

    //////////////////////////////////////////////////////////////////////////
    // WMXLIB 클래스 구현
    //////////////////////////////////////////////////////////////////////////

    WMXLIB::WMXLIB()
        : wmx3(nullptr)
        , coreMotion(nullptr)
        , wmx3Io(nullptr)
        , isConnected(false)
        , lastError(WMX_API_ERROR_CODE())
    {
        // Io 클래스 인스턴스 생성
        io = new common::Io(this);

        // Initial output 버퍼 초기화
        memset(initialOut, 0, sizeof(initialOut));
    }

    WMXLIB::~WMXLIB()
    {
        if (isConnected) {
            CloseDevice();
        }

        delete io;
        io = nullptr;
    }

    WMXAPIFUNC WMXLIB::CreateDevice(TCHAR* path, PLTFRM_TYPE type)
    {
        // WMX3 API 인스턴스 생성
        wmx3 = new wmx3Api::WMX3Api();

        // WMX3 디바이스 생성
        // path는 WMX3 설치 경로로 사용 (예: "C:\Program Files\SoftServo\WMX3")
        long ret = wmx3->CreateDevice(path, wmx3Api::DeviceType::DeviceTypeNormal);
        if (ret != 0) {
            delete wmx3;
            wmx3 = nullptr;
            return ret;
        }

        // CoreMotion 모듈 생성
        coreMotion = new wmx3Api::CoreMotion(wmx3);

        // Io 모듈 생성
        wmx3Io = new wmx3Api::Io(wmx3);

        isConnected = true;
        return 0;
    }

    WMXAPIFUNC WMXLIB::CloseDevice()
    {
        if (wmx3Io) {
            delete wmx3Io;
            wmx3Io = nullptr;
        }

        if (coreMotion) {
            delete coreMotion;
            coreMotion = nullptr;
        }

        if (wmx3) {
            wmx3->CloseDevice();
            delete wmx3;
            wmx3 = nullptr;
        }

        isConnected = false;
        return 0;
    }

    WMXAPIFUNC WMXLIB::StartCommunication()
    {
        if (!wmx3) return -1;

        // WMX3에서는 CreateDevice 시 이미 통신이 시작됨
        // 호환성을 위해 성공 반환
        return 0;
    }

    WMXAPIFUNC WMXLIB::StopCommunication()
    {
        // WMX3에서는 CloseDevice 시 통신 종료
        // 호환성을 위해 성공 반환
        return 0;
    }

    WMXAPIFUNC WMXLIB::GetStatus(WMX_STATUS* st)
    {
        if (!wmx3 || !coreMotion || !wmx3Io || !st) return -1;

        // WMX3 상태 조회
        wmx3Api::CoreMotionStatus wmx3Status;
        long ret = coreMotion->GetStatus(&wmx3Status);
        if (ret != 0) return ret;

        // WMX3 상태를 WMX 1.5 상태로 변환
        StatusMapper::MapStatus(wmx3Status, wmx3Io, st);

        return 0;
    }

    WMXAPIFUNC WMXLIB::GetStatus(WMX_STATUS* st, short axis)
    {
        // 단일 축 상태 조회 - 전체 조회 후 해당 축만 사용
        return GetStatus(st);
    }

    WMXAPIFUNC WMXLIB::GetStatus(WMX_STATUS* st, short firstAxis, short lastAxis)
    {
        // 범위 축 상태 조회 - 전체 조회 후 해당 범위만 사용
        return GetStatus(st);
    }

    WMXAPIFUNC WMXLIB::GetVersion(double* pCeVersion, double* pPeVersion)
    {
        if (!coreMotion) return -1;

        // WMX3 버전 조회
        int major, minor, revision, fix;
        long ret = coreMotion->GetVersion(&major, &minor, &revision, &fix);
        if (ret != 0) return ret;

        // WMX 1.5 형식으로 변환
        if (pCeVersion) *pCeVersion = major + minor / 1000.0;
        if (pPeVersion) *pPeVersion = revision + fix / 1000.0;

        return 0;
    }

} // namespace wmxAPI
