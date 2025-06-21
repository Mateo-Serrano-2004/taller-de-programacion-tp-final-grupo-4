#!/bin/bash

# Counter Strike 2D - Desinstalador del Sistema
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

# Función para confirmar acción
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

# Función para verificar permisos de administrador
check_admin_permissions() {
    if [[ $EUID -ne 0 ]]; then
        print_warning "Este desinstalador requiere permisos de administrador"
        print_status "Ejecutando con sudo..."
        sudo "$0" "$@"
        exit $?
    fi
}

# Función para eliminar binarios del sistema
remove_system_binaries() {
    print_status "Eliminando binarios del sistema..."
    
    local binaries=("cs2d_client" "cs2d_editor" "cs2d_server")
    
    for binary in "${binaries[@]}"; do
        if [[ -f "${BINARY_DIR}/${binary}" ]]; then
            sudo rm -f "${BINARY_DIR}/${binary}"
            print_success "Binario ${binary} eliminado de ${BINARY_DIR}"
        fi
    done
}

# Función para eliminar directorios del sistema
remove_system_directories() {
    print_status "Eliminando directorios del sistema..."
    
    if [[ -d "${VAR_DIR}" ]]; then
        sudo rm -rf "${VAR_DIR}"
        print_success "Directorio ${VAR_DIR} eliminado"
    fi
    
    if [[ -d "${ETC_DIR}" ]]; then
        sudo rm -rf "${ETC_DIR}"
        print_success "Directorio ${ETC_DIR} eliminado"
    fi
}

# Función para limpiar archivos de build
clean_build_files() {
    print_status "Limpiando archivos de compilación..."
    
    if [[ -d "build" ]]; then
        rm -rf build
        print_success "Directorio build eliminado"
    fi
    
    if [[ -f "Makefile" ]]; then
        make clean 2>/dev/null || true
        print_success "Archivos temporales de make eliminados"
    fi
}

# Función para eliminar accesos directos del escritorio
remove_desktop_shortcuts() {
    print_status "Eliminando accesos directos del escritorio..."
    
    DESKTOP_DIR="$HOME/Desktop"
    if [[ -n "$XDG_DESKTOP_DIR" ]]; then
        DESKTOP_DIR="$XDG_DESKTOP_DIR"
    fi
    
    local shortcuts=(
        "${PROJECT_FULL_NAME} - Cliente.desktop"
        "${PROJECT_FULL_NAME} - Editor.desktop"
    )
    
    for shortcut in "${shortcuts[@]}"; do
        if [[ -f "$DESKTOP_DIR/$shortcut" ]]; then
            rm -f "$DESKTOP_DIR/$shortcut"
            print_success "Acceso directo $shortcut eliminado"
        fi
    done
}

# Función para desinstalar dependencias (opcional)
uninstall_dependencies() {
    if confirm_action "¿Deseas desinstalar las dependencias del sistema? (Esto puede afectar otros proyectos)"; then
        print_warning "Desinstalando dependencias del sistema..."
        
        # Ubuntu 24.04 LTS
        sudo apt-get remove -y qtbase5-dev qtmultimedia5-dev libqt5multimedia5-plugins \
            libyaml-cpp-dev libgtest-dev libasound2-dev libpulse-dev libaudio-dev \
            libjack-dev libsndio-dev libx11-dev libxext-dev libxrandr-dev \
            libxcursor-dev libxinerama-dev libxi-dev libxss-dev libxxf86vm-dev \
            libxrender-dev libgl1-mesa-dev libglu1-mesa-dev libpng-dev \
            libjpeg-dev libtiff-dev libwebp-dev libfreetype6-dev \
            libharfbuzz-dev libfribidi-dev
        
        print_success "Dependencias de Ubuntu 24.04 LTS eliminadas"
    else
        print_status "Saltando desinstalación de dependencias"
    fi
}

# Función para mostrar información de desinstalación
show_uninstall_info() {
    print_success "¡Desinstalación completada!"
    echo
    echo "=== ARCHIVOS ELIMINADOS ==="
    echo "✓ Binarios del sistema (${BINARY_DIR}/cs2d_*)"
    echo "✓ Directorios del sistema (${VAR_DIR}/, ${ETC_DIR}/)"
    echo "✓ Archivos de compilación (build/)"
    echo "✓ Accesos directos del escritorio"
    echo
    echo "=== NOTAS ==="
    echo "• El código fuente del proyecto permanece intacto"
    echo "• Puedes volver a instalar ejecutando: sudo ./install.sh"
    echo "• Las dependencias del sistema no fueron eliminadas por seguridad"
    echo
}

# Función principal
main() {
    echo "=========================================="
    echo "  ${PROJECT_FULL_NAME} - DESINSTALADOR DEL SISTEMA"
    echo "  Compatible con Ubuntu 24.04 LTS"
    echo "=========================================="
    echo
    
    # Verificar si estamos en el directorio correcto
    if [[ ! -f "CMakeLists.txt" ]]; then
        print_error "Este script debe ejecutarse desde el directorio raíz del proyecto"
        exit 1
    fi
    
    # Verificar permisos de administrador
    check_admin_permissions "$@"
    
    # Confirmar desinstalación
    if ! confirm_action "¿Estás seguro de que deseas desinstalar ${PROJECT_FULL_NAME} del sistema?"; then
        print_status "Desinstalación cancelada"
        exit 0
    fi
    
    # Eliminar binarios del sistema
    remove_system_binaries
    
    # Eliminar directorios del sistema
    remove_system_directories
    
    # Limpiar archivos de build
    clean_build_files
    
    # Eliminar accesos directos
    remove_desktop_shortcuts
    
    # Opcional: desinstalar dependencias
    uninstall_dependencies
    
    # Mostrar información final
    show_uninstall_info
}

# Ejecutar función principal
main "$@" 