#include "include/items.hpp"
#include "include/map.hpp"
#include "include/player.hpp"
#include <algorithm>
#include <raylib.h>
#include <vector>

std::vector<Item*> Item::items = {};

Model* Bomb::bombModel = nullptr;
Model* Credit::creditModel = nullptr;
Model* Health::healthModel = nullptr;
Model* Life::lifeModel = nullptr;
Model* Clock::clockModel = nullptr;

    void Item::draw() const {
    DrawModelEx(*this->model, this->position, {0.0f, 1.0f, 0.0f}, this->rotation, {this->scale, this->scale, this->scale}, WHITE);
}

void Item::drawItems() {
    for(auto& item : items) {
        item->draw();
    }
}

void Item::update() {
    this->rotation = (((int) (1000*GetTime())) % 314) / 100.0f;
}

void Item::initializeItem(Model* model, int row, int col) {
    this->model = model;
    this->position = {TILE_SIZE*col, ITEM_SIZE/2.0f, TILE_SIZE*row};
    BoundingBox box = GetModelBoundingBox(*model);
    this->scale = ITEM_SIZE/(box.max.x - box.min.x);
    this->collisionBox = {{position.x - ITEM_SIZE, 0.0f     , position.z - ITEM_SIZE},
                          {position.x + ITEM_SIZE, ITEM_SIZE, position.z + ITEM_SIZE}};

    items.push_back(this); 
}

Bomb::Bomb(int row, int col) {
    if(bombModel == nullptr)
        bombModel = new Model(LoadModel("../resources/items/bomb.obj"));

    this->initializeItem(bombModel, row, col);
}

Health::Health(int row, int col) {
    if(healthModel == nullptr)
        healthModel = new Model(LoadModel("../resources/items/heart.obj"));

    this->initializeItem(healthModel, row, col);
}

Life::Life(int row, int col) {
    if(lifeModel == nullptr)
        lifeModel = new Model(LoadModel("../resources/items/crown.obj"));

    this->initializeItem(lifeModel, row, col);
}

Credit::Credit(int row, int col, int credits) {
    if(creditModel == nullptr)
        creditModel = new Model(LoadModel("../resources/items/star.obj"));

    this->initializeItem(creditModel, row, col);

    this->credits = credits;
}

Clock::Clock(int row, int col, int time) {
    if(clockModel == nullptr)
        clockModel = new Model(LoadModel("../resources/items/clock.obj"));

    this->initializeItem(clockModel, row, col);

    this->time = time;
}

void Bomb::get(Player& player) {
    player.incBomb();
    items.erase(std::remove(items.begin(), items.end(), this), items.end());
    delete this; 
}

void Health::get(Player& player) {
    player.incHealth();
    items.erase(std::remove(items.begin(), items.end(), this), items.end());
    delete this; 
}

void Life::get(Player& player) {
    player.incLife();
    items.erase(std::remove(items.begin(), items.end(), this), items.end());
    delete this; 
}

void Clock::get(Player& player) {
    player.addTime(time);
    items.erase(std::remove(items.begin(), items.end(), this), items.end());
    delete this; 
}

void Credit::get(Player& player) {
    player.addCredits(credits);
    items.erase(std::remove(items.begin(), items.end(), this), items.end());
    delete this; 
}

