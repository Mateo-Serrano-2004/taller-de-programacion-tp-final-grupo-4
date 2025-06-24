#!/bin/bash

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

print_status() { echo -e "${BLUE}[INFO]${NC} $1"; }
print_success() { echo -e "${GREEN}[SUCCESS]${NC} $1"; }
print_warning() { echo -e "${YELLOW}[WARNING]${NC} $1"; }
print_error() { echo -e "${RED}[ERROR]${NC} $1"; }

confirm_action() {
    echo -n "$1 (y/N): "
    read -r response
    case "$response" in [yY][eE][sS]|[yY]) return 0 ;; *) return 1 ;; esac
}

# Chequea si SDL2 está instalado en /usr/local/lib/cmake/SDL2
sdl2_already_installed() {
    if pkg-config --exists sdl2; then
        return 0
    else
        return 1
    fi
}

install_sdl2_from_source() {
    if sdl2_already_installed; then
        print_status "SDL2 ya está instalado en /usr/local, omitiendo compilación desde fuente."
        return 0
    fi

    print_status "Instalando SDL2 desde fuente..."
    local original_dir=$(pwd)
    mkdir -p /tmp/sdl2_build && cd /tmp/sdl2_build || { print_error "No se pudo crear /tmp/sdl2_build"; exit 1; }

    # SDL2 base
    wget -q https://github.com/libsdl-org/SDL/releases/download/release-2.28.5/SDL2-2.28.5.tar.gz || { print_error "Falló la descarga de SDL2"; exit 1; }
    tar -xzf SDL2-2.28.5.tar.gz || { print_error "Falló la extracción de SDL2"; exit 1; }
    cd SDL2-2.28.5 || { print_error "No se encontró el directorio SDL2-2.28.5"; exit 1; }
    ./configure --prefix=/usr/local || { print_error "Error en configure SDL2"; exit 1; }
    make -j$(nproc) || { print_error "Error de compilación SDL2"; exit 1; }
    sudo make install || { print_error "Error en make install SDL2"; exit 1; }
    sudo ldconfig

    # SDL2_image
    cd ../
    wget -q https://github.com/libsdl-org/SDL_image/releases/download/release-2.6.3/SDL2_image-2.6.3.tar.gz || { print_error "Falló la descarga de SDL2_image"; exit 1; }
    tar -xzf SDL2_image-2.6.3.tar.gz || { print_error "Falló la extracción de SDL2_image"; exit 1; }
    cd SDL2_image-2.6.3 || { print_error "No se encontró SDL2_image-2.6.3"; exit 1; }
    ./configure --prefix=/usr/local || { print_error "Error en configure SDL2_image"; exit 1; }
    make -j$(nproc) || { print_error "Error de compilación SDL2_image"; exit 1; }
    sudo make install || { print_error "Error en make install SDL2_image"; exit 1; }
    sudo ldconfig

    # SDL2_mixer
    cd ../
    wget -q https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.6.3/SDL2_mixer-2.6.3.tar.gz || { print_error "Falló la descarga de SDL2_mixer"; exit 1; }
    tar -xzf SDL2_mixer-2.6.3.tar.gz || { print_error "Falló la extracción de SDL2_mixer"; exit 1; }
    cd SDL2_mixer-2.6.3 || { print_error "No se encontró SDL2_mixer-2.6.3"; exit 1; }
    ./configure --prefix=/usr/local || { print_error "Error en configure SDL2_mixer"; exit 1; }
    make -j$(nproc) || { print_error "Error de compilación SDL2_mixer"; exit 1; }
    sudo make install || { print_error "Error en make install SDL2_mixer"; exit 1; }
    sudo ldconfig

    # SDL2_ttf
    cd ../
    wget -q https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.20.2/SDL2_ttf-2.20.2.tar.gz || { print_error "Falló la descarga de SDL2_ttf"; exit 1; }
    tar -xzf SDL2_ttf-2.20.2.tar.gz || { print_error "Falló la extracción de SDL2_ttf"; exit 1; }
    cd SDL2_ttf-2.20.2 || { print_error "No se encontró SDL2_ttf-2.20.2"; exit 1; }
    ./configure --prefix=/usr/local || { print_error "Error en configure SDL2_ttf"; exit 1; }
    make -j$(nproc) || { print_error "Error de compilación SDL2_ttf"; exit 1; }
    sudo make install || { print_error "Error en make install SDL2_ttf"; exit 1; }
    sudo ldconfig

    cd "$original_dir" || { print_error "No se pudo volver al directorio original"; exit 1; }
    rm -rf /tmp/sdl2_build

    # Verificación CMake config SDL2
    print_status "Verificando archivos CMake config SDL2 en /usr/local/lib/cmake"
    for mod in SDL2_image SDL2_mixer SDL2_ttf; do
        if [ ! -d "/usr/local/lib/cmake/$mod" ]; then
            print_warning "No se encontró /usr/local/lib/cmake/$mod - puede que no esté instalado correctamente"
        fi
    done

    print_success "SDL2 y módulos instalados correctamente desde fuente"
}

install_sdl2pp_from_source() {
    if pkg-config --exists SDL2pp; then
        print_status "SDL2pp ya está instalado, omitiendo compilación."
        return 0
    fi

    print_status "Instalando SDL2pp desde fuente..."
    local original_dir=$(pwd)
    mkdir -p /tmp/sdl2pp_build && cd /tmp/sdl2pp_build || { print_error "No se pudo crear /tmp/sdl2pp_build"; exit 1; }

    git clone https://github.com/libSDL2pp/libSDL2pp.git || { print_error "Falló la descarga de SDL2pp"; exit 1; }
    cd libSDL2pp || { print_error "No se encontró el directorio libSDL2pp"; exit 1; }
    mkdir build && cd build
    cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local || { print_error "CMake falló para SDL2pp"; exit 1; }
    make -j$(nproc) || { print_error "Error de compilación SDL2pp"; exit 1; }
    sudo make install || { print_error "Error en make install SDL2pp"; exit 1; }
    sudo ldconfig

    cd "$original_dir"
    rm -rf /tmp/sdl2pp_build
    print_success "SDL2pp instalado correctamente desde fuente"
}

install_dependencies() {
    print_status "Instalando dependencias del sistema..."
    sudo apt-get update
    sudo apt-get install -y \
    cmake g++ build-essential pkg-config \
    qtbase5-dev qtmultimedia5-dev libqt5multimedia5-plugins \
    gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly \
    libyaml-cpp-dev \
    libasound2-dev libpulse-dev libaudio-dev libjack-dev libsndio-dev \
    libx11-dev libxext-dev libxrandr-dev libxcursor-dev libxinerama-dev \
    libxi-dev libxss-dev libxxf86vm-dev libxrender-dev \
    libgl1-mesa-dev libglu1-mesa-dev libpng-dev libjpeg-dev libtiff-dev \
    libwebp-dev libfreetype6-dev libharfbuzz-dev libfribidi-dev
    if [[ $? -ne 0 ]]; then
        print_error "Error instalando dependencias del sistema"
        exit 1
    fi

    install_sdl2_from_source
    install_sdl2pp_from_source

    # Asegurar que /usr/local/lib esté en ld.so.conf
    if ! grep -q "/usr/local/lib" /etc/ld.so.conf.d/local.conf 2>/dev/null; then
        echo "/usr/local/lib" | sudo tee /etc/ld.so.conf.d/local.conf
        sudo ldconfig
    fi

    print_success "Dependencias instaladas"
}

compile_and_install() {
    print_status "Compilando proyecto..."
    mkdir -p build && cd build
    cmake .. -DCMAKE_BUILD_TYPE=Release -DCS2D_CLIENT=ON -DCS2D_EDITOR=ON -DCS2D_SERVER=ON || { print_error "Error en cmake"; exit 1; }
    make -j$(nproc) || { print_error "Error de compilación"; exit 1; }
    cd ..

    print_status "Verificando librerías dinámicas de los binarios..."
    ldd build/cs2d_client | grep "not found" && print_warning "Faltan librerías en cs2d_client"

    print_status "Instalando binarios..."
    sudo cp build/cs2d_* "${BINARY_DIR}/" && sudo chmod +x "${BINARY_DIR}/cs2d_"*

    print_status "Copiando archivos del juego..."
    sudo mkdir -p "${VAR_DIR}/assets/gfx" "${VAR_DIR}/assets/sfx" "${VAR_DIR}/maps"
    sudo mkdir -p "${ETC_DIR}/cfg"
    [[ -d assets/gfx ]] && sudo cp -r assets/gfx/* "${VAR_DIR}/assets/gfx/"
    [[ -d assets/sfx ]] && sudo cp -r assets/sfx/* "${VAR_DIR}/assets/sfx/"
    [[ -d server/maps ]] && sudo cp -r server/maps/* "${VAR_DIR}/maps/"
    [[ -f server/game_config.yaml ]] && sudo cp server/game_config.yaml "${ETC_DIR}/cfg/"

    print_success "¡Instalación completada!"
}

run_install() {
    echo "==== ${PROJECT_FULL_NAME} - INSTALACIÓN ===="
    install_dependencies
    compile_and_install
}

run_uninstall() {
    echo "==== ${PROJECT_FULL_NAME} - DESINSTALACIÓN ===="
    confirm_action "¿Estás seguro que querés desinstalar $PROJECT_FULL_NAME?" || exit 0

    for bin in cs2d_client cs2d_editor cs2d_server; do
        [[ -f "${BINARY_DIR}/$bin" ]] && sudo rm -f "${BINARY_DIR}/$bin"
    done

    sudo rm -rf "${VAR_DIR}" "${ETC_DIR}" build

    confirm_action "¿Querés desinstalar las dependencias del sistema? Esto puede afectar otros proyectos." && \
    sudo apt-get remove -y qtbase5-dev qtmultimedia5-dev libqt5multimedia5-plugins \
        libyaml-cpp-dev libasound2-dev libpulse-dev libaudio-dev \
        libjack-dev libsndio-dev libx11-dev libxext-dev libxrandr-dev \
        libxcursor-dev libxinerama-dev libxi-dev libxss-dev libxxf86vm-dev \
        libxrender-dev libgl1-mesa-dev libglu1-mesa-dev libpng-dev \
        libjpeg-dev libtiff-dev libwebp-dev libfreetype6-dev libharfbuzz-dev libfribidi-dev

    print_success "¡Desinstalación completa!"
}

show_ascii_art() {
    cat << 'EOF'

        ------            -------           ------           ------              
    ---------------   ---------------   -------------- -----------------    
  ----√√√√√√√√√√∞-------√√√√√√√√√√∞-------√√√√√√√√√∞-----√√√√√√√√√√√√∞≠---- 
 ---√√√∞∞∞∞∞∞∞∞∞∞∞∞---∞√√∞∞∞∞∞∞∞∞∞∞∞∞---√√√∞∞∞∞∞∞∞∞∞∞∞---∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞---
---∞√√∞∞∞∞∞≠∞∞∞∞∞∞∞≠-×√√∞∞∞∞∞≠∞∞∞∞∞∞∞--∞√√∞∞∞∞--∞∞∞∞∞∞∞--∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞---
---√√∞∞∞∞∞--∞∞∞∞∞∞∞∞-≠∞∞∞∞∞∞≈-=∞∞∞∞∞∞--∞∞∞∞∞∞≠--∞√∞∞∞∞∞--∞∞∞∞∞∞∞--∞∞∞∞∞∞∞=--
---√√∞∞∞∞∞--∞∞∞∞∞∞∞∞-≠∞∞∞∞∞∞∞-÷∞∞∞∞∞∞--∞∞∞∞∞∞≠--√√∞∞∞∞∞--∞∞∞∞∞∞∞--∞∞∞∞∞∞∞≈--
---∞∞∞∞∞∞∞--∞∞∞∞∞∞∞∞--∞∞∞∞∞∞∞∞∞×---------------√√∞∞∞∞∞÷--∞∞∞∞∞∞∞--∞∞∞∞∞∞∞≈--
---∞∞∞∞∞∞∞---≈≈≠≠≈≈÷---∞∞∞∞∞∞∞∞∞∞∞---- -------√√∞∞∞∞∞∞---∞∞∞∞∞∞∞--∞∞∞∞∞∞∞≈--
---∞∞∞∞∞∞∞--------------=∞∞∞∞∞∞∞∞∞∞∞----  ---√√∞∞∞∞∞∞----∞∞∞∞∞∞∞--∞∞∞∞∞∞∞≈--
---∞∞∞∞∞∞∞-----------------∞∞∞∞∞∞∞∞∞∞--- ---√√∞∞∞∞∞÷-----∞∞∞∞∞∞∞--∞∞∞∞∞∞∞≈--
---∞∞∞∞∞∞∞--∞√√√√√∞∞--√√√√√√≠-∞∞∞∞∞∞∞∞----×√√∞∞∞∞∞-------∞∞∞∞∞∞∞--∞∞∞∞∞∞∞≈--
---∞∞∞∞∞∞∞--∞∞∞∞∞∞∞∞-×∞√√√∞∞∞--∞∞∞∞∞∞∞---=√√∞∞∞∞∞---  ---∞∞∞∞∞∞∞--∞∞∞∞∞∞∞≠--
---∞∞∞∞∞∞∞--∞√∞∞∞∞∞∞--∞∞∞∞∞∞∞--√√∞∞∞∞∞--∞√√∞∞∞∞∞---------∞∞∞∞∞∞∞--√√∞∞∞∞∞≠--
 --≠∞∞∞∞∞∞∞√√√∞∞∞∞∞---∞∞∞∞∞∞∞√√√√∞∞∞∞∞-√√√∞∞∞∞∞√√√√√√∞×--∞∞∞∞∞∞∞√√√√∞∞∞∞∞---
 ---∞∞∞∞∞∞∞√∞∞∞∞∞∞-----∞∞∞∞∞∞√√∞∞∞∞∞∞--∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞×--∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞---
  ----÷∞∞∞∞∞∞∞∞∞---- ----≈∞∞∞∞∞∞∞∞≠----∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞×--∞∞∞∞∞∞∞∞∞∞∞∞∞=---- 
    --------------     --------------------------------------------------   
         ----               ----             ----             ----

EOF
}

show_menu() {
    clear
    show_ascii_art
    echo "======================================"
    echo "      ${PROJECT_FULL_NAME} - INSTALADOR"
    echo "======================================"
    echo "1) Instalar"
    echo "2) Desinstalar"
    echo "3) Salir"
    echo
    echo -n "Seleccione una opción [1-3]: "
    read -r choice
    echo

    case "$choice" in
        1) run_install ;;
        2) run_uninstall ;;
        3) echo "Saliendo..."; exit 0 ;;
        *) echo "Opción inválida"; sleep 1; show_menu ;;
    esac
}

# Ejecutar como root
if [[ $EUID -ne 0 ]]; then
    print_warning "Este script requiere permisos de administrador."
    print_status "Ejecutando con sudo..."
    exec sudo "$0"
fi

show_menu

