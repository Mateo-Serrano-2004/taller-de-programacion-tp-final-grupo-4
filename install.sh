#!/bin/bash

set -e

PROJECT_NAME="cs2d"
PROJECT_FULL_NAME="Counter Strike 2D"
BINARY_DIR="/usr/bin"
VAR_DIR="/var/${PROJECT_NAME}"
ETC_DIR="/etc/${PROJECT_NAME}"

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

print_status() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

command_exists() {
    command -v "$1" >/dev/null 2>&1
}

confirm_action() {
    echo -n "$1 (y/N): "
    read -r response
    case "$response" in
        [yY][eE][sS]|[yY])
            return 0
            ;;
        *)
            return 1
            ;;
    esac
}

check_installation() {
    if [[ -f "${BINARY_DIR}/cs2d_client" ]] && [[ -f "${BINARY_DIR}/cs2d_editor" ]] && [[ -f "${BINARY_DIR}/cs2d_server" ]]; then
        print_warning "${PROJECT_FULL_NAME} ya está instalado en el sistema"
        echo
        echo "Ubicaciones de instalación:"
        echo "  Binarios: ${BINARY_DIR}/cs2d_*"
        echo "  Assets: ${VAR_DIR}/"
        echo "  Config: ${ETC_DIR}/"
        echo
        
        if confirm_action "¿Deseas reinstalar ${PROJECT_FULL_NAME}?"; then
            print_status "Procediendo con reinstalación..."
            return 0
        else
            print_status "Instalación cancelada"
            exit 0
        fi
    fi
}

install_sdl2_from_source() {
    print_status "Descargando e instalando SDL2 desde fuente..."
    
    local original_dir=$(pwd)
    
    mkdir -p /tmp/sdl2_build
    cd /tmp/sdl2_build
    
    if [[ ! -d "SDL2-2.28.5" ]]; then
        wget https://github.com/libsdl-org/SDL/releases/download/release-2.28.5/SDL2-2.28.5.tar.gz
        tar -xzf SDL2-2.28.5.tar.gz
    fi
    
    cd SDL2-2.28.5
    
    ./configure --prefix=/usr/local
    make -j$(nproc)
    sudo make install
    sudo ldconfig
    
    cd ..
    if [[ ! -d "SDL2_image-2.6.3" ]]; then
        wget https://github.com/libsdl-org/SDL_image/releases/download/release-2.6.3/SDL2_image-2.6.3.tar.gz
        tar -xzf SDL2_image-2.6.3.tar.gz
    fi
    
    cd SDL2_image-2.6.3
    ./configure --prefix=/usr/local
    make -j$(nproc)
    sudo make install
    sudo ldconfig
    
    cd ..
    if [[ ! -d "SDL2_mixer-2.6.3" ]]; then
        wget https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.6.3/SDL2_mixer-2.6.3.tar.gz
        tar -xzf SDL2_mixer-2.6.3.tar.gz
    fi
    
    cd SDL2_mixer-2.6.3
    ./configure --prefix=/usr/local
    make -j$(nproc)
    sudo make install
    sudo ldconfig
    
    cd ..
    if [[ ! -d "SDL2_ttf-2.20.2" ]]; then
        wget https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.20.2/SDL2_ttf-2.20.2.tar.gz
        tar -xzf SDL2_ttf-2.20.2.tar.gz
    fi
    
    cd SDL2_ttf-2.20.2
    ./configure --prefix=/usr/local
    make -j$(nproc)
    sudo make install
    sudo ldconfig
    
    rm -rf /tmp/sdl2_build
    cd "$original_dir"
    
    print_success "SDL2 instalado desde fuente"
}

install_dependencies() {
    print_status "Verificando dependencias..."
    
    if command_exists cmake && command_exists g++ && [[ -f "/usr/local/lib/libSDL2.so" ]]; then
        print_success "Dependencias ya instaladas"
        return 0
    fi
    
    print_status "Instalando dependencias..."
    
    sudo apt-get update
    
    sudo apt-get install -y cmake g++ build-essential pkg-config
    
    sudo apt-get install -y qtbase5-dev qtmultimedia5-dev libqt5multimedia5-plugins
    
    sudo apt-get install -y gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly
    
    sudo apt-get install -y libyaml-cpp-dev
    
    sudo apt-get install -y libasound2-dev libpulse-dev libaudio-dev libjack-dev \
        libsndio-dev libx11-dev libxext-dev libxrandr-dev libxcursor-dev \
        libxinerama-dev libxi-dev libxss-dev libxxf86vm-dev libxrender-dev \
        libgl1-mesa-dev libglu1-mesa-dev libpng-dev libjpeg-dev libtiff-dev \
        libwebp-dev libfreetype6-dev libharfbuzz-dev libfribidi-dev
    
    install_sdl2_from_source
    
    print_success "Dependencias instaladas correctamente"
}

setup_sdl2_config() {
    if [[ -d "./cmake/sdl2" ]]; then
        print_status "Configurando archivos de configuración de SDL2..."
        
        sudo mkdir -p /usr/lib/x86_64-linux-gnu/cmake/SDL2_image
        sudo mkdir -p /usr/lib/x86_64-linux-gnu/cmake/SDL2_mixer
        sudo mkdir -p /usr/lib/x86_64-linux-gnu/cmake/SDL2_ttf
        
        if [[ -f "./cmake/sdl2/sdl2_image-config.cmake" ]]; then
            sudo cp ./cmake/sdl2/sdl2_image-config.cmake /usr/lib/x86_64-linux-gnu/cmake/SDL2_image/
        fi
        
        if [[ -f "./cmake/sdl2/sdl2_mixer-config.cmake" ]]; then
            sudo cp ./cmake/sdl2/sdl2_mixer-config.cmake /usr/lib/x86_64-linux-gnu/cmake/SDL2_mixer/
        fi
        
        if [[ -f "./cmake/sdl2/sdl2_ttf-config.cmake" ]]; then
            sudo cp ./cmake/sdl2/sdl2_ttf-config.cmake /usr/lib/x86_64-linux-gnu/cmake/SDL2_ttf/
        fi
        
        print_success "Configuración de SDL2 completada"
    fi
}

compile_project() {
    print_status "Compilando ${PROJECT_FULL_NAME}..."
    
    mkdir -p build
    cd build
    
    cmake .. -DCMAKE_BUILD_TYPE=Release \
             -DCS2D_CLIENT=ON \
             -DCS2D_SERVER=ON \
             -DCS2D_EDITOR=ON
    
    make -j$(nproc)
    
    cd ..
    
    print_success "Compilación completada"
}

create_system_directories() {
    print_status "Creando directorios del sistema..."
    
    sudo mkdir -p "${BINARY_DIR}"
    sudo mkdir -p "${VAR_DIR}"
    sudo mkdir -p "${ETC_DIR}"
    
    sudo mkdir -p "${VAR_DIR}/assets/gfx"
    sudo mkdir -p "${VAR_DIR}/assets/sfx"
    sudo mkdir -p "${VAR_DIR}/maps"
    
    sudo mkdir -p "${ETC_DIR}/cfg"
    
    print_success "Directorios del sistema creados"
}

install_binaries() {
    print_status "Instalando binarios en ${BINARY_DIR}..."
    
    if [[ -f "build/cs2d_client" ]]; then
        sudo cp build/cs2d_client "${BINARY_DIR}/"
        sudo chmod +x "${BINARY_DIR}/cs2d_client"
        print_success "Cliente instalado: ${BINARY_DIR}/cs2d_client"
    else
        print_error "No se encontró el ejecutable del cliente"
        exit 1
    fi
    
    if [[ -f "build/cs2d_editor" ]]; then
        sudo cp build/cs2d_editor "${BINARY_DIR}/"
        sudo chmod +x "${BINARY_DIR}/cs2d_editor"
        print_success "Editor instalado: ${BINARY_DIR}/cs2d_editor"
    else
        print_error "No se encontró el ejecutable del editor"
        exit 1
    fi
    
    if [[ -f "build/cs2d_server" ]]; then
        sudo cp build/cs2d_server "${BINARY_DIR}/"
        sudo chmod +x "${BINARY_DIR}/cs2d_server"
        print_success "Servidor instalado: ${BINARY_DIR}/cs2d_server"
    else
        print_error "No se encontró el ejecutable del servidor"
        exit 1
    fi
}

install_assets() {
    print_status "Instalando assets en ${VAR_DIR}..."
    
    if [[ -d "assets/gfx" ]]; then
        sudo cp -r assets/gfx/* "${VAR_DIR}/assets/gfx/"
        print_success "Assets gráficos instalados"
    fi
    
    if [[ -d "assets/sfx" ]]; then
        sudo cp -r assets/sfx/* "${VAR_DIR}/assets/sfx/"
        print_success "Assets de sonido instalados"
    fi
    
    if [[ -d "server/maps" ]]; then
        sudo cp -r server/maps/* "${VAR_DIR}/maps/"
        print_success "Mapas instalados"
    fi
}

install_config() {
    print_status "Instalando configuración en ${ETC_DIR}..."
    
    if [[ -f "server/game_config.yaml" ]]; then
        sudo cp server/game_config.yaml "${ETC_DIR}/cfg/"
        print_success "Configuración del juego instalada"
    fi
}

main() {
    echo "=========================================="
    echo "    ${PROJECT_FULL_NAME} - INSTALADOR DEL SISTEMA"
    echo "=========================================="
    echo
    
    if [[ ! -f "CMakeLists.txt" ]] || [[ ! -f "Makefile" ]]; then
        print_error "Este script debe ejecutarse desde el directorio raíz del proyecto"
        exit 1
    fi
    
    if [[ $EUID -ne 0 ]]; then
        print_warning "Este instalador requiere permisos de administrador"
        print_status "Ejecutando con sudo..."
        sudo "$0" "$@"
        exit $?
    fi
    
    check_installation
    
    install_dependencies
    setup_sdl2_config
    
    compile_project
    
    create_system_directories
    
    install_binaries
    
    install_assets
    
    install_config
    
    print_success "¡Instalación completada!"
    echo
    echo "=== ${PROJECT_FULL_NAME} INSTALADO ==="
    echo
    echo "BINARIOS:"
    echo "  cs2d_client"
    echo "  cs2d_editor"
    echo "  cs2d_server"
    echo
    echo "DESINSTALAR: sudo ./uninstall.sh"
    echo
}

main "$@" 