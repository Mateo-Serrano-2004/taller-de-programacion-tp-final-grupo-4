# Documentación Técnica - Counter Strike 2D

Este documento describe la arquitectura y estructura técnica del proyecto Counter Strike 2D.

## Índice

- [Arquitectura del Servidor](#arquitectura-del-servidor)
- [Componentes Principales del Servidor](#componentes-principales-del-servidor)
- [Colas de Comunicación](#colas-de-comunicación)
- [Configuración](#configuración)
- [Manejo de Errores](#manejo-de-errores)

## Arquitectura del Servidor

### Estructura de Clases en el Servidor

![Diagrama de clases server](pics/Diagrama_clases_server.png)

### Estructura de Hilos en el Servidor

<img src="pics/Diagrama_hilos_server.png" alt="Diagrama hilos server" width="700">

## Componentes Principales del Servidor

### 1. Server (Hilo Principal)
**Responsabilidad**: Punto de entrada del servidor, inicialización y gestión del ciclo de vida

**Funciones principales**:
- Carga de mapas disponibles desde el directorio `maps/`
- Creación del socket de escucha
- Inicialización del `GameManager` y `Acceptor`
- Control del ciclo de vida del servidor

### 2. Acceptor (Hilo de Aceptación)
**Responsabilidad**: Aceptar nuevas conexiones de clientes

**Funciones principales**:
- Escucha en el socket principal para nuevas conexiones
- Crea instancias de `ClientHandler` para cada cliente conectado
- Gestiona la limpieza de clientes desconectados
- Mantiene una lista de clientes activos

### 3. ClientHandler (Hilo por Cliente)
**Responsabilidad**: Manejo de comunicación con un cliente específico

**Funciones principales**:
- Recepción y procesamiento de eventos del cliente
- Gestión de eventos de lobby (crear/unión de juegos, listar juegos)
- Delegación de eventos de juego al `GameManager`
- Coordinación con `ClientHandlerSender`

### 4. ClientHandlerSender (Hilo de Envío)
**Responsabilidad**: Envío de datos al cliente

**Funciones principales**:
- Procesamiento de cola de mensajes para envío
- Serialización y envío de DTOs al cliente
- Manejo de errores de comunicación

### 5. GameManager (Gestor de Juegos)
**Responsabilidad**: Administración centralizada de todas las partidas

**Funciones principales**:
- Creación y destrucción de juegos
- Gestión del ciclo de vida de las partidas
- Asignación de jugadores a juegos
- Limpieza de juegos terminados

### 6. Game (Hilo de Juego)
**Responsabilidad**: Lógica de una partida específica

**Funciones principales**:
- Procesamiento de eventos de jugadores
- Actualización del estado del juego
- Broadcast del estado a todos los jugadores
- Gestión de rondas y lógica de juego

## Colas de Comunicación

| Cola | Tipo | Descripción |
|------|------|-------------|
| **GameQueue** | `Queue<std::pair<uint8_t, GameEventVariant>>` | Cola de eventos de juego (player_id + GameEventVariant) |
| **SenderQueue** | `Queue<DTO::DTOVariant>` | Cola interna del ClientHandlerSender para enviar los datos al cliente |

## Configuración

### Archivos de Configuración
- **`game_config.yaml`**: Configuración general del juego
  - Parámetros de juego (rondas, tiempo, dinero)
  - Configuración de armas y jugadores
  - Configuración de pantalla y FOV
- **`maps/`**: Archivos YAML con definición de mapas
- **`assets/`**: Recursos gráficos y de sonido

## Manejo de Errores

### Excepciones Específicas
| Excepción | Descripción | Cuándo se lanza |
|-----------|-------------|-----------------|
| **InvalidGameException** | Juego no válido o inexistente | Al intentar unirse a un juego inválido |
| **InvalidPlayerException** | Jugador no válido | Al procesar eventos de jugador inexistente |
| **ClosedQueue** | Cola cerrada | Cliente desconectado |
| **std::exception** | Errores de comunicación de red | Problemas de socket |

### Estrategias de Performance
- **Reap de juegos**: Limpieza automática de juegos terminados
- **Reap de clientes**: Eliminación de clientes desconectados
