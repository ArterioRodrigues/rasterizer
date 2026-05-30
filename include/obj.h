#pragma once
#include "pch.h"

struct Triangle {
    int a, b, c;
};

struct Mesh {
    std::vector<Vec2> uv;
    std::vector<Vec3> vertices;
    std::vector<Triangle> uv_indexs;
    std::vector<Triangle> vertex_indexs;
    std::vector<Triangle> normal_indexs;
};

Mesh load_obj(const std::string &path);
