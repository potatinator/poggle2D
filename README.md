# 3D experiment
## build and run
to build and run the program, run<br/>
```g++ main.cpp shader.cpp gameobject.cpp glad.c -o build/src/2d -lglfw -lGL -lglm -lassimp && ./build/src/2d  ```<br/>
or on windows:
```g++ main.cpp shader.cpp gameobject.cpp glad.c -o build/src/2d.exe -lglfw -lGL -lglm -lassimp```<br/>
``` ./build/src/2d.exe  ```<br/>
this will compile to /build/src/3d, then run it. make sure the dir exists, the command is run from the 3d dir, and all includes are installed
## required packages
 - glfw
 - glm
 - assimp
 - glew(GL)# pogle
