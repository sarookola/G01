#pragma once
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <string>
#include <osgText\String>

using namespace std;
class convertutf8
{
public:
	int CalcChar(int id, bool prev, bool next);
	osgText::String Convertp(osgText::String m_pText, int direction);
	osgText::String converdirection(osgText::String m_pText,int direction);

	convertutf8();
	~convertutf8();
};

