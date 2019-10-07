# CXX      := -c++
# CXXFLAGS := -pedantic-errors -Wall -Wextra -Werror
# LDFLAGS  := -L/usr/lib -lstdc++ -lm
# OBJ_DIR  := ./objs
# APP_DIR  := ./apps
# TARGET   := golf
# INCLUDE  := -Iinclude/
# SRC      := $(wildcard src/*.cpp)         

# OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

# all: build $(APP_DIR)/$(TARGET)

# $(OBJ_DIR)/%.o: %.cpp
# 	@mkdir -p $(@D)
# 	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

# $(APP_DIR)/$(TARGET): $(OBJECTS)
# 	@mkdir -p $(@D)
# 	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(APP_DIR)/$(TARGET) $(OBJECTS)

# .PHONY: all build clean debug release

# build:
# 	@mkdir -p $(APP_DIR)
# 	@mkdir -p $(OBJ_DIR)

# debug: CXXFLAGS += -DDEBUG -g
# debug: all

# release: CXXFLAGS += -O2
# release: all

# # # Rules for compiling test suite.
# # # - Grab every .cpp file in tests/, compile them to .o files
# # # - Build the test program w/ catchmain.cpp
# # OBJS_TEST += $(filter-out $(EXE_OBJ), $(OBJS))
# # CPP_TEST = $(wildcard tests/*.cpp)
# # CPP_TEST += /catch/catchmain.cpp
# # OBJS_TEST += $(CPP_TEST:.cpp=.o)

# # $(TEST): $(patsubst %.o, $(OBJ_DIR)/%.o, $(OBJS_TEST))
# # 	$(LD) $^ $(LDFLAGS) -o $@

# clean:
# 	-@rm -rvf $(OBJ_DIR)/*
# 	-@rm -rvf $(APP_DIR)/*
# 	rm -rf $(TEST) *.o *.d

# Executable names:
EXE = golf
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = main.o player.o engine.o

#
# This is a generic Makefile designed to compile a sample directory of code.
# This file depends on variables having been set before calling:
#   EXE: The name of the result file
#   OBJS: Array of objects files (.o) to be generated
#   CLEAN_RM: Optional list of additional files to delete on `make clean`
#
# @author Wade Fagen-Ulmschneider, <waf@illinois.edu>
# @author Jeffrey Tolar
#

# Compiler/linker comfig and object/depfile directory:
CXX = clang++
LD = clang++
OBJS_DIR = .objs

# Add standard CS 225 object files
# OBJS += cs225/HSLAPixel.o cs225/PNG.o cs225/lodepng/lodepng.o

# -MMD and -MP asks clang++ to generate a .d file listing the headers used in the source code for use in the Make process.
#   -MMD: "Write a depfile containing user headers"
#   -MP : "Create phony target for each dependency (other than main file)"
#   (https://clang.llvm.org/docs/ClangCommandLineReference.html)
DEPFILE_FLAGS = -MMD -MP

# Provide lots of helpful warning/errors:
WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable

# Flags for compile:
CXXFLAGS += -std=c++1y -stdlib=libc++ -O0 $(WARNINGS) $(DEPFILE_FLAGS) -g -c

# Flags for linking:
LDFLAGS += -std=c++1y -stdlib=libc++

# Rule for `all` (first/default rule):
all: $(EXE)

# Rule for linking the final executable:
# - $(EXE) depends on all object files in $(OBJS)
# - `patsubst` function adds the directory name $(OBJS_DIR) before every object file
$(EXE): $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS))
	$(LD) $^ $(LDFLAGS) -o $@

# Ensure .objs/ exists:
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/catch
	@mkdir -p $(OBJS_DIR)/tests	

# Rules for compiling source code.
# - Every object file is required by $(EXE)
# - Generates the rule requiring the .cpp file of the same name
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@


# Rules for compiling test suite.
# - Grab every .cpp file in tests/, compile them to .o files
# - Build the test program w/ catchmain.cpp from cs225
OBJS_TEST += $(filter-out $(EXE_OBJ), $(OBJS))
CPP_TEST = $(wildcard tests/*.cpp)
CPP_TEST += catch/catchmain.cpp
OBJS_TEST += $(CPP_TEST:.cpp=.o)

$(TEST): $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_TEST))
	$(LD) $^ $(LDFLAGS) -o $@

# Additional dependencies for object files are included in the clang++
# generated .d files (from $(DEPFILE_FLAGS)):
-include $(OBJS_DIR)/*.d
-include $(OBJS_DIR)/catch/*.d
-include $(OBJS_DIR)/tests/*.d


# Standard C++ Makefile rules:
clean:
	rm -rf $(EXE) $(TEST) $(OBJS_DIR) $(CLEAN_RM) *.o *.d

tidy: clean
	rm -rf doc

.PHONY: all tidy clean










