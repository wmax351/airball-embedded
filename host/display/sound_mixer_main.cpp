#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>

#include "sound_mixer.h"
#include "sine_layer.h"
#include "pwm_layer.h"
#include "balance_layer.h"

int main(int argc, char**argv) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <device-name>" << std::endl;
    return -1;
  }

  airball::sound_mixer m(argv[1]);

  if (!m.start()) {
    std::cout << "Error" << std::endl;
    return -1;
  }

  std::cout << "actual_rate = " << m.actual_rate() << std::endl;
  std::cout << "actual_period_size = " << m.actual_period_size() << std::endl;

  airball::sine_layer tone(m.frequency_to_period(432));
  airball::balance_layer bounce(1.0, 1.0, m.seconds_to_frames(0.05));
  airball::pwm_layer dit(
      m.frequency_to_period(10),
      m.frequency_to_period(20) / 2,
      m.seconds_to_frames(0.01));

  std::vector<airball::sound_layer*> layers;
  layers.push_back(&tone);
  layers.push_back(&bounce);
  layers.push_back(&dit);

  m.set_layers(layers);

  int period = 500;

  for (int i = 0; i < period; i++) {
    double phase_angle = ((double) i / (double) period * 20) * M_PI * 2.0;
    bounce.set_gains(sin(phase_angle), cos(phase_angle));
    tone.set_period(m.frequency_to_period(440 + i));
    size_t p = m.frequency_to_period(3 + (i / 25));
    dit.set_parameters(p,p / 2,m.seconds_to_frames(0.01));
    std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(100));
  }

  return 0;
}
