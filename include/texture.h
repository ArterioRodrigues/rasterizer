#pragma once
#include "pch.h"

struct Texture {
    int width, height, channels;
    std::vector<uint32_t> pixels;
};

void load_texture(Texture &texture, const char *path);
