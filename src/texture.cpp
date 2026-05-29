#include "../include/texture.h"

void load_texture(Texture &texture, const char *path) {
    unsigned char *data = stbi_load(path, &texture.width, &texture.height, &texture.channels, 4);
    uint32_t buffer = 0;

    for (int i = 0; data; i++, data++) {
        buffer +=  (uint32_t)*data << i%4 * 4;

        if (i % 4 != 0)
            continue;

        texture.pixels.push_back(buffer);
        buffer = 0;
    }
}
