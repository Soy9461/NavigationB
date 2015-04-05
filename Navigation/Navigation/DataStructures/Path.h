//
// Created by cfwloader on 4/5/15.
//

#ifndef NAVIGATIONB_PATH_H
#define NAVIGATIONB_PATH_H

#include "BaseStructure.h"

class Path {
public:
private:
    std::deque<Navigation_Point*> nodeRecords;
    double cost;
};


#endif //NAVIGATIONB_PATH_H
