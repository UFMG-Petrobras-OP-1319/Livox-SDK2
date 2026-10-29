#include <dlfcn.h>
#include <iostream>

#include "livox_lidar_api.h"

int main() {
  LivoxLidarSdkVer version{};
  GetLivoxLidarSdkVer(&version);
  if (version.major != 1 || version.minor != 3 || version.patch != 1) {
    std::cerr << "expected SDK version 1.3.1, got " << version.major << '.'
              << version.minor << '.' << version.patch << '\n';
    return 1;
  }

  // Check the loaded shared object at runtime without sending device commands.
  if (dlsym(RTLD_DEFAULT, "SetLivoxLidarEscMode") == nullptr ||
      dlsym(RTLD_DEFAULT, "SetLivoxLidarPpsSyncMode") == nullptr) {
    std::cerr << "expected ESC and PPS API symbols in the loaded SDK\n";
    return 1;
  }
  return 0;
}
