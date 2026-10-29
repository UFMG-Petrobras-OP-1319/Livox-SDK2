#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "parse_cfg_file.h"

// The parser uses the SDK's process-global logger. Keep this test independent
// of spdlog's header-only templates while exercising the real parser.
void InitLogger();
void UninitLogger();

int main(int argc, char** argv) {
  if (argc != 3) {
    std::cerr << "usage: test_mid360s_config_parser <config> <expected-type>\n";
    return 2;
  }
  using namespace livox::lidar;
  InitLogger();
  ParseCfgFile parser(argv[1]);
  std::shared_ptr<std::vector<LivoxLidarCfg>> lidars;
  std::shared_ptr<std::vector<LivoxLidarCfg>> custom_lidars;
  std::shared_ptr<LivoxLidarLoggerCfg> logger_cfg;
  std::shared_ptr<LivoxLidarSdkFrameworkCfg> framework_cfg;
  const bool parsed = parser.Parse(lidars, custom_lidars, logger_cfg,
                                   framework_cfg);
  if (!parsed) {
    std::cerr << "configuration parse failed: " << argv[1] << '\n';
    UninitLogger();
    return 1;
  }
  if (!lidars || !custom_lidars ||
      lidars->size() + custom_lidars->size() != 1) {
    std::cerr << "expected exactly one configured lidar\n";
    UninitLogger();
    return 1;
  }
  const auto& cfg = lidars->empty() ? custom_lidars->front() : lidars->front();
  const int expected_type = std::atoi(argv[2]);
  if (cfg.device_type != expected_type ||
      cfg.lidar_net_info.cmd_data_port != 56100 ||
      cfg.lidar_net_info.push_msg_port != 56200 ||
      cfg.lidar_net_info.point_data_port != 56300 ||
      cfg.lidar_net_info.imu_data_port != 56400 ||
      cfg.lidar_net_info.log_data_port != 56500 ||
      cfg.host_net_info.host_ip != "192.168.1.5" ||
      cfg.host_net_info.cmd_data_port != 56101 ||
      cfg.host_net_info.push_msg_port != 56201 ||
      cfg.host_net_info.point_data_port != 56301 ||
      cfg.host_net_info.imu_data_port != 56401 ||
      cfg.host_net_info.log_data_port != 56501) {
    std::cerr << "parsed model or host/device network fields were incorrect\n";
    UninitLogger();
    return 1;
  }
  UninitLogger();
  return 0;
}
