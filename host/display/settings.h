#ifndef AIRBALL_SETTINGS_H
#define AIRBALL_SETTINGS_H

#include <string>
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>

namespace airball {

template <class T> class Parameter;

class Settings {
public:
  Settings();
  ~Settings() {}

  /**
   * @return the display setting, full scale indicated air speed. (Knots)
   */
  double v_full_scale() const;

  /**
   * @return the rotation indicated air speed (Vr). (Knots)
   */
  double v_r() const;

  /**
   * @return the maximum flap extension indicated air speed (Vfe). (Knots)
   */
  double v_fe() const;

  /**
   * @return the maximum normal operating indicated air speed (Vno). (Knots)
   */
  double v_no() const;

  /**
   * @return the never-exceed indicated air speed (Vne). (Knots)
   */
  double v_ne() const;

  /**
   * @return the stall angle of attack. (Degrees)
   */
  double alpha_stall() const;

  /**
   * @return the display setting, minimum angle of attack shown. (Degrees)
   */
  double alpha_min() const;

  /**
   * @return the maximum climb rate angle of attack. (Degrees)
   */
  double alpha_x() const;

  /**
   * @return the maximum climb angle angle of attack. (Degrees)
   */
  double alpha_y() const;

  /**
   * @return the reference stabilized approach angle of attack. (Degrees)
   */
  double alpha_ref() const;

  /**
   * @return the display setting, full scale angle of yaw. (Degrees)
   */
  double beta_full_scale() const;

  /**
   * @return the display setting, constant bias to angle of yaw. (Degrees)
   */
  double beta_bias() const;

  /**
   * @return the current barometer setting. (Inches of mercury)
   */
  double baro_setting() const;

  /**
   * @return the ball smoothing factor.
   */
  double ball_smoothing_factor() const;

  /**
   * @return the VSI smoothing factor.
   */
  double vsi_smoothing_factor() const;

  /**
   * Load settings from a specified file path.
   */
   void load(const std::string &path);

private:

  void load_str(std::string);

  template <class T> T get_value(const Parameter<T>* p) const;

  rapidjson::Document document_;
};

} // namespace airball

#endif // AIRBALL_SETTINGS_H
