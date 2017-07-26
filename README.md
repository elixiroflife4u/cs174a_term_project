# cs174a-term-project

Final project for UCLA 174A Graphics I put together with team Tarun Solanki, Mike Sechooler, Howard ??, and Garrett Johnson

![image](/docs/image1.png)

## Controls

### Basic
Basic controls for operating the main character
```
ESC		quit

W 		move forward
A 		move left
D 		move right
S 		move back

Q E 		cycle weapon
SPACE 		jump (with a tank?!)

Mouse 		look direction

Left Click 	shoot
Right Click 	enable shield
```

### Debug
Controls for toggling a variety of graphics features
```
P O		increase / decrease normal map depth

L K 		enable / disable fog layer

;		enter full screen (cannot get out, must exit with 'esc')
"		enter first person view
```

### UI
Top bar is health

Bottom bar is shield recharge

## Technologies and Dependencies
### Advanced topics
#### Collision Detection
AABB and sphere collision on environment and characters in conjunction with basic physics

#### Normal Mapping
Normal map in shader with variable intensity

#### Multiple Lights
Support for up to 10 dynamic point lights

#### Render Texture Rendering
Rendering to render texture to create "portals"

### Other
#### Load OBJs
Use library (presumably from [this repo](https://github.com/stcui/Obj-Loader)) to load obj models

#### Sound
Play back sounds using SDL

#### Image Loading
DevIL to load images

#### Graphics
Use GLUT, OpenGL to set up and interact with GPU

Used helper code from Angel to get handle some math from [here](http://www.cs.unm.edu/~angel/BOOK/INTERACTIVE_COMPUTER_GRAPHICS/SIXTH_EDITION/)
