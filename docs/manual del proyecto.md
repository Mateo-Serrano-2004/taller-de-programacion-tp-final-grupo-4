# Manual del Proyecto

## División de Tareas

Una vez dada la consigna, el corrector nos recomendó una posible división del trabajo, la cual decidimos respetar.

### Responsabilidades por Integrante

- **Camila Mantilla**: Es la encargada de realizar el Qt Editor y la interfaz del juego inicialmente, básicamente el pre-partida.
- **Jonathan Dominguez**: Es el encargado de realizar toda la comunicación mediante sockets en ambos lados (cliente-servidor) y a su vez, es también el que maneja todo lo relacionado con los hilos.
- **Marcos Navarro**: Es el encargado de manejar toda la información/lógica del juego del lado del servidor.
- **Mateo Serrano**: Es el encargado de implementar la interfaz gráfica, usando SDL2pp, y la lógica del microcontrolador del lado del cliente.

### Cronograma

El proyecto consta de máximo 7 semanas, donde vamos a plasmar en este mismo documento lo realizado semanalmente. Donde en la 5ta semana es la primera entrega y en la 7ma la última.

---

## Entorno de Desarrollo

### IDE y Herramientas

El equipo del proyecto estaba ya familiarizado con IDEs basados en VSCode, y fue el IDE junto con Cursor que se usó. Además todo el equipo trabajó sobre WSL, dado que es con lo que ya venían trabajando.

### Librerías Externas

- **SDL2pp**: se utiliza para implementar el motor gráfico.
- **Qt editor**: se utiliza para hacer editor de mapas y el lobby.
- **Google Test**: se usó para verificar el correcto funcionamiento de los protocolos.

### Estándares de Código

Se utilizó un estándar de código definido en un archivo clang-format, cppcheck para revisiones estáticas de código, y cpplint como linter.

---

## Semanas de Trabajo

### Semana 1 (6/5 - 13/5)

**Camila Mantilla**:

Lectura y aprendizaje básico de QT. Instalación de QTCreator y QTDesigner. Tutorial de la cátedra. Realización de ejemplos pequeños del manejo de QT.

**Jonathan Dominguez**:

 Implementación simple del protocolo para ambas partes, con un DTO básico que debería de cumplir las exigencias de una partida.

**Marcos Navarro**:

Definición de un GameLogic como componente central encargado de aplicar las reglas del juego a cada partida (rondas, condiciones de victoria, daño, compras, etc.). Definición de la lógica de física, responsable del movimiento, las colisiones, y la simulación de trayectoria e impacto de disparos. Definición de entidades colisionables.

**Mateo Serrano**:

Familiarización con el entorno de trabajo. Instalación de SDL2pp y dependencias, prueba de tests y planificación de wrappers específicos del proyecto.

---

### Semana 2 (13/5 - 20/5)

**Camila Mantilla**:

Creación del lobby en QTCreator más eventos.

**Jonathan Dominguez**:

Manejo de eventos con Variantes y Visitor. Implementación Dummy de un GameManager y de un Game.

**Marcos Navarro**:

Lógica de negocio, round y player básico.

**Mateo Serrano**:

Implementación de clases de ventana, renderizadores, textura y manager de texturas, básicos, para empezar a probar renderizado. Implementación de un controlador local sincronizado y una capa de sincronización por cola de mensajería en el lado del cliente.

---

### Semana 3 (20/5 - 27/5)

**Camila Mantilla**:

Configuración de Cmake para el lobby en Qt5 por consola. Señales para el protocolo y creación del controlador.

**Jonathan Dominguez**:

Implementación completa de un GameManager.
Y conexión con cliente y servidor mediante hilos.

**Marcos Navarro**:

Implementación de ciclo de la partida a un tickrate constante. Procesamiento de eventos de movimientos y su lógica para la partida y el jugador. Creación de un snapshot de la partida con la posición de cada jugador conectado para broadcastearla a los clientes. Test de lógica de player y partida.

**Mateo Serrano**:

Implementación de eventos de movimiento y rotación.

---

### Semana 4 (27/5 - 3/6)

**Camila Mantilla**:

Creación del editor y formato yaml base del mapa.

**Jonathan Dominguez**:

Ayuda en la creación del editor.

**Marcos Navarro**:

Creación de ronda. Mejora de movimiento y ronda con manejo de tiempo con recupero de ticks.

**Mateo Serrano**:

Unificación del trabajo hasta el momento. Compatibilidad con QT5. Cambio de la arquitectura del proyecto. Aplicación de nuevos patrones de diseño, actualización de la implementación de eventos.

---

### Semana 5 (3/6 - 10/6)

**Camila Mantilla**:

 Fixes del Editor. Creación del parser.

**Jonathan Dominguez**:

Ayuda en la creación del parser y agrego el envío de las texturas del mapa por protocolo.

**Marcos Navarro**:

Implementación de arma básica, cambio de arma, compra de arma, lógica de economía, un GameLogic, disparo básico.

**Mateo Serrano**:

Extensión de los recursos gráficos en SDL. Incorporación de eventos y contextos dentro del juego.

---

### Semana 6 (10/6 - 17/6)

**Camila Mantilla**:

Implementación del parser para el Yaml config del juego y estructuramiento del mismo.

**Jonathan Dominguez**:

Refactor al protocolo y a la queue del sender del cliente, para poder mandar cualquier cosa.

**Marcos Navarro**:

Mejora en ronda y cambio de estado. Refactor de armas, manejo de bomba  y demás features. Mejora de disparo.

**Mateo Serrano**:

Se incluyen algunas animaciones, eventos y manejo de disparos, entre otros features.

---

### Semana 7 (17/6 - 24/6)

**Camila Mantilla**:

Armado de la documentación del proyecto.

**Jonathan Dominguez**:

Implementación completa de los test y arreglo de errores. Y ayuda en el armado de los documentos. Creación del instalador de juego.

**Marcos Navarro**:

Dropeo de weapon por casos. Swap de teams. Uso de configs para los parámetros de game, round y weapon. Sistema de colisiones. Compra munición y arreglo de disparo y recarga. Mejora de disparo por colisiones. Fixes en general.

**Mateo Serrano**:

Se añade el mapa, nuevas animaciones, tablero de estadísticas, configuración, sonidos.

## Features no implementadas

- El editor no puede crear mapas con armas.
- No hay música de fondo en el juego.
- No hay sonido de cargador vacio ni de pasos.
- No se puede cambiar ni el volumen de los sonidos ni los FPS.
- No hay sonidos con distancia.
- No se puede cambiar el keybinding.
- No se puede seleccionar el equipo al ingresar partida ni elegir la skin cuando cambias de equipo automáticamente.
