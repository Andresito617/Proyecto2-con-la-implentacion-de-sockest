# Servidor de Juego de Cartas en C++

Este proyecto implementa un **servidor multijugador en C++** para un juego de cartas desarrollado con programación orientada a objetos. Está diseñado para ejecutarse desde consola y conectar varios clientes en red. Es ideal para prácticas de arquitectura cliente-servidor y manejo de objetos en C++.

---

## 🎮 ¿De qué trata el juego?

El objetivo es ganar la mayor cantidad de rondas posibles utilizando cartas que superen, en color y número, la carta líder jugada por el primer jugador en cada turno. Cada ronda representa un pequeño duelo entre los jugadores, y al final, quien haya ganado más rondas es el ganador de la partida.

---

## 🎮 Descripción del juego

- El juego utiliza un mazo de **36 cartas únicas**.
- Las cartas se dividen en **4 colores**: Azul, Verde, Rojo y Naranja.
- Cada color tiene cartas con números del **1 al 9**, sin repeticiones.
- Las cartas se barajan automáticamente al inicio de la partida.
- Se reparten de forma equitativa según la cantidad de jugadores:
  - 2 jugadores → 18 cartas cada uno.
  - 3 jugadores → 12 cartas cada uno.
  - 4 jugadores → 9 cartas cada uno.

---

## 🕹️ Reglas del juego

1. **Inicio del juego:**
   - Se solicita el número de jugadores (mínimo 2, máximo 4).
   - El sistema selecciona aleatoriamente qué jugador comienza.

2. **Turnos:**
   - El jugador inicial lanza una carta.
   - Los demás deben jugar una carta del **mismo color y con un número mayor**, si pueden.
   - Si no pueden (o deciden no competir), pueden lanzar cualquier carta, pero no podrán ganar esa ronda.

3. **Evaluación:**
   - El jugador que haya jugado la carta **más alta del mismo color inicial** gana la ronda.
   - Las cartas jugadas se retiran del mazo y se usan para calcular puntajes.

4. **Fin del juego:**
   - El juego termina cuando los jugadores se quedan sin cartas.
   - Gana quien haya **ganado más rondas** o acumulado más puntos (dependiendo del criterio implementado).

---

## ⚙️ Características principales

- Servidor escrito en C++ que acepta múltiples conexiones de jugadores.
- Sistema de turnos y manejo de reglas personalizado.
- Clases para abstraer:
  - `Jugador`: almacena nombre, ID y mano de cartas.
  - `Carta`: representa los atributos de cada carta (color, valor, tipo...).
  - `Juego`: lógica del juego, validación de movimientos, turnos y condición de victoria.
  - `Servidor`: maneja conexiones, turnos y ejecución de la partida.

---

## Estructura de Clases

### Jugador
Representa a un jugador con atributos como ID, nombre, y métodos para manipular su mano de cartas.

### Carta
Representa una carta del juego con atributos como tipo, valor o color (según la lógica del juego).

### Juego
Controla la lógica general: inicio de partida, turnos, acciones válidas, y control de ganadores.

### Servidor
Gestiona las conexiones de los jugadores y el ciclo del juego en red (TCP/IP o similar).

## Compilación

Este proyecto requiere `g++` (recomendado: versión que venga con MSYS2, como `ucrt64` en Windows).

Para compilar:

```bash
g++ -std=c++17 -g servidor.cpp jugador.cpp juego.cpp carta.cpp -o servidor.exe

---

Desarrollado por Eduardo Andres Osorio Monsalve
