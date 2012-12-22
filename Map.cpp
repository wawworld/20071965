#include "Map.h"

//------------------------------  LoadMap  ------------------------------------
// FilePath경로에 있는 텍스트파일을 읽고, 화면에 그린다.
// 파일은 @로 마침표를 찍어주어야만 한다.
//-----------------------------------------------------------------------------
bool Map::LoadMap()
{
	FILE *fp;

	fp = fopen(file_path_,"r");

	if(fp == NULL)
	{
		return false;
	}

	char ch;

	while(true)
	{
		ch = fgetc(fp);
		if(ch=='@') break;
		putchar(ch);
	}

	int f_close = fclose(fp);

	if(f_close != NULL)
	{
		return false;
	}

	return true;
}