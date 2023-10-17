g++ -g  -o program $1 -lGL -lGLU -lGLEW $(pkg-config --cflags --libs sdl2)  -lSDL2_image  graphic_engine/windows/window.cpp math_engine/math.cpp graphic_engine/colors/color.cpp graphic_engine/geometry/geometry.cpp graphic_engine/geometry/geometry2.cpp graphic_engine/shaders/Shader.cpp graphic_engine/buffers/buffers.cpp graphic_engine/renderer/renderer.cpp graphic_engine/textures/texture.cpp graphic_engine/transformations/transformation.cpp graphic_engine/pencil/pencil.cpp 
 