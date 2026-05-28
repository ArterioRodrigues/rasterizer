g++ -std=c++20 -o main src/main.cpp src/renderer.cpp src/sdl_context.cpp src/camera.cpp $(sdl2-config --cflags --libs)

mv main build/
./build/main
