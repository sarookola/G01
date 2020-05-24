#pragma once
#include "PackReader.h"
#include <winsock2.h>
#include <process.h>
#include <string>
#include <winsock2.h>
#include <Windows.h>
#include <stdio.h>


using namespace std;



#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>



#include "SettingPack.h"
#include"Socket.h"
#include"../Osgtest01.h"

#include <algorithm> // sort


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 4096
#define DEFAULT_PORT "9710"

#include <thread>         // std::thread


class soceketS1
{
public:
	SOCKET ConnectSocket = INVALID_SOCKET;
	Osgtest01 *ost;
	SettingPack  settingp;
	ControolPack controolp;

	PackReader s;
	char * text1 = "shayan is testing";
	bool active = true , socketIsreading=false;
	soceketS1(Osgtest01 ost);
	soceketS1();


	void packUpdatedProcess();
	void setOsgtest01(Osgtest01 *ost);
	int connection();
	int sendS1(char *sendbuf);
	char * receiveS1();
	void connectAnd();
	bool newSettingpack = false;
	~soceketS1();
};

