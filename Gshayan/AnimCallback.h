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

using namespace std;

class AnimCallback :
	public osg::NodeCallback
{
public:
	//META_Object(osgAnimation, AnimtkUpdateCallback);

	AnimCallback();

	AnimCallback(const AnimCallback& val, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY) :
		osg::Object(val, copyop),
		osg::Callback(val, copyop),
		osg::NodeCallback(val, copyop),
	//	_sampler(val._sampler),
		_startTime(val._startTime),
		_currentTime(val._currentTime),
		_playing(val._playing),
		_lastUpdate(val._lastUpdate),
		_samplerPos(val._samplerPos),
		_samplerRot(val._samplerRot),
		_samplerSca(val._samplerSca),
		_samplerPosB(val._samplerPosB),
		_samplerRotB(val._samplerRotB),
		_samplerScaB(val._samplerScaB)

	{}

	//osg::ref_ptr<osganimation::sampler> _samplerpos;
	//osg::ref_ptr<osganimation::sampler> _samplerrot;
	//osg::ref_ptr<osganimation::sampler> _samplersca;


	//osg::ref_ptr<osgAnimation::MatrixLinearSampler> _sampler;

	osg::ref_ptr<osgAnimation::Vec3LinearSampler> _samplerPos;
	osg::ref_ptr<osgAnimation::Vec3LinearSampler> _samplerRot;
	osg::ref_ptr<osgAnimation::Vec3LinearSampler> _samplerSca;

	osg::ref_ptr<osgAnimation::Vec3CubicBezierSampler> _samplerPosB;
	osg::ref_ptr<osgAnimation::Vec3CubicBezierSampler> _samplerRotB;
	osg::ref_ptr<osgAnimation::Vec3CubicBezierSampler> _samplerScaB;


	osg::Timer_t _startTime;
	osg::Timer_t _currentTime;
	bool _playing, _loop = true;;
	unsigned int _lastUpdate;

	/** Callback method called by the NodeVisitor when visiting a node.*/
	//virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);
//virtual	void oprateAttime(float time);

	void start()
	{
		_startTime = osg::Timer::instance()->tick();
		_currentTime = _startTime;
		_playing = true; 
	//	cout << "startaat :" << _startTime << endl;
	}
	void stop() { 
		//_currentTime = _startTime;
		_playing = false; }
	enum Motion_Linear_Bezier_
	{
		Linear, Bezier, Beziercubic

	} motion_Linear_Bezier_;

	~AnimCallback();
};

