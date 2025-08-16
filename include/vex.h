#pragma once

#include <vector>
#include <math.h>
#include <stdio.h>
#include <cstdint>
#include <climits>
#include <stdlib.h>
#include <cstdlib>
#include <string.h>
#include <algorithm>
#include <functional>
#include <random>
#include <chrono>
#include <unordered_map>
#include <sstream>
#include <iomanip>
#include <memory>
#include <atomic>
#include <tuple>
#include <sstream>
#include <type_traits>
#include <iostream> 
#include <cstddef>

#include "v5.h"
#include "v5_vcs.h"

#include "mikLib/globals.h"
#include "mikLib/Drive/util.h"
#include "mikLib/Devices/motors.h"
#include "mikLib/Devices/distance.h"
#include "mikLib/Devices/piston.h"
#include "mikLib/Drive/odom.h"
#include "mikLib/Drive/PID.h"
#include "assembly.h"
#include "mikLib/Drive/chassis.h"
#include "autons.h"
#include "robot-config.h"

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
#include "test.h"