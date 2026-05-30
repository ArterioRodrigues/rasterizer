#pragma once
#include "pch.h"

struct Texture {
    int width, height, channels;
    std::vector<uint32_t> pixels;
};

Texture load_texture(const char *path);
