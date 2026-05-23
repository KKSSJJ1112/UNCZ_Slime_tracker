/*
    SlimeVR Code is placed under the MIT license
    Copyright (c) 2021 Eiren Rain & SlimeVR contributors
*/

#include <i2cscan.h>
#include "GlobalVars.h"
#include "Wire.h"
#include "batterymonitor.h"
#include "credentials.h"
#include "debugging/TimeTaken.h"
#include "globals.h"
#include "logging/Logger.h"
#include "ota.h"
#include "serial/serialcommands.h"
#include "status/TPSCounter.h"

Timer<> globalTimer;
SlimeVR::Logging::Logger logger("SlimeVR");
SlimeVR::Sensors::SensorManager sensorManager;
SlimeVR::LEDManager ledManager;
SlimeVR::Status::StatusManager statusManager;
SlimeVR::Configuration::Configuration configuration;
SlimeVR::Network::Manager networkManager;
SlimeVR::Network::Connection networkConnection;
SlimeVR::WiFiNetwork wifiNetwork;
SlimeVR::WifiProvisioning wifiProvisioning;

#if DEBUG_MEASURE_SENSOR_TIME_TAKEN
SlimeVR::Debugging::TimeTakenMeasurer sensorMeasurer{"Sensors"};
#endif

int sensorToCalibrate = -1;
bool blinking = false;
unsigned long blinkStart = 0;
unsigned long loopTime = 0;
unsigned long lastStatePrint = 0;
bool secondImuActive = false;
BatteryMonitor battery;
TPSCounter tpsCounter;

void setup() {
    // 시리얼 통신 시작 (USB CDC On Boot 설정이 중요)
    Serial.begin(serialBaudRate);
    globalTimer = timer_create_default();

    Serial.println();
    Serial.println();
    Serial.println();

    logger.info("SlimeVR v" FIRMWARE_VERSION " starting up...");

    char vendorBuffer[512];
    size_t writtenLength;

    if (strlen(VENDOR_URL) == 0) {
        sprintf(vendorBuffer, "Vendor: %s, product: %s%n", VENDOR_NAME, PRODUCT_NAME, &writtenLength);
    } else {
        sprintf(vendorBuffer, "Vendor: %s (%s), product: %s%n", VENDOR_NAME, VENDOR_URL, PRODUCT_NAME, &writtenLength);
    }

    if (strlen(UPDATE_ADDRESS) > 0 && strlen(UPDATE_NAME) > 0) {
        sprintf(vendorBuffer + writtenLength, ", firmware update url: %s, name: %s", UPDATE_ADDRESS, UPDATE_NAME);
    }
    logger.info("%s", vendorBuffer);

    statusManager.setStatus(SlimeVR::Status::LOADING, true);

    // [최우선] SDO 핀을 먼저 설정 (센서 주소 충돌 방지)
#ifdef PIN_IMU_SDO
    pinMode(PIN_IMU_SDO, OUTPUT);
    digitalWrite(PIN_IMU_SDO, HIGH);
    delay(200); // 충분한 안정화 시간 (USB 미연결 시에도 안정적)
    logger.info("GPIO%d (SDO) set to HIGH for dual sensor setup", PIN_IMU_SDO);
#endif

    ledManager.setup();
    configuration.setup();

    SerialCommands::setUp();

    auto clearResult = I2CSCAN::clearBus(PIN_IMU_SDA, PIN_IMU_SCL);
    if (clearResult != 0) {
        logger.warn("Can't clear I2C bus, error %d", clearResult);
    }

#ifdef ESP32
    Wire.end();
#endif
    Wire.begin(static_cast<int>(PIN_IMU_SDA), static_cast<int>(PIN_IMU_SCL));
#ifdef ESP32
    Wire.setTimeOut(150);
#endif
    Wire.setClock(I2C_SPEED);

    // IMU 부팅을 위한 대기
    delay(500);

    // [핵심] sensorManager.setup() 내부에서 SPI 초기화가 진행됩니다.
    sensorManager.setup();

    // WiFi credentials 강제 설정 (빌드 캐시 문제 우회)
    #ifndef WIFI_CREDS_SSID
    #define WIFI_CREDS_SSID "your-ssid"
    #define WIFI_CREDS_PASSWD "your-password"
    #endif
    logger.info("WiFi credentials: SSID='%s', Pass length=%d", WIFI_CREDS_SSID, strlen(WIFI_CREDS_PASSWD));

    networkManager.setup();
    OTA::otaSetup(otaPassword);
    battery.Setup();

    statusManager.setStatus(SlimeVR::Status::LOADING, false);

    sensorManager.postSetup();

    loopTime = micros();
    tpsCounter.reset();
}

void loop() {
    tpsCounter.update();
    globalTimer.tick();
    SerialCommands::update();
    OTA::otaUpdate();
    networkManager.update();

#if DEBUG_MEASURE_SENSOR_TIME_TAKEN
    sensorMeasurer.before();
#endif
    sensorManager.update();
#if DEBUG_MEASURE_SENSOR_TIME_TAKEN
    sensorMeasurer.after();
#endif

    battery.Loop();
    ledManager.update();
    
    // [수정] I2C 스캔 업데이트 비활성화
    // I2CSCAN::update();

#ifdef TARGET_LOOPTIME_MICROS
    long elapsed = (micros() - loopTime);
    if (elapsed < TARGET_LOOPTIME_MICROS) {
        long sleepus = TARGET_LOOPTIME_MICROS - elapsed - 100;
        long sleepms = sleepus / 1000;
        if (sleepms > 0) {
            delay(sleepms);
            sleepus -= sleepms * 1000;
        }
        if (sleepus > 100) {
            delayMicroseconds(sleepus);
        }
    }
    loopTime = micros();
#endif

#if defined(PRINT_STATE_EVERY_MS) && PRINT_STATE_EVERY_MS > 0
    unsigned long now = millis();
    if (lastStatePrint + PRINT_STATE_EVERY_MS < now) {
        lastStatePrint = now;
        SerialCommands::printState();
    }
#endif
}