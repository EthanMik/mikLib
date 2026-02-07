#pragma once

#include <memory>
#include <vector>
#include <math.h>
#include <cstdint>
#include <cstdlib>
#include <algorithm>
#include <functional>
#include <sstream>
#include <iomanip>
#include <type_traits>

#include "v5.h"
#include "v5_vcs.h"

#include "mikLib/globals.h"
#include "mikLib/Drive/util.h"

#include "mikLib/UI/graphics/drawable.h"
#include "mikLib/UI/UI_component.h"

#include "mikLib/UI/UI_util.h"
#include "mikLib/UI/graphics/image.h"
#include "mikLib/UI/graphics/rectangle.h"
#include "mikLib/UI/graphics/logo.h"
#include "mikLib/UI/graphics/circle.h"
#include "mikLib/UI/graphics/text.h"
#include "mikLib/UI/graphics/pixel.h"
#include "mikLib/UI/graphics/line.h"
#include "mikLib/UI/graphics/group.h"

#include "mikLib/UI/button.h"
#include "mikLib/UI/toggle.h"
#include "mikLib/UI/label.h"
#include "mikLib/UI/graphic.h"
#include "mikLib/UI/background.h"
#include "mikLib/UI/textbox.h"
#include "mikLib/UI/screen.h"
#include "mikLib/UI/screens/console_screen.h"
#include "mikLib/UI/screens/auton_screen.h"
#include "mikLib/UI/screens/config_screen.h"
#include "mikLib/UI/screens/graph_screen.h"

#include "mikLib/UI/UI_manager.h"

#include "robot-config.h"
#include "autons.h"
