#include "include/map.hpp"
#include "include/teachers.hpp"
#include <iostream>
#include <raylib.h>

Texture* Teacher::teachDTexture = nullptr;
Texture* Teacher::teachSTexture = nullptr;
Texture* Teacher::teachRTexture = nullptr;
Texture* Teacher::teachLTexture = nullptr;
Texture* Teacher::teachJTexture = nullptr;

Model* Teacher::teachDModel = nullptr;
Model* Teacher::teachSModel = nullptr;
Model* Teacher::teachRModel = nullptr;
Model* Teacher::teachLModel = nullptr;
Model* Teacher::teachJModel = nullptr;

Teacher::Teacher(int row, int col, Model& model, Map& map)
: row(row), col(col) {
    this->position = new Vector3({row*TILE_SIZE, TILE_SIZE/2.0f, col*TILE_SIZE});
    this->collisionBox = new BoundingBox({{position->x-TILE_SIZE/2.0f,      0.0f, position->z-TILE_SIZE/2.0f},
                                          {position->x+TILE_SIZE/2.0f, TILE_SIZE, position->z+TILE_SIZE/2.0f}});

    this->model = &model;

    this->rightRay = new Ray({*this->position, { 1.0f, 0.0f,  0.0f}});
    this->upRay    = new Ray({*this->position, { 0.0f, 0.0f, -1.0f}});
    this->leftRay  = new Ray({*this->position, {-1.0f, 0.0f,  0.0f}});
    this->downRay  = new Ray({*this->position, { 0.0f, 0.0f,  1.0f}});

    this->map = &map;

    teachers.push_back(this);
}

void Teacher::draw(bool debug) const {
    DrawModel(*this->model, *this->position, 1.0f, WHITE);
    if(debug) {
        DrawRay(*this->rightRay, BLUE);
        DrawRay(*this->upRay, BLUE);
        DrawRay(*this->leftRay, BLUE);
        DrawRay(*this->downRay, BLUE);
        DrawBoundingBox(*this->collisionBox, BLUE);
    }
}

void Teacher::update(Player& player) {
    this->row = (int) this->position->x / TILE_SIZE;
    this->col = (int) this->position->z / TILE_SIZE;

    this->rightRay->position = *this->position;
    this->upRay->position = *this->position;
    this->leftRay->position = *this->position;
    this->downRay->position = *this->position;

    RayCollision rightCollision = GetRayCollisionBox(*rightRay, player.getViewBox());
    RayCollision upCollision = GetRayCollisionBox(*upRay, player.getViewBox());
    RayCollision leftCollision = GetRayCollisionBox(*leftRay, player.getViewBox());
    RayCollision downCollision = GetRayCollisionBox(*downRay, player.getViewBox());
    
    this->seesPlayer = rightCollision.hit || upCollision.hit || leftCollision.hit || downCollision.hit;
    this->seesPlayer = this->seesPlayer ? this->map->checkVision(this->row, this->col, player.getRow(), player.getCol()) : false;

}

Teacher* Teacher::makeTeachD(int row, int col, Map& map) {
    if(teachDTexture == nullptr) {
        teachDTexture = new Texture(LoadTexture("../resources/teachers/teachDTexture.png"));
        teachDModel = new Model(LoadModelFromMesh(GenMeshCube(TILE_SIZE, TILE_SIZE, TILE_SIZE)));
        teachDModel->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *teachDTexture;
    }
    return new Teacher(row, col, *teachDModel, map);
}

Teacher* Teacher::makeTeachS(int row, int col, Map& map) {
    if(teachSTexture == nullptr) {
        teachSTexture = new Texture(LoadTexture("../resources/teachers/teachSTexture.png"));
        teachSModel = new Model(LoadModelFromMesh(GenMeshCube(TILE_SIZE, TILE_SIZE, TILE_SIZE)));
        teachSModel->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *teachSTexture;
    }
    return new Teacher(row, col, *teachSModel, map);
}

Teacher* Teacher::makeTeachR(int row, int col, Map& map) {
    if(teachRTexture == nullptr) {
        teachRTexture = new Texture(LoadTexture("../resources/teachers/teachRTexture.png"));
        teachRModel = new Model(LoadModelFromMesh(GenMeshCube(TILE_SIZE, TILE_SIZE, TILE_SIZE)));
        teachRModel->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *teachRTexture;
    }
    return new Teacher(row, col, *teachRModel, map);
}

Teacher* Teacher::makeTeachL(int row, int col, Map& map) {
    if(teachLTexture == nullptr) {
        teachLTexture = new Texture(LoadTexture("../resources/teachers/teachLTexture.png"));
        teachLModel = new Model(LoadModelFromMesh(GenMeshCube(TILE_SIZE, TILE_SIZE, TILE_SIZE)));
        teachLModel->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *teachLTexture;
    }
    return new Teacher(row, col, *teachLModel, map);
}

Teacher* Teacher::makeTeachJ(int row, int col, Map& map) {
    if(teachJTexture == nullptr) {
        teachJTexture = new Texture(LoadTexture("../resources/teachers/teachJTexture.png"));
        teachJModel = new Model(LoadModelFromMesh(GenMeshCube(TILE_SIZE, TILE_SIZE, TILE_SIZE)));
        teachJModel->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *teachJTexture;
    }
    return new Teacher(row, col, *teachJModel, map);
}
