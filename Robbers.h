#pragma once

#include "iostream"
#include "bmpDrawing.h"

enum cost
{
    WIFE_PRICE = -1,
    HORSE_PRICE = 2,
    RUBY_PRICE = 3
};

struct Robber
{
    std::string name;
    bool alive = true;
    int horses=0;
    int wives=0;
    int rubies=0;
    Robber* nextFriend = nullptr;
};
typedef Robber Band;

[[nodiscard]]
Robber* add(Band* band, const std::string & name, int horses, int wives, int rubies);

[[nodiscard]]
Robber* kill(Band* band, const std::string& name);

[[nodiscard]]
int evalRobber(Robber* rob);

[[nodiscard]][[maybe_unused]]
int evalBandTotal(Band* band);

void printRobber(Robber* r);

void printBandMoney(Band* band);

void printActual(Band* band);

void eraseBand(Band* band);

void printAll(Band* band);

[[nodiscard]]
Robber* findRich(Band* band);

[[nodiscard]]
Robber* findByName(Band* band, const std::string& name);

void drawDiagram(Band* band);

