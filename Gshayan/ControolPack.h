#pragma once
#include <vector>
#include "sockets\SettingPack.h"
#include <stdio.h>


using namespace std;


class ControolPack
{
public:

	struct Vis_Anim_Bool {
		int id;
		bool vis,visactive;
		bool objectanim;
		int motionDimIndex;
		bool colorAnim;
		bool imagePlay;

	};
	struct DataPackString {
		int id;
		string st;
	};
	struct DataPackanimationStartEnd {
		int id;
		bool startEndEnable, sequenceNotMovie;
		int start, end;
		int animRate;
		bool play, live, playEn, liveEn;
	};
	struct DataPackDims {
		int id,dim1,dim2;
		vector<vector<SettingPack::drawSettingDims >> DimsList;

	};

	vector<Vis_Anim_Bool> vis_Anim_Bool;
	vector<DataPackString> datapackString, datapackImage, dataPacMovie, dataPackffmpegmovie;
	vector<DataPackanimationStartEnd> dataPackanimationStartEnds;
	vector<DataPackDims> dataPackDims;
//	vector<SettingPack::DrawSettingS> drawsettingOne;
	void clear();

	ControolPack();
	~ControolPack();
};

