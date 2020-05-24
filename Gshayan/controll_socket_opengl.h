#pragma once


#include "stdafx.h"
#include "Osgtest01.h"
#include "resource.h"
#include  "sockets\soceketS1.h"
#include <thread>
#include"GdiKeyer.h"



#define MAX_LOADSTRING 100

class controll_socket_opengl
{
public:
	
	Osgtest01* osg; 
	soceketS1 sockets1;
	DeckLinkKeyerDelegate* dckLinkKeyerDelegate;
	BYTE* pbDestData;

	bool decklinkactive = true;
	int x = 0;

	osg::Timer_t start_tick;

	controll_socket_opengl();
	~controll_socket_opengl();
	
	

	void masterLoop();


	//void error_callback(int error, const char* description);
	//int imgui();



};

