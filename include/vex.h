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

#include "654X_Drive/util.h"
#include "654X_Drive/motors.h"
#include "654X_Drive/odom.h"
#include "654X_Drive/PID.h"
#include "654X_Drive/assembly.h"
#include "654X_Drive/example_assembly.h"
#include "654X_Drive/chassis.h"
#include "autons.h"
#include "robot-config.h"

#include "654X_UI/graphics/drawable.h"
#include "654X_UI/UI_component.h"

#include "654X_UI/UI_util.h"
#include "654X_UI/graphics/image.h"
#include "654X_UI/graphics/rectangle.h"
#include "654X_UI/graphics/text.h"
#include "654X_UI/graphics/pixel.h"
#include "654X_UI/graphics/line.h"
#include "654X_UI/graphics/group.h"

#include "654X_UI/button.h"
#include "654X_UI/toggle.h"
#include "654X_UI/label.h"
#include "654X_UI/graphic.h"
#include "654X_UI/background.h"
#include "654X_UI/textbox.h"
#include "654X_UI/screen.h"
#include "654X_UI/screens/console_screen.h"
#include "654X_UI/screens/auton_screen.h"
#include "654X_UI/screens/config_screen.h"
#include "654X_UI/screens/graph_screen.h"

#include "654X_UI/UI_manager.h"
#include "test.h"