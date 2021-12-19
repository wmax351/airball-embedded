#include <algorithm>
#include "pwm_layer.h"

namespace airball {

pwm_layer::pwm_layer(snd_pcm_uframes_t period, snd_pcm_uframes_t on_period, snd_pcm_uframes_t fade_period)
    : sound_layer(period),
      on_period_(std::min(on_period, period)),
      fade_period_(std::min(fade_period, (period - on_period) / 2)) {}

double pwm_layer::factor(snd_pcm_uframes_t k) const {
  k %= period();
  if (k < on_period_) {
    // Initial "on" period
    return 1.0;
  }
  if (k < (on_period_ + fade_period_)) {
    // Fade out
    return (double) ((on_period_ + fade_period_) - k) / (double) fade_period_;
  }
  if (k < (period() - fade_period_)) {
    // Next "off" period
    return 0.0;
  }
  // Fade in
  return (double) (k - (period() - fade_period_)) / (double) fade_period_;
}

void pwm_layer::apply(int16_t* buf, snd_pcm_uframes_t frames, snd_pcm_uframes_t pos) const {
  for (size_t i = 0; i < frames; i++) {
    double f = factor(pos);
    for (int j = 0; j < 2; j++) {
      *buf = (int16_t) ((double) *buf * f);
      buf++;
    }
    pos++;
  }
}

} // namespace airball
