#include "Debug.h"

namespace Util {

Debug* Debug::instance() {
  static Debug s_instance;
  return &s_instance;
}

}  // namespace Util
