# 2D Gravity Simulator

![C++](https://img.shields.io/badge/Language-C++-blue)
![SFML](https://img.shields.io/badge/SFML-3.0.2-orange)
![License](https://img.shields.io/badge/License-MIT-green)

**Description**
Interactive simulator of 2D bodies with gravitational forces written in **C++** using **SFML**. The user can create bodies dynamically adjusting their mass, size, color and initial velocity, and visualize their trajectories in real time.

## Features
- 2D Gravity simulation with multiple bodies
- Creation of bodies with left mouse click
- Adjustment of initial velocity by moving the mouse
- Adjustment of mass and radius using the mouse wheel
- Change of body color while creating it
- Visualization of the trajectories
- Real-time FPS display

## Dependencies
- **C++ compiler**: g++ 10 or above (support for C++17)
- **make**  
- [SFML 3.0.2](https://www.sfml-dev.org/)


## Compilation
1. Navigate to the `/build` dir:
```bash
cd build
```
2. Execute `make` to compile the project:
```bash
make
```
## Future improvements
Potential enhancements for the simulator:
- **Collision handling**: Implement physical interactions between bodies to prevent overlapping
- **Simulation control**: Add features to pause, resume and run the simulation backwards
- **UI enhancements**: Include sliders or panels for the creation and adjustment of bodies
