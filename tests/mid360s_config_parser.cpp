#include <cassert>
#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

#include "parse_cfg_file.h"

int main(int argc, char** argv) {
  assert(argc == 3);
  using namespace livox::lidar;
  ParseCfgFile parser(argv[1]);
  std::shared_ptr<std::vector<LivoxLidarCfg>> lidars;
  std::shared_ptr<std::vector<LivoxLidarCfg>> custom_lidars;
  std::shared_ptr<LivoxLidarLoggerCfg> logger_cfg;
  std::shared_ptr<LivoxLidarSdkFrameworkCfg> framework_cfg;
  assert(parser.Parse(lidars, custom_lidars, logger_cfg, framework_cfg));
  assert(lidars && custom_lidars);
  assert(lidars->size() + custom_lidars->size() == 1);
  const auto& cfg = lidars->empty() ? custom_lidars->front() : lidars->front();
  assert(cfg.device_type == std::atoi(argv[2]));
  assert(cfg.lidar_net_info.cmd_data_port == 56100);
  assert(cfg.lidar_net_info.push_msg_port == 56200);
  assert(cfg.lidar_net_info.point_data_port == 56300);
  assert(cfg.lidar_net_info.imu_data_port == 56400);
  assert(cfg.lidar_net_info.log_data_port == 56500);
  assert(cfg.host_net_info.host_ip == "192.168.1.5");
  assert(cfg.host_net_info.cmd_data_port == 56101);
  assert(cfg.host_net_info.push_msg_port == 56201);
  assert(cfg.host_net_info.point_data_port == 56301);
  assert(cfg.host_net_info.imu_data_port == 56401);
  assert(cfg.host_net_info.log_data_port == 56501);
  return 0;
}
