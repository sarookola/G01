#pragma once
#include <iostream>
//#include "shNodePic.h"
//#include <osg/io_utils>
//#include <osg/Geometry>
//#include <osg/Shape>
//#include <osg/ShapeDrawable>
//#include <osg/Material>
//#include <osg/MatrixTransform>
//#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
//#include <osgGA/TrackballManipulator>
//#include <osgAnimation/Sampler>
//#include <osgAnimation/EaseMotion>
#include <osg/ImageSequence>
#include <osg/Texture2D>
#include <osg/TextureRectangle>

using namespace std;

class stateSetCallback_ImageSequence :
	public osg::StateSet::Callback
{
public:
	osg::ImageSequence*  imageSequence;
	unsigned int currentframe,startFrame,endframe;
	int frameRate, animLength;
	bool useTextureRectangle;


	//osg::ref_ptr<osgAnimation::Vec4LinearSampler> _sampler;
	osg::Timer_t _startTime;
	osg::Timer_t _currentTime;
	bool _playing, _loop;
	unsigned int _lastUpdate ;


	virtual void operator()(osg::StateSet* state, osg::NodeVisitor* nv);

	void start();// { _startTime = osg::Timer::instance()->tick(); _currentTime = _startTime; _playing = true; }
	void stop();// { _currentTime = _startTime; _playing = false; }
	stateSetCallback_ImageSequence(osg::ImageSequence*  imageSequence1);
	//stateSetCallback_ImageSequence();
	~stateSetCallback_ImageSequence();
};

