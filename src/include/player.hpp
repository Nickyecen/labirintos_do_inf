#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <raylib.h>

#define WALKING_SPEED 1.5f
#define SPRINTING_SPEED 4.5f
#define SENSITIVITY 0.25f

class Player {
    // VARIABLES
    private:
        Vector3 position;
        Camera3D* camera;
   
    // METHODS
    public:
        Player();

        void update();

        Camera3D* getCamera() const;

    private:
        Vector3 getMovement();
        Vector3 getRotation();
};

#endif
