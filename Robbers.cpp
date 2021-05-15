//
// Created by stepan on 15.05.2021.
//

#include "Robbers.h"

[[nodiscard]]
Robber* add(Band* band, const std::string & name, int horses, int wives, int rubies)
{
    auto* temp = new Robber{name, true, horses, wives, rubies, nullptr};
    if(band == nullptr)
        return temp;
    Robber* T;
    for(T = band; T->nextFriend != nullptr; T=T->nextFriend);
    T->nextFriend = temp;
    return band;
}

Robber* kill(Band* band, const std::string & name)
{
    Robber* T;
    for(T = band; T != nullptr; T = T->nextFriend)
        if(T->alive && T->name==name)
            break;

    if (T== nullptr)
        return nullptr;
    else
        T->alive = false;

    return T;
}

[[nodiscard]]
int evalRobber(Robber* rob)
{
    if(rob == nullptr)
        return 0;
    if(rob->alive)
        return  rob->rubies * RUBY_PRICE +
                rob->wives * WIFE_PRICE +
                rob->horses * HORSE_PRICE;
    else
        return 0;
}

[[nodiscard]][[maybe_unused]]
int evalBandTotal(Band* band)
{
    int sum = 0;
    for(Robber* T = band; T != nullptr; T=T->nextFriend)
        sum += evalRobber(T);
    return sum;
}

void printRobber(Robber* r)
{
    if(r== nullptr)
        return;
    std::cout << r->name << " ";
    printf("Судьба: %s, лошади: %d, жёны: %d, рубины:%d\n",
           ((r->alive)?"Жив":"Мертв"),
           r->horses,
           r->wives,
           r->rubies);
}

void printBandMoney(Band* band)
{
    int aliveTotal = 0, horsesTotal = 0, wivesTotal = 0, rubiesTotal = 0;
    for(Robber* T = band; T != nullptr; T=T->nextFriend)
        aliveTotal += T->alive?1:0,
        horsesTotal+=T->horses,
        wivesTotal+=T->wives,
        rubiesTotal+=T->rubies;

    printf("Всего живых: %d; Всего лошадей: %d; Всего жен: %d; Всего рубинов: %d\n",
           aliveTotal, horsesTotal, wivesTotal, rubiesTotal);
    printf("Всего богатства: %d\n",rubiesTotal * RUBY_PRICE +
                                 wivesTotal * WIFE_PRICE +
                                 horsesTotal * HORSE_PRICE);
}

void printActual(Band* band)
{
    for(Robber* t = band; t != nullptr; t=t->nextFriend)
        if(t->alive)
            printRobber(t);
}

void eraseBand(Band* band)
{
    if(band == nullptr)
        return;
    else
        eraseBand(band->nextFriend);
    delete band;
}

void printAll(Band* band)
{
    for(Robber* t = band; t != nullptr; t=t->nextFriend)
        printRobber(t);
}


[[nodiscard]]
Robber* findRich(Band* band)
{
    Robber* next;
    if(band == nullptr || (next = findRich(band->nextFriend)) == nullptr)
        return band == nullptr ?
               nullptr
                               :
               new Robber{band->name, band->alive,
                          band->horses, band->wives,
                          band->rubies, nullptr};

    if(!band->alive)
        return next;

    if(evalRobber(band) == evalRobber(next))
        return new Robber{band->name, band->alive,
                          band->horses, band->wives,
                          band->rubies, next};
    if(evalRobber(band) > evalRobber(next))
    {
        eraseBand(next);
        return new Robber{band->name, band->alive,
                          band->horses, band->wives,
                          band->rubies, nullptr};
    }
    else
    {
        return next;
    }
}


[[nodiscard]]
Robber* findByName(Band* band, const std::string & name)
{
    if(band == nullptr)
        return nullptr;
    if(band->name != name)
        return findByName(band->nextFriend,name);
    else
        return new Robber{band->name, band->alive,
                          band->horses, band->wives,
                          band->rubies, findByName(band->nextFriend,name)};
}

void drawDiagram(Band* band)
{
    create("diagram.bmp",500,400);
    for(int i = 0; i < 40; ++i,band=band->nextFriend)
    {
        if(band== nullptr)
            break;
        drawRectangle(i*10,band->horses*10,8,band->horses*10,band->alive?GREEN:BLACK,0);
    }
    writeFile();
    close();
}
