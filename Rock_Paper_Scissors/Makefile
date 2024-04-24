# 编译器
CC = g++
# 编译器标志
CFLAGS = -Icode/h -Wall -O2 -MMD

# 源文件目录
SRC_DIR = code/cpp
# 对象文件目录
OBJ_DIR = build
# 目标文件文件夹
BIN_DIR = bin

# 可执行文件名称
TARGET = $(BIN_DIR)\run.exe

# 找到所有的 .cpp 文件
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
# 将 .cpp 文件的列表转换为 .o 文件的列表
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
# 每个.o文件的依赖表文件
DEPS = $(OBJECTS:.o=.d)

# 默认目标
all: dirs $(TARGET)

# 创建文件夹目标
dirs:
	if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"

# 链接目标
$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@

# 从 .cpp 生成 .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(DEPS)

# 清理目标
clean:
	del /Q $(TARGET)
	del /Q $(OBJ_DIR)\*.o
	del /Q $(OBJ_DIR)\*.d
	rmdir /s /q $(OBJ_DIR)
.PHONY: all clean dirs

