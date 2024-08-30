#include "include/map.hpp"
#include <fstream>
#include <raylib.h>
#include <string>

// ############ MAP ############
Map::Map(std::string path) {
    std::ifstream file(path);

    if(!file.is_open()) {
        std::cerr<<"ERROR: Error while opening map: "<<path<<'\n';
    }

    if(!(file>>rows>>cols)) {
        std::cerr<<"ERROR: Error while reading size of map: "<<path<<'\n';
    }

    this->charMap = new char*[rows];

    std::string line;
    std::getline(file, line);
    for(int row = 0; row < rows; row++) {

        if(std::getline(file, line)) { 

            charMap[row] = new char[cols];
            for(int col = 0; col < cols; col++)
                charMap[row][col] = line[col];

        } else {
            std::cerr<<"ERROR: Error while reading map: "<<path<<'\n';
        }

    }

    this->tileMap = Tile::makeTileMap(rows, cols, charMap);

}

void Map::print() const {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++)
            std::cout<<charMap[i][j];
        std::cout<<'\n';
    }
}

void Map::draw(bool debug) const {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            tileMap[i][j].draw(debug);
        }
    }
}

BoundingBox* Map::getCollision(int row, int col) const {
    if(row >= 0 && col >= 0 && row < rows && col < cols)
        return tileMap[row][col].getCollision();
    return nullptr;
}

Vector3 Map::getPosition(int row, int col) const {
    if(row >= 0 && col >= 0 && row < rows && col < cols)
        return tileMap[row][col].getPosition();
    return {};
}

bool Map::isWall(int row, int col) const {
    if(row >= 0 && col >= 0 && row < rows && col < cols)
        return tileMap[row][col].isWall();
    return {};
}

// ############ TILE ############
Texture* Tile::wallTexture = nullptr;
Texture* Tile::floorTexture = nullptr;

Mesh* Tile::tileMesh = nullptr;

Model* Tile::floorModel = nullptr;
Model* Tile::wallModel = nullptr;

Tile::Tile() {}

Tile::Tile(Vector3 position, Model& model, bool wall, int row, int col)
: position(position), model(&model), wall(wall), row(row), col(col) {}

void Tile::draw(bool debug) const { 
    DrawModel(*this->model, this->position, 1.0f, WHITE);
    if(debug) DrawBoundingBox(boundingBox, GREEN);
}

void Tile::initializeTiles() {
    if(tileMesh == nullptr) {
        floorTexture = new Texture(LoadTexture("../resources/tiles/floor_diff.png"));
        wallTexture = new Texture(LoadTexture("../resources/tiles/wall_diff.png"));

        tileMesh = new Mesh(GenMeshCube(TILE_SIZE, TILE_SIZE, TILE_SIZE));

        floorModel = new Model(LoadModelFromMesh(*tileMesh));
        floorModel->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *floorTexture;

        wallModel = new Model(LoadModelFromMesh(*tileMesh));
        wallModel->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *wallTexture;
    }
}

Tile** Tile::makeTileMap(int numRows, int numCols, char** charMap) {

    initializeTiles();

    Tile** tileMap = new Tile*[numRows];

    for(int r = 0; r < numRows; r++) {
        tileMap[r] = new Tile[numCols];
        for(int c = 0; c < numCols; c++) {

            Tile* tile = &tileMap[r][c];
            
            tile->row = r;
            tile->col = c;
            if(r > 0) tile->up = &tileMap[r-1][c];
            if(c > 0) tile->up = &tileMap[r][c-1];
            
            switch (charMap[r][c]) {
                case 'f':
                case 'c':
                case 'p':
                    tile->position = {c*TILE_SIZE, -TILE_SIZE/2.0f, r*TILE_SIZE};
                    tile->wall = false;
                    tile->model = floorModel;
                    tile->boundingBox = {};
                    break;
                case 'w':
                    tile->position = {c*TILE_SIZE, TILE_SIZE/2.0f, r*TILE_SIZE};
                    tile->wall = true;
                    tile->model = wallModel;
                    tile->boundingBox = {{tile->position.x - TILE_SIZE/2.0f, tile->position.y - TILE_SIZE/2.0f, tile->position.z - TILE_SIZE/2.0f},
                                         {tile->position.x + TILE_SIZE/2.0f, tile->position.y + TILE_SIZE/2.0f, tile->position.z + TILE_SIZE/2.0f}};
                    break;
                default: 
                    tile->position = {c*TILE_SIZE, TILE_SIZE/2.0f, r*TILE_SIZE};
                    tile->wall = true;
                    tile->model = new Model(LoadModelFromMesh(*tileMesh));
            }


        } 
    }

    return tileMap;
}

Vector3 Tile::getPosition() const { return position; }
BoundingBox* Tile::getCollision() { return &this->boundingBox; }
bool Tile::isWall() const { return this->wall; }
