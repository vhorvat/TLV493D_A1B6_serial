#include "TLx493D_inc.hpp"

using namespace ifx::tlx493d;

const uint8_t POWER_PIN = 15; 

TLx493D_A1B6 dut(Wire, TLx493D_IIC_ADDR_A0_e);
char buffer[64];

void setup() {
    Serial.begin(115200);
    delay(3000);

    dut.setPowerPin(POWER_PIN, OUTPUT, INPUT, HIGH, LOW, 0, 250000);
    dut.begin();

    Serial.print("setup done.\n");
}


void loop() {
    double t, x, y, z;
    dut.getMagneticFieldAndTemperature(&x, &y, &z, &t);
    sprintf(buffer, "%d,%d,%d\n", (int)(x * 1000), (int)(y * 1000), (int)(z * 1000));
    Serial.print(buffer);
    delay(10);

}
