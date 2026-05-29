#include "../include/obj.h"
Mesh load_obj(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << "Error: Couldn't open file!" << std::endl;
        system("halt");
    }

    Mesh mesh;
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty() && (line[0] == 'v' || line[0] == 'f') && (line[1] == ' ' || line[1] == 't')) {
            std::stringstream ss(line);
            std::string type;
            float x, y, z;

            ss >> type >> x >> y >> z;
            if (type == "v")
                mesh.vertices.push_back(Vec3{x, y, z});
            else if (type == "vt")
                mesh.uv.push_back(Vec2{x, y});
            else if (type == "f")
                mesh.faces.push_back(Triangle{int(x - 1), int(y - 1), int(z - 1)});
        }
    }
    return mesh;
}
