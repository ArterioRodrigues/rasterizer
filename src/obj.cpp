#include "../include/obj.h"

int parse_int(auto rng) {
    auto sv = std::string_view(rng.begin(), rng.end());
    int val = 0;
    std::from_chars(sv.data(), sv.data() + sv.size(), val);
    return val - 1; 
}

auto parse_face_token(std::string_view token) {
    int indices[3] = {0, 0, 0};
    int i = 0;
    for (auto part : token | std::views::split('/')) {
        if (i < 3)
            indices[i++] = parse_int(part);
    }
    return std::make_tuple(indices[0], indices[1], indices[2]);
}

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
            std::string type, x, y, z;

            ss >> type >> x >> y >> z;
            if (type == "v")
                mesh.vertices.push_back(Vec3{std::stof(x), std::stof(y), std::stof(z)});
            else if (type == "vt")
                mesh.uv.push_back(Vec2{std::stof(x), std::stof(y)});
            else if (type == "f") {
                auto [vx, ux, nx] = parse_face_token(x);
                auto [vy, uy, ny] = parse_face_token(y);
                auto [vz, uz, nz] = parse_face_token(z);

                mesh.vertex_indexs.push_back(Triangle{vx, vy, vz});
                mesh.uv_indexs.push_back(Triangle{ux, uy, uz});
                mesh.normal_indexs.push_back(Triangle{nx, ny, nz});
            }
        }
    }
    return mesh;
}
