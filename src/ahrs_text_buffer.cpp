#include <algorithm>
#include <sstream>
#include <vector>

#include "ahrs/ahrs.h"
#include "ahrs_viewer/sensor_from_text.h"

namespace txtsens {

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
    auto splits = split_str(readout, ',');

    std::vector<double> numerized(splits.size());
    std::transform(splits.begin(), splits.end(), numerized.begin(),
                   [](const std::string& s) { return std::stod(s); });

    dt = numerized[0];
    gyror = ahrs::sensor_readout{numerized[1], numerized[2], numerized[3]};
    accr = ahrs::sensor_readout{numerized[4], numerized[5], numerized[6]};
    magr = ahrs::sensor_readout{numerized[7], numerized[8], numerized[9]};
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
