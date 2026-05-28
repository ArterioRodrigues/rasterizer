#pragma once
#include "pch.h"

struct Triangle {
    int a, b, c;
};

struct Mesh {
    std::vector<Vec3> vertices;
    std::vector<Triangle> faces;
};

Mesh load_obj(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << "Error: Couldn't open file!" << std::endl;
        system("halt");
    }

    Mesh mesh;
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty() && (line[0] == 'v' || line[0] == 'f') && line[1] == ' ') {
            std::stringstream ss(line);
            char type;
            float x, y, z;

            ss >> type >> x >> y >> z;
            type == 'v' ? mesh.vertices.push_back(Vec3{x, y, z})
                        : mesh.faces.push_back(Triangle{int(x - 1), int(y - 1), int(z - 1)});
        }
    }
    return mesh;
}
