#pragma once

#include <vector>
#include <math.h>
#include <stdio.h>
#include <cstdint>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <iomanip>
#include <memory>
#include <atomic>
#include <sstream>
#include <iostream>

#include "v5.h"
#include "v5_vcs.h"

#include "654-Template/util.h"
#include "654-Template/motors.h"
#include "654-Template/odom.h"
#include "654-Template/PID.h"
#include "654-Template/manual_drive.h"
#include "654-Template/auton_drive.h"
#include "654-Template/auton_drive_methods.h"
#include "robot-config.h"


#include "654-Template/654-UI/graphics/drawable.h"
#include "654-Template/654-UI/UI_component.h"

#include "654-Template/654-UI/UI_util.h"
#include "654-Template/654-UI/graphics/image.h"
#include "654-Template/654-UI/graphics/rectangle.h"

#include "654-Template/654-UI/button.h"
#include "654-Template/654-UI/toggle.h"
#include "654-Template/654-UI/label.h"
#include "654-Template/654-UI/graphic.h"
#include "654-Template/654-UI/background.h"
#include "654-Template/654-UI/screen.h"
#include "654-Template/654-UI/screens/console_screen.h"

// #include "654-Template/654-UI/shapes/circle.h"
// #include "654-Template/654-UI/shapes/line.h"

#include "654-Template/654-UI/UI_manager.h"
#include "654-Template/test.h"