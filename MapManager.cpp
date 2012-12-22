#include "MapManager.h"

MapManager *MapManager::instance_;

MapManager* MapManager::GetInstance()
{
	if(!instance_)
	{
		instance_ = new MapManager();
	}

	return instance_;
}

//------------------------------ RegisterMap ----------------------------------
// Map을 등록한다.
//-----------------------------------------------------------------------------
void MapManager::RegisterMap(Map* new_map)
{
	map_list_.push_back(new_map);
}

//----------------------------- GetMapFromID ----------------------------------
// 아이디를 넣으면 해당 Map을 반환한다.
//-----------------------------------------------------------------------------
Map* MapManager::GetMapFromID(int id) const
{
	MAP_LIST::const_iterator it = map_list_.begin();

	for(it = map_list_.begin(); it != map_list_.end(); it++)
	{
		if((*it)->GetID() == id)
		{
			return (*it);
		}
	}

	return NULL;
}

//------------------------------ RemoveMap ------------------------------------
// 아이디를 넣으면 해당 Map을 컨테이너에서 지운다.
//-----------------------------------------------------------------------------
void MapManager::RemoveMap(int id)
{    
	MAP_LIST::const_iterator it = map_list_.begin();

	for(it = map_list_.begin(); it != map_list_.end(); it++)
	{
		if((*it)->GetID() == id)
		{
			map_list_.erase(it);
		}
	}

	return;
} 

//----------------------------- Destory ---------------------------------------
// 모든 자료를 정리하고 지운다.
//-----------------------------------------------------------------------------
void MapManager::Destory()
{
	for(MAP_LIST::const_iterator it = map_list_.begin(); it != map_list_.end(); it++)
	{
		(*it)->~Map();

		delete (*it);
	}

	map_list_.clear();
	delete instance_;
}
