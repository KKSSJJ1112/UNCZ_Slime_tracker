<h2 align="center">🚧 開発中 / 개발중 / Under Development 🚧</h2>

---

# UNCZ SlimeVR Tracker

[🇯🇵 日本語](#日本語) | [🇰🇷 한국어](#한국어) | [🇺🇸 English](#english)

<p align="center">
  <!-- 実演GIF / 실연 GIF / Demo GIF -->
  <img src="pic/demo.gif" alt="Demo" width="600"/>
</p>

---

## 日本語

### 1. 概要

UNCZ SlimeVR Tracker は SlimeVR エコシステム互換のカスタム IMU トラッカーボードである。ESP32-C3 を中心に IMU・磁気センサ・バッテリー充電・昇降圧 DC-DC を 1 枚に統合し、USB-C 1 ポートで充電とファームウェア書き込みを兼ねる構成となっている。

- ボードサイズ: **約 50mm × 35mm**
- 電源: 1 セル Li-ion / Li-Po **1100mAh**
- 通信: Wi-Fi (ESP32-C3 内蔵)
- 充電/通信: USB-C 単一ポート
- 4 層 PCB 設計

### 2. 使用 IC 一覧

| 役割 | 型番 | 主な仕様 |
|------|------|----------|
| MCU | ESP32-C3-MINI-1-H4X | RISC-V, Wi-Fi/BLE, 内蔵アンテナ |
| 昇降圧 DC-DC | TPS63802DSGR | Iq 11µA, EN ピン制御 |
| 充電 IC | BQ24232HRGTR | パワーパス内蔵, OVP 28V |
| IMU | LSM6DSV16XTR | 6 軸, I²C 0x6B |
| 磁気センサ | QMC6309 | 3 軸, I²C 0x7C (オプション実装) |
| USB データ TVS | USBLC6-2SC6 | D+/D- ESD 保護 |
| バッテリー | 1100mAh 1S Li-ion/Li-Po | 公称 3.7V |

### 3. 出力 CLC フィルタ

TPS63802 の出力リップル抑制のため、共振周波数 **約 1.4MHz** をターゲットとした CLC フィルタを実装している。

**フィルタ構成**
- C1 (前段): **10µF**
- L: **1µH**
- C2 (後段): **10µF**
- 共振周波数: f₀ = 1 / (2π√(LC)) ≈ 1.59MHz (C 並列換算)

**スナバ・ダンピング**
LC 共振による Q 値スパイクを抑えるため、後段に並列スナバを配置。
- ダンピング抵抗: **1Ω 抵抗 × 3 個並列 = 0.33Ω**
- スナバ容量: **22µF × 3 個並列 = 66µF**

この構成によりフィルタの Q 値を適切に下げ、過渡応答時のリンギングを抑制している。

<p align="center">
  <!-- LTspice シミュレーション画像 -->
  <img src="pic/ltspice_simulation.png" alt="LTspice Simulation" width="600"/>
</p>

### 4. ファイル構成

| フォルダ | 内容 |
|----------|------|
| `pic/` | 測定写真、実演 GIF |
| `EASY_EDA_PRO/` | EasyEDA Pro プロジェクトファイル、ライブラリファイル |
| `JLC_PCB/` | ガーバーファイル、BOM、Pick & Place ファイル |
| `Datasheet/` | 使用部品のデータシート |
| `Firmware/` | SlimeVR オープンソースベースのファームウェア |
| `License/` | ライセンスファイル |

### 5. ファームウェア

本プロジェクトのファームウェアに関するすべての部分は **[SlimeVR オープンソースプロジェクト](https://github.com/SlimeVR/SlimeVR-Tracker-ESP)** に準拠する。

### 6. リビジョン履歴

| Rev | 内容 |
|-----|------|
| REV1 | モジュールベースの拡張ボード設計 |
| REV5 | チップベースの再設計 (現行) |

### 7. ライセンス

- **ハードウェア (PCB, 回路図, 3D ファイル)**: [MIT License](https://github.com/KKSSJJ1112/UNCZ_Slime_tracker/blob/main/License/MIT)
- **ドキュメント**: [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/)

---

## 한국어

### 1. 개요

UNCZ SlimeVR Tracker는 SlimeVR 생태계와 호환되는 커스텀 IMU 트래커 보드입니다. ESP32-C3를 중심으로 IMU, 자력계, 배터리 충전 회로, 벅부스트 DC-DC를 한 장의 PCB에 통합했으며, 단일 USB-C 포트로 충전과 펌웨어 장입을 모두 처리합니다.

- 보드 사이즈: **약 50mm × 35mm**
- 전원: 1셀 Li-ion / Li-Po **1100mAh**
- 통신: Wi-Fi (ESP32-C3 내장)
- 충전/통신: USB-C 단일 포트
- 4레이어 PCB 설계

### 2. 사용 IC 목록

| 역할 | 부품 | 주요 사양 |
|------|------|-----------|
| MCU | ESP32-C3-MINI-1-H4X | RISC-V, Wi-Fi/BLE, 내장 안테나 |
| 벅부스트 DC-DC | TPS63802DSGR | Iq 11µA, EN 핀 제어 |
| 충전 IC | BQ24232HRGTR | 파워패스 내장, OVP 28V |
| IMU | LSM6DSV16XTR | 6축, I²C 0x6B |
| 자력계 | QMC6309 | 3축, I²C 0x7C (옵션 실장) |
| USB 데이터 TVS | USBLC6-2SC6 | D+/D- ESD 보호 |
| 배터리 | 1100mAh 1S Li-ion/Li-Po | 공칭 3.7V |

### 3. 출력 CLC 필터

TPS63802 출력 리플 억제를 위해 공진 주파수 **약 1.4MHz**를 타겟으로 한 CLC 필터를 구성했습니다.

**필터 구성**
- C1 (전단): **10µF**
- L: **1µH**
- C2 (후단): **10µF**
- 공진 주파수: f₀ = 1 / (2π√(LC)) ≈ 1.59MHz (C 병렬 환산)

**스너버 댐핑**
LC 공진으로 인한 Q값 스파이크를 억제하기 위해 후단에 병렬 스너버를 배치하여 의도적으로 Q값을 조정했습니다.
- 댐핑 저항: **1Ω 저항 3개 병렬 = 0.33Ω**
- 스너버 커패시터: **22µF 3개 병렬 = 66µF**

이 구성으로 필터의 Q값을 적절히 낮춰 과도 응답 시 링잉을 억제합니다.

<p align="center">
  <!-- LTspice 시뮬레이션 이미지 -->
  <img src="pic/ltspice_simulation.png" alt="LTspice Simulation" width="600"/>
</p>

### 4. 파일 구성

| 폴더 | 내용 |
|------|------|
| `pic/` | 측정 사진, 실연 GIF |
| `EASY_EDA_PRO/` | EasyEDA Pro 프로젝트 파일, 라이브러리 파일 |
| `JLC_PCB/` | 거버 파일, BOM, Pick & Place 파일 |
| `Datasheet/` | 사용 부품 데이터시트 |
| `Firmware/` | SlimeVR 오픈소스 기반 펌웨어 |
| `License/` | 라이센스 파일 |

### 5. 펌웨어

본 프로젝트의 펌웨어와 관련된 모든 부분은 **[SlimeVR 오픈소스 프로젝트](https://github.com/SlimeVR/SlimeVR-Tracker-ESP)** 를 따릅니다.

### 6. 리비전 히스토리

| Rev | 내용 |
|-----|------|
| REV1 | 모듈 기반의 확장 보드 설계 |
| REV5 | 칩 기반의 재설계 (현행) |

### 7. 라이센스

- **하드웨어 (PCB, 회로도, 3D 파일)**: [MIT License](https://github.com/KKSSJJ1112/UNCZ_Slime_tracker/blob/main/License/MIT)
- **문서**: [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/)

---

## English

### 1. Overview

The UNCZ SlimeVR Tracker is a custom IMU tracker board compatible with the SlimeVR ecosystem. Built around the ESP32-C3, it integrates an IMU, magnetometer, battery charger, and buck-boost DC-DC converter onto a single PCB, with a single USB-C port handling both charging and firmware upload.

- Board size: **~50mm × 35mm**
- Power: 1-cell Li-ion / Li-Po **1100mAh**
- Communication: Wi-Fi (ESP32-C3 built-in)
- Charging/Communication: Single USB-C port
- 4-layer PCB design

### 2. IC List

| Role | Part | Key Specs |
|------|------|-----------|
| MCU | ESP32-C3-MINI-1-H4X | RISC-V, Wi-Fi/BLE, built-in antenna |
| Buck-Boost DC-DC | TPS63802DSGR | Iq 11µA, EN pin control |
| Charger IC | BQ24232HRGTR | Power path built-in, OVP 28V |
| IMU | LSM6DSV16XTR | 6-axis, I²C 0x6B |
| Magnetometer | QMC6309 | 3-axis, I²C 0x7C (optional) |
| USB Data TVS | USBLC6-2SC6 | D+/D- ESD protection |
| Battery | 1100mAh 1S Li-ion/Li-Po | Nominal 3.7V |

### 3. Output CLC Filter

A CLC filter targeting a resonant frequency of **~1.4MHz** is implemented to suppress output ripple from the TPS63802.

**Filter Configuration**
- C1 (front): **10µF**
- L: **1µH**
- C2 (rear): **10µF**
- Resonant frequency: f₀ = 1 / (2π√(LC)) ≈ 1.59MHz (with parallel C)

**Snubber Damping**
To suppress the Q-factor spike caused by LC resonance, a parallel snubber is placed at the rear stage, intentionally tuning the Q-factor.
- Damping resistor: **1Ω × 3 in parallel = 0.33Ω**
- Snubber capacitor: **22µF × 3 in parallel = 66µF**

This configuration appropriately lowers the filter's Q-factor, suppressing ringing during transient response.

<p align="center">
  <!-- LTspice simulation image -->
  <img src="pic/ltspice_simulation.png" alt="LTspice Simulation" width="600"/>
</p>

### 4. File Structure

| Folder | Contents |
|--------|----------|
| `pic/` | Measurement photos, demo GIFs |
| `EASY_EDA_PRO/` | EasyEDA Pro project files, library files |
| `JLC_PCB/` | Gerber files, BOM, Pick & Place files |
| `Datasheet/` | Datasheets of used components |
| `Firmware/` | SlimeVR open-source-based firmware |
| `License/` | License files |

### 5. Firmware

All firmware-related portions of this project follow the **[SlimeVR open-source project](https://github.com/SlimeVR/SlimeVR-Tracker-ESP)**.

### 6. Revision History

| Rev | Description |
|-----|-------------|
| REV1 | Module-based expansion board design |
| REV5 | Chip-based redesign (current) |

### 7. License

- **Hardware (PCB, Schematics, 3D files)**: [MIT License](https://github.com/KKSSJJ1112/UNCZ_Slime_tracker/blob/main/License/MIT)
- **Documentation**: [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/)
