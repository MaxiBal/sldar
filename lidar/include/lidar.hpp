#ifndef LIDAR_ROS_PUBLISHER_HPP
#define LIDAR_ROS_PUBLISHER_HPP

#include <cassert>
#include <memory>

#include "sl_lidar.h"

#define BAUDRATE 115200

#ifndef countof
#define countof(_Array) (int)(sizeof(_Array) / sizeof(_Array[0]))
#endif

namespace slamdar {
namespace lidar {

class lidar
{

    std::unique_ptr<sl::ILidarDriver> lidar_;

public:

    lidar(const std::string& lidar_port = "/dev/ttyUSB0") : lidar_(*sl::createLidarDriver())
    {
        auto channel = sl::createSerialPortChannel(lidar_port, BAUDRATE);

        auto res = lidar_->connect(*channel);

        assert(SL_IS_OK(res));
    }

    sl_lidar_response_device_info_t get_device_info()
    {
        sl_lidar_response_device_info_t deviceInfo;
        auto res = lidar_->getDeviceInfo(deviceInfo);

        assert(SL_IS_OK(res));

        return deviceInfo;
    }

    void update_scan(sl_lidar_response_measurement_node_hq_t** buf)
    {
        size_t buf_size = countof(*buf);

        auto res = lidar_->grabScanDataHq(*buf, buf_size);

        assert(SL_IS_OK(res));
    }

};

}
}

#endif