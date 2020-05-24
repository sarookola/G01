#pragma once

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer/View>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
#include <osgViewer/Renderer>


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
#include <osg/Drawable>
#include <osg/MatrixTransform>
#include <osgAnimation/BasicAnimationManager>
#include <osgAnimation/UpdateMatrixTransform>
#include <osgAnimation/StackedRotateAxisElement>
#include <algorithm>


#include <osg/Node>
#include <osg/PositionAttitudeTransform>
#include <osg/ref_ptr>
#include <stdio.h>
#include<iostream>
#include <tchar.h>
#include <conio.h>
#include <objbase.h>		// Necessary for COM
#include <comutil.h>
#include <iostream>
#include <stdio.h>
#include "shNodePic.h"
#include"sockets\SettingPack.h"
#include"ControolPack.h"
#include "EaseMotionSampler.h"
#include "AnimMatrixKeyCallback.h"
#include "AnimBezierKeyCallback.h"
#include "AnimLinearKeyCallback.h"
#include "ImagesequenceEvent.h"
#include"convertutf8.h"

#define _USE_MATH_DEFINES // for C
#include <math.h>

class Osgtest01
{
public:
	Osgtest01();
	~Osgtest01();

	//const unsigned int WINDOW_WIDTH = 800;
	//const unsigned int WINDOW_HEIGHT = 600;
	const unsigned int MASK_2D = 0xF0000000;
	const unsigned int MASK_3D = 0x0F000000;
	const float        M_START = 0.0f;
	const float        M_DURATION = 2.0f;
	const float        M_CHANGE = 1.0f;

	const int multidampleForAntialising = 4;

	EaseMotionSampler* EASE_MOTION_SAMPLER = 0;
	//osg::Geode*        EASE_MOTION_GEODE = 0;
	//osg::Geode*			geode;
	//osg::Geode* ge;

	int viewWidth = 800, viewHeight = 450;

	int ti;
	int lightnum = 0;
	osg::Group* lightGroup;
	/*int x = 100;
	osg::PositionAttitudeTransform* trans;
	osg::ref_ptr<osg::PositionAttitudeTransform> hexXform, hexXform3, hexXform4, hexXform5;
	osg::MatrixTransform *trans5;*/
	osgViewer::Viewer *_viewer;

	osg::Vec4 backcolor = osg::Vec4(0.250, 0.00, 0.000, 00.0);
	//osg::Geometry * myCreateTexturedQuadGeometry(const osg::Vec3& pos, float width, float height, osg::Image* image, bool useTextureRectangle, bool xyPlane, bool option_flip);
	int getti();
	//Function run
	//    void run() override;
	void building();
	void view(int X, osg::Vec3d pos);
	void runframe(int X, int Y, int W, int H);
	osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> _mGraphicsWindow;

public: 		osg::Image*  image2;

	//void settrans5(float f1, float f2, float f3);
	//osg::MatrixTransform *getTrans5() const;
	//void setTrans5(osg::MatrixTransform *value);
	//void sethexXform5pos(int X, int Y, int z );
	//osg::MatrixTransform *mtLeft ,*mtr;
	//AnimtkStateSetUpdateCallback* animtkStateS;
	//osg::StateSet *st2;
	//shNodePic sh;
	//osg::StateSet* setupStateSet();

			
	osgViewer::Viewer *getViewer() const;
	void setViewer(osgViewer::Viewer *viewer);

	void Osgtest01::runframe2();
	void Osgtest01::runframe3(BYTE* pbDestData3);

	void updatesettingpack(SettingPack settingp);
	void checkvisafterrsetting();
	void updateControolgpack(ControolPack controolp);
	vector<shNodePic> nodePicVectorB;
	bool  visit( int index, vector<int>* vec);
	vector<int> maketree();


	osg::ref_ptr<osg::Group> root = new osg::Group;

	void CaptureScreen();
	
	
};

