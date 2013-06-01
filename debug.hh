#include <iostream>

namespace chess {
  static bool debug = false;
}

#define PRINT(type, text) { \
  std::cerr << "    " << type << ": " << __PRETTY_FUNCTION__ << " - " << __FILE__ << " (" << __LINE__ << ") - " << text << std::endl; \
}

#define PRINTS(type) { \
  std::cerr << "    " << type << ": " << __PRETTY_FUNCTION__ << std::endl; \
}

#define ERROR(text) { \
  PRINT("ERROR", text) \
}

#define DEBUGLINE(text) { \
  if (chess::debug) { \
    PRINT("DEBUG", text); \
  } \
}

#define ENTER() { \
  if (chess::debug) { \
    PRINTS("ENTER"); \
  } \
}

#define RETURN() { \
  if (chess::debug) { \
    PRINTS("RETURN"); \
  } \
}
