#include "include/player.hpp"
#include <raylib.h>
#include <raymath.h>

Player::Player() {
    this->position = {0, 1.6, 0};

    this->camera = new Camera3D;

    this->camera->position = this->position;
    this->camera->fovy = 60;
    this->camera->projection = CAMERA_PERSPECTIVE;
    this->camera->target = {1, 0, 0};
    this->camera->up = {0, 1, 0};

}

void Player::update() {
    Vector3 movement = this->getMovement();
    Vector3 rotation = this->getRotation();

    UpdateCameraPro(this->camera, movement, rotation, 0.0f);
}

Vector3 Player::getMovement() {
    Vector3 movement = Vector3Zero();

    if(IsKeyDown(KEY_W))
        movement = Vector3Add(movement, {1, 0, 0});
    if(IsKeyDown(KEY_S))
        movement = Vector3Add(movement, {-1, 0, 0});
    if(IsKeyDown(KEY_A))
        movement = Vector3Add(movement, {0, -1, 0});
    if(IsKeyDown(KEY_D))
        movement = Vector3Add(movement, {0, 1, 0});

    movement = Vector3Normalize(movement);

    float speed = IsKeyDown(KEY_LEFT_SHIFT) ? SPRINTING_SPEED : WALKING_SPEED;
    movement = Vector3Scale(movement, speed*GetFrameTime());

    return movement;
}

Vector3 Player::getRotation() {
    Vector3 rotation = Vector3Zero();
    Vector2 mouseMovement = Vector2Scale(GetMouseDelta(), SENSITIVITY);

    rotation.x = mouseMovement.x;
    rotation.y = mouseMovement.y;

    return rotation;
}

Camera3D* Player::getCamera() const { return this->camera; }
