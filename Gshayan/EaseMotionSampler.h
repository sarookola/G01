#pragma once
#include <osg/Geode>
#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>
#include <osgGA/TrackballManipulator>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgAnimation/EaseMotion>
#include <osgWidget/WindowManager>
#include <osgWidget/Box>
#include <osgWidget/Table>
#include <osgWidget/Label>

#include <osg/Material>
#include <iostream>

class EaseMotionSampler : public osg::NodeCallback {
public:
	~EaseMotionSampler();
	//EaseMotionSampler() : _angle(0.) {}


	float     _previous;
	osg::Vec3 _pos;
	osg::Matrix _start, _end;

	osg::ref_ptr<osgAnimation::Motion> _motion;

	EaseMotionSampler(const osg::Vec3& pos) :_previous(0.0f), _pos(pos) {}
	EaseMotionSampler(osg::Matrix start, const osg::Vec3& pos);
	EaseMotionSampler(osg::Matrix start, osg::Matrix end) :_start(start), _end(end) {}
	void operator()(osg::Node* node, osg::NodeVisitor* nv);

	template<typename T>void setMotion();


protected:
	double _angle;
	float        _DURATION = 2.0f;


};

