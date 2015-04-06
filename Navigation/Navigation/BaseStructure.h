#ifndef _BASESTRUCTURE_H_
#define _BASESTRUCTURE_H_

#include "Stdafx.h"
#include "Vector3.h"

// 路点类型
// 可以随时添加
enum PointType
{
	ePT_WayPoint			= 0,
	ePT_ClassRoom			= 1,
	ePT_BuildingEntrance	= 2,
	ePT_Stair				= 3,


	ePT_None,
};

//------------------------------------------------------------
//Point Base Object
//------------------------------------------------------------
class Navigation_Edge;

//路点
class Navigation_Point
{
private:
	int Id;
	Vec3 Position;
	int Type;
	std::string Name;
	std::deque<Navigation_Edge*> ToEdges;

	void GenerateId();
public:
	Navigation_Point();
	Navigation_Point(double x, double y, double z, std::string _name);

	~Navigation_Point();

	//各种Get和Set
	inline const Vec3 &GetPos() const {return Position;}
	inline Vec3 GetPos(){return Position;}

	inline void SetPos(const Vec3 &Pos){Position = Pos;}
	inline const int GetType(){return Type;}

	void SetType(int _type){Type = _type;}
	const std::string &GetName()const {return Name;}

	const int GetId(){return Id;}
	inline void SetId(int _id){Id = _id;}

	const std::deque<Navigation_Edge*> &GetEdges()const {return ToEdges;}


	// 描述:
	// 给该节点添加边
	// 参数:
	// 要添加的边的指针
	void AddEdges(Navigation_Edge *pEdge);

	// 描述:
	// 检查是否已经有到某路点的边
	// 参数:
	// pTo--要检查的出路点
	const bool CheckEdgeAvailable(Navigation_Point *To);

	// 描述
	// 检查两点是否可达，当前实现中仅通过距离来判定
	// 参数:
	// pTo--要检查的出路点
	const bool CheckReachable(Navigation_Point *pTo);
};


class Navigation_Edge 
{
private:
	Navigation_Point *Link_From;
	Navigation_Point *Link_To;
	double EdgeCost;
	void CalculateCost();
public:
	Navigation_Edge()
		:	Link_From(NULL)
		,	Link_To(NULL)
		,	EdgeCost(9999){}

	Navigation_Edge(Navigation_Point *From)
		:	Link_From(From)
		,	Link_To(NULL)
		,	EdgeCost(9999){}

	Navigation_Edge(Navigation_Point *From, Navigation_Point *To)
		:	Link_From(From)
		,	Link_To(To)
		,	EdgeCost(9999)
	{
		CalculateCost();
	}


	inline const Navigation_Point *GetFromPoint()const {return Link_From;}
	inline const Navigation_Point *GetToPoint()const {return Link_To;}
	inline Navigation_Point *GetFromPoint() {return Link_From;}
	inline Navigation_Point *GetToPoint() {return Link_To;}

	const double GetCost()const {return EdgeCost;}
};



#endif
