#include "include/player.hpp"
#include <cmath>
#include <raylib.h>
#include <raymath.h>

Player::Player(Vector2 pos) {
    this->position = {pos.x, PLAYER_HEIGHT - 0.1f, pos.y};
    this->collisionBox = {{position.x - COLLISION_SIZE, 0.0f, position.z - COLLISION_SIZE},
                          {position.x + COLLISION_SIZE, PLAYER_HEIGHT, position.z + COLLISION_SIZE}};

    row = std::round(position.z / TILE_SIZE);
    col = std::round(position.x / TILE_SIZE);

    this->camera = new Camera3D;

    this->camera->position = this->position;
    this->camera->fovy = 60;
    this->camera->projection = CAMERA_PERSPECTIVE;
    this->camera->target = {1, 0, 0};
    this->camera->up = {0, 1, 0};
}

void Player::update(Map& tileMap) {
    Vector3 movement = this->getMovement(tileMap);
    Vector3 rotation = this->getRotation();

    UpdateCameraPro(this->camera, Vector3Zero(), rotation, 0.0f);
    this->camera->position = Vector3Add(movement, this->camera->position);
    this->camera->target = Vector3Add(movement, this->camera->target);

    this->position = camera->position;
    this->collisionBox = {{position.x - COLLISION_SIZE, 0.0f, position.z - COLLISION_SIZE},
                          {position.x + COLLISION_SIZE, PLAYER_HEIGHT, position.z + COLLISION_SIZE}};

    row = std::round(position.z / TILE_SIZE);
    col = std::round(position.x / TILE_SIZE);
}

Vector3 Player::getMovement(Map& map) { 

    Vector3 movement = Vector3Zero();

    Vector3 forward = Vector3Subtract(this->camera->target, this->camera->position);
    forward.y = 0.0f;
    forward = Vector3Normalize(forward);

    Vector3 right = Vector3CrossProduct(forward, {0.0f, 1.0f, 0.0f});

    if(map.isWall(row, col)) {
        camera->position = {round(position.x), position.y, round(position.z)};
        position = camera->position;
    } 

    if(IsKeyDown(KEY_W))
        movement = Vector3Add(movement, forward);
    if(IsKeyDown(KEY_S))
        movement = Vector3Add(movement, Vector3Negate(forward));
    if(IsKeyDown(KEY_A))
        movement = Vector3Add(movement, Vector3Negate(right));
    if(IsKeyDown(KEY_D))
        movement = Vector3Add(movement, right);

    movement = Vector3Normalize(movement);

    if(map.isWall(row, col + 1) && CheckCollisionBoxes(*map.getCollision(row, col + 1), this->collisionBox)) {
        movement.x = movement.x > 0 ? 0 : movement.x;
    } else if(map.isWall(row, col - 1) && CheckCollisionBoxes(*map.getCollision(row, col - 1), this->collisionBox)) {
        movement.x = movement.x < 0 ? 0 : movement.x;
    }
    
    if(map.isWall(row - 1, col) && CheckCollisionBoxes(*map.getCollision(row - 1, col), this->collisionBox)) {
        movement.z = movement.z < 0 ? 0 : movement.z;
    } else if(map.isWall(row + 1, col) && CheckCollisionBoxes(*map.getCollision(row + 1, col), this->collisionBox)) {
        movement.z = movement.z > 0 ? 0 : movement.z;
    }

    float speed = IsKeyDown(KEY_LEFT_SHIFT) ? SPRINTING_SPEED : WALKING_SPEED;
    movement = Vector3Scale(movement, GetFrameTime()*speed);

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
