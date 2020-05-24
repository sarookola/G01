#pragma once

//#include <iostream>
//#include <osg/io_utils>
//#include <osg/Geometry>
//#include <osg/Shape>
//#include <osg/ShapeDrawable>
//#include <osg/Material>
//#include <osg/MatrixTransform>
//#include <osgViewer/Viewer>
//#include <osgViewer/ViewerEventHandlers>
//#include <osgGA/TrackballManipulator>
//#include <osgAnimation/Sampler>
//
//using namespace std;
#include "AnimCallback.h"
class AnimLinearKeyCallback :
	public AnimCallback
	//public osg::NodeCallback
{
public:
	//META_Object(osgAnimation, AnimtkUpdateCallback);

	AnimLinearKeyCallback();
	int t = 356;
	//AnimLinearKeyCallback(const AnimLinearKeyCallback& val, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY) :
	//	osg::Object(val, copyop),
	//	osg::Callback(val, copyop),
	//	osg::NodeCallback(val, copyop),
	//	_samplerPos(val._samplerPos),
	//	_samplerRot(val._samplerRot),
	//	_samplerSca(val._samplerSca),
	//	_startTime(val._startTime),
	//	_currentTime(val._currentTime),
	//	_playing(val._playing),
	//	_lastUpdate(val._lastUpdate)
	//{
	//}

	//AnimLinearKeyCallback(const AnimLinearKeyCallback& val, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY) :

	//	_samplerPos(val._samplerPos),
	//	_samplerRot(val._samplerRot),
	//	_samplerSca(val._samplerSca)
	//{
	//}

	/** Callback method called by the NodeVisitor when visiting a node.*/
	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);
	void operateAttime(osg::MatrixTransform* transform, float time);

	/*void start() { _startTime = osg::Timer::instance()->tick(); _currentTime = _startTime; _playing = true; }
	void stop() { _currentTime = _startTime; _playing = false; }*/

	//osg::ref_ptr<osgAnimation::Vec3LinearSampler> _samplerPos;
	//osg::ref_ptr<osgAnimation::Vec3LinearSampler> _samplerRot;
	//osg::ref_ptr<osgAnimation::Vec3LinearSampler> _samplerSca;
	//osg::Timer_t _startTime;
	//osg::Timer_t _currentTime;
	//bool _playing, _loop = true;;
	//unsigned int _lastUpdate;

	~AnimLinearKeyCallback();
};

