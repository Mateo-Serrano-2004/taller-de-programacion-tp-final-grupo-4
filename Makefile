.PHONY: all test clean editor client common server build

NAME := cs2d

debug:
	mkdir -p build/
	cmake -S . -B ./build -DCMAKE_BUILD_TYPE=Debug
	cmake --build build/

install-compile-tools:
	@echo "Installing dependencies"
	@sudo apt-get update
	@echo "Installing build dependencies"
	@sudo apt-get install -y cmake g++
	@echo "Installing code utilities"
	@sudo apt-get install -y valgrind
	@sudo apt-get install -y gdb
	@sudo apt-get install -y pre-commit
	@sudo apt-get install -y clang-format
	@sudo apt-get install -y cppcheck
	@sudo apt-get install -y cpplint

install-yaml:
	@sudo apt-get install -y libyaml-cpp-dev

install-sdl2:
	@echo "Installing SDL2 dependencies"
	@sudo apt-get install -y libsdl2-2.0-0 libsdl2-dev libsdl2-image-2.0-0 libsdl2-image-dev libsdl2-mixer-2.0-0 libsdl2-mixer-dev libsdl2-ttf-2.0-0 libsdl2-ttf-dev
	@echo "Setting up SDL2 cmake config files"
	@if [ ! -e "/usr/lib/x86_64-linux-gnu/cmake/SDL2_image" ]; then \
	    sudo mkdir -p /usr/lib/x86_64-linux-gnu/cmake/SDL2_image; \
	    sudo cp ./cmake/sdl2/sdl2_image-config.cmake /usr/lib/x86_64-linux-gnu/cmake/SDL2_image/; \
	fi
	@if [ ! -e "/usr/lib/x86_64-linux-gnu/cmake/SDL2_mixer" ]; then \
	    sudo mkdir -p /usr/lib/x86_64-linux-gnu/cmake/SDL2_mixer; \
	    sudo cp ./cmake/sdl2/sdl2_mixer-config.cmake /usr/lib/x86_64-linux-gnu/cmake/SDL2_mixer/; \
	fi
	@if [ ! -e "/usr/lib/x86_64-linux-gnu/cmake/SDL2_ttf" ]; then \
	    sudo mkdir -p /usr/lib/x86_64-linux-gnu/cmake/SDL2_ttf; \
	    sudo cp ./cmake/sdl2/sdl2_ttf-config.cmake /usr/lib/x86_64-linux-gnu/cmake/SDL2_ttf/; \
	fi

install-qt5:
	@echo "Installing QT dependencies"
	@sudo apt-get install -y qtbase5-dev
	@sudo apt-get install -y qtmultimedia5-dev
	@sudo apt-get install -y libqt5multimedia5-plugins
	@sudo apt-get install -y gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly

install-gtest:
	@echo "Installing GTest dependencies"
	@sudo apt-get install -y libgtest-dev

install: install-compile-tools install-sdl2 install-qt5 install-yaml install-gtest

clean:
	rm -Rf ./build