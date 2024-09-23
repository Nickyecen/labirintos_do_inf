#include "include/map.hpp"
#include <fstream>
#include <raylib.h>
#include <string>
#include <vector>

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

Tile::Tile(Vector3 position, Model& model, bool wall, bool corner, int row, int col)
: position(position), model(&model), wall(wall), corner(corner), row(row), col(col) {}

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
            if(c > 0) tile->left = &tileMap[r][c-1];
            
            switch (charMap[r][c]) {
                case 'f':
                case 'p': {
                    char rightChar = charMap[r][c+1], upChar = charMap[r-1][c], leftChar = charMap[r][c-1], downChar = charMap[r+1][c]; 
                    bool rightWall = rightChar != 'f' && rightChar != 'p';
                    bool upWall = upChar != 'f' && upChar != 'p';
                    bool leftWall = leftChar != 'f' && leftChar != 'p';
                    bool downWall = downChar != 'f' && downChar != 'p';

                    bool isCorner = !rightWall&&upWall&&!leftWall&&downWall
                                 || rightWall&&!upWall&&leftWall&&!downWall;
                    isCorner = !isCorner;

                    tile->position = {c*TILE_SIZE, -TILE_SIZE/2.0f, r*TILE_SIZE};
                    tile->wall = false;
                    tile->corner = isCorner;
                    tile->model = floorModel;
                    tile->boundingBox = {};
                    break;
                }
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
                    tile->boundingBox = {{tile->position.x - TILE_SIZE/2.0f, tile->position.y - TILE_SIZE/2.0f, tile->position.z - TILE_SIZE/2.0f},
                                         {tile->position.x + TILE_SIZE/2.0f, tile->position.y + TILE_SIZE/2.0f, tile->position.z + TILE_SIZE/2.0f}};
            }

        } 
    }

    for(int r = 0; r < numRows; r++) {
        for(int c = 0; c < numCols; c++) {
            Tile* tile = &tileMap[r][c];
            if(r < numRows) tile->down = &tileMap[r+1][c];
            if(c < numCols) tile->right = &tileMap[r][c+1];
        }
    }

    return tileMap;
}

std::vector<Corner*> Corner::makeCornerVector(int numRows, int numCols, Tile **tileMap) {
 
    std::vector<Corner*> cornerVector = {};
    std::queue<Corner*> cornerQueue = {};

    bool foundFirstCorner = false;
    for(int r = 0; r < numRows && !foundFirstCorner; r++) {
        for(int c = 0 ; c < numCols && !foundFirstCorner; c++) {
            if(tileMap[r][c].isCorner()) {
                cornerQueue.push(new Corner(&tileMap[r][c]));
                cornerVector.push_back(cornerQueue.front());
                foundFirstCorner = true;                
            }
        }
    }

    while(!cornerQueue.empty()) {
        Corner* current = cornerQueue.front();
        cornerQueue.pop();

        Tile *right, *down;
        for(right = current->tile->getRight(); right != nullptr && !right->isCorner() && !right->isWall(); right = right->getRight());
        for(down = current->tile->getDown(); down != nullptr && !down->isCorner() && !down->isWall(); down = down->getDown());

        if(right != nullptr && !right->isWall()) { 
            Corner* newCorner = new Corner(right);
            cornerQueue.push(newCorner);
            cornerVector.push_back(newCorner);

            current->right = newCorner;
            newCorner->left = current;
        } if(down != nullptr && !down->isWall()) {
            Corner* newCorner = new Corner(down);
            cornerQueue.push(newCorner);
            cornerVector.push_back(newCorner);

            current->down = newCorner;
            newCorner->up = current;
        }

    }

    return cornerVector;
}

Corner::Corner(Tile* tile)
: tile(tile) {}

std::vector<Tile*> Map::getFloors() const {
    std::vector<Tile*> floors = {};
    
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            Tile* curTile = &tileMap[i][j];

            if(!curTile->isWall()) floors.push_back(curTile);
        }
    }

    return floors;
}

bool Map::checkVision(int rowA, int colA, int rowB, int colB) {
    if(rowA == rowB) {

        int smaller, bigger; 

        if(colA > colB) {
            smaller = colB;
            bigger = colA;
        } else if(colA < colB) { 
            smaller = colA;
            bigger = colB;
        } else {
            return true;
        }

        for(int i = smaller; i < bigger; i++)
            if(tileMap[rowA][i].isWall()) return false;

        return true;

    } else if(colA == colB) {

        int smaller, bigger; 

        if(rowA > rowB) {
            smaller = rowB;
            bigger = rowA;
        } else if(rowA < rowB) { 
            smaller = rowA;
            bigger = rowB;
        }

        for(int i = smaller; i < bigger; i++)
            if(tileMap[i][colA].isWall()) return false;

        return true;

    }

    return false;
}

Vector3 Tile::getPosition() const { return position; }
BoundingBox* Tile::getCollision() { return &this->boundingBox; }
bool Tile::isWall() const { return this->wall; }
bool Tile::isCorner() const { return this->corner; }
int Tile::getRow() const { return this->row; }
int Tile::getCol() const { return this->col; }
Tile* Tile::getRight() const { return this->right; }
Tile* Tile::getUp() const { return this->up; }
Tile* Tile::getLeft() const { return this->left; }
Tile* Tile::getDown() const { return this->down; }
