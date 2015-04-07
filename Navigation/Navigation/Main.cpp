#include <iostream>
#include "DataStructures/NavigationMap.h"

int main() {
    Building_B TheBuilding;
    TheBuilding.DebugPrint();
    std::string fromPoint = "101";
    std::string toPoint = "1_Stair_S_2";
    std::deque<Navigation_Point *> *path = TheBuilding.FindPath(fromPoint, toPoint);
    if (path != nullptr) {
        for (std::deque<Navigation_Point *>::iterator iterator = path->begin(),
                     end = path->end();
             iterator != end;
             ++iterator) {
            std::cout << (*iterator)->GetName() << std::endl;
        }
        delete path;
    }else{
        std::cout << "看起来好像没路到那里去呢。" << std::endl;
    }
    //getchar();
    return 0;
}