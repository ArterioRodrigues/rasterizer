#include "../include/renderer.h"
#include "../include/camera.h"

uint32_t *framebuffer = static_cast<uint32_t *>(malloc(WINDOW_SIZE * sizeof(uint32_t)));
float *depthbuffer = static_cast<float *>(malloc(WINDOW_SIZE * sizeof(float)));

void clear_framebuffer(uint32_t color) { std::fill(framebuffer, framebuffer + WINDOW_SIZE, color); }
void clear_depthbuffer(float depth) { std::fill(depthbuffer, depthbuffer + WINDOW_SIZE, depth); }

void set_pixel(int x, int y, uint32_t color) {
    if (x < 0 || x >= WINDOW_W || y < 0 || y >= WINDOW_H)
        return;
    framebuffer[y * WINDOW_W + x] = color;
}
void draw_line(int x0, int y0, int x1, int y1, uint32_t color) {
    int error = 0;
    int dy = std::abs(y1 - y0);
    int dx = std::abs(x1 - x0);

    int mx = x1 - x0 < 0 ? -1 : 1;
    int my = y1 - y0 < 0 ? -1 : 1;

    while (x0 != x1 || y0 != y1) {
        set_pixel(x0, y0, color);

        if ((2 * error) >= dx) {
            y0 += my;
            error -= dx;
        } else {
            x0 += mx;
            error += dy;
        }
    }
}

void draw_line(int x0, int y0, float z0, int x1, int y1, float z1, uint32_t color) {
    int error = 0;
    int dy = std::abs(y1 - y0);
    int dx = std::abs(x1 - x0);

    int mx = x1 - x0 < 0 ? -1 : 1;
    int my = y1 - y0 < 0 ? -1 : 1;
    int steps_taken = 0;
    float total_steps = std::max(dx, dy);

    while (x0 != x1 || y0 != y1) {
        float t = steps_taken / total_steps;
        float depth = z0 * (1.0 - t) + z1 * t;
        if (!(x0 < 0 || x0 >= WINDOW_W || y0 < 0 || y0 >= WINDOW_H) && (depth < depthbuffer[y0 * WINDOW_W + x0])) {
            depthbuffer[y0 * WINDOW_W + x0] = depth;
            set_pixel(x0, y0, color);
        }

        if ((2 * error) >= dx) {
            y0 += my;
            error -= dx;
        } else {
            x0 += mx;
            error += dy;
        }
        steps_taken++;
    }
}
void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    int min_x = std::min({x0, x1, x2});
    int max_x = std::max({x0, x1, x2});
    int min_y = std::min({y0, y1, y2});
    int max_y = std::max({y0, y1, y2});

    for (int x = min_x; x <= max_x; x++) {
        for (int y = min_y; y <= max_y; y++) {
            int x0_x1 = (x0 - x1) * (y - y1) - (y0 - y1) * (x - x1);
            int x2_x0 = (x2 - x0) * (y - y0) - (y2 - y0) * (x - x0);
            int x1_x2 = (x1 - x2) * (y - y2) - (y1 - y2) * (x - x2);

            if (x0_x1 <= 0 && x1_x2 <= 0 && x2_x0 <= 0 || x0_x1 >= 0 && x1_x2 >= 0 && x2_x0 >= 0)
                set_pixel(x, y, color);
        }
    }
}

void draw_triangle(int x0, int y0, float z0, int x1, int y1, float z1, int x2, int y2, float z2, uint32_t color) {
    int min_x = std::min({x0, x1, x2});
    int max_x = std::max({x0, x1, x2});
    int min_y = std::min({y0, y1, y2});
    int max_y = std::max({y0, y1, y2});

    min_x = std::max(min_x, 0);
    min_y = std::max(min_y, 0);
    max_x = std::min(max_x, WINDOW_W - 1);
    max_y = std::min(max_y, WINDOW_H - 1);

    for (int x = min_x; x <= max_x; x++) {
        for (int y = min_y; y <= max_y; y++) {
            int x0_x1 = (x0 - x1) * (y - y1) - (y0 - y1) * (x - x1);
            int x2_x0 = (x2 - x0) * (y - y0) - (y2 - y0) * (x - x0);
            int x1_x2 = (x1 - x2) * (y - y2) - (y1 - y2) * (x - x2);

            float w0 = static_cast<float>(x1_x2) / (x0_x1 + x2_x0 + x1_x2);
            float w1 = static_cast<float>(x2_x0) / (x0_x1 + x2_x0 + x1_x2);
            float w2 = static_cast<float>(x0_x1) / (x0_x1 + x2_x0 + x1_x2);

            float depth = w0 * z0 + w1 * z1 + w2 * z2;

            if ((x0_x1 <= 0 && x1_x2 <= 0 && x2_x0 <= 0 || x0_x1 >= 0 && x1_x2 >= 0 && x2_x0 >= 0) &&
                depth < depthbuffer[y * WINDOW_W + x]) {
                depthbuffer[y * WINDOW_W + x] = depth;
                set_pixel(x, y, color);
            }
        }
    }
}

void draw_rectangle(Vec3 a, Vec3 b, Vec3 c, Vec3 d, uint32_t color) {
    int ax, ay, bx, by, cx, cy, dx, dy;
    float ad, bd, cd, dd;

    project(a, ax, ay, ad);
    project(b, bx, by, bd);
    project(c, cx, cy, cd);
    project(d, dx, dy, dd);

    draw_triangle(ax, ay, ad, bx, by, bd, cx, cy, cd, color);
    draw_triangle(ax, ay, ad, cx, cy, cd, dx, dy, dd, color);
}

