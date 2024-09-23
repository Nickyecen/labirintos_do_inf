#ifndef MAP_HPP
#define MAP_HPP

#include <string>
#include <iostream>
#include <raylib.h>
#include <vector>
#include <queue>

#define TILE_SIZE 2.0f

class Tile {
    // VARIABLES
    private:
        Vector3 position;
        Model* model = nullptr;
        BoundingBox boundingBox;

        int row, col;

        bool wall;
        bool corner;

        Tile* right = nullptr;
        Tile* up = nullptr;
        Tile* left = nullptr;
        Tile* down = nullptr;

        static Texture* wallTexture;
        static Texture* floorTexture;

        static Mesh* tileMesh;

        static Model* floorModel;
        static Model* wallModel;

    // METHODS
    private:
        Tile();
    public:
        Tile(Vector3 position, Model& model, bool isWall, bool isCorner, int row, int col);

        static Tile** makeTileMap(int numRows, int numCols, char** charMap);

        void draw(bool debug) const;
        BoundingBox* getCollision();
        Vector3 getPosition() const;
        int getRow() const;
        int getCol() const;
        Tile* getRight() const;
        Tile* getUp() const;
        Tile* getLeft() const;
        Tile* getDown() const;
        bool isWall() const;
        bool isCorner() const;

        static void initializeTiles();
};

class Corner {
    private:
        Tile* tile = nullptr;

        Corner* right = nullptr;
        Corner* up = nullptr;
        Corner* left = nullptr;
        Corner* down = nullptr;

    public:
        Corner(Tile* tile);

        static std::vector<Corner*> makeCornerVector(int numRows, int numCols, Tile** tileMap);
};

class Map {

    // VARIABLES
    private:
        int rows, cols;
        char** charMap;
        Tile** tileMap;

    // METHODS
    public:
        Map(std::string path);
        void print() const;
        void draw(bool debug) const;
        BoundingBox* getCollision(int row, int col) const;
        Vector3 getPosition(int row,  int col) const;
        bool isWall(int row, int col) const;

        std::vector<Tile*> getFloors() const;

        bool checkVision(int rowA, int colA, int rowB, int colB);
};

#endif
