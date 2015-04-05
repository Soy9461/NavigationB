#include "NavigationMap.h"

void NavigationGraph::AddNewPoint(double x, double y, double z, int type, std::string _name)
{
	Navigation_Point *NewPoint = new Navigation_Point(x, y, z, _name);
	NewPoint->SetType(type);
	std::deque<Navigation_Point*>::iterator iter = Points.begin();
	std::deque<Navigation_Point*>::iterator end = Points.end();
	while(iter != end)
	{
		if(NewPoint->CheckReachable((*iter)) == true)
		{
			AddNewEdge(NewPoint, (*iter));
			AddNewEdge((*iter), NewPoint);
		}
		++iter;
	}

	Points.push_back(NewPoint);
}

void NavigationGraph::AddNewEdge(Navigation_Point *pFrom, Navigation_Point *pTo)
{
	const bool Available = pFrom->CheckEdgeAvailable(pTo);
	if(Available)
	{
		Navigation_Edge *pEdge = new Navigation_Edge(pFrom, pTo);
		pFrom->AddEdges(pEdge);
	}
}

void NavigationGraph::AddNewEdge(std::string &FromName, std::string &ToName)
{
	Navigation_Point *pFrom(NULL);
	Navigation_Point *pTo(NULL);
	std::deque<Navigation_Point*>::iterator iter = Points.begin();
	std::deque<Navigation_Point*>::iterator end = Points.end();
	while(iter != end)
	{
		if((*iter)->GetName() == FromName && !pFrom)
			pFrom = (*iter);
		if((*iter)->GetName() == ToName && !pTo)
			pTo = (*iter);
		if(pFrom && pTo)
			break;
		++iter;
	}

	if(iter != end)
	{
		AddNewEdge(pFrom, pTo);
	}
}

void NavigationGraph::AddNewEdge(char *FromName, char *ToName)
{
	Navigation_Point *pFrom(NULL);
	Navigation_Point *pTo(NULL);
	std::deque<Navigation_Point*>::iterator iter = Points.begin();
	std::deque<Navigation_Point*>::iterator end = Points.end();
	while(iter != end)
	{
		if((*iter)->GetName() == FromName && !pFrom)
			pFrom = (*iter);
		if((*iter)->GetName() == ToName && !pTo)
			pTo = (*iter);
		if(pFrom && pTo)
			break;
		++iter;
	}

	if(iter != end)
	{
		AddNewEdge(pFrom, pTo);
	}
}

Navigation_Point *NavigationGraph::GetPointByName(std::string &name)
{
	//Replace by std::find_if later

	std::deque<Navigation_Point*>::iterator iter = Points.begin();
	std::deque<Navigation_Point*>::iterator end = Points.end();
	while(iter != end)
	{
		if((*iter)->GetName() == name)
			return (*iter);
		++iter;
	}
	return NULL;
}

void NavigationGraph::DebugPrint()
{
	std::deque<Navigation_Point*>::iterator iter = Points.begin();
	std::deque<Navigation_Point*>::iterator end = Points.end();
	while(iter != end)
	{
		Navigation_Point *ThePoint = (*iter);
		const std::deque<Navigation_Edge*> &Edges = ThePoint->GetEdges();
		std::deque<Navigation_Edge*>::const_iterator edge_iter = Edges.begin();
		std::deque<Navigation_Edge*>::const_iterator edge_end = Edges.end();
		while(edge_iter != edge_end)
		{
			printf("%s --- %s , Distance %.2lfm\n", (*edge_iter)->GetFromPoint()->GetName().c_str(), (*edge_iter)->GetToPoint()->GetName().c_str(), (*edge_iter)->GetCost());
			++edge_iter;
		}
		printf("\n");
		++iter;
	}
}




#define _CRT_SECURE_NO_WARNINGS

void Building_B::GenerateGraph()
{
	TheGraph.AddNewPoint(280,7.14,0,ePT_Stair,"1_Stair_S_1");
	TheGraph.AddNewPoint(270.76,9.36,0,ePT_ClassRoom,"101");
	TheGraph.AddNewPoint(255.36,9.36,0,ePT_ClassRoom,"103");
	TheGraph.AddNewPoint(239.74,9.36,0,ePT_ClassRoom,"105");
	TheGraph.AddNewPoint(229.29,7.14,0,ePT_Stair,"1_Stair_S_2");
	TheGraph.AddNewPoint(223.90,9.36,0,ePT_ClassRoom,"106");
	TheGraph.AddNewPoint(213.45,7.14,0,ePT_Stair,"1_Stair_S_3");
	TheGraph.AddNewPoint(207.95,9.36,0,ePT_ClassRoom,"107");
	TheGraph.AddNewPoint(182.65,7.14,0,ePT_Stair,"1_Stair_S_4");
	TheGraph.AddNewPoint(149.54,7.14,0,ePT_Stair,"1_Stair_S_5");
	TheGraph.AddNewPoint(129.96,7.14,0,ePT_Stair,"1_Stair_S_6");
	TheGraph.AddNewPoint(96.52,7.14,0,ePT_Stair,"1_Stair_S_7");
	TheGraph.AddNewPoint(68.58,7.14,0,ePT_Stair,"1_Stair_S_8");
	TheGraph.AddNewPoint(15.23,7.14,0,ePT_Stair,"1_Stair_S_9");

	for(int i = 1; i <= 7; ++i)
	{
		char index[2];
		_itoa_s(i,index,10);
		if(i <= 5)
		{
			TheGraph.AddNewPoint(257.34,17.28,(i - 1)*5,ePT_Stair, index + std::string("_Stair_C_1"));
			TheGraph.AddNewPoint(222.80,17.28,(i - 1)*5,ePT_Stair, index + std::string("_Stair_C_2"));
		}
		if(i <= 6)
		{
			TheGraph.AddNewPoint(194.64,17.28,(i - 1)*5,ePT_Stair, index + std::string("_Stair_C_3"));
			TheGraph.AddNewPoint(159.66,17.28,(i - 1)*5,ePT_Stair, index + std::string("_Stair_C_4"));
		}
		if(i <= 7)
			TheGraph.AddNewPoint(108.29,17.28,(i - 1)*5,ePT_Stair, index + std::string("_Stair_C_5"));
		TheGraph.AddNewPoint(60.11,17.28,(i - 1)*5,ePT_Stair, index + std::string("_Stair_C_6"));
		if(i <= 4)
			TheGraph.AddNewPoint(31.18,17.28,(i - 1)*5,ePT_Stair, index + std::string("_Stair_C_7"));
	}

	TheGraph.AddNewPoint(192.33,26.94,0,ePT_Stair,"1_Stair_N_1");
	TheGraph.AddNewPoint(115.44,26.94,0,ePT_Stair,"1_Stair_N_2");
}

NavigationPath *NavigationGraph::FindPath(std::string &FromName, std::string &ToName) {
	Navigation_Point* startPoint = this->GetPointByName(FromName), *targetPoint = this->GetPointByName(ToName);
	std::map<int, DijkstraNode> dijkstraNodes;
	return nullptr;
}
