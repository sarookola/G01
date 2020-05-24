#pragma once

#include "AnimCallback.h"

using namespace std;

class AnimMatrixKeyCallback :
	public AnimCallback
{
public:
	//META_Object(osgAnimation, AnimtkUpdateCallback);

	AnimMatrixKeyCallback();

	AnimMatrixKeyCallback(const AnimMatrixKeyCallback& val, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY) :
	//	osg::Object(val, copyop),
	//	osg::Callback(val, copyop),
	//	osg::NodeCallback(val, copyop),
		_sampler(val._sampler)
	//	_startTime(val._startTime),
	//	_currentTime(val._currentTime),
	//	_playing(val._playing),
	//	_lastUpdate(val._lastUpdate)
	{
	}

	/** Callback method called by the NodeVisitor when visiting a node.*/
	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);


	//void start() { _startTime = osg::Timer::instance()->tick(); _currentTime = _startTime; _playing = true; }
	//void stop() { _currentTime = _startTime; _playing = false; }

	 osg::ref_ptr<osgAnimation::MatrixLinearSampler> _sampler;

	//osg::ref_ptr<osgAnimation::Vec3CubicBezierSampler> _samplerPos;
	//osg::ref_ptr<osgAnimation::Vec3CubicBezierSampler> _samplerRot;
	//osg::ref_ptr<osgAnimation::Vec3CubicBezierSampler> _samplerSca;


	//osg::Timer_t _startTime;
	//osg::Timer_t _currentTime;
	//bool _playing, _loop = true;;
	//unsigned int _lastUpdate;

	~AnimMatrixKeyCallback();
};

