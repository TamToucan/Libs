#include "Debug.h"

namespace Util {

namespace {
  Debug g_debugInstance;
}

Debug* Debug::instance() {
  return &g_debugInstance;
}

}  // namespace Util
