#include "NavigationMap.h"
#include <fstream>

unsigned int NavigationGraph::AddNewPoint(double x, double y, double z, int type, std::string _name)
{
	Navigation_Point *NewPoint = new Navigation_Point(x, y, z, _name);
	NewPoint->SetType(type);
	GenerateEdge(NewPoint);

	NewPoint->SetId(static_cast<int>(Points.size()));
	Points.push_back(NewPoint);
	return NewPoint->GetId();
}

unsigned int NavigationGraph::AddNewExclusionPoint(double x, double y, double z, int type, std::string _name, int _exclusion_type)
{
	ExclusionNavigationPoint *NewPoint = new ExclusionNavigationPoint(x, y, z, _name);
	NewPoint->SetType(type);
	NewPoint->SetExclusionType(_exclusion_type);
	GenerateEdge(NewPoint);

	NewPoint->SetId(static_cast<int>(Points.size()));
	Points.push_back(NewPoint);
	return NewPoint->GetId();
}

void NavigationGraph::GenerateEdge(INavigationPoint *pPoint)
{
	std::deque<INavigationPoint*>::iterator iter = Points.begin();
	std::deque<INavigationPoint*>::iterator end = Points.end();
	while(iter != end)
	{
		/*const Vec3 &FromPosition = pPoint->GetPos();
		const Vec3 &ToPosition = (*iter)->GetPos();
		float Distance2D = (FromPosition - ToPosition).Getlength2D();
		if(Distance2D <= 0.1)
		{
			//delete (*iter);
			//iter = Points.erase(iter);
			//end = Points.end();
			++iter;
			continue;
		}*/
		if(pPoint->CheckReachable((*iter)) == true)
		{
			AddNewEdge(pPoint, (*iter));
			AddNewEdge((*iter), pPoint);
		}
		++iter;
	}
}

void NavigationGraph::AddNewEdge(INavigationPoint *pFrom, INavigationPoint *pTo)
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
	INavigationPoint *pFrom(NULL);
	INavigationPoint *pTo(NULL);
	std::deque<INavigationPoint*>::iterator iter = Points.begin();
	std::deque<INavigationPoint*>::iterator end = Points.end();
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
	INavigationPoint *pFrom(NULL);
	INavigationPoint *pTo(NULL);
	std::deque<INavigationPoint*>::iterator iter = Points.begin();
	std::deque<INavigationPoint*>::iterator end = Points.end();
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

INavigationPoint *NavigationGraph::GetPointByName(std::string &name)
{
	//Replace by std::find_if later

	std::deque<INavigationPoint*>::iterator iter = Points.begin();
	std::deque<INavigationPoint*>::iterator end = Points.end();
	while(iter != end)
	{
		if((*iter)->GetName() == name)
			return (*iter);
		++iter;
	}
	return NULL;
}

INavigationPoint *NavigationGraph::GetPointById(int Id)
{
	//Replace by std::find_if later

	std::deque<INavigationPoint*>::iterator iter = Points.begin();
	std::deque<INavigationPoint*>::iterator end = Points.end();
	while(iter != end)
	{
		if((*iter)->GetId() == Id)
			return (*iter);
		++iter;
	}
	return NULL;
}


void NavigationGraph::DebugPrint()
{
	/*std::deque<INavigationPoint*>::iterator iter = Points.begin();
	std::deque<INavigationPoint*>::iterator end = Points.end();
	while(iter != end)
	{
		INavigationPoint *ThePoint = (*iter);
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
	}*/

	std::ofstream SaveFile("OutputGraphs.txt");

	std::deque<INavigationPoint*>::iterator iter = Points.begin();
	std::deque<INavigationPoint*>::iterator end = Points.end();
	while(iter != end)
	{
		INavigationPoint *ThePoint = (*iter);
		const std::deque<Navigation_Edge*> &Edges = ThePoint->GetEdges();
		std::deque<Navigation_Edge*>::const_iterator edge_iter = Edges.begin();
		std::deque<Navigation_Edge*>::const_iterator edge_end = Edges.end();
		SaveFile<<"CurPoint: "<< ThePoint->GetName()<<" Height: "<<ThePoint->GetPos().z<<std::endl;
		while(edge_iter != edge_end)
		{
			SaveFile<<(*edge_iter)->GetFromPoint()->GetName()<<" --- "<< (*edge_iter)->GetToPoint()->GetName() << "  Distance: " << (*edge_iter)->GetCost() << std::endl;
			//printf("%s --- %s , Distance %.2lfm\n", (*edge_iter)->GetFromPoint()->GetName().c_str(), (*edge_iter)->GetToPoint()->GetName().c_str(), (*edge_iter)->GetCost());
			++edge_iter;
		}
		SaveFile<<std::endl;
		++iter;
	}

}

void NavigationGraph::DebugCheck()
{
	for(int i = 0; i < Points.size(); ++i)
	{
		for(int j = 0; j < Points.size(); ++j)
		{
			std::string fromPoint = Points[i]->GetName();
			std::string toPoint = Points[j]->GetName();
			std::deque<INavigationPoint *> *path = FindPath(fromPoint, toPoint);
			if (path != nullptr) 
			{
				/*double distance = 0;
				for (std::deque<INavigationPoint *>::iterator iterator = path->begin(),
					end = path->end();
					iterator != end;
					++iterator)
				{
					if(std::distance(iterator, end) > 1)
					{
						std::deque<INavigationPoint *>::iterator next = iterator;
						++next;
						distance += ((*iterator)->GetPos() - (*next)->GetPos()).GetLength();
					}
					//std::cout << (*iterator)->GetName() << std::endl;
				}
				printf("Available: %s -> %s, distance: %.2lf\n", fromPoint.c_str(), toPoint.c_str(), distance);*/
				delete path;
			}
			else
			{
				printf("No way from %s -> %s\n", fromPoint.c_str(), toPoint.c_str());
			}
		}
	}
}



#define _CRT_SECURE_NO_WARNINGS

const double Building_B::CalculateHeight(double pos_x, double default_height)
{
	if(default_height == 0)
		return 0.f;
	double diff = 280 - pos_x;
	//double noise = diff /20 * 2;
	double sin_factor = sin(0.04);
	double diff_height = diff * sin_factor;
	return default_height - diff_height > 0 ? default_height - diff_height : 0;
}

void Building_B::GenerateFloor_1()
{
	TheGraph.AddNewPoint(270.76,9.36,0,ePT_ClassRoom,"101");
	TheGraph.AddNewPoint(255.36,9.36,0,ePT_ClassRoom,"103");
	TheGraph.AddNewPoint(239.74,9.36,0,ePT_ClassRoom,"105");
	TheGraph.AddNewPoint(223.90,9.36,0,ePT_ClassRoom,"106");
	TheGraph.AddNewPoint(207.95,9.36,0,ePT_ClassRoom,"107");

	TheGraph.AddNewPoint(177.15,13.86,0,ePT_BuildingEntrance,"Center_Door_1");
	TheGraph.AddNewPoint(79.80,13.86,0,ePT_BuildingEntrance,"Center_Door_2");

	TheGraph.AddNewPoint(252.61,21.3,0,ePT_BuildingEntrance,"North_Door_1");
	TheGraph.AddNewPoint(200.25,21.3,0,ePT_BuildingEntrance,"North_Door_2");
	TheGraph.AddNewPoint(182.87,21.3,0,ePT_BuildingEntrance,"North_Door_3");
	TheGraph.AddNewPoint(159.99,21.3,0,ePT_BuildingEntrance,"North_Door_4");

	TheGraph.AddNewExclusionPoint(142.5,21.3,0,ePT_WayPoint,"1_WayPoint_1", ePT_BuildingEntrance | ePT_WayPoint);

	TheGraph.AddNewPoint(124.68,21.3,0,ePT_BuildingEntrance,"North_Door_5");
	TheGraph.AddNewPoint(99.16,21.3,0,ePT_BuildingEntrance,"North_Door_6");

	TheGraph.AddNewExclusionPoint(85.08,21.3,0,ePT_WayPoint,"1_WayPoint_2", ePT_BuildingEntrance | ePT_WayPoint);

	TheGraph.AddNewPoint(64.18,21.3,0,ePT_BuildingEntrance,"North_Door_7");
	TheGraph.AddNewPoint(42.40,21.3,0,ePT_BuildingEntrance,"North_Door_8");
	TheGraph.AddNewPoint(18.86,21.3,0,ePT_BuildingEntrance,"North_Door_9");
}

void Building_B::GenerateFloor_2()
{
	TheGraph.AddNewPoint(270.76,9.36,CalculateHeight(270.76,5),ePT_ClassRoom,"201");
	TheGraph.AddNewPoint(255.36,9.36,CalculateHeight(255.36,5),ePT_ClassRoom,"203");
	TheGraph.AddNewPoint(239.74,9.36,CalculateHeight(239.74,5),ePT_ClassRoom,"206");
	TheGraph.AddNewPoint(223.90,9.36,CalculateHeight(223.90,5),ePT_ClassRoom,"207");
	TheGraph.AddNewPoint(207.95,9.36,CalculateHeight(207.95,5),ePT_ClassRoom,"208");
	TheGraph.AddNewPoint(192.77,9.36,CalculateHeight(192.77,5),ePT_ClassRoom,"211");
	TheGraph.AddNewPoint(159.77,9.36,CalculateHeight(159.77,5),ePT_ClassRoom,"216");
	TheGraph.AddNewPoint(140.30,9.36,CalculateHeight(140.30,5),ePT_ClassRoom,"217");
	TheGraph.AddNewPoint(124.02,9.36,CalculateHeight(124.02,5),ePT_ClassRoom,"218");
	TheGraph.AddNewPoint(102.56,9.36,CalculateHeight(102.56,5),ePT_ClassRoom,"118");
}

void Building_B::GenerateFloor_3()
{
	TheGraph.AddNewPoint(270.76,9.36,CalculateHeight(270.76,10),ePT_ClassRoom,"301");
	TheGraph.AddNewPoint(255.36,9.36,CalculateHeight(255.36,10),ePT_ClassRoom,"303");
	TheGraph.AddNewPoint(239.74,9.36,CalculateHeight(239.74,10),ePT_ClassRoom,"306");
	TheGraph.AddNewPoint(223.90,9.36,CalculateHeight(223.90,10),ePT_ClassRoom,"307");
	TheGraph.AddNewPoint(207.95,9.36,CalculateHeight(207.95,10),ePT_ClassRoom,"308");
	TheGraph.AddNewPoint(192.77,9.36,CalculateHeight(192.77,10),ePT_ClassRoom,"311");
	TheGraph.AddNewPoint(176.93,9.36,CalculateHeight(176.93,10),ePT_ClassRoom,"312");
	TheGraph.AddNewPoint(159.77,9.36,CalculateHeight(159.77,10),ePT_ClassRoom,"314");
	TheGraph.AddNewPoint(140.30,9.36,CalculateHeight(140.30,10),ePT_ClassRoom,"315");
	TheGraph.AddNewPoint(124.02,9.36,CalculateHeight(124.02,10),ePT_ClassRoom,"316");
	TheGraph.AddNewPoint(108.18,9.36,CalculateHeight(108.18,10),ePT_ClassRoom,"318");

	TheGraph.AddNewPoint(79.80,9.36,CalculateHeight(79.80,10),ePT_ClassRoom,"320");
	TheGraph.AddNewPoint(62.64,9.36,CalculateHeight(62.64,10),ePT_ClassRoom,"321");
	TheGraph.AddNewPoint(40.64,9.36,CalculateHeight(40.64,10),ePT_ClassRoom,"324");
	TheGraph.AddNewPoint(32.28,9.36,CalculateHeight(32.28,10),ePT_ClassRoom,"325");
}

void Building_B::GenerateFloor_4()
{
	TheGraph.AddNewPoint(270.76,9.36,CalculateHeight(270.76,15),ePT_ClassRoom,"401");
	TheGraph.AddNewPoint(255.36,9.36,CalculateHeight(255.36,15),ePT_ClassRoom,"403");
	TheGraph.AddNewPoint(239.74,9.36,CalculateHeight(239.74,15),ePT_ClassRoom,"406");
	TheGraph.AddNewPoint(223.90,9.36,CalculateHeight(223.90,15),ePT_ClassRoom,"407");
	TheGraph.AddNewPoint(207.95,9.36,CalculateHeight(207.95,15),ePT_ClassRoom,"408");
	TheGraph.AddNewPoint(192.77,9.36,CalculateHeight(192.77,15),ePT_ClassRoom,"411");
	TheGraph.AddNewPoint(176.93,9.36,CalculateHeight(176.93,15),ePT_ClassRoom,"412");
	TheGraph.AddNewPoint(159.77,9.36,CalculateHeight(159.77,15),ePT_ClassRoom,"414");
	TheGraph.AddNewPoint(140.30,9.36,CalculateHeight(140.30,15),ePT_ClassRoom,"415");
	TheGraph.AddNewPoint(124.02,9.36,CalculateHeight(124.02,15),ePT_ClassRoom,"416");
	TheGraph.AddNewPoint(108.18,9.36,CalculateHeight(108.18,15),ePT_ClassRoom,"418");
	TheGraph.AddNewPoint(91.02,9.36,CalculateHeight(91.02,15),ePT_ClassRoom,"419");

	TheGraph.AddNewPoint(79.80,9.36,CalculateHeight(79.80,15),ePT_ClassRoom,"421");
	TheGraph.AddNewPoint(62.64,9.36,CalculateHeight(62.64,15),ePT_ClassRoom,"422");
	TheGraph.AddNewPoint(42.40,9.36,CalculateHeight(42.40,15),ePT_ClassRoom,"425");
	TheGraph.AddNewPoint(27.00,9.36,CalculateHeight(27.00,15),ePT_ClassRoom,"426");
}

void Building_B::GenerateFloor_5()
{
	TheGraph.AddNewPoint(270.76,9.36,CalculateHeight(270.76,20),ePT_WayPoint,"5_WayPoint_1");
	TheGraph.AddNewPoint(255.36,9.36,CalculateHeight(255.36,20),ePT_ClassRoom,"501");
	TheGraph.AddNewPoint(239.74,9.36,CalculateHeight(239.74,20),ePT_WayPoint,"5_WayPoint_1");
	TheGraph.AddNewPoint(223.90,9.36,CalculateHeight(223.90,20),ePT_ClassRoom,"502");
	TheGraph.AddNewPoint(207.95,9.36,CalculateHeight(207.95,20),ePT_ClassRoom,"503");
	TheGraph.AddNewPoint(192.77,9.36,CalculateHeight(192.77,20),ePT_ClassRoom,"506");
	TheGraph.AddNewPoint(176.93,9.36,CalculateHeight(176.93,20),ePT_ClassRoom,"507");
	TheGraph.AddNewPoint(159.77,9.36,CalculateHeight(159.77,20),ePT_ClassRoom,"509");
	TheGraph.AddNewPoint(140.30,9.36,CalculateHeight(140.30,20),ePT_ClassRoom,"510");
	TheGraph.AddNewPoint(124.02,9.36,CalculateHeight(124.02,20),ePT_ClassRoom,"511");
	TheGraph.AddNewPoint(108.18,9.36,CalculateHeight(108.18,20),ePT_ClassRoom,"513");
	TheGraph.AddNewPoint(91.02,9.36,CalculateHeight(91.02,20),ePT_ClassRoom,"514");

	TheGraph.AddNewPoint(79.80,9.36,CalculateHeight(79.80,20),ePT_ClassRoom,"516");
	TheGraph.AddNewPoint(62.64,9.36,CalculateHeight(62.64,20),ePT_ClassRoom,"517");
	TheGraph.AddNewPoint(42.40,9.36,CalculateHeight(42.40,20),ePT_ClassRoom,"520");
	TheGraph.AddNewPoint(27.00,9.36,CalculateHeight(27.00,20),ePT_ClassRoom,"521");
}

void Building_B::GenerateFloor_6()
{
	TheGraph.AddNewPoint(176.93,9.36,CalculateHeight(176.93,25),ePT_ClassRoom,"601");
	TheGraph.AddNewPoint(159.77,9.36,CalculateHeight(159.77,25),ePT_WayPoint,"6_WayPoint_1");
	TheGraph.AddNewPoint(140.30,9.36,CalculateHeight(140.30,25),ePT_ClassRoom,"602");
	TheGraph.AddNewPoint(124.02,9.36,CalculateHeight(124.02,25),ePT_ClassRoom,"603");
	TheGraph.AddNewPoint(108.18,9.36,CalculateHeight(108.18,25),ePT_ClassRoom,"605");
	TheGraph.AddNewPoint(91.02,9.36,CalculateHeight(91.02,25),ePT_ClassRoom,"606");

	TheGraph.AddNewPoint(79.80,9.36,CalculateHeight(79.80,25),ePT_ClassRoom,"608");
	TheGraph.AddNewPoint(62.64,9.36,CalculateHeight(62.64,25),ePT_ClassRoom,"609");
	TheGraph.AddNewPoint(42.40,9.36,CalculateHeight(42.40,25),ePT_ClassRoom,"612");
	TheGraph.AddNewPoint(27.00,9.36,CalculateHeight(27.00,25),ePT_ClassRoom,"613");
}


void Building_B::GenerateFloor_7()
{
	TheGraph.AddNewPoint(91.02,9.36,CalculateHeight(91.02,30),ePT_ClassRoom,"701");
	TheGraph.AddNewPoint(79.80,9.36,CalculateHeight(79.80,30),ePT_ClassRoom,"7_WayPoint_1");
	TheGraph.AddNewPoint(62.64,9.36,CalculateHeight(62.64,30),ePT_ClassRoom,"703");
	TheGraph.AddNewPoint(42.40,9.36,CalculateHeight(42.40,30),ePT_ClassRoom,"706");
	TheGraph.AddNewPoint(27.00,9.36,CalculateHeight(27.00,30),ePT_ClassRoom,"707");
}

void Building_B::GenerateNorth()
{
	TheGraph.AddNewPoint(200.25,26.94,10,ePT_ClassRoom,"442");
	TheGraph.AddNewPoint(176.27,26.94,10,ePT_ClassRoom,"443");
	TheGraph.AddNewPoint(149.65,26.94,10,ePT_ClassRoom,"437");
	TheGraph.AddNewPoint(123.14,26.94,10,ePT_ClassRoom,"434");
	TheGraph.AddNewPoint(99.38,26.94,10,ePT_ClassRoom,"433");
	TheGraph.AddNewPoint(163.51,17.28,10,ePT_WayPoint,"3_South_To_North4_1");
	TheGraph.AddNewPoint(148.77,17.28,10,ePT_WayPoint,"3_South_To_North4_2");

	TheGraph.AddNewPoint(200.25,26.94,20,ePT_ClassRoom,"538");
	TheGraph.AddNewPoint(176.27,26.94,20,ePT_ClassRoom,"537");
	TheGraph.AddNewPoint(149.65,26.94,20,ePT_ClassRoom,"532");
	TheGraph.AddNewPoint(123.14,26.94,20,ePT_ClassRoom,"529");
	TheGraph.AddNewPoint(99.38,26.94,20,ePT_ClassRoom,"528");
	TheGraph.AddNewPoint(87.28,17.28,10,ePT_WayPoint,"4_South_To_North4_1");
	TheGraph.AddNewPoint(180.23,17.28,10,ePT_WayPoint,"4_South_To_North5_1");
	TheGraph.AddNewPoint(87.28,17.28,20,ePT_WayPoint,"5_South_To_North5_1");
}

void Building_B::GenerateSouthStairs()
{
	float height_factor = 0.f;
	for(int i = 1; i <= 7; ++i)
	{
		char index[2];
		_itoa_s(i,index,10);
		if(i <= 7)
		{
			TheGraph.AddNewPoint(68.58,7.14,CalculateHeight(68.58,(i - 1)*5),ePT_Stair, index + std::string("_Stair_S_8"));
			if(i >= 4)
				TheGraph.AddNewPoint(25.24,7.14,CalculateHeight(25.24,(i - 1)*5),ePT_Stair, index + std::string("_Stair_S_9"));
			TheGraph.AddNewPoint(15.23,7.14,CalculateHeight(15.23,(i - 1)*5),ePT_Stair, index + std::string("_Stair_S_10"));
		}
		if(i <= 6)
		{
			TheGraph.AddNewPoint(149.54,7.14,CalculateHeight(149.54,(i - 1)*5),ePT_Stair, index + std::string("_Stair_S_5"));
			TheGraph.AddNewPoint(129.96,7.14,CalculateHeight(129.96,(i - 1)*5),ePT_Stair, index + std::string("_Stair_S_6"));
			TheGraph.AddNewPoint(96.52,7.14,CalculateHeight(96.52,(i - 1)*5),ePT_Stair, index + std::string("_Stair_S_7"));
		}
		if(i <= 5)
		{
			TheGraph.AddNewPoint(280,7.14,CalculateHeight(280,(i - 1)*5),ePT_Stair, index + std::string("_Stair_S_1"));
			TheGraph.AddNewPoint(229.29,7.14,CalculateHeight(229.29,(i - 1)*5),ePT_Stair, index + std::string("_Stair_S_2"));
			TheGraph.AddNewPoint(213.45,7.14,CalculateHeight(213.45,(i - 1)*5),ePT_Stair, index + std::string("_Stair_S_3"));
			TheGraph.AddNewPoint(182.65,7.14,CalculateHeight(182.65,(i - 1)*5),ePT_Stair, index + std::string("_Stair_S_4"));
		}
	}

	/*TheGraph.AddNewPoint(280,7.14,0,ePT_Stair,"1_Stair_S_1");
	TheGraph.AddNewPoint(229.29,7.14,0,ePT_Stair,"1_Stair_S_2");
	TheGraph.AddNewPoint(213.45,7.14,0,ePT_Stair,"1_Stair_S_3");
	TheGraph.AddNewPoint(182.65,7.14,0,ePT_Stair,"1_Stair_S_4");
	TheGraph.AddNewPoint(149.54,7.14,0,ePT_Stair,"1_Stair_S_5");
	TheGraph.AddNewPoint(129.96,7.14,0,ePT_Stair,"1_Stair_S_6");
	TheGraph.AddNewPoint(96.52,7.14,0,ePT_Stair,"1_Stair_S_7");
	TheGraph.AddNewPoint(68.58,7.14,0,ePT_Stair,"1_Stair_S_8");
	TheGraph.AddNewPoint(25.24,7.14,0,ePT_Stair,"1_Stair_S_9");
	TheGraph.AddNewPoint(15.23,7.14,0,ePT_Stair,"1_Stair_S_10")*/
}

void Building_B::GenerateCenterStairs()
{
	for(int i = 1; i <= 7; ++i)
	{
		char index[2];
		_itoa_s(i,index,10);
		if(i <= 5)
		{
			TheGraph.AddNewPoint(257.34,17.28,CalculateHeight(257.34,(i - 1)*5),ePT_Stair, index + std::string("_Stair_C_1"));
			TheGraph.AddNewPoint(222.80,17.28,CalculateHeight(222.80,(i - 1)*5),ePT_Stair, index + std::string("_Stair_C_2"));
		}
		if(i <= 6)
		{
			TheGraph.AddNewPoint(194.64,17.28,CalculateHeight(194.64,(i - 1)*5),ePT_Stair, index + std::string("_Stair_C_3"));
			TheGraph.AddNewPoint(159.66,17.28,CalculateHeight(159.66,(i - 1)*5),ePT_Stair, index + std::string("_Stair_C_4"));
		}
		if(i <= 7)
		{
			TheGraph.AddNewPoint(108.29,17.28,CalculateHeight(108.29,(i - 1)*5),ePT_Stair, index + std::string("_Stair_C_5"));
			TheGraph.AddNewPoint(60.11,17.28,CalculateHeight(60.11,(i - 1)*5),ePT_Stair, index + std::string("_Stair_C_6"));
		}
		if(i <= 4)
			TheGraph.AddNewPoint(26.34,17.28,CalculateHeight(26.34,(i - 1)*5),ePT_Stair, index + std::string("_Stair_C_7"));
	}
}

void Building_B::GenerateNorthStairs()
{
	/*for(int i = 3; i <= 5; ++i)
	{
		char index[2];
		_itoa_s(i,index,10);
		TheGraph.AddNewPoint(192.33,26.94,10,ePT_Stair, std::string("3_Stair_N_1"));
		TheGraph.AddNewPoint(115.44,26.94,10,ePT_Stair, std::string("3_Stair_N_2"));
	}*/
	unsigned int Id_1 = TheGraph.AddNewPoint(192.33,26.94,0,ePT_Stair, std::string("1_Stair_N_1"));
	unsigned int Id_2 = TheGraph.AddNewPoint(115.44,26.94,0,ePT_Stair, std::string("1_Stair_N_2"));

	unsigned int Id_3 = TheGraph.AddNewPoint(192.33,26.94,10,ePT_Stair, std::string("3_Stair_N_1"));
	unsigned int Id_4 = TheGraph.AddNewPoint(115.44,26.94,10,ePT_Stair, std::string("3_Stair_N_2"));

	unsigned int Id_5 = TheGraph.AddNewPoint(192.33,26.94,20,ePT_Stair, std::string("5_Stair_N_1"));
	unsigned int Id_6 = TheGraph.AddNewPoint(115.44,26.94,20,ePT_Stair, std::string("5_Stair_N_2"));

	TheGraph.AddNewEdge(TheGraph.GetPointById(Id_1), TheGraph.GetPointById(Id_3));
	TheGraph.AddNewEdge(TheGraph.GetPointById(Id_3), TheGraph.GetPointById(Id_5));

	TheGraph.AddNewEdge(TheGraph.GetPointById(Id_2), TheGraph.GetPointById(Id_4));
	TheGraph.AddNewEdge(TheGraph.GetPointById(Id_4), TheGraph.GetPointById(Id_6));
	/*TheGraph.AddNewPoint(192.33,26.94,0,ePT_Stair,"1_Stair_N_1");
	TheGraph.AddNewPoint(115.44,26.94,0,ePT_Stair,"1_Stair_N_2");*/
}

void Building_B::GenerateGraph()
{
	GenerateFloor_1();
	GenerateFloor_2();
	GenerateFloor_3();
	GenerateFloor_4();
	GenerateFloor_5();
	GenerateFloor_6();
	GenerateFloor_7();
	GenerateNorth();
	/*TheGraph.AddNewPoint(280,7.14,0,ePT_Stair,"1_Stair_S_1");
	TheGraph.AddNewPoint(229.29,7.14,0,ePT_Stair,"1_Stair_S_2");
	TheGraph.AddNewPoint(213.45,7.14,0,ePT_Stair,"1_Stair_S_3");
	TheGraph.AddNewPoint(182.65,7.14,0,ePT_Stair,"1_Stair_S_4");
	TheGraph.AddNewPoint(149.54,7.14,0,ePT_Stair,"1_Stair_S_5");
	TheGraph.AddNewPoint(129.96,7.14,0,ePT_Stair,"1_Stair_S_6");
	TheGraph.AddNewPoint(96.52,7.14,0,ePT_Stair,"1_Stair_S_7");
	TheGraph.AddNewPoint(68.58,7.14,0,ePT_Stair,"1_Stair_S_8");
	TheGraph.AddNewPoint(15.23,7.14,0,ePT_Stair,"1_Stair_S_9");*/

	GenerateSouthStairs();
	GenerateCenterStairs();
	GenerateNorthStairs();
}


std::deque<INavigationPoint*> *NavigationGraph::FindPath(std::string &FromName, std::string &ToName) {
	INavigationPoint *startPoint = this->GetPointByName(FromName), *targetPoint = this->GetPointByName(ToName);

	if(!startPoint)
	{
		printf("No %s in this graph\n", FromName.c_str());
		return NULL;
	}
	if(!targetPoint)
	{
		printf("No %s in this graph\n", ToName.c_str());
		return NULL;
	}

	std::map<int, DijkstraNode *> dijkstraNodes;

	for (std::deque<INavigationPoint *>::const_iterator iter = Points.begin(), end = Points.end();
		iter != end; ++iter) {
			dijkstraNodes.insert(std::make_pair((*iter)->GetId(), new DijkstraNode(*iter)));
	}

	//---- 从出路点开始，初始化迪杰斯特拉算法
	//Navigation_Point *currentPoint = startPoint;
	DijkstraNode *currentNode = dijkstraNodes[startPoint->GetId()];
	currentNode->addNodeToPathTail(currentNode->getThePoint());
	currentNode->setCost(0);

	//---- 算法正体
	while (currentNode != nullptr) {
		currentNode->setFoundShortestPath(true);

		//出路点的相邻点更新权值
		std::deque<Navigation_Edge *>::const_iterator edgeIterator = currentNode->getThePoint()->GetEdges().begin();
		std::deque<Navigation_Edge *>::const_iterator edge_end = currentNode->getThePoint()->GetEdges().end();
		while(edgeIterator != edge_end)
		{
			Navigation_Edge* IterEdge = (*edgeIterator);
			DijkstraNode *IterNode = dijkstraNodes[IterEdge->GetToPoint()->GetId()];
			if (!IterNode->isFoundShortestPath()) 
			{
				bool InfValue(IterNode->getCost() == INF);
				bool LessValue(currentNode->getCost() + IterEdge->GetCost() < IterNode->getCost());

				if (InfValue || LessValue) 
				{
					IterNode->setCost(currentNode->getCost() + IterEdge->GetCost());

					//dijkstraNodes[(*edgeIterator)->GetToPoint()->GetId()]->getDistance().addPointToPathTail(currentNode);
					IterNode->setNodesInPath(currentNode->getNodesInPath());

					//这里曾使用了const_cast,后来改了
					IterNode->addNodeToPathTail(IterEdge->GetToPoint());
				}
			}
			++edgeIterator;
		}

		currentNode = DijkstraNode::findMinimumPath(dijkstraNodes);
	}
	//---- 算法结束

	std::deque<INavigationPoint *> *targetPath = nullptr;

	if (dijkstraNodes[targetPoint->GetId()]->getCost() < INF) {
		targetPath = new std::deque<INavigationPoint *>(
			dijkstraNodes[targetPoint->GetId()]->getNodesInPath().begin(),
			dijkstraNodes[targetPoint->GetId()]->getNodesInPath().end());
	}

	//清除map中second部分指向的内存
	for (std::map<int, DijkstraNode *>::const_iterator iterator = dijkstraNodes.begin(), end = dijkstraNodes.end();
		iterator != end;
		++iterator) {
			delete (*iterator).second;
			//(*iterator).second = nullptr;
	}

	return targetPath;
}

std::deque<INavigationPoint *>* Building_B::FindPath(std::string& FromNode, std::string& ToNode) {
	return TheGraph.FindPath(FromNode, ToNode);
}


void Building_B::DebugFindPath(std::string &sFrom, std::string &sTo)
{
	std::deque<INavigationPoint *> *path = FindPath(sFrom, sTo);
	if (path != nullptr)
	{
		double distance = 0;
		for (std::deque<INavigationPoint *>::iterator iterator = path->begin(),
			end = path->end();
			iterator != end;
		++iterator)
		{
			if(std::distance(iterator, end) > 1)
			{
				std::deque<INavigationPoint *>::iterator next = iterator;
				++next;
				distance += ((*iterator)->GetPos() - (*next)->GetPos()).GetLength();
				printf("%s -> ", (*iterator)->GetName().c_str());
			}
			else
				printf("%s\n", (*iterator)->GetName().c_str());
		}
		printf("Distance: %.1lfm", distance);
		delete path;
	}
	else
	{
		printf("No way from %s -> %s", sFrom.c_str(), sTo.c_str());
	}
}