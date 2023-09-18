TARGET ?= main
SRC_DIRS := ./src

SRCS := $(shell find $(SRC_DIRS) -name "*.cpp" -or -name "*.c" -or -name "*.s")
OBJS := $(addsuffix .o,$(basename $(SRCS)))
DEPS := $(OBJS:.o=.d)

GLFW_INCLUDE_PATH := /opt/homebrew/Cellar/glfw/3.3.8/include
GLFW_LIB_PATH := /opt/homebrew/Cellar/glfw/3.3.8/lib
GLEW_INCLUDE_PATH := /opt/homebrew/Cellar/glew/2.2.0_1/include
GLEW_LIB_PATH := /opt/homebrew/Cellar/glew/2.2.0_1/lib

EXT_LIBS := -Iext/cglm/include

INC_FLAGS := $(EXT_LIBS) -I$(GLFW_INCLUDE_PATH) -I$(GLEW_INCLUDE_PATH)

LDFLAGS = -lm -L$(GLFW_LIB_PATH) -L$(GLEW_LIB_PATH) -lglfw -lglew -framework OpenGl -framework IOKit -framework Cocoa
CFLAGS ?= $(INC_FLAGS) -MMD -MP -O3 -Wall -Wextra -Werror -pedantic
CC = clang

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS)

.PHONY: clean, count
clean:
	$(RM) $(TARGET) $(OBJS) $(DEPS)

count:
	tokei src/ --exclude "stb_image.h"

print-%  : ; @echo $* = $($*)

-include $(DEPS)
