.PHONY: all clean
.PHONY: release/app-cli-linux-x64 release/app-gui-linux-x64
.PHONY: release/app-cli-win-x64.exe release/app-gui-win-x64.exe
.PHONY: out/stud-unit-test-report.json

MAKEFILE := makefile

RELEASE_DIR_SERVER := release

QT_LIBS_SERVER = -L/usr/lib/x86_64-linux-gnu -lQt6Core -lQt6Gui -lQt6Widgets
QT_FLAGS_SERVER := -I/usr/include/x86_64-linux-gnu/qt6 -I/usr/include/x86_64-linux-gnu/qt6/QtCore -I/usr/include/x86_64-linux-gnu/qt6/QtWidgets

# все серверные цели
all: release/app-cli-linux-x64 release/app-gui-linux-x64 release/app-cli-win-x64 release/app-gui-win-x64 out/stud-unit-test-report.json

# серверная linux cli-сборка 
release/app-cli-linux-x64:
	$(MAKE) -f $(MAKEFILE) $@ RELEASE_DIR="$(RELEASE_DIR_SERVER)" QT_FLAGS="$(QT_FLAGS_SERVER)" QT_LIBS="$(QT_LIBS_SERVER)"

# серверная linux gui-сборка
release/app-gui-linux-x64:
	echo "error" && exit 1

# серверная windows cli-сборка 
release/app-cli-win-x64:
	echo "error" && exit 1

# серверная windows gui-сборка
release/app-gui-win-x64:
	echo "error" && exit 1

# unit-тесты
out/stud-unit-test-report.json:
	$(MAKE) -f $(MAKEFILE) $@ RELEASE_DIR="$(RELEASE_DIR_SERVER)" QT_FLAGS="$(QT_FLAGS_SERVER)" QT_LIBS="$(QT_LIBS_SERVER)"

clean:
	$(MAKE) -f $(MAKEFILE) $@