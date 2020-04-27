#include <algorithm>
#include <cmath>
#include <sstream>
#include <vector>

#include "ahrs/ahrs.h"
#include "ahrs_viewer/sensor_from_text.h"

namespace txtsens {

double to_rad(double deg) { return deg * M_PI / 180; }

std::vector<std::string> split_str(const std::string& str, const char delim) {
    std::vector<std::string> ret;
    std::string sub;
    std::stringstream ss{str};

    while (std::getline(ss, sub, delim)) {
        ret.push_back(sub);
    }

    return ret;
}

void AhrsTextBuffer::parse_readout(std::string readout) {
    enum csv_pos : size_t {
        dt_p = 0, accx_p, accy_p, accz_p,
        gyrox_p, gyroy_p, gyroz_p,
        magx_p, magy_p, magz_p
    };

    auto splits = split_str(readout, ',');
    std::vector<double> numerized(splits.size());

    std::transform(splits.begin(), splits.end(), numerized.begin(),
                   [](const std::string& s) { return std::stod(s); });
    std::transform(numerized.begin() + gyrox_p, numerized.begin() + gyroz_p + 1,
                   numerized.begin() + gyrox_p,
                   [](const double d) { return to_rad(d); });

    dt = numerized[dt_p];
    accr = ahrs::sensor_readout{numerized[accx_p], numerized[accy_p],
                                numerized[accz_p]};
    gyror = ahrs::sensor_readout{numerized[gyrox_p], numerized[gyroy_p],
                                 numerized[gyroz_p]};
    magr = ahrs::sensor_readout{numerized[magx_p], numerized[magy_p],
                                numerized[magz_p]};
}

bool AhrsTextBuffer::fetch() {
    std::string readout;
    if (!std::getline(input, readout)) {
        return false;
    }

    parse_readout(readout);
    return true;
}

ahrs::sensor_readout AhrsTextBuffer::get_gyro_readout() { return gyror; }
ahrs::sensor_readout AhrsTextBuffer::get_acc_readout() { return accr; }
ahrs::sensor_readout AhrsTextBuffer::get_mag_readout() { return magr; }

}  // namespace txtsens
