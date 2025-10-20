# 3D Rotation Cube Simulation

This project is a simple 3D cube rotation visualizer written in C using OpenGL and GLFW.

## Preview

<img src="https://github.com/user-attachments/assets/f4419a25-05bf-4ba9-8d0e-f1b1fd718489" width="400" />

---

## How I Built This

### 1. **3D Rotation Math**

To rotate a point in 3D, I used rotation matrices for the X, Y, and Z axes, as found on Wikipedia.

<img width="333" height="318" alt="image" src="https://github.com/user-attachments/assets/0a2ac833-11ab-4467-a16e-e907a0ce7473" />


I then combined these matrices to get the full rotation formula for any point.

<img width="761" height="95" alt="image" src="https://github.com/user-attachments/assets/7e50abaa-260a-4805-badd-6d13cca76328" />


### 2. **Using Symbolab**

I used Symbolab to expand and simplify the matrix math.  
This made it easier to write the rotation as C functions.

<img width="921" height="187" alt="image" src="https://github.com/user-attachments/assets/43a4431f-3e26-4719-9646-38be7a1f1a92" />


### 3. **Rotation Functions in C**

With the formulas, I created three functions (`rotateX`, `rotateY`, `rotateZ`) to rotate any point in 3D by its coordinates (like 3, 3, 3).

### 4. **3D to 2D Projection**

To display the cube, I convert the 3D coordinates to 2D using this simplified perspective formula:

```
x' = x / (z/d + 1)
y' = y / (z/d + 1)
```

<img width="603" height="86" alt="image" src="https://github.com/user-attachments/assets/e08f0b74-6310-4a33-844a-2d14bcd19ef8" />


### 5. **Rendering with OpenGL**

I used OpenGL (with help from ChatGPT) to draw lines between the projected points, creating the wireframe cube.

---

## Features

- 3D cube rotation (X, Y, Z axes)
- Manual 3D to 2D projection
- Wireframe rendering
- Real-time animation (60 FPS)
- Clean window exit

## Requirements

- C compiler
- [GLFW](https://www.glfw.org/)
- OpenGL development libraries

## Build & Run

```bash
gcc cube.c -lglfw -lGL -lm -o cube
./cube
```


---
