// This program logs telemetry, with a timestamp, to standard output (which can
// be redirected to a file).

#include <iostream>
#include <backward/strstream>
#include <fstream>

#include "format.h"
#include "xbee_telemetry_client.h"
#include "xbee_known_types.h"
#include "airdata_sample.h"

constexpr unsigned int AIRDATA_BUF_LEN = 1024;
char airdata_buf[AIRDATA_BUF_LEN];

int main(int argc, char **argv) {
  // TODO: Not a good idea to directly pass enum values as an integer.
  const airball::xbee_known_types::xbee_type type =
      (airball::xbee_known_types::xbee_type)
          std::stoi(argv[1], nullptr, 10);
  auto device = std::string(argv[2]);

  airball::XbeeTelemetryClient telemetry_client(type, device);

  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wmissing-noreturn"

  for (;;) {
    std::unique_ptr<sample> sample = telemetry_client.get();
    auto ads = dynamic_cast<airdata_sample*>(sample.get());
    if (ads != nullptr) {
      ads->snprintf(airdata_buf, AIRDATA_BUF_LEN);
      std::cout << airdata_buf << std::endl;
    }
  }

  #pragma clang diagnostic pop

  return 0;
}
