#ifndef TEACHERS_HPP
#define TEACHERS_HPP

#include <raylib.h>
#include <vector>

#include "player.hpp"

class Teacher {
    // VARIABLES
    public:
        std::vector<Teacher*> teachers; 
    private:
        static Texture* teachDTexture;
        static Texture* teachSTexture;
        static Texture* teachRTexture;
        static Texture* teachLTexture;
        static Texture* teachJTexture;

        static Model* teachDModel;
        static Model* teachSModel;
        static Model* teachRModel;
        static Model* teachLModel;
        static Model* teachJModel;

        Ray* rightRay = nullptr;
        Ray* upRay = nullptr;
        Ray* leftRay = nullptr;
        Ray* downRay = nullptr;

        bool seesPlayer = false;

        Vector3* position = nullptr;
        int row, col;
        BoundingBox* collisionBox = nullptr;
        Model* model;

    // METHODS
    public:
        Teacher(int row, int col, Model& model);

        void draw(bool debug) const;
        void update(Player& player);

        static Teacher* makeTeachD(int row, int col);
        static Teacher* makeTeachS(int row, int col);
        static Teacher* makeTeachR(int row, int col);
        static Teacher* makeTeachL(int row, int col);
        static Teacher* makeTeachJ(int row, int col);
};

#endif
