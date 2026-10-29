#include <cassert>

#include "livox_lidar_api.h"

int main() {
  LivoxLidarSdkVer version{};
  GetLivoxLidarSdkVer(&version);
  assert(version.major == 1);
  assert(version.minor == 3);
  assert(version.patch == 1);

  // Link-time references guard the newly exported API symbols without sending
  // configuration commands to hardware.
  auto esc_mode_api = &SetLivoxLidarEscMode;
  auto pps_mode_api = &SetLivoxLidarPpsSyncMode;
  (void)esc_mode_api;
  (void)pps_mode_api;
  return 0;
}
