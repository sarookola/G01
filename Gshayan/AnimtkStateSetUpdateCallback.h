#pragma once
#include <iostream>
#include <osg/io_utils>
#include <osg/Geometry>
#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osg/Material>
#include <osg/MatrixTransform>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>
#include <osgAnimation/Sampler>
#include <osgAnimation/EaseMotion>

using namespace std;


class AnimtkStateSetUpdateCallback :
	public osg::StateSet::Callback
{
public:
	//typename T
	osg::ref_ptr<osgAnimation::Vec4LinearSampler> _sampler;
	//template <typename T> t ;
	//osg::ref_ptr<osgAnimation::Sampler> _sampler;
	osg::Timer_t _startTime;
	osg::Timer_t _currentTime;
	bool _playing, _loop;
	unsigned int _lastUpdate;
	osgText::Text* _text;
	bool istext;
	//template<typename T>void setMotion();
/*

	META_Object(osgAnimation, AnimtkStateSetUpdateCallback);

	AnimtkStateSetUpdateCallback();

	AnimtkStateSetUpdateCallback(const AnimtkStateSetUpdateCallback& val, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
	*/	
	// Callback method called by the NodeVisitor when visiting a node.
	virtual void operator()(osg::StateSet* state, osg::NodeVisitor* nv);

	void start();// { _startTime = osg::Timer::instance()->tick(); _currentTime = _startTime; _playing = true; }
	void stop();// { _currentTime = _startTime; _playing = false; }

	AnimtkStateSetUpdateCallback(osgText::Text* text);
	AnimtkStateSetUpdateCallback(const AnimtkStateSetUpdateCallback & val, const osg::CopyOp & copyop);
	~AnimtkStateSetUpdateCallback();
};

