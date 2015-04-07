//
// Created by cfwloader on 4/5/15.
//

#ifndef NAVIGATIONB_NAVIGATIONPATH_H
#define NAVIGATIONB_NAVIGATIONPATH_H

#include <deque>
#include "BaseStructure.h"

/*
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
    void addPointToPathTail(const Navigation_Point* const) const;


    std::deque<Navigation_Point *> const &getNodesInPath() const {
        return nodesInPath;
    }

    void setNodesInPath(std::deque<Navigation_Point *> const &nodesInPath) {
        NavigationPath::nodesInPath = nodesInPath;
    }

    friend std::ostream& operator<<(std::ostream&, const NavigationPath&);

private:

    // 深度复制双端队列
    // 屏蔽，因为不需要深度复制以及深度清理
    //void DeepCopy(std::deque<Navigation_Point*>&);

    // 当发生析构、重新附值、深度拷贝前，深度清理双端队列的内存
    // 同理
    //void DeepClean();

    //map返回的second是const的，只能通过mutable解决这个矛盾的样子
    mutable std::deque<Navigation_Point*> nodesInPath;
};
 */

class DijkstraNode{
public:

    explicit DijkstraNode(Navigation_Point* point) : thePoint(point), foundShortestPath(false), cost(INF), distance(){
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

    Navigation_Point *getThePoint() const {
        return thePoint;
    }

    void setThePoint(Navigation_Point *thePoint) {
        DijkstraNode::thePoint = thePoint;
    }

    std::deque<Navigation_Point *> const &getNodesInPath() const {
        return nodesInPath;
    }

    void setNodesInPath(std::deque<Navigation_Point *> const &nodesInPath) {
        DijkstraNode::nodesInPath = nodesInPath;
    }

    void addNodeToPathTail(const Navigation_Point* const point) const {
        nodesInPath.push_back(point);
    }

    static DijkstraNode* findMinimumPath(const std::map<int, DijkstraNode*>&);

private:
    bool foundShortestPath;
    double cost;
    Navigation_Point* thePoint;
    mutable std::deque<Navigation_Point*> nodesInPath;
};


#endif //NAVIGATIONB_NAVIGATIONPATH_H
