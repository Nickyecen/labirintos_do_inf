#include "include/items.hpp"
#include "include/map.hpp"
#include "include/player.hpp"
#include <algorithm>
#include <ctime>
#include <raylib.h>
#include <vector>
#include <iostream>

std::vector<Item*> Item::items = {};

Model* Bomb::bombModel = nullptr;
Model* Credit::creditModel = nullptr;
Model* Health::healthModel = nullptr;
Model* Life::lifeModel = nullptr;
Model* Clock::clockModel = nullptr;

Texture* Clock::diffuse = nullptr;

Item::~Item() {}

void Item::genRandom(Map &map, int numCredits, int numLives, int numHealth, int numBombs, int numTime) {
    std::vector<Tile*> floors = map.getFloors();
    int* order = LoadRandomSequence((int) floors.size(), 0, (int) floors.size());

    int i = 0;
    Tile* it = 0;
    while(numCredits > 0) {
        int amount = GetRandomValue(1, std::max(numCredits, 5));
        numCredits -= amount;

        it = floors[order[i++]];
        new Credit(it->getRow(), it->getCol(), amount);
    } while(numTime > 0) {
        int amount = 5*GetRandomValue(1, std::max(numCredits, 6));
        numTime -= amount;

        it = floors[order[i++]];
        new Clock(it->getRow(), it->getCol(), amount);
    } while(numBombs > 0) {
        numBombs--;
        it = floors[order[i++]];
        new Bomb(it->getRow(), it->getCol());
    } while(numHealth > 0) {
        numHealth--;
        it = floors[order[i++]];
        new Health(it->getRow(), it->getCol());
    } while(numLives > 0) {
        numLives--;
        it = floors[order[i++]];
        new Life(it->getRow(), it->getCol());
    }
}

void Item::draw() const {
    DrawModelEx(*this->model, this->position, {0.0f, 1.0f, 0.0f}, this->rotation, {this->scale, this->scale, this->scale}, WHITE);
}

void Item::drawBB() const {
    DrawBoundingBox(this->collisionBox, RED);
}

void Item::drawItems(bool debug) {
    for(const auto& item : items) item->draw();

    if(debug)
        for(auto& item : items)
            item->drawBB();
}

void Item::update(Player& player) {
    this->rotation += ITEM_SPEED*GetFrameTime();
    if(player.getRow() == this->row && player.getCol() == this->col) {
        if(CheckCollisionBoxes(this->collisionBox, player.getCollision()))
            this->get(player);
    }
}

void Item::updateItems(Player& player) {
    for(auto it = items.begin(); it != items.end();) {
        if((*it)->collected) {
            (*it)->~Item();
            it = items.erase(it);
        } else {
            (*it)->update(player);
            it++;
        }
    }
}

void Item::initializeItem(Model* model, int row, int col) {
    this->model = model;
    this->row = row;
    this->col = col;
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
    if(clockModel == nullptr) {
        clockModel = new Model(LoadModel("../resources/items/clock.obj"));
        diffuse = new Texture(LoadTexture("../resources/items/clock_diff.png"));
        clockModel->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *diffuse;
    }

    this->initializeItem(clockModel, row, col);

    this->time = time;
}

void Bomb::get(Player& player) {
    player.incBomb();
    this->collected = true; 
}

void Health::get(Player& player) {
    player.incHealth();
    this->collected = true;
}

void Life::get(Player& player) {
    player.incLife();
    this->collected = true;
}

void Clock::get(Player& player) {
    player.addTime(time);
    this->collected = true;
}

void Credit::get(Player& player) {
    player.addCredits(credits);
    this->collected = true;
}

