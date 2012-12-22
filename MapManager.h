#ifndef MAP_MANAGER_H_
#define MAP_MANAGER_H_

//------------------------------------------------------------------------
//
//  [11/18/2012 KimSiHoon]
//
//  Name:   StageManager.h
//
//  Desc:   MapÀ» °ü¸®ÇÑ´Ù.       
//
//  Author: ±è½ÃÈÆ (bongnam_go@naver.com) 
//
//------------------------------------------------------------------------

#include "Map.h"
#include <list>

#define MAP_MANAGER MapManager::GetInstance()

class MapManager
{

public:

	static MapManager* GetInstance();

	void RegisterMap(Map* new_map);

	Map* GetMapFromID(int id)const;

	void RemoveMap(int id);

	void Destory();

private:

	typedef std::list<Map*> MAP_LIST;

private:

	static MapManager *instance_;

	MAP_LIST map_list_;

private:

	MapManager(){}
	MapManager(const MapManager&);
	MapManager& operator=(const MapManager&);
	~MapManager(){}

};

#endif