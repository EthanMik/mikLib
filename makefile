# VEXcode makefile 2019_03_26_01

# Set to 1 to reduce upload speeds but disable Brain UI completely. 
# Controller auton selector will be unaffected. 0 by default.
FAST_COMPILE = 0

# show compiler output
VERBOSE = 0

# parallel compilation
MAKEFLAGS += -j$(shell nproc)

# include toolchain options
include vex/mkenv.mk

# enable debug metadata
CFLAGS += -g
CXX_FLAGS += -g

# location of the project source cpp and c files
SRC_C  = $(wildcard src/*.cpp)
SRC_C += $(wildcard src/*.c)
SRC_C += $(wildcard src/*/*.cpp)
SRC_C += $(wildcard src/*/*.c)
SRC_C += $(wildcard src/*/*/*.cpp)
SRC_C += $(wildcard src/*/*/*.c)
SRC_C += $(wildcard src/*/*/*/*.cpp)
SRC_C += $(wildcard src/*/*/*/*.c)
SRC_C += $(wildcard src/*/*/*/*/*.cpp)
SRC_C += $(wildcard src/*/*/*/*/*.c)
SRC_C += $(wildcard src/*/*/*/*/*/*.cpp)
SRC_C += $(wildcard src/*/*/*/*/*/*.c)

ifeq ($(FAST_COMPILE), 1)
DEFINES += -DFAST_COMPILE
SRC_C := $(filter-out src/test.cpp, $(SRC_C))
SRC_C := $(filter-out $(wildcard src/mikLib/UI/components/*.cpp), $(SRC_C))
SRC_C := $(filter-out $(wildcard src/mikLib/UI/graphics/*.cpp), $(SRC_C))
SRC_C := $(filter-out $(wildcard src/mikLib/UI/config_screen.cpp), $(SRC_C))
SRC_C := $(filter-out $(wildcard src/mikLib/UI/console_screen.cpp), $(SRC_C))
SRC_C := $(filter-out $(wildcard src/mikLib/UI/graph_screen.cpp), $(SRC_C))
SRC_C := $(filter-out $(wildcard src/mikLib/UI/motors_screen.cpp), $(SRC_C))
endif

OBJ = $(addprefix $(BUILD)/, $(addsuffix .o, $(basename $(SRC_C))) )

# location of include files that c and cpp files depend on
SRC_H  = $(wildcard include/*.h)
SRC_H += $(wildcard include/**/*.h)
SRC_H += $(wildcard include/**/**/*.h)
SRC_H += $(wildcard include/**/**/**/*.h)

# additional dependancies
SRC_A  = makefile

# project header file locations
INC_F  = include

# build targets
all: $(BUILD)/$(PROJECT).bin

# include build rules
include vex/mkrules.mk
