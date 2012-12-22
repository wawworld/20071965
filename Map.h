#ifndef MAP_H_
#define MAP_H_

//------------------------------------------------------------------------
//
//  [11/18/2012 KimSiHoon]
//
//  Name:   Map.h
//
//  Desc:   Map클래스, Map은 만들어질때 아이디와 파일경로를 입력해 주어야한다.
//			해당 파일경로에 해당하는 파일을 읽어 맵을 로드한다.
//
//  Author: 김시훈 (bongnam_go@naver.com) 
//
//------------------------------------------------------------------------

#include <iostream>

class Map
{
public:

	explicit Map(int id, char *file_path) : id_(id)
	{
		file_path_ = new char[sizeof(file_path)+1];
		strcpy(file_path_,file_path);
	}
	~Map(){}

	int GetID() const { return id_; }
	bool LoadMap();

private :

	int id_;
	char* file_path_;


};


#endif