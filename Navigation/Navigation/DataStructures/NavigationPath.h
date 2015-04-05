//
// Created by cfwloader on 4/5/15.
//

#ifndef NAVIGATIONB_NAVIGATIONPATH_H
#define NAVIGATIONB_NAVIGATIONPATH_H

#include <deque>
#include "BaseStructure.h"

class NavigationPath {
public:

    NavigationPath();

    NavigationPath(const NavigationPath&);

    ~NavigationPath();

    // 赋值动作，带有深度复制功能，旧值内存能被正确管理
    // 后来想想还是先浅复制好了，内存管理出错再考虑深度复制
    // 把深度复制的代码注释了，没有删
    const NavigationPath& operator=(const NavigationPath&);

    // 将新节点加入到路径尾部，深度复制节点值
    // 后来想想还是浅复制好了
    void addPointToPathTail(Navigation_Point* const);

    friend std::ostream& operator<<(std::ostream&, const NavigationPath&);

private:

    // 深度复制双端队列
    // 屏蔽，因为不需要深度复制以及深度清理
    //void DeepCopy(std::deque<Navigation_Point*>&);

    // 当发生析构、重新附值、深度拷贝前，深度清理双端队列的内存
    // 同理
    //void DeepClean();

    std::deque<Navigation_Point*> nodesInPath;
};

class DijkstraNode{
public:


    DijkstraNode() : visited(false), foundShortestPath(false), cost(INF), distance(){
    }

    bool isVisited() const {
        return visited;
    }

    void setVisited(bool visited) {
        DijkstraNode::visited = visited;
    }

    bool isFoundShortestPath() const {
        return foundShortestPath;
    }

    void setFoundShortestPath(bool foundShortestPath) {
        DijkstraNode::foundShortestPath = foundShortestPath;
    }


    double getCost() const {
        return cost;
    }

    void setCost(double cost) {
        DijkstraNode::cost = cost;
    }

    NavigationPath const &getDistance() const {
        return distance;
    }

    void setDistance(NavigationPath const &distance) {
        DijkstraNode::distance = distance;
    }

    void addNodeToPathTail(const Navigation_Point* const point){
        distance.addPointToPathTail(point);
    }

private:
    bool visited;
    bool foundShortestPath;
    double cost;
    NavigationPath distance;
};


#endif //NAVIGATIONB_NAVIGATIONPATH_H
