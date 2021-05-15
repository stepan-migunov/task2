#include <iostream>
#include "Robbers.h"

int main()
{
    std::string input;
    std::string help = "*************************************************************\n"
                       "Введите, что требуется сделать:\n"
                       "\tbandAll - вывести полный состав банды\n"
                       "\tbandActual - вывести актуальный состав банды\n"
                       "\tadd - добавить разбойника в банду\n"
                       "\tkill - убить члена банды\n"
                       "\ttotal - ИТОГО\n"
                       "\trich - показать самого богатого\n"
                       "\tfind - найти разбойников по имени\n"
                       "\tdiagram - нарисовать диаграмму\n"
                       "\thelp - вывести эту подсказку\n"
                       "\tquit - завершить программу\n"
                       "*************************************************************\n\n";
    std::cout << help;
    Band* band = nullptr;
    band = add(band,"Мехмат",10,10, 10);
    band = add(band,"Махмуд",9,8,7);
    band = add(band,"Махмет",6,5,4);
    band = add(band,"Мемхат",3,2,1);
    band = add(band,"Метмах",11,12,13);
    band = add(band,"Хеммат",14,15,16);

    while(input != "quit")
    {
        std::cin >> input;
        if(input == "help")
        {
            input = "";

            std::cout << help;
        }
        else if (input == "quit")
        {
            input = "";

            break;
        }
        else if(input == "bandAll")
        {
            printAll(band);

            input = "";
        }
        else if(input == "bandActual")
        {
            printActual(band);

            input = "";
        }
        else if(input == "add")
        {
            std::cout << "Введите имя, количество лошадей, количество жён, количество рубинов:" << std::endl;
            std::string name; int horses,wives,rubies;
            std::cin >> name >> horses >> wives >> rubies;

            band = add(band,name,horses,wives,rubies);

            input = "";
        }
        else if(input == "kill")
        {
            std::cout << "Введите имя того, кого надо убить:" << std::endl;
            std::string name; std::cin >> name;

            kill(band, name);
        }
        else if(input == "total")
        {
            printBandMoney(band);

            input = "";
        }
        else if(input == "rich")
        {
            Band* b = findRich(band);
            printAll(b);
            eraseBand(b);

            input = "";
        }
        else if(input == "find")
        {
            std::cout << "Введите имя того разбойника, которого хотите найти:" << std::endl;
            std::string name; std::cin >> name;

            Band* b = findByName(band,name);
            printAll(b);
            eraseBand(b);

            input = "";
        }
        else if(input == "diagram")
        {
            drawDiagram(band);

            input = "";
        }
    }
    return 0;
}
