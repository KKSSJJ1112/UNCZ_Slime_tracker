# Slime Tracker Rev02

[English](#english) | [한국어](#한국어)

---

## English

### Overview
Custom SlimeVR tracker with optimized power circuit design for reduced ripple and noise.

### Specifications
| Item | Description |
|------|-------------|
| MCU | ESP32-C3 Super Mini |
| IMU | SlimeVR Mumo Breakout Module V1 (ICM-45686 + QMC6309) |
| Battery | 1100mAh Li-Po |
| PCB Size | ~80mm x 30mm |

### Features
- **Optimized Power Circuit**: Minimized ripple and noise compared to standard designs
- **Compact Form Factor**: Streamlined 2-layer PCB design
- **Production Ready**: Includes JLCPCB manufacturing files

### Repository Structure
```
├── 3D/                    # 3D model files (case, mount, etc.)
├── Datasheets/            # Component datasheets
├── KiCad/                 # KiCad project files
│   ├── *.kicad_pcb
│   ├── *.kicad_sch
│   └── *.kicad_pro
└── Production/            # Manufacturing files
    ├── BOM.csv            # Bill of Materials (JLCPCB format)
    ├── PartList.csv       # Component list
    └── Positions.csv      # Pick and place file
```

### Manufacturing
Production files are optimized for JLCPCB:
1. Upload Gerber files from `Production/` folder
2. Use provided BOM and position files for SMT assembly

### Power Circuit Comparison
<!-- Add your oscilloscope comparison images here -->
*Ripple and noise measurement comparison coming soon*

### License
TBD

### Revision History
- **Rev02** (Current): Power circuit optimization, noise reduction
- **Rev01**: Initial design

---

## 한국어

### 개요
전원부 리플 및 노이즈 최소화를 달성한 커스텀 SlimeVR 트래커입니다.

### 사양
| 항목 | 내용 |
|------|------|
| MCU | ESP32-C3 Super Mini |
| IMU | SlimeVR Mumo Breakout Module V1 (ICM-45686 + QMC6309) |
| 배터리 | 1100mAh Li-Po |
| PCB 크기 | 약 80mm x 30mm |

### 특징
- **전원부 최적화**: 기존 설계 대비 리플 및 노이즈 최소화
- **컴팩트 설계**: 2레이어 PCB 기반 간결한 설계
- **양산 대응**: JLCPCB 제조 파일 포함

### 저장소 구조
```
├── 3D/                    # 3D 모델 파일 (케이스, 마운트 등)
├── Datasheets/            # 부품 데이터시트
├── KiCad/                 # KiCad 프로젝트 파일
│   ├── *.kicad_pcb
│   ├── *.kicad_sch
│   └── *.kicad_pro
└── Production/            # 제조용 파일
    ├── BOM.csv            # 부품 목록 (JLCPCB 형식)
    ├── PartList.csv       # 파트 리스트
    └── Positions.csv      # 부품 배치 파일
```

### 제조 방법
JLCPCB 기준 제조 파일 제공:
1. `Production/` 폴더의 거버 파일 업로드
2. 제공된 BOM 및 위치 파일로 SMT 조립 주문

### 전원부 비교
<!-- 오실로스코프 비교 이미지 추가 예정 -->
*리플 및 노이즈 측정 비교 이미지 추가 예정*

### 라이선스
미정

### 변경 이력
- **Rev02** (현재): 전원부 최적화, 노이즈 저감
- **Rev01**: 최초 설계

---

## Contact
For questions or suggestions, please open an issue.
