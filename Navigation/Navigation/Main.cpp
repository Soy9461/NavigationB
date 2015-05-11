#include <iostream>
#include "NavigationMap.h"

int main()
{
	Building_B TheBuilding;
	TheBuilding.DebugPrint();
	//TheBuilding.GetGraph().DebugCheck();
	std::string FromString("101");
	std::string ToString("425");
	TheBuilding.DebugFindPath(FromString,ToString);
	getchar();
	return 0;
}
