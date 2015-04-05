//
// Created by cfwloader on 4/5/15.
//

#ifndef NAVIGATIONB_DIJKSTRA_H
#define NAVIGATIONB_DIJKSTRA_H

#include "../DataStructures/NavigationMap.h"
#include "../DataStructures/Path.h"

Path getTheShortestPath(const NavigationGraph&, const Navigation_Point&, const Navigation_Point&);

#endif //NAVIGATIONB_DIJKSTRA_H
