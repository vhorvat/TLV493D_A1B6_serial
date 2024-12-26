#include "TLx493D_inc.hpp"

using namespace ifx::tlx493d;

const uint8_t POWER_PIN = 15; 

TLx493D_A1B6 dut(Wire, TLx493D_IIC_ADDR_A0_e);

const int CALIBRATION_READINGS = 50; 
double xOffset = 0.0, yOffset = 0.0, zOffset = 0.0, tOffset = 0.0; 
bool isCalibrated = false; 

void setup() {
    Serial.begin(115200);
    delay(3000);

    dut.setPowerPin(POWER_PIN, OUTPUT, INPUT, HIGH, LOW, 0, 250000);
    dut.begin();
    dut.setDefaultConfig();

    Serial.print("Setup done.\n");

    Serial.println("Calibrating sensor...");
    double t, x, y, z;
    for (int i = 0; i < CALIBRATION_READINGS; i++) {
        dut.getMagneticFieldAndTemperature(&x, &y, &z, &t);
        xOffset += x;
        yOffset += y;
        zOffset += z;
        delay(100); 
    }

    xOffset /= CALIBRATION_READINGS;
    yOffset /= CALIBRATION_READINGS;
    zOffset /= CALIBRATION_READINGS;

    Serial.println("Calibration complete.");
    isCalibrated = true;
}


void loop() {
    if (!isCalibrated) {
        return;
    }

    double t, x, y, z;
    dut.getMagneticFieldAndTemperature(&x, &y, &z, &t);

    x -= xOffset;
    y -= yOffset;
    z -= zOffset;

    Serial.print("x:(");
    Serial.print((int)(x * 1000));
    Serial.print(" µT), y:(");
    Serial.print((int)(y * 1000));
    Serial.print(" µT), z:(");
    Serial.print((int)(z * 1000));
    Serial.print(" µT), t:(");
    Serial.print(t);
    Serial.println("°C)");

}
