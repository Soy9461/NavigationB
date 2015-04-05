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
    const NavigationPath& operator=(const NavigationPath&);

    //将新节点加入到路径尾部，深度复制节点值
    void AddPointToPathTail(Navigation_Point* const);


    double GetCost();

private:

    //深度复制双端队列
    void DeepCopy(std::deque<Navigation_Point*>&);

    //当发生析构、重新附值、深度拷贝前，深度清理双端队列的内存
    void DeepClean();

    std::deque<Navigation_Point*> nodesInPath;
    double cost;
};


#endif //NAVIGATIONB_NAVIGATIONPATH_H
