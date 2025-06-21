#!/bin/bash

# Counter Strike 2D - Instalador del Sistema
# Autor: Equipo de desarrollo CS2D
# Versión: 1.0
# Compatible con Ubuntu 24.04 LTS

set -e  # Salir si hay algún error

# Hacer el script ejecutable automáticamente
chmod +x "$0"

# Configuración del proyecto
PROJECT_NAME="cs2d"
PROJECT_FULL_NAME="Counter Strike 2D"
BINARY_DIR="/usr/bin"
VAR_DIR="/var/${PROJECT_NAME}"
ETC_DIR="/etc/${PROJECT_NAME}"

# Colores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Función para imprimir mensajes con colores
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

# Función para verificar si un comando existe
command_exists() {
    command -v "$1" >/dev/null 2>&1
}

# Función para descargar e instalar SDL2 desde fuente
install_sdl2_from_source() {
    print_status "Descargando e instalando SDL2 desde fuente..."
    
    # Crear directorio temporal
    mkdir -p /tmp/sdl2_build
    cd /tmp/sdl2_build
    
    # Descargar SDL2
    if [[ ! -d "SDL2-2.28.5" ]]; then
        wget https://github.com/libsdl-org/SDL/releases/download/release-2.28.5/SDL2-2.28.5.tar.gz
        tar -xzf SDL2-2.28.5.tar.gz
    fi
    
    cd SDL2-2.28.5
    
    # Compilar e instalar SDL2
    ./configure --prefix=/usr/local
    make -j$(nproc)
    sudo make install
    sudo ldconfig
    
    # Descargar SDL2_image
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
    
    # Descargar SDL2_mixer
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
    
    # Descargar SDL2_ttf
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
    
    # Limpiar
    cd /
    rm -rf /tmp/sdl2_build
    
    print_success "SDL2 instalado desde fuente"
}

# Función para instalar dependencias en Ubuntu 24.04 LTS
install_dependencies_ubuntu() {
    print_status "Instalando dependencias en Ubuntu 24.04 LTS..."
    
    sudo apt-get update
    
    # Dependencias básicas de compilación
    sudo apt-get install -y cmake g++ build-essential pkg-config
    
    # Dependencias de Qt5
    sudo apt-get install -y qtbase5-dev qtmultimedia5-dev libqt5multimedia5-plugins
    
    # Dependencias de GStreamer para Qt Multimedia
    sudo apt-get install -y gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly
    
    # Dependencias de YAML
    sudo apt-get install -y libyaml-cpp-dev
    
    # Dependencias de testing
    sudo apt-get install -y libgtest-dev
    
    # Dependencias para SDL2 (desarrollo)
    sudo apt-get install -y libasound2-dev libpulse-dev libaudio-dev libjack-dev \
        libsndio-dev libx11-dev libxext-dev libxrandr-dev libxcursor-dev \
        libxinerama-dev libxi-dev libxss-dev libxxf86vm-dev libxrender-dev \
        libgl1-mesa-dev libglu1-mesa-dev libpng-dev libjpeg-dev libtiff-dev \
        libwebp-dev libfreetype6-dev libharfbuzz-dev libfribidi-dev
    
    # Herramientas de desarrollo (opcional)
    sudo apt-get install -y valgrind gdb pre-commit clang-format cppcheck cpplint
    
    # Instalar SDL2 desde fuente para mejor compatibilidad
    install_sdl2_from_source
    
    print_success "Dependencias instaladas correctamente"
}

# Función para configurar SDL2 en Ubuntu/Debian
setup_sdl2_config() {
    if [[ -d "./cmake/sdl2" ]]; then
        print_status "Configurando archivos de configuración de SDL2..."
        
        # Crear directorios si no existen
        sudo mkdir -p /usr/lib/x86_64-linux-gnu/cmake/SDL2_image
        sudo mkdir -p /usr/lib/x86_64-linux-gnu/cmake/SDL2_mixer
        sudo mkdir -p /usr/lib/x86_64-linux-gnu/cmake/SDL2_ttf
        
        # Copiar archivos de configuración
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

# Función para compilar el proyecto
compile_project() {
    print_status "Compilando ${PROJECT_FULL_NAME}..."
    
    # Crear directorio de build
    mkdir -p build
    cd build
    
    # Configurar con CMake
    cmake .. -DCMAKE_BUILD_TYPE=Release \
             -DCS2D_CLIENT=ON \
             -DCS2D_SERVER=ON \
             -DCS2D_EDITOR=ON \
             -DCS2D_TESTS=ON
    
    # Compilar
    make -j$(nproc)
    
    cd ..
    
    print_success "Compilación completada"
}

# Función para ejecutar tests unitarios
run_tests() {
    print_status "Ejecutando tests unitarios..."
    
    if [[ -f "build/cs2d_tests" ]]; then
        cd build
        ./cs2d_tests
        cd ..
        print_success "Tests unitarios completados"
    else
        print_warning "No se encontró el ejecutable de tests"
    fi
}

# Función para crear directorios del sistema
create_system_directories() {
    print_status "Creando directorios del sistema..."
    
    # Crear directorios principales
    sudo mkdir -p "${BINARY_DIR}"
    sudo mkdir -p "${VAR_DIR}"
    sudo mkdir -p "${ETC_DIR}"
    
    # Crear subdirectorios en /var/cs2d/
    sudo mkdir -p "${VAR_DIR}/assets"
    sudo mkdir -p "${VAR_DIR}/assets/gfx"
    sudo mkdir -p "${VAR_DIR}/assets/sfx"
    sudo mkdir -p "${VAR_DIR}/maps"
    sudo mkdir -p "${VAR_DIR}/logs"
    
    # Crear subdirectorios en /etc/cs2d/
    sudo mkdir -p "${ETC_DIR}/config"
    sudo mkdir -p "${ETC_DIR}/maps"
    
    print_success "Directorios del sistema creados"
}

# Función para instalar binarios en /usr/bin
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

# Función para instalar assets en /var/cs2d/
install_assets() {
    print_status "Instalando assets en ${VAR_DIR}..."
    
    # Copiar assets gráficos
    if [[ -d "assets/gfx" ]]; then
        sudo cp -r assets/gfx/* "${VAR_DIR}/assets/gfx/"
        print_success "Assets gráficos instalados"
    fi
    
    # Copiar assets de sonido
    if [[ -d "assets/sfx" ]]; then
        sudo cp -r assets/sfx/* "${VAR_DIR}/assets/sfx/"
        print_success "Assets de sonido instalados"
    fi
    
    # Copiar mapas
    if [[ -d "server/maps" ]]; then
        sudo cp -r server/maps/* "${VAR_DIR}/maps/"
        print_success "Mapas instalados"
    fi
}

# Función para instalar configuración en /etc/cs2d/
install_config() {
    print_status "Instalando configuración en ${ETC_DIR}..."
    
    # Copiar archivo de configuración del juego
    if [[ -f "server/game_config.yaml" ]]; then
        sudo cp server/game_config.yaml "${ETC_DIR}/config/"
        print_success "Configuración del juego instalada"
    fi
    
    # Crear archivo de configuración del sistema
    sudo tee "${ETC_DIR}/config/system.conf" > /dev/null << EOF
# Configuración del sistema ${PROJECT_FULL_NAME}
# Generado automáticamente por el instalador

# Directorios del sistema
ASSETS_DIR=${VAR_DIR}/assets
MAPS_DIR=${VAR_DIR}/maps
LOGS_DIR=${VAR_DIR}/logs
CONFIG_DIR=${ETC_DIR}/config

# Configuración por defecto
DEFAULT_PORT=8080
MAX_PLAYERS=10
GAME_FPS=60
EOF

    print_success "Configuración del sistema instalada"
}

# Función para crear accesos directos en el escritorio
create_desktop_shortcuts() {
    if [[ -n "$XDG_DESKTOP_DIR" ]] || [[ -d "$HOME/Desktop" ]]; then
        print_status "Creando accesos directos en el escritorio..."
        
        DESKTOP_DIR="$HOME/Desktop"
        if [[ -n "$XDG_DESKTOP_DIR" ]]; then
            DESKTOP_DIR="$XDG_DESKTOP_DIR"
        fi
        
        # Acceso directo para el cliente
        cat > "$DESKTOP_DIR/${PROJECT_FULL_NAME} - Cliente.desktop" << EOF
[Desktop Entry]
Version=1.0
Type=Application
Name=${PROJECT_FULL_NAME} - Cliente
Comment=Juego multijugador ${PROJECT_FULL_NAME}
Exec=${BINARY_DIR}/cs2d_client
Icon=${VAR_DIR}/assets/gfx/logo.png
Terminal=false
Categories=Game;
EOF

        # Acceso directo para el editor
        cat > "$DESKTOP_DIR/${PROJECT_FULL_NAME} - Editor.desktop" << EOF
[Desktop Entry]
Version=1.0
Type=Application
Name=${PROJECT_FULL_NAME} - Editor
Comment=Editor de mapas para ${PROJECT_FULL_NAME}
Exec=${BINARY_DIR}/cs2d_editor
Icon=${VAR_DIR}/assets/gfx/logo.png
Terminal=false
Categories=Game;Graphics;
EOF

        chmod +x "$DESKTOP_DIR/${PROJECT_FULL_NAME} - Cliente.desktop"
        chmod +x "$DESKTOP_DIR/${PROJECT_FULL_NAME} - Editor.desktop"
        
        print_success "Accesos directos creados en el escritorio"
    fi
}

# Función para mostrar información de uso
show_usage_info() {
    print_success "¡Instalación completada!"
    echo
    echo "=== ${PROJECT_FULL_NAME} INSTALADO ==="
    echo
    echo "BINARIOS INSTALADOS EN:"
    echo "  Cliente: ${BINARY_DIR}/cs2d_client"
    echo "  Editor: ${BINARY_DIR}/cs2d_editor"
    echo "  Servidor: ${BINARY_DIR}/cs2d_server"
    echo
    echo "ASSETS INSTALADOS EN:"
    echo "  ${VAR_DIR}/assets/"
    echo "  ${VAR_DIR}/maps/"
    echo
    echo "CONFIGURACIÓN EN:"
    echo "  ${ETC_DIR}/config/"
    echo
    echo "=== CÓMO USAR ==="
    echo
    echo "CLIENTE (Doble click o consola):"
    echo "  Doble click en: ${PROJECT_FULL_NAME} - Cliente"
    echo "  O desde consola: cs2d_client"
    echo
    echo "EDITOR DE MAPAS (Doble click o consola):"
    echo "  Doble click en: ${PROJECT_FULL_NAME} - Editor"
    echo "  O desde consola: cs2d_editor"
    echo
    echo "SERVIDOR (Solo consola):"
    echo "  cs2d_server <puerto>"
    echo "  Ejemplo: cs2d_server 8080"
    echo
    echo "ACCESOS DIRECTOS:"
    echo "  Se han creado accesos directos en el escritorio"
    echo
    echo "DESINSTALAR:"
    echo "  sudo ./uninstall.sh"
    echo
}

# Función principal
main() {
    echo "=========================================="
    echo "    ${PROJECT_FULL_NAME} - INSTALADOR DEL SISTEMA"
    echo "    Compatible con Ubuntu 24.04 LTS"
    echo "=========================================="
    echo
    
    # Verificar si estamos en el directorio correcto
    if [[ ! -f "CMakeLists.txt" ]] || [[ ! -f "Makefile" ]]; then
        print_error "Este script debe ejecutarse desde el directorio raíz del proyecto"
        exit 1
    fi
    
    # Verificar permisos de administrador
    if [[ $EUID -ne 0 ]]; then
        print_warning "Este instalador requiere permisos de administrador"
        print_status "Ejecutando con sudo..."
        sudo "$0" "$@"
        exit $?
    fi
    
    # Instalar dependencias para Ubuntu 24.04 LTS
    install_dependencies_ubuntu
    setup_sdl2_config
    
    # Compilar el proyecto
    compile_project
    
    # Ejecutar tests unitarios
    run_tests
    
    # Crear directorios del sistema
    create_system_directories
    
    # Instalar binarios
    install_binaries
    
    # Instalar assets
    install_assets
    
    # Instalar configuración
    install_config
    
    # Crear accesos directos
    create_desktop_shortcuts
    
    # Mostrar información de uso
    show_usage_info
}

# Ejecutar función principal
main "$@" 