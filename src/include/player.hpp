#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <raylib.h>

#include "map.hpp"

#define WALKING_SPEED 1.5f
#define SPRINTING_SPEED 4.5f
#define SENSITIVITY 0.25f
#define COLLISION_SIZE 0.1f
#define PLAYER_HEIGHT 1.7f

class Player {
    // VARIABLES
    private:
        int row, col;

        Vector3 position;
        Camera3D* camera;

        BoundingBox collisionBox;
   
    // METHODS
    public:
        Player(Vector2 pos);

        void update(Map&);

        Camera3D* getCamera() const;

    private:
        Vector3 getMovement(Map&);
        Vector3 getRotation();
};

#endif
