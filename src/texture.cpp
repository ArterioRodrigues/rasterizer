#include "../include/texture.h"

Texture load_texture(const char *path) {
    Texture texture;
    unsigned char *data = stbi_load(path, &texture.width, &texture.height, &texture.channels, 4);
    uint32_t buffer = 0;

    for (int i = 0; i < texture.width * texture.height * 4; i++, data++) {
        buffer += (uint32_t)*data << (i % 4) * 8;

        if (i % 4 != 3)
            continue;

        texture.pixels.push_back(buffer);
        buffer = 0;
    }

    return texture;
}
