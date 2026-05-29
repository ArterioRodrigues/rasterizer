g++ -std=c++20 -o main \
  src/main.cpp src/renderer.cpp src/obj.cpp \
  src/sdl_context.cpp src/camera.cpp src/texture.cpp src/stb_image.cpp \
  $(sdl2-config --cflags --libs)

mv main build/
./build/main
