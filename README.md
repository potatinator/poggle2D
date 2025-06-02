# 2D engine
## build and run
to build and run the program, run<br/>
```g++ main.cpp shader.cpp gameobject.cpp texture.cpp game.cpp ui.cpp glad.c -o build/src/2d -I./include -lglfw -lGL -lglm -lassimp && ./build/src/2d  ```<br/>
or on windows:<br/>
```g++ main.cpp shader.cpp gameobject.cpp texture.cpp game.cpp ui.cpp glad.c -o build/src/2d.exe -I./include -L/ucrt64/lib -lopengl32 -lglfw3 -lgdi32 -lassimp```<br/>
``` ./build/src/2d.exe  ```<br/>
this will compile to /build/src/2d, then run it. make sure the dir exists, the command is run from the 3d dir, and all includes are installed
## dependancies
 - glfw(mingw-w64-ucrt-x86_64-glfw)
 - assimp(mingw-w64-ucrt-x86_64-assimp)
 - glm(mingw-w64-ucrt-x86_64-glm)
 - opengl(in windows SDK)