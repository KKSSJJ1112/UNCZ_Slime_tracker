// defines.h - 최소 필수 정의만 포함 (I2C 모드)

// 배터리 모니터링 비활성화
#ifdef BATTERY_MONITOR
#undef BATTERY_MONITOR
#endif
// BATTERY_MONITOR를 정의하지 않음 = 비활성화

// WiFi 설정 - 강제 하드코딩
#ifdef WIFI_CREDS_SSID
#undef WIFI_CREDS_SSID
#endif
#define WIFI_CREDS_SSID "----"

#ifdef WIFI_CREDS_PASSWD
#undef WIFI_CREDS_PASSWD
#endif
#define WIFI_CREDS_PASSWD "----"

#ifndef IMU
#define IMU IMU_ICM45686
#endif

#ifndef IMU_ROTATION
#define IMU_ROTATION DEG_270
#endif

#ifndef SECOND_IMU_ROTATION
#define SECOND_IMU_ROTATION DEG_270
#endif

#ifndef PRIMARY_IMU_OPTIONAL
#define PRIMARY_IMU_OPTIONAL false
#endif

#ifndef SECONDARY_IMU_OPTIONAL
#define SECONDARY_IMU_OPTIONAL true
#endif

// 센서 설정 리스트 (2개 센서: 0x69 메인, 0x68 서브)
#ifndef SENSOR_DESC_LIST
#define SENSOR_DESC_LIST \
    SENSOR_DESC_ENTRY(IMU_ICM45686, 105, DEG_270, DIRECT_WIRE(4, 6), false, DIRECT_PIN(7), 0) \
    SENSOR_DESC_ENTRY(IMU_ICM45686, 104, DEG_270, DIRECT_WIRE(4, 6), true, DIRECT_PIN(255), 0)
#endif

// SDO 핀 제어 (Sensor 1을 0x69로 설정)
#ifndef PIN_IMU_SDO
#define PIN_IMU_SDO 5
#endif
