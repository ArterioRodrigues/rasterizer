#pragma once
#include "camera.h"
#include "obj.h"
#include "texture.h"
#include "pch.h"

enum RenderMode { SOLID, WIREFRAME, TEXTURE};

extern uint32_t *framebuffer;
extern float *depthbuffer;

void clear_framebuffer(uint32_t color);
void clear_depthbuffer(float depth);

void set_pixel(int x, int y, uint32_t color);
void draw_line(int x0, int y0, int x1, int y1, uint32_t color);
void draw_line(int x0, int y0, float z0, int x1, int y1, float z1, uint32_t color);
void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void draw_triangle(int x0, int y0, float z0, int x1, int y1, float z1, int x2, int y2, float z2, uint32_t color);
void draw_rectangle(Vec3 a, Vec3 b, Vec3 c, Vec3 d, uint32_t color);
void draw_mesh(Camera camera, Mesh mesh, Texture &texture, RenderMode mode);
