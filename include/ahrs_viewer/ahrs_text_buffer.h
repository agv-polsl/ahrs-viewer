#ifndef AHRS_TEXT_BUFFER_H
#define AHRS_TEXT_BUFFER_H

#include <fstream>
#include <iostream>

#include "ahrs/ahrs_sensors.h"

namespace txtsens {

class AhrsTextBuffer {
   public:
    AhrsTextBuffer(std::istream& is) : input{is} {}
    bool fetch();
    ahrs::sensor_readout get_gyro_readout();
    ahrs::sensor_readout get_acc_readout();
    ahrs::sensor_readout get_mag_readout();

   private:
    void parse_readout(std::string readout);

    std::istream& input;
    ahrs::sensor_readout gyror;
    ahrs::sensor_readout accr;
    ahrs::sensor_readout magr;
};

}  // namespace txtsens

#endif
