#ifndef _NAVIGATIONMAP_H_
#define _NAVIGATIONMAP_H_

#include "Stdafx.h"
#include "BaseStructure.h"
#include "NavigationPath.h"

// 导航网
class NavigationGraph
{
private:
	std::deque<INavigationPoint*> Points;

	void GenerateEdge(INavigationPoint *pPoint);
public:
	NavigationGraph()
	{
	}

	// 描述:
	// 增加新的路点
	// 参数:
	// x, y, z--路点的坐标, type--路点的类型, _name--路点的名称
	// 路点类型参见PointType, 在BaseStructure.h里
	unsigned int AddNewPoint(double x, double y, double z, int type, std::string _name);

	// 描述:
	// 增加新的限制访问路点
	// 参数:
	// x, y, z--路点的坐标, type--路点的类型, _name--路点的名称, _exclusion_type--限制类型
	// 路点类型参见PointType, 在BaseStructure.h里, 限制类型与路点类型相同
	unsigned int AddNewExclusionPoint(double x, double y, double z, int type, std::string _name, int _exclusion_type);

	// 描述:
	// 连接两个路点
	// 参数:
	// pFrom--出路点, pTo--入路点
	void AddNewEdge(INavigationPoint *pFrom, INavigationPoint *pTo);

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
	INavigationPoint *GetPointByName(std::string &name);

	// 描述:
	// 通过Id获取路点
	// 参数:
	// Id--路点Id
	// 返回值:
	// 路点指针
	INavigationPoint *GetPointById(int Id);
	// 描述:
	// 输出所有路点以及其连接边
	void DebugPrint();

	// 描述：
	// 获得指定路点间的最短路径
	// 实现算法为Dijkstra算法
	// 参数：
	// FromName--出路点名称，ToName--入路点名称
	// 返回值：
	// 成功时返回NavigationPath指针
	// 失败时返回空指针
	std::deque<INavigationPoint*>* FindPath(std::string& FromName, std::string& ToName);

	void DebugCheck();
};

// 逗B楼
class Building_B
{
private:
	NavigationGraph TheGraph;

	void GenerateGraph();

	const double CalculateHeight(double pos_x, double default_height);
	void GenerateFloor_1();
	void GenerateFloor_2();
	void GenerateFloor_3();
	void GenerateFloor_4();
	void GenerateFloor_5();
	void GenerateFloor_6();
	void GenerateFloor_7();
	void GenerateNorth();
	void GenerateSouthStairs();
	void GenerateCenterStairs();
	void GenerateNorthStairs();
public:
	Building_B(){GenerateGraph();}

	// 描述:
	// 获取路网
	// 返回值:
	// 路网的引用
	NavigationGraph &GetGraph(){return TheGraph;}

	std::deque<INavigationPoint*>* FindPath(std::string&, std::string&);

	// 描述:
	// 输出路网的所有路点以及其连接边
	void DebugPrint(){TheGraph.DebugPrint();}

	void DebugFindPath(std::string &sFrom, std::string &sTo);
};
#endif