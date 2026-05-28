#include "../include/camera.h"

void project(Vec3 point, int &screen_x, int &screen_y, float &depth) {
    screen_x = ((point.x * FOCAL_LENGTH) / -point.z) + (float(WINDOW_W) / 2);
    screen_y = ((-point.y * FOCAL_LENGTH) / -point.z) + (float(WINDOW_H) / 2);

    depth = (-point.z - NEAR_PLANE) / (FAR_PLANE - NEAR_PLANE);
}

Vec3 apply_view(Camera camera, Vec3 point) {
    float yaw_radians = camera.yaw * (std::numbers::pi / 180.0);
    float pitch_radians = camera.pitch * (std::numbers::pi / 180.0);

    point = point - camera.position;

    float x = point.x;
    float y = point.y;
    float z = point.z;

    point.x = x * std::cos(yaw_radians) + z * std::sin(yaw_radians);
    point.z = -x * std::sin(yaw_radians) + z * std::cos(yaw_radians);

    x = point.x;
    y = point.y;
    z = point.z;

    point.y = y * std::cos(pitch_radians) - z * std::sin(pitch_radians);
    point.z = y * std::sin(pitch_radians) + z * std::cos(pitch_radians);

    return point;
}
