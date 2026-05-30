#pragma once

struct Vec3 {
    float x, y, z;
    Vec3 operator-(Vec3 &other) { return Vec3{x - other.x, y - other.y, z - other.z}; }
    Vec3 operator-(Vec3 &&other) { return Vec3{x - other.x, y - other.y, z - other.z}; }
    Vec3 operator+(Vec3 &other) { return Vec3{x + other.x, y + other.y, z + other.z}; }
    Vec3 operator+(Vec3 &&other) { return Vec3{x + other.x, y + other.y, z + other.z}; }
    Vec3 operator*(int &n) { return Vec3{x + n, y + n, z + n}; }
    Vec3 operator*(int &&n) { return Vec3{x + n, y + n, z + n}; }
};

struct Vec2 {
    float x, y;
};

struct Point {
    int x, y;
    float z;
};
