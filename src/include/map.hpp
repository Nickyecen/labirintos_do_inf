#ifndef MAP_HPP
#define MAP_HPP

#include <string>
#include <iostream>
#include <raylib.h>

#define TILE_SIZE 2.0f

class Tile {
    // VARIABLES
    private:
        Vector3 position;
        Model* model = nullptr;

        int row, col;

        bool isWall;

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
        Tile(Vector3 position, Model& model, bool isWall, int row, int col);

        static Tile** makeTileMap(int numRows, int numCols, char** charMap);

        void draw() const;

        static void initializeTiles();
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
        void draw() const;

};

#endif
