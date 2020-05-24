#pragma once
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer/View>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
#include <osgViewer/Renderer>
#include <osgDB/Registry>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
#include <osgDB/FileNameUtils>
#include <osgDB/FileUtils>

#include <osg/ImageSequence>


#include <osg/Geode>
#include <osg/Geometry>
#include <osg/StateSet>
#include <osg/Material>
#include <osg/Texture2D>
#include <osg/TextureRectangle>
#include <osg/TextureCubeMap>
#include <osg/TexMat>
#include <osg/CullFace>
#include <osg/ImageStream>
#include <osg/io_utils>


#include <osgGA/TrackballManipulator>
#include <osgGA/StateSetManipulator>
#include <osgGA/EventVisitor>
#include <iostream>
#include <osg/MatrixTransform>


#include <sys/timeb.h>

#include <osg/ShapeDrawable>
#include <osg/MatrixTransform>
#include <osgAnimation/BasicAnimationManager>
#include <osgAnimation/UpdateMatrixTransform>
#include <osgAnimation/StackedRotateAxisElement>
#include <algorithm>


#include <osg/Node>
#include <osg/PositionAttitudeTransform>
#include <osg/ref_ptr>

#include <osgText/Font>
#include <osgText/Text>
#include <osgText/String>


#include<iostream>
#include <tchar.h>
#include <conio.h>
#include <comutil.h>
#include <iostream>
#include <stdio.h>
#include"sockets\SettingPack.h"
#include "AnimMatrixKeyCallback.h"
#include "AnimBezierKeyCallback.h"
#include "AnimLinearKeyCallback.h"
#include "AnimtkStateSetUpdateCallback.h"
#include "stateSetCallback_ImageSequence.h"
#include "convertutf8.h"

class shNodePic
{
public:
	int id = -1, idRoot = -1;
	int parent = -1, parentRoot = -1;
	int ito;
	bool vis,
	 
		isImagesequentially=false ,
	 isnew = true;
	int direction = 0;// left to right , right to left
	float frame_duration = .04;
	//osg::Vec4 backcolor = osg::Vec4(0.0, 0.0, 0.0, 0.0);

	osgText::String textst;
	//string textst;

	//osgViewer::Viewer *_viewer;

	osg::Geometry* pictureQuad;
	osg::Geode*	geode;

	osgText::Text* text;

	//    MainControll mmaincontroller;

	osg::ref_ptr<osg::Image> image ;
	osg::ref_ptr<osg::ImageSequence> imageSequence;
	osgDB::DirectoryContents getSuitableFiles(string arguments);
	void readSettingpackImageOrSeq(SettingPack settingp,int draw);
	void readSettingPackText(SettingPack settingp, int draw);
	bool readSettingPackObj(SettingPack settingp, int draw);
	bool readLight(SettingPack settingp, int draw, int lightnum);

//	vector <AnimCallback*> animcallbacks;
	AnimCallback* animcallback =NULL;
	bool animloop;
	//AnimCallback* LinearKeyCallback;
	enum Motion_Linear_Bezier_
	{
		Linear, Bezier, Beziercubic

	} motion_Linear_Bezier_;

	vector<vector<SettingPack::drawSettingDims>> drawingDims;
	//vector<SettingPack::drawSettingDims> drawingColor;


	bool MotionCallBackCerate(vector<SettingPack::drawSettingDims> dims);
	void Motionsave(SettingPack settingp, int draw);

	//vector<AnimtkStateSetUpdateCallback*> statecallbacks;
	AnimtkStateSetUpdateCallback* statecallback = NULL;
//	void stateCallback(SettingPack settingp, int draw);
	bool stateCallbackCerate(vector<SettingPack::drawSettingDims> dims);

	stateSetCallback_ImageSequence* imageSeqCallBack;
	void stateCallback_ImageSequence(SettingPack settingp, int draw);
	void setVisible(bool vis);
	void imagePlay(bool play);
	void objectanim(bool play, int dim);
	void objectColor(bool play, int dim);

	bool geodevis;


	bool preLoad=true;


	bool fullscreen = false;
	//            !arguments.read("--interactive");
	bool option_flip = false;
	//            arguments.read("--flip");
	bool useTextureRectangle = true;

	bool xyPlane = true;
	bool imageaspectuse = false;


	osg::MatrixTransform *trans; // osg::PositionAttitudeTransform *trans;	//osg::Transform *trans;//
	osg::Geometry * myCreateTexturedQuadGeometry( int alignment );



	osg::ref_ptr<osgText::Font> font;
	osg::Vec4 textColor = osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f);;// (0.0f, 1.0f, 0.0f, 1.0f);
	float alignmentCharacterSize = 25.0f;

	osg::Geode *myCreateTextGeode();
	template<class T>
	void crateMotion(SettingPack settingp, int draw, T keypos,T keyrot, T keysca);


	osgText::TextBase::AlignmentType alignmnet;
	int  fontResulation, charSize,textmaxwide;
	bool fback, fItalic, fBold;


	shNodePic();

	~shNodePic();
//	wchar_t * UTF8toUnicode_(const string & s);
};

