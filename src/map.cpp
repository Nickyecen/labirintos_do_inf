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

void Map::draw() const {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            tileMap[i][j].draw();
        }
    }
}

// ############ TILE ############
Texture* Tile::wallTexture = nullptr;
Texture* Tile::floorTexture = nullptr;

Mesh* Tile::tileMesh = nullptr;

Model* Tile::floorModel = nullptr;
Model* Tile::wallModel = nullptr;

Tile::Tile() {}

Tile::Tile(Vector3 position, Model& model, bool isWall, int row, int col)
: position(position), model(&model), isWall(isWall), row(row), col(col) {}

void Tile::draw() const { DrawModel(*this->model, this->position, 1.0f, WHITE); }

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
            
            tileMap[r][c].row = r;
            tileMap[r][c].col = c;
            if(r > 0) tileMap[r][c].up = &tileMap[r-1][c];
            if(c > 0) tileMap[r][c].up = &tileMap[r][c-1];
            
            switch (charMap[r][c]) {
                case 'f':
                case 'c':
                case 'p':
                    tileMap[r][c].position = {c*TILE_SIZE, -TILE_SIZE/2.0f, r*TILE_SIZE};
                    tileMap[r][c].isWall = false;
                    tileMap[r][c].model = floorModel;
                    break;
                case 'w':
                    tileMap[r][c].position = {c*TILE_SIZE, TILE_SIZE/2.0f, r*TILE_SIZE};
                    tileMap[r][c].isWall = true;
                    tileMap[r][c].model = wallModel;
                    break;
                default: 
                    tileMap[r][c].position = {c*TILE_SIZE, TILE_SIZE/2.0f, r*TILE_SIZE};
                    tileMap[r][c].isWall = true;
                    tileMap[r][c].model = new Model(LoadModelFromMesh(*tileMesh));
            }

        } 
    }

    return tileMap;
}


