#pragma once
#include "pch.h"

struct Triangle {
    int a, b, c;
};

struct Mesh {
    std::vector<Vec2> uv;
    std::vector<int> uv_indices;
    std::vector<Vec3> vertices;
    std::vector<Triangle> faces;
};

Mesh load_obj(const std::string &path);
