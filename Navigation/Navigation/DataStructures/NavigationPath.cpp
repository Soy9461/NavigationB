//
// Created by cfwloader on 4/5/15.
//

#include "NavigationPath.h"

NavigationPath::NavigationPath() : cost(INF){
}

NavigationPath::NavigationPath(NavigationPath const &aConst) : cost(aConst.cost){
    this->DeepCopy(aConst.nodesInPath);
}

NavigationPath::~NavigationPath() {
    if(cost < INF){
        this->DeepClean();
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
        cost = INF;
    }
}

const NavigationPath &NavigationPath::operator=(NavigationPath const &aConst) {
    if(cost < INF){
        this->DeepClean();
        cost = INF;
    }
    cost = aConst.cost;
    this->DeepCopy(aConst.nodesInPath);
    return *this;
}

void NavigationPath::DeepClean() {
    Navigation_Point* ptr;
    while(!nodesInPath.empty()){
        ptr = nodesInPath.front();
        delete ptr;
        nodesInPath.pop_front();
    }
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
}

void NavigationPath::DeepCopy(std::deque<Navigation_Point *> &deque) {
    std::deque<Navigation_Point*>::const_iterator iter,end;
    iter = deque.begin();
    end = deque.end();
    while(iter != end){
        nodesInPath.push_back(new Navigation_Point((*iter)->GetPos().x, (*iter)->GetPos().y, (*iter)->GetPos().z, (*iter)->GetName()));
        ++iter;
    }
}

void NavigationPath::AddPointToPathTail(Navigation_Point *const point) {
    nodesInPath.push_back(new Navigation_Point(point->GetPos().x, point->GetPos().y, point->GetPos().z, point->GetName()));
}

double NavigationPath::GetCost() {
    return cost;
}
