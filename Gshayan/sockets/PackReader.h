#pragma once
#include<stdio.h>
#include<iostream>
//#include <winsock2.h>
//#include <process.h>
//#include <string>
//#include <winsock2.h>
//#include <Windows.h>
//
//#include <stdio.h>
//
//
//using namespace std;
//
//
//
//#define WIN32_LEAN_AND_MEAN
//
//#include <windows.h>
//#include <winsock2.h>
//#include <ws2tcpip.h>
//#include <stdlib.h>
//#include <stdio.h>
//
//#include "include\json\json.h"
//#include "include\json\reader.h"
//#include"test2.h"
//#include "SettingPack.h"
//#include"Socket.h"
//
//
//#include <algorithm> // sort
//
//
//// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
//#pragma comment (lib, "Ws2_32.lib")
//#pragma comment (lib, "Mswsock.lib")
//#pragma comment (lib, "AdvApi32.lib")
//
//
//#define DEFAULT_BUFLEN 4096
//#define DEFAULT_PORT "9710"

#define _USE_MATH_DEFINES // for C
#include <math.h>

#include "include\json\json.h"
#include "include\json\reader.h"
#include "SettingPack.h"
#include "..\ControolPack.h"





class PackReader
{
public:
	bool decode(string text, SettingPack &s ,ControolPack &c);
	string texttoUnicode(string text);
	wchar_t* UTF8toUnicode(const string & s);
	PackReader();
	~PackReader();
};

