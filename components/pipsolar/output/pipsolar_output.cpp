#include "pipsolar_output.h"
#include "esphome/core/log.h"
#include "esphome/core/helpers.h"

namespace esphome {
namespace pipsolar {

static const char *const TAG = "pipsolar.output";

void PipsolarOutput::write_state(float state) {
  char tmp[32];

  if (std::find(this->possible_values_.begin(), this->possible_values_.end(), state) ==
      this->possible_values_.end()) {
    ESP_LOGD(TAG, "Will not write value %f because it is not in the allowed values list", state);
    return;
  }

  int written = snprintf(tmp, sizeof(tmp), this->set_command_.c_str(), state);

  if (written < 0 || written >= sizeof(tmp)) {
    ESP_LOGE(TAG, "Generated PI18 command is too long");
    return;
  }

  ESP_LOGD(TAG, "Will write: %s from value %.0f", tmp, state);
  this->parent_->switch_command(std::string(tmp));
}

}  // namespace pipsolar
}  // namespace esphome
