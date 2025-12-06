# Random Walk Simulation (SDL2)

This project is a simple random‑walk visualizer built using **SDL2**.  
A set of agents start at the center of the window and walk in random directions, leaving colorful trails behind them.

---

## Requirements

You need **SDL2** and its development headers installed.

On Ubuntu/Debian:

```
sudo apt install libsdl2-dev
```

---

## Build Instructions

Compile using:

```
gcc -Wall -Wextra -g -o main main.c `sdl2-config --cflags --libs`
```

This uses `sdl2-config` to automatically pull the correct include paths and library flags.

---

## Usage

Run with default agent count (5 agents):

```
./main
```

Run with custom number of agents:

```
./main 200
```

Agents draw trails as they perform a random walk.

---

## How It Works

• Each agent starts at the center of the window.  
• A random hue is assigned and converted from **HSL to RGB** for vibrant color trails.  
• Every frame, agents pick a random direction from one of four cardinals (up, down, left, right) and move 10 steps.  
• A small 2×2 pixel square is drawn at each position to form the trail.  
• The screen is never cleared, so trails accumulate over time.

---

## Controls

• Close the window to quit.

---

## File Overview

**main.c** — Entry point, SDL setup, agent loop  
**Agent struct** — Stores agent position + RGB color  
**move_agent()** — Random movement + drawing code  
**hsl2rgb()** — Converts hue-based colors into vibrant RGB  
**create_agents()** — Initializes all agents with random colors

---

## Notes

This is a simple visual demo, not a physics simulation.  
Feel free to tweak speed, trail size, color logic, or movement patterns.

---
