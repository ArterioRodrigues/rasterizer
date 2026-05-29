#include "../include/camera.h"
#include "../include/configuration.h"
#include "../include/obj.h"
#include "../include/renderer.h"
#include "../include/sdl_context.h"
#include "../include/texture.h"

bool toggle = true;
Camera camera;
Mesh mesh = load_obj("./build/cube.obj");

Texture t;
bool handle_keydown(SDL_Keycode code) {
    float yaw_radians = camera.yaw * (std::numbers::pi / 180.0);
    Vec3 forward = {std::sin(yaw_radians), 0.0f, -std::cos(yaw_radians)};
    Vec3 right = {std::cos(yaw_radians), 0.0f, std::sin(yaw_radians)};

    switch (code) {
    case SDLK_w:
        camera.position = camera.position + forward;
        return true;
    case SDLK_s:
        camera.position = camera.position - forward;
        return true;
    case SDLK_a:
        camera.position = camera.position - right;
        return true;
    case SDLK_d:
        camera.position = camera.position + right;
        return true;

    case SDLK_h:
        camera.yaw -= 10;
        return true;
    case SDLK_l:
        camera.yaw += 10;
        return true;

    case SDLK_j:
        camera.pitch += 10;
        return true;
    case SDLK_k:
        camera.pitch -= 10;
        return true;

    case SDLK_t:
        toggle = !toggle;
        return true;
    }

    return true;
}

void update_world() { draw_mesh(camera, mesh, toggle ? SOLID : WIREFRAME); }

bool loop() {
    while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
        case SDL_QUIT:
            return false;
        case SDL_KEYDOWN:
            return handle_keydown(event.key.keysym.sym);
        }
    }

    clear_framebuffer(WHITE);
    clear_depthbuffer(1.0f);
    update_world();

    SDL_UpdateTexture(texture, NULL, framebuffer, WINDOW_W * sizeof(uint32_t));
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    return true;
}

int main() {
    init_sdl();

    load_texture(t, "build/img.png");
    while (loop())
        SDL_Delay(10);

    kill_sdl();
    return 0;
}
