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

#include "Drive/util.h"
#include "Devices/motors.h"
#include "Devices/distance.h"
#include "Devices/piston.h"
#include "Drive/odom.h"
#include "Drive/PID.h"
#include "assembly.h"
#include "Drive/chassis.h"
#include "autons.h"
#include "robot-config.h"

#include "UI/graphics/drawable.h"
#include "UI/UI_component.h"

#include "UI/UI_util.h"
#include "UI/graphics/image.h"
#include "UI/graphics/rectangle.h"
#include "UI/graphics/text.h"
#include "UI/graphics/pixel.h"
#include "UI/graphics/line.h"
#include "UI/graphics/group.h"

#include "UI/button.h"
#include "UI/toggle.h"
#include "UI/label.h"
#include "UI/graphic.h"
#include "UI/background.h"
#include "UI/textbox.h"
#include "UI/screen.h"
#include "UI/screens/console_screen.h"
#include "UI/screens/auton_screen.h"
#include "UI/screens/config_screen.h"
#include "UI/screens/graph_screen.h"

#include "UI/UI_manager.h"
#include "test.h"