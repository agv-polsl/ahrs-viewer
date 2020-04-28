#include <iostream>

#include "ahrs/ahrs.h"
#include "ahrs_viewer/ahrs_text_buffer.h"
#include "ahrs_viewer/sensor_from_text.h"

int main() {
    txtsens::AhrsTextBuffer inbuffer{std::cin};
    txtsens::GyroFromText gyro{inbuffer};
    txtsens::AccFromText acc{inbuffer};
    txtsens::MagFromText mag{inbuffer};
    ahrs::Ahrs ahrs{gyro, acc, mag, 1.0};

    while (inbuffer.fetch()) {
        ahrs.set_dt(inbuffer.get_dt());
        auto readout = ahrs.update();
        std::cout << "x: " << readout.x << '\t';
        std::cout << "y: " << readout.y << '\t';
        std::cout << "z: " << readout.z << '\n';
    }

    return 0;
}
