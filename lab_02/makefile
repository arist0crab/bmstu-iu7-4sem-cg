# ============================================
#   папки
# ============================================

SRC_DIR := src
INC_DIR := inc
FRM_DIR := forms
BUILD_DIR := build
RELEASE_DIR := release

# ============================================
#   компилятор и флаги
# ============================================

# c++
CXX := g++
CXX_FLAGS := -std=c++17 -I$(INC_DIR) -Wall -Werror -Wpedantic -Wextra

# qt
QT_LIBS ?= -L/usr/lib64/qt6 -lQt6Core -lQt6Gui -lQt6Widgets
QT_FLAGS ?= -I/usr/include/qt6 -I/usr/include/qt6/QtCore -I/usr/include/qt6/QtWidgets

# покрытие
GCOV := -lgcov
GCOV_FLAGS := -fprofile-arcs -ftest-coverage

# ============================================
#   исходники
# ============================================

SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

# ============================================
#   сборка исполняемых
# ============================================

$(RELEASE_DIR)/gui-app.exe: $(RELEASE_DIR) | $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/gui-build
	cd $(BUILD_DIR)/gui-build && cmake $(CURDIR) && make
	cp $(BUILD_DIR)/gui-build/gui_app $@

# ============================================
#   сборка папок
# ============================================

$(BUILD_DIR) $(RELEASE_DIR):
	mkdir -p $@


clean:
	rm -rf $(BUILD_DIR) $(RELEASE_DIR)