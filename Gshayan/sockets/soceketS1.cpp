#include "soceketS1.h"




soceketS1::soceketS1(Osgtest01 ot)
{
	ost = &ot;
}

soceketS1::soceketS1()
{

}

void soceketS1::packUpdatedProcess()
{
	newSettingpack = false;
	controolp.clear();
	settingp.clear();
}

void soceketS1::setOsgtest01(Osgtest01 *ot)
{
	ost = ot;
}
int soceketS1::connection()
{

	WSADATA wsaData;

	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;
	//char *sendbuf = "this is a test";
	//char recvbuf[DEFAULT_BUFLEN];
	int iResult;
	//int recvbuflen = DEFAULT_BUFLEN;



	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// Attempt to connect to an address until one succeeds


	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);

		if (ConnectSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			return 1;
		}

		// Connect to server.

		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}

		break;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		return 1;
	}
	return iResult;

}

int soceketS1::sendS1(char *sendbuf) {
	// Send an initial buffer
	int iResult;
	//char *sendbuf2 = "this is a test";
	if ((ConnectSocket != INVALID_SOCKET)) {
		iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
		if (iResult == SOCKET_ERROR) {
			printf("send failed with error: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return 1;
		}

		printf("Bytes Sent: %ld\n", iResult);
		return iResult;
	}
	return -1;
}

char* soceketS1::receiveS1() {
	osg::Timer_t time0=osg::Timer::instance()->time_u();
	if (newSettingpack || socketIsreading)
	{
		cout << "990220 -    Socket1   - socket is reading" << endl;
		return"0";
	}
	socketIsreading = true;
	int iResult,part;
	char *recvbuf;
	//wchar_t *recvbuf_t;
	//vector<string> buffer;
	string  rpack;
	int recvbuflen = DEFAULT_BUFLEN;

	do {
		rpack = "";
		part = 0;
		do {
			recvbuf = new char[DEFAULT_BUFLEN];
			//recvbuf_t = new wchar_t[DEFAULT_BUFLEN];

			iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);

		//	wstring ws(recvbuf_t);
			//string sto(ws.begin(), ws.end());

			string  sto = recvbuf;
			
		//	cout << " ++++++++++++ iresult=" << iResult << "\tstrlenrecvbuf " << strlen(recvbuf) << "\t dtosize=" << sto.size() ;
		//cout << "    new sto==" << sto.size() << endl;
			if (sto.size() > iResult) {
				sto = sto.substr(0, iResult);
				part++;
			}
			
			rpack = rpack + sto;
			//buffer.push_back(sto);
				//	cout << "iResult="<< iResult<<" \t buffer="<< recvbuf << endl;
			} while (iResult == DEFAULT_BUFLEN);
			if (iResult > 0)
			{
				//	printf("Bytes received: %d  \t and index =%d      parts=%d\n", iResult, rpack.size() ,part);
					//cout << recvbuf << endl;
				string  sto = "", st = "";
				//for (size_t i = 0; i < buffer.size(); i++)
				//{

				//	//cout <<"i"<<i<<endl<< "sto.size+++++++++++++++++++++++++++++++++++++++++=" << sto.size()<< "\t"<<"sto=" << sto << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"<<endl;

				//	//	cout << "sto>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>=" << sto << "\t************************************" << endl<<endl;

				//	st = st + buffer.at(i);
				//}
				//cout << endl << endl << "_____________________________________________________" << st << endl;
			if(	s.decode (rpack, settingp, controolp))
				newSettingpack = true;
			cout << "990220- read pack at " << (osg::Timer::instance()->time_u() - time0) / 100000 << endl;
			//	buffer.clear();
			//  ost->runframe2();
			//  ost->sethexXform5pos(settingp.drawSettingS[0].drawingDimsList[0][0].pos[0], settingp.drawSettingS[0].drawingDimsList[0][0].pos[1], settingp.drawSettingS[0].drawingDimsList[0][0].pos[2]);
			}
			else if (iResult == 0)
				printf("Connection closed\n");
			else
				printf("recv failed with error: %d\n", WSAGetLastError());


		}
	 while (iResult > 0 && ConnectSocket != INVALID_SOCKET);
		socketIsreading = false;
		char* tet = "test";

		return tet;// recvbuf;
	}

void soceketS1::connectAnd()
{
	while (active) {
		if (connection() == 0) {
			cout << "connection=" << endl;
			cout << "recieve=";
			cout << (receiveS1()) << endl;
		}
	}

}
soceketS1::~soceketS1()
{
	closesocket(ConnectSocket);
	WSACleanup();

}
