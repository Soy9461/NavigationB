#ifndef _BASESTRUCTURE_H_
#define _BASESTRUCTURE_H_

#include "Stdafx.h"
#include "Vector3.h"

extern const double INF;

// 路点类型
// 可以随时添加
enum PointType
{
	ePT_WayPoint			= 0x0001,
	ePT_ClassRoom			= 0x0002,
	ePT_BuildingEntrance	= 0x0004,
	ePT_Stair				= 0x0008,


	ePT_None,
};

//------------------------------------------------------------
//Point Base Object
//------------------------------------------------------------
class Navigation_Edge;

class INavigationPoint
{
public:
	virtual void GenerateId() = 0;

	virtual inline const Vec3 &GetPos() const = 0;
	virtual inline Vec3 GetPos() = 0;

	virtual inline void SetPos(const Vec3 &Pos) = 0;
	virtual inline const int GetType() = 0;

	virtual void SetType(int _type) = 0;
	virtual const std::string &GetName()const  = 0;

	virtual const int GetId() = 0;
	virtual inline void SetId(int _id) = 0;

	virtual const std::deque<Navigation_Edge*> &GetEdges()const = 0;
	virtual const unsigned int GetExclusionType() = 0;
	virtual void SetExclusionType(int _etype) = 0;

	// 描述:
	// 给该节点添加边
	// 参数:
	// 要添加的边的指针
	virtual void AddEdges(Navigation_Edge *pEdge) = 0;

	// 描述:
	// 检查是否已经有到某路点的边
	// 参数:
	// pTo--要检查的出路点
	virtual const bool CheckEdgeAvailable(INavigationPoint *To) = 0;

	// 描述
	// 检查两点是否可达，当前实现中仅通过距离来判定
	// 参数:
	// pTo--要检查的出路点
	virtual const bool CheckReachable(INavigationPoint *pTo) = 0;
};

//路点
class Navigation_Point : public INavigationPoint
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

	virtual const unsigned int GetExclusionType(){return -1;}
	virtual void SetExclusionType(int _etype){}

	// 描述:
	// 给该节点添加边
	// 参数:
	// 要添加的边的指针
	void AddEdges(Navigation_Edge *pEdge);

	// 描述:
	// 检查是否已经有到某路点的边
	// 参数:
	// pTo--要检查的出路点
	const bool CheckEdgeAvailable(INavigationPoint *To);

	// 描述
	// 检查两点是否可达，当前实现中仅通过距离来判定
	// 参数:
	// pTo--要检查的出路点
	const bool CheckReachable(INavigationPoint *pTo);
};

class ExclusionNavigationPoint : public Navigation_Point
{
private:
	int ExclusionType;
public:
	ExclusionNavigationPoint()
	:	Navigation_Point(){}
	ExclusionNavigationPoint(double x, double y, double z, std::string _name)
	:	Navigation_Point(x,y,z,_name){}
	virtual const unsigned int GetExclusionType(){return ExclusionType;}
	virtual void SetExclusionType(int _etype){ExclusionType = _etype;}
};

class Navigation_Edge 
{
private:
	INavigationPoint *Link_From;
	INavigationPoint *Link_To;
	double EdgeCost;
	void CalculateCost();
public:
	Navigation_Edge()
		:	Link_From(NULL)
		,	Link_To(NULL)
		,	EdgeCost(9999){}

	Navigation_Edge(INavigationPoint *From)
		:	Link_From(From)
		,	Link_To(NULL)
		,	EdgeCost(9999){}

	Navigation_Edge(INavigationPoint *From, INavigationPoint *To)
		:	Link_From(From)
		,	Link_To(To)
		,	EdgeCost(9999)
	{
		CalculateCost();
	}


	inline const INavigationPoint *GetFromPoint()const {return Link_From;}
	inline const INavigationPoint *GetToPoint()const {return Link_To;}
	inline INavigationPoint *GetFromPoint() {return Link_From;}
	inline INavigationPoint *GetToPoint() {return Link_To;}

	const double GetCost()const {return EdgeCost;}
};



#endif
