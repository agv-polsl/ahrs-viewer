#ifndef SENSOR_FROM_TEXT_H
#define SENSOR_FROM_TEXT_H

#include "ahrs/ahrs_sensors.h"
#include "ahrs_viewer/ahrs_text_buffer.h"

namespace txtsens {

class SensorFromText : ahrs::Sensor {
   public:
    SensorFromText(AhrsTextBuffer& buffer) : buffer{buffer} {}

   protected:
    AhrsTextBuffer& buffer;
};

class GyroFromText : SensorFromText {
   ahrs::sensor_readout read() override { return buffer.get_gyro_readout(); }
};
class AccFromText : SensorFromText {
   ahrs::sensor_readout read() override { return buffer.get_acc_readout(); }
};
class MagFromText : SensorFromText {
   ahrs::sensor_readout read() override { return buffer.get_mag_readout(); }
};

}  // namespace txtsens

#endif
