#pragma once

#include <vector>

using namespace std;

class SettingPack
{
public:
	bool updated;
	struct drawSettingDims
	{
//		int id;
		double pos[3];
		double scale[3];
		double angle[3];
		int acceleratein, accelerateout;
		int strokC;
		int textC;
		int opac;
		int frames;
	};
	struct drawSettingColors
	{
//		int id;
		int strokC;
		int textC;
		int opac;
		int frames;
	};
	struct DrawSettingS
	{
		int id = 0;
		int parent;
		int ito; //image text object
		int language;
		string text1;
		string image;
		bool vis;
		//bool textvisiblity;
		bool imageSequency;
		bool anloop;
		bool seqLoop;
		int sequencCount;
		int AnimateRate;
		vector<vector<drawSettingDims>> drawingDimsList;
		vector<vector<drawSettingDims>> drawingColorList;
		int back;
		int linkTo;
		vector<int> childs;
		int alignment = 1;//0=left 1- middele 2:right....
		int CharacterSize = 40;//0=left 1- middele 2:right Allignment Vertically
		int fontResulation = 40;
		int fontMAxwide=100;
		int bezierLinear = 0;
		string font;

		bool fback, fItalic, fBold;

	};

		const int ver = 9710;
	vector<DrawSettingS> drawSettingS;
	string font="arial";
	int strok;
	int* screenDim;
	double* camera;
	int backcolor;
	wstring path;
	string fontpath;
	int SeetingCode;
	int currentChildDimIndex;
	int currentParentDimIndex;
	int selectedItem = 0;
	int activedimState = 0;
	int activeDimIndex = 0;


	int exit;
	void clear();
	SettingPack();
	~SettingPack();
};

