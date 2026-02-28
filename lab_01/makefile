# ============================================
#   папки
# ============================================

SRC_DIR := src
OUT_DIR := out
BUILD_DIR := build
BUILD_CLI_DIR := $(BUILD_DIR)/cli
BUILD_GUI_DIR := $(BUILD_DIR)/gui
COVERAGE_DIR := $(OUT_DIR)/coverage
RELEASE_DIR ?= local

# ============================================
#   компилятор и флаги
# ============================================

# c++
CXX := g++
CXX_FLAGS := -std=c++17 -I$(SRC_DIR) -Wall -Werror -Wpedantic -Wextra

# qt
QT_LIBS ?= -L/usr/lib64/qt6 -lQt6Core -lQt6Gui -lQt6Widgets
QT_FLAGS ?= -I/usr/include/qt6 -I/usr/include/qt6/QtCore -I/usr/include/qt6/QtWidgets

# покрытие
GCOV := -lgcov
GCOV_FLAGS := -fprofile-arcs -ftest-coverage

# ============================================
#   исходники
# ============================================

# все
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)

# cli-объектники (в build/cli)
CLI_SOURCES := $(filter-out $(SRC_DIR)/main_gui.cpp $(SRC_DIR)/mainwindow.cpp $(SRC_DIR)/manager.cpp $(SRC_DIR)/draw.cpp, $(SOURCES))
CLI_OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_CLI_DIR)/%.o, $(CLI_SOURCES))

# gui-объектники (в build/gui)
GUI_SOURCES := $(filter $(SRC_DIR)/main_gui.cpp $(SRC_DIR)/mainwindow.cpp, $(SOURCES))
GUI_OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_GUI_DIR)/%.o, $(GUI_SOURCES))

PRO_FILE := gui.pro

# ============================================
#   тесты
# ============================================

TEST_IN := tests/pos_in.json
TEST_OUT := tests/pos_out.json
TMP_JSON := $(OUT_DIR)/tmp.json
REPORT_JSON := $(OUT_DIR)/stud-unit-test-report.json

# ============================================
#   цели
# ============================================

# все цели
all: cli-build gui-build test

# цель локальной cli-сборки
cli-build: $(RELEASE_DIR)/app-cli-linux-x64

# цель локальной gui-сборки
gui-build: $(RELEASE_DIR)/app-gui-linux-x64

# цель локальной тестовой сборки
test: out/stud-unit-test-report.json

clean:
	rm -rf $(BUILD_DIR) $(OUT_DIR) local release

.PHONY: all clean cli-build gui-build test
.PHONY: $(RELEASE_DIR)/app-cli-linux-x64 $(RELEASE_DIR)/app-gui-linux-x64
.PHONY: $(RELEASE_DIR)/app-cli-win-x64.exe $(RELEASE_DIR)/app-gui-win-x64.exe
.PHONY: out/stud-unit-test-report.json

# ============================================
#   сборка исполняемых
# ============================================

# linux cli-сборка 
$(RELEASE_DIR)/app-cli-linux-x64: $(RELEASE_DIR) | $(CLI_OBJECTS)
	$(CXX) $(CLI_OBJECTS) -o $@  $(GCOV) $(QT_LIBS)

# linux gui-сборка
$(RELEASE_DIR)/app-gui-linux-x64: $(RELEASE_DIR) | $(BUILD_GUI_DIR)
	cd $(BUILD_GUI_DIR) && qmake $(CURDIR)/$(PRO_FILE) && make
	cp $(BUILD_GUI_DIR)/app-gui-linux-x64 $@

# windows cli-сборка 
$(RELEASE_DIR)/app-cli-win-x64:
	echo "error" && exit 1

# windows gui-сборка
$(RELEASE_DIR)/app-gui-win-x64:
	echo "error" && exit 1

# unit-тесты
$(REPORT_JSON): $(RELEASE_DIR)/app-cli-linux-x64 | $(OUT_DIR) $(COVERAGE_DIR)
	@test -f $(TEST_IN) || (echo "ERROR: no input test file"; exit 1)
	@test -f $(TEST_OUT) || (echo "ERROR: no output test file"; exit 1)
	
	@./$(RELEASE_DIR)/app-cli-linux-x64 $(TEST_IN) > $(TMP_JSON)
	
	@dtst=$$(date +"%Y-%m-%dT%H:%M:%S%:z"); \
	if jq .result $(TMP_JSON) 2>/dev/null > $(TMP_JSON)_result && \
		jq .result $(TEST_OUT) 2>/dev/null > $(TEST_OUT)_result && \
		cmp -s $(TMP_JSON)_result $(TEST_OUT)_result; then \
		PASSED=1; FAILED=0; \
	else \
   		PASSED=0; FAILED=1; \
	fi; \
	rm -f $(TMP_JSON)_result $(TEST_OUT)_result; \
	lcov --capture --directory $(BUILD_DIR) --output-file $(COVERAGE_DIR)/coverage.info --ignore-errors empty 2>&1 | grep -v "WARNING\|unexecuted\|geninfo" || true; \
	lcov --extract $(COVERAGE_DIR)/coverage.info '$(SRC_DIR)/*.cpp' --output-file $(COVERAGE_DIR)/src_coverage.info --ignore-errors unused 2>&1 | grep -v "WARNING\|unexecuted\|geninfo" || true; \
	COVERAGE=`lcov --summary $(COVERAGE_DIR)/src_coverage.info 2>/dev/null | grep "lines" | awk '{print $$2}' | tr -d '%' | head -1` || echo "0.0"; \
	echo "{\"timestamp\":\"$$dtst\",\"coverage\":$$COVERAGE,\"passed\":$$PASSED,\"failed\":$$FAILED}" > $(REPORT_JSON)

# ============================================
#   сборка объектников и папок
# ============================================

# сборка объектников cli-сценария
$(BUILD_CLI_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_CLI_DIR)
	$(CXX) $(CXX_FLAGS) $(QT_FLAGS) $(GCOV_FLAGS) -c $< -o $@

# сборка объектников gui-сценария
$(BUILD_GUI_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_GUI_DIR)
	$(CXX) $(CXX_FLAGS) $(QT_FLAGS) $(GCOV_FLAGS) -c $< -o $@

# создание необходимых папок
$(BUILD_DIR) $(BUILD_CLI_DIR) $(BUILD_GUI_DIR) $(RELEASE_DIR) $(OUT_DIR) $(COVERAGE_DIR):
	mkdir -p $@
