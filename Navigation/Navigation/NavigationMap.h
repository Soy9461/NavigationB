#ifndef _NAVIGATIONMAP_H_
#define _NAVIGATIONMAP_H_

#include "Stdafx.h"
#include "BaseStructure.h"

// 导航网
class NavigationGraph
{
private:
	std::deque<Navigation_Point*> Points;
public:
	NavigationGraph()
	{
	}

	// 描述:
	// 增加新的路点
	// 参数:
	// x, y, z--路点的坐标, type--路点的类型, _name--路点的名称
	// 路点类型参见PointType, 在BaseStructure.h里
	void AddNewPoint(double x, double y, double z, int type, std::string _name);

	// 描述:
	// 连接两个路点
	// 参数:
	// pFrom--出路点, pTo--入路点
	void AddNewEdge(Navigation_Point *pFrom, Navigation_Point *pTo);

	// 描述:
	// 连接两个路点
	// 参数:
	// FromName--出路点名称, ToName--入路点名称
	void AddNewEdge(std::string &FromName, std::string &ToName);

	// 描述:
	// 连接两个路点
	// 参数:
	// FromName--出路点名称, ToName--入路点名称
	// 兼容char*写法
	void AddNewEdge(char *FromName, char *ToName);

	// 描述:
	// 通过名称获取路点
	// 参数:
	// name--路点名称
	// 返回值:
	// 路点指针
	Navigation_Point *GetPointByName(std::string &name);

	// 描述:
	// 输出所有路点以及其连接边
	void DebugPrint();
};

// 逗B楼
class Building_B
{
private:
	NavigationGraph TheGraph;

	void GenerateGraph();
public:
	Building_B(){GenerateGraph();}

	// 描述:
	// 获取路网
	// 返回值:
	// 路网的引用
	NavigationGraph &GetGraph(){return TheGraph;}

	// 描述:
	// 输出路网的所有路点以及其连接边
	void DebugPrint(){TheGraph.DebugPrint();}
};
#endif