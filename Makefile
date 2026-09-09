# 简单的 C++ 编译 Makefile
# 用法:
#   make                          编译默认源目录下所有 .cpp 到 build/（保留目录结构）
#   make one SRC=路径/文件名.cpp   只编译指定源文件
#   make run SRC=路径/文件名.cpp   编译并运行指定源文件（程序读输入时直接在终端输入）
#   make SRC_DIR=源目录            改用其他源目录（默认 STL）
#   make clean                    删除 build/

CXX       := g++
CXXFLAGS  := -std=c++17 -O2 -Wall
BUILD_DIR := build

# 默认源目录；命令行可用 make SRC_DIR=其他目录 覆盖，也可直接改这一行
SRC_DIR ?= STL

# 递归收集 $(SRC_DIR) 下的所有 .cpp
SRCS := $(shell find $(SRC_DIR) -type f -name '*.cpp' 2>/dev/null)
BINS := $(patsubst %.cpp,$(BUILD_DIR)/%,$(SRCS))

.PHONY: all one run clean

all: $(BINS)

# 全量编译：每个 .cpp 单独生成同名可执行文件
$(BUILD_DIR)/%: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $<

# 单独编译指定文件，输出到 build/ 下与原文件同路径的位置
# 例: make one SRC=STL/uglyNumber.cpp
one:
	@test -n "$(SRC)" || (echo "用法: make one/run SRC=路径/文件名.cpp"; exit 1)
	@test -f "$(SRC)" || (echo "找不到源文件: $(SRC)"; exit 1)
	@mkdir -p $(BUILD_DIR)/$(dir $(SRC))
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/$(basename $(SRC)) $(SRC)

# 编译并运行单个源文件
# 例: make run SRC=STL/uglyNumber.cpp
run: one
	@$(BUILD_DIR)/$(basename $(SRC))

clean:
	rm -rf $(BUILD_DIR)
