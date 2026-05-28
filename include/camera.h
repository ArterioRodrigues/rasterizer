#pragma once
#include "pch.h"

#define FOCAL_LENGTH 400
#define NEAR_PLANE 0.1f
#define FAR_PLANE 100.0f


struct Camera {
    Vec3 position;
    float yaw;
    float pitch;

    Camera() {
        position = {0, 0, 0};
        yaw = 0;
        pitch = 0;
    }
};

void project(Vec3 point, int &screen_x, int &screen_y, float &depth);
Vec3 apply_view(Camera camera, Vec3 point);
