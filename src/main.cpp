#include <iostream>

#include "ahrs_viewer/ahrs_text_buffer.h"
#include "ahrs_viewer/sensor_from_text.h"
#include "ahrs/ahrs.h"

int main() {
    txtsens::AhrsTextBuffer inbuffer{std::cin};
    txtsens::GyroFromText gyro{inbuffer};
    txtsens::AccFromText acc{inbuffer};
    txtsens::MagFromText mag{inbuffer};
	ahrs::Ahrs ahrs{gyro, acc, mag, 1.0};

    while (inbuffer.fetch()) {	
		auto readout = ahrs.update();
		std::cout << "x: " << readout.x << '\n';
		std::cout << "y: " << readout.y << '\n';
		std::cout << "z: " << readout.z << '\n';
    }

    return 0;
}
