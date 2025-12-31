

![asd](https://github.com/user-attachments/assets/8228291a-ee7a-49d2-be5c-5b5ca0e44572)

# UNCZ_Slime_tracker

[English](#english) | [한국어](#한국어)

---

## English

### Overview
Custom SlimeVR tracker.

### Specifications
| Item | Description |
|------|-------------|
| MCU | ESP32-C3 Super Mini |
| IMU | SlimeVR Mumo Breakout Module V1 (ICM-45686 + QMC6309) |
| Battery | 1100mAh Li-Po |
| PCB Size | ~80mm x 30mm |

### Features
- **Optimized Power Circuit**: Minimized ripple and noise (77mV → 20mV)
- **Compact Form Factor**: Streamlined 2-layer PCB design
- **Production Ready**: Includes JLCPCB manufacturing files

### Repository Structure
```
├── 3D/                    # 3D model files (STL - case, mount, etc.)
├── Datasheets/            # Component datasheets
├── Demonstration_Video/   # Demo videos
├── SlimeVR/               # SlimeVR firmware source code
├── KiCad/                 # KiCad project files
│   ├── *.kicad_pcb
│   ├── *.kicad_sch
│   └── *.kicad_pro
├── License/               # License files
├── Measurement_Pic/       # Power circuit ripple measurement photos
└── Production/            # Manufacturing files
    ├── BOM.csv            # Bill of Materials (JLCPCB format)
    └── Positions.csv      # Pick and place file
```

### Manufacturing
Production files are optimized for JLCPCB:
1. Generate Gerber and drill files from KiCad project (`KiCad/` folder)
2. Upload generated Gerber files to JLCPCB
3. Use provided BOM and position files for SMT assembly

### Firmware

Based on the official SlimeVR open-source firmware.  
Original repository: https://github.com/SlimeVR/SlimeVR-Tracker-ESP

This repository contains only the modified files. Clone the original repository first, then apply these changes.

#### Modified Files

| File | Changes |
|------|---------|
| `src/defines.h` | Hardcoded WiFi credentials, battery monitoring disabled, dual sensor config (`SENSOR_DESC_LIST` - 0x69, 0x68), SDO pin control (`PIN_IMU_SDO = 5`) |
| `src/main.cpp` | SDO pin initialization (GPIO5 → HIGH, 200ms delay), WiFi credentials fallback |
| `src/network/wifihandler.cpp` | Hardcoded WiFi credentials (`tryHardcodedCredentials()` function) |
| `src/network/wifihandler.h` | WiFi timeout reduced: 11s → 4s |
| `src/sensors/softfusion/drivers/icm45base.h` | Default I2C address changed: 0x68 → 0x69 |
| `board-defaults.json` | `BOARD_LOLIN_C3_MINI` dual sensor config (Sensor 0: 0x69, Sensor 1: 0x68) |
| `platformio.ini` | Upload flags adjusted (`--after=no_reset`) |

#### Key Features
- ✅ Dual sensor support (I2C address 0x68 + 0x69)
- ✅ Dynamic SDO pin control (GPIO5 for address separation)
- ✅ Improved WiFi stability (timeout adjustment, multiple fallback)
- ✅ Battery monitoring disabled

#### Dual Sensor Setup
When using 2 sensors, **short the INT pin of the secondary tracker to GND**.

#### Build & Flash
1. Install PlatformIO
2. Open `SlimeVR/` folder in VSCode
3. Build and upload to ESP32-C3

#### WiFi Configuration
Edit the following files and replace WiFi credentials:

1. **src/defines.h** (Line 13, 18)
   - Change `WIFI_CREDS_SSID` to your WiFi SSID
   - Change `WIFI_CREDS_PASSWD` to your WiFi password

2. **src/main.cpp** (Line 104, 105)
   - Change `WIFI_CREDS_SSID` to your WiFi SSID  
   - Change `WIFI_CREDS_PASSWD` to your WiFi password

3. **src/network/wifihandler.cpp** (Line 310, 311)
   - Change `HARDCODED_SSID` to your WiFi SSID
   - Change `HARDCODED_PASSWD` to your WiFi password

**Note:** All three locations must match for reliable WiFi connection.

### Power Circuit Measurement
![Power Circuit Comparison](Measurement_Pic/ripple_comparison.jpg)

77mV → 20mV  
From bottom to top: immediately after boost converter, after LC filter, and before final IMU power supply.

### License
- Hardware (PCB, Schematics, 3D files): [MIT License](License/MIT)
- Documentation: [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/)

### Revision History
- **Rev02** (Current): Power circuit, Charging circuit changed
- **Rev01**: Initial design

---

## 한국어

### 개요
커스텀 SlimeVR 트래커입니다.

### 사양
| 항목 | 내용 |
|------|------|
| MCU | ESP32-C3 Super Mini |
| IMU | SlimeVR Mumo Breakout Module V1 (ICM-45686 + QMC6309) |
| 배터리 | 1100mAh Li-Po |
| PCB 크기 | 약 80mm x 30mm |

### 특징
- **전원부 최적화**: 리플 및 노이즈 최소화 (77mV → 20mV)
- **컴팩트 설계**: 2레이어 PCB 기반 간결한 설계
- **양산 대응**: JLCPCB 제조 파일 포함

### 저장소 구조
```
├── 3D/                    # 3D 모델 파일 (STL - 케이스, 마운트 등)
├── Datasheets/            # 부품 데이터시트
├── Demonstration_Video/   # 시연 영상
├── SlimeVR/               # SlimeVR 펌웨어 소스 코드
├── KiCad/                 # KiCad 프로젝트 파일
│   ├── *.kicad_pcb
│   ├── *.kicad_sch
│   └── *.kicad_pro
├── License/               # 라이선스 파일
├── Measurement_Pic/       # 전원부 리플 측정 사진
└── Production/            # 제조용 파일
    ├── BOM.csv            # 부품 목록 (JLCPCB 형식)
    └── Positions.csv      # 부품 배치 파일
```

### 제조 방법
JLCPCB 기준 제조 파일 제공:
1. KiCad 프로젝트(`KiCad/` 폴더)에서 Gerber 및 드릴 파일 생성
2. 생성된 Gerber 파일을 JLCPCB에 업로드
3. 제공된 BOM 및 위치 파일로 SMT 조립 주문

### 펌웨어

SlimeVR 공식 오픈소스 펌웨어를 기반으로 합니다.  
원본 저장소: https://github.com/SlimeVR/SlimeVR-Tracker-ESP

이 저장소에는 수정된 파일만 포함되어 있습니다. 원본 저장소를 먼저 클론한 후 변경사항을 적용하세요.

#### 수정된 파일

| 파일 | 변경 내용 |
|------|----------|
| `src/defines.h` | WiFi 정보 하드코딩, 배터리 모니터링 비활성화, 듀얼 센서 설정 (`SENSOR_DESC_LIST` - 0x69, 0x68), SDO 핀 제어 (`PIN_IMU_SDO = 5`) |
| `src/main.cpp` | SDO 핀 초기화 (GPIO5 → HIGH, 200ms delay), WiFi credentials fallback |
| `src/network/wifihandler.cpp` | WiFi 정보 하드코딩 (`tryHardcodedCredentials()` 함수) |
| `src/network/wifihandler.h` | WiFi 타임아웃 단축: 11초 → 4초 |
| `src/sensors/softfusion/drivers/icm45base.h` | I2C 기본 주소 변경: 0x68 → 0x69 |
| `board-defaults.json` | `BOARD_LOLIN_C3_MINI` 듀얼 센서 설정 (Sensor 0: 0x69, Sensor 1: 0x68) |
| `platformio.ini` | 업로드 플래그 조정 (`--after=no_reset`) |

#### 핵심 기능
- ✅ 듀얼 센서 지원 (I2C 주소 0x68 + 0x69)
- ✅ SDO 핀 동적 제어 (GPIO5로 센서 주소 분리)
- ✅ WiFi 안정성 개선 (타임아웃 조정, 다중 fallback)
- ✅ 배터리 모니터링 비활성화

#### 듀얼 센서 사용 시
센서 2개 사용 시, **보조 트래커의 INT 핀을 GND에 쇼트**시켜 사용하세요.

#### 빌드 및 업로드
1. PlatformIO 설치
2. VSCode에서 `SlimeVR/` 폴더 열기
3. ESP32-C3에 빌드 및 업로드

#### WiFi 설정
아래 파일들에서 WiFi 정보를 수정하세요:

1. **src/defines.h** (13, 18번째 줄)
   - `WIFI_CREDS_SSID`를 본인의 WiFi SSID로 변경
   - `WIFI_CREDS_PASSWD`를 본인의 WiFi 비밀번호로 변경

2. **src/main.cpp** (104, 105번째 줄)
   - `WIFI_CREDS_SSID`를 본인의 WiFi SSID로 변경
   - `WIFI_CREDS_PASSWD`를 본인의 WiFi 비밀번호로 변경

3. **src/network/wifihandler.cpp** (310, 311번째 줄)
   - `HARDCODED_SSID`를 본인의 WiFi SSID로 변경
   - `HARDCODED_PASSWD`를 본인의 WiFi 비밀번호로 변경

**참고:** 세 곳 모두 동일하게 설정해야 WiFi 연결이 정상 작동합니다.

### 전원부 측정
![전원부 비교](Measurement_Pic/ripple_comparison.jpg)

77mV → 20mV  
맨 아래부터 승압 직후, LC필터 이후, 최종 IMU 공급 직전

### 라이선스
- Hardware (PCB, Schematics, 3D files): [MIT License](License/MIT)
- Documentation: [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/)

### 변경 이력
- **Rev02** (현재): 전원부, 충전부 수정
- **Rev01**: 최초 설계

---
