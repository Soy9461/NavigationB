//
// Created by cfwloader on 4/5/15.
//

#include <ostream>
#include "NavigationPath.h"

NavigationPath::NavigationPath() {
}

NavigationPath::NavigationPath(NavigationPath const &aConst) : nodesInPath(aConst.nodesInPath) {
    //this->DeepCopy(aConst.nodesInPath);
    //this->nodesInPath = aConst.nodesInPath;
}

NavigationPath::~NavigationPath() {
    //this->DeepClean();
    /*
    std::deque<Navigation_Point*>::iterator iter, end;
    iter = nodesInPath.begin();
    end = nodesInPath.end();
    while(iter != end){
        delete (*iter);
        *iter = 0;
        ++iter;
    }
    */
    while (!nodesInPath.empty())nodesInPath.pop_front();
}

const NavigationPath &NavigationPath::operator=(NavigationPath const &aConst) {
    //this->DeepCopy(aConst.nodesInPath);

    //不知道调用deque的重载操作符=时会不会正确清理，自己手动pop
    while (!nodesInPath.empty())nodesInPath.pop_front();

    this->nodesInPath = aConst.nodesInPath;
    return *this;
}

/*
void NavigationPath::DeepClean() {
    Navigation_Point* ptr;
    while(!nodesInPath.empty()){
        ptr = nodesInPath.front();
        delete ptr;
        nodesInPath.pop_front();
    }
    // ---原段注释线
    std::deque<Navigation_Point*>::iterator iter, end;
    iter = nodesInPath.begin();
    end = nodesInPath.end();
    while(iter != end){
        delete (*iter);
        *iter = 0;
        ++iter;
    }
    // ---原段注释线
}
*/

/*
void NavigationPath::DeepCopy(std::deque<Navigation_Point *> &deque) {
    std::deque<Navigation_Point *>::const_iterator iter, end;
    iter = deque.begin();
    end = deque.end();
    while (iter != end) {
        nodesInPath.push_back(new Navigation_Point((*iter)->GetPos().x, (*iter)->GetPos().y, (*iter)->GetPos().z,
                                                   (*iter)->GetName()));
        ++iter;
    }
}
*/

void NavigationPath::addPointToPathTail(const Navigation_Point *const point) const {
    //nodesInPath.push_back(new Navigation_Point(point->GetPos().x, point->GetPos().y, point->GetPos().z, point->GetName()));
    nodesInPath.push_back(point);
}

std::ostream &operator<<(std::ostream &os, NavigationPath const &aConst) {
    std::deque<Navigation_Point*>::iterator iter, end;
    iter = nodesInPath.begin();
    end = nodesInPath.end();
    while(iter != end){
        os << (*iter)->GetName() << " ";
        ++iter;
    }
    os << std::endl;
    return os;
}

static DijkstraNode *DijkstraNode::findMinimumPath(std::map<int, DijkstraNode *> const &map) {
    DijkstraNode* targetNode = nullptr;
    double targetCost = INF;
    std::map<int, DijkstraNode*>::const_iterator iterator, end;

    for(iterator = map.begin(), end = map.end(); iterator != end; ++iterator){
        if(((*iterator).second->getCost() < targetCost) && !((*iterator).second->isFoundShortestPath())){
            targetNode = (*iterator).second;
            targetCost = targetNode->getCost();
        }
    }

    return targetNode;
}
