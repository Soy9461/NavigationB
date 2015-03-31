#include "BaseStructure.h"
#include <assert.h>
#include <algorithm>

class EdgeCompare_Pointer 
{  
public:   
	EdgeCompare_Pointer(Navigation_Point *_to)
	{
		To = _to;
	}

	bool operator () (Navigation_Edge *pEdge) 
	{  
		return pEdge->GetToPoint() == To;
	}  

private:
	Navigation_Point *To;
};  

Navigation_Point::Navigation_Point()
	:	Id(-1)
	,	Position(Vec3(0,0,0))
	,	Type(ePT_None)
	,	Name("")
{

}

Navigation_Point::Navigation_Point(double x, double y, double z, std::string _name)
	:	Id(-1)
	,	Position(Vec3(x,y,z))
	,	Type(ePT_None)
	,	Name(_name)
{

}

Navigation_Point::~Navigation_Point()
{
	std::deque<Navigation_Edge*>::iterator iter = ToEdges.begin();
	std::deque<Navigation_Edge*>::iterator end = ToEdges.end();
	while (iter != end)
	{
		delete (*iter);
		++iter;
	}

	ToEdges.clear();
}


void Navigation_Point::GenerateId()
{
	int height_factor = static_cast<int>((Position.z / 5) + 1);

}

void Navigation_Point::AddEdges(Navigation_Edge *pEdge)
{
	assert(pEdge);
	//if(CheckAvailable(pEdge->GetToPoint()))
	ToEdges.push_back(pEdge);
}

const bool Navigation_Point::CheckEdgeAvailable(Navigation_Point *To)
{
	if(To == this)
		return false;

	std::deque<Navigation_Edge*>::iterator find_iter = std::find_if(ToEdges.begin(), ToEdges.end(), EdgeCompare_Pointer(To));
	if(find_iter == ToEdges.end())
	{
		return true;
	}
	return false;
}

const bool Navigation_Point::CheckReachable(Navigation_Point *pTo)
{
	const Vec3 &FromPosition = this->GetPos();
	const Vec3 &ToPosition = pTo->GetPos();
	bool IsStair = (Type == ePT_Stair && pTo->GetType() == ePT_Stair);
	if(!IsStair)		//楼梯的高度可达距离与普通路点不同，分而治之,此处为普通路点的判定
	{
		if(abs(FromPosition.z - ToPosition.z) > 2.5)			//高度判定
		{
			return false;
		}

		float Distance2D = (FromPosition - ToPosition).Getlength2D();
		if(Distance2D > 17)			//水平距离判定
		{
			return false;
		}

		return true;
	}
	else				//此处为楼梯的判定
	{
		float DiffHeight = abs(FromPosition.z - ToPosition.z);
		float Distance2D = (FromPosition - ToPosition).Getlength2D();
		if(DiffHeight < 6 && Distance2D < 0.5)		//同一个楼梯的上下连接
		{
			return true;
		}

		if(Distance2D < 20 && DiffHeight < 2)		//不同楼梯的水平连接
			return true;

		return false;
	}
	return false;
}






void Navigation_Edge::CalculateCost()
{
	if(Link_From && Link_To)
	{
		const Vec3 &FromPosition = Link_From->GetPos();
		const Vec3 &ToPosition = Link_To->GetPos();

		EdgeCost = (FromPosition - ToPosition).GetLength();
	}
}