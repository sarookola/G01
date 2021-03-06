/* -LICENSE-START-
 ** Copyright (c) 2010 Blackmagic Design
 **
 ** Permission is hereby granted, free of charge, to any person or organization
 ** obtaining a copy of the software and accompanying documentation covered by
 ** this license (the "Software") to use, reproduce, display, distribute,
 ** execute, and transmit the Software, and to prepare derivative works of the
 ** Software, and to permit third-parties to whom the Software is furnished to
 ** do so, all subject to the following:
 **
 ** The copyright notices in the Software and this entire statement, including
 ** the above license grant, this restriction and the following disclaimer,
 ** must be included in all copies of the Software, in whole or in part, and
 ** all derivative works of the Software, unless such copies or derivative
 ** works are solely in the form of machine-executable object code generated by
 ** a source language processor.
 **
 ** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 ** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 ** FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 ** SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 ** FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 ** ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 ** DEALINGS IN THE SOFTWARE.
 ** -LICENSE-END-
 */
 //
 // OpenGLOutput.cpp
 // OpenGLOutput
 //

#include "stdafx.h"
#include "controll_socket_opengl.h"
#include "AnimtkStateSetUpdateCallback.h"

int main() {
	controll_socket_opengl s;
	return 0;
}



#include <iostream>
#include <stdio.h>
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
//
//class AnimtkUpdateCallbackOld : public osg::NodeCallback
//{
//public:
//	META_Object(osgAnimation, AnimtkUpdateCallbackOld);
//
//	AnimtkUpdateCallbackOld()
//	{
//		_sampler = new osgAnimation::MatrixLinearSampler;
//		_playing = false;
//		islinear = true;
//		_lastUpdate = 0;
//	}
//	AnimtkUpdateCallbackOld(const AnimtkUpdateCallbackOld& val, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY) :
//		osg::Object(val, copyop),
//		osg::Callback(val, copyop),
//		osg::NodeCallback(val, copyop),
//		_sampler(val._sampler),
//		_startTime(val._startTime),
//		_currentTime(val._currentTime),
//		_playing(val._playing),
//		_lastUpdate(val._lastUpdate)
//	{
//	}
//
//	/** Callback method called by the NodeVisitor when visiting a node.*/
//	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
//	{
//		if (nv->getVisitorType() == osg::NodeVisitor::UPDATE_VISITOR &&
//			nv->getFrameStamp() &&
//			nv->getFrameStamp()->getFrameNumber() != _lastUpdate)
//		{
//
//			_lastUpdate = nv->getFrameStamp()->getFrameNumber();
//			_currentTime = osg::Timer::instance()->tick();
//
//			if (_playing && _sampler.get() && _sampler->getKeyframeContainer())
//			{
//				osg::MatrixTransform* transform = dynamic_cast<osg::MatrixTransform*>(node);
//				if (transform) {
//					osg::Matrixf result;
//					//osg::Vec3 result;
//					float t = osg::Timer::instance()->delta_s(_startTime, _currentTime);
//					float duration = _sampler->getEndTime() - _sampler->getStartTime();
//					t = fmod(t, duration);
//					t += _sampler->getStartTime();
//					_sampler->getValueAt(t, result);
//					//transform->setMatrix(osg::Matrix::translate(result));
//					std::cout << "resut;" << result << std::endl;
//					transform->setMatrix((result));
//				}
//			}
//		}
//		// note, callback is responsible for scenegraph traversal so
//		// they must call traverse(node,nv) to ensure that the
//		// scene graph subtree (and associated callbacks) are traversed.
//		traverse(node, nv);
//	}
//
//	void start() { _startTime = osg::Timer::instance()->tick(); _currentTime = _startTime; _playing = true; }
//	void stop() { _currentTime = _startTime; _playing = false; }
//
//	osg::ref_ptr<osgAnimation::MatrixLinearSampler> _sampler;
//	osg::Timer_t _startTime;
//	osg::Timer_t _currentTime;
//	bool _playing;
//	bool islinear;
//	unsigned int _lastUpdate;
//};
//
//osg::MatrixTransform* setupAnimtkNode(osg::Geode* staticGeode)
//{
//
//	osg::Geode* geode = new osg::Geode();
//	geode->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(0.0f, 0.0f, 0.0f), 20)));
//
//	osg::Vec3 v[5];
//
//	v[0] = osg::Vec3(0, 0, 0);
//	v[1] = osg::Vec3(20, 40, 60);
//	v[2] = osg::Vec3(40, 60, 20);
//	v[3] = osg::Vec3(60, 20, 40);
//	v[4] = osg::Vec3(0, 0, 0);
//
//	osg::MatrixTransform* node = new osg::MatrixTransform();
//	AnimtkUpdateCallbackOld* callback = new AnimtkUpdateCallbackOld();
//	//osgAnimation::Vec3CubicBezierKeyframeContainer* keys = callback->_sampler->getOrCreateKeyframeContainer();
//	osgAnimation::MatrixKeyframeContainer* keys = callback->_sampler->getOrCreateKeyframeContainer();
//
//	double x;
//	x = 1.0;
//	osg::Matrixf *f = new osg::Matrixf(1.0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
//
//	//osg::PositionAttitudeTransform
//	*f = osg::Matrixf::scale(osg::Vec3f(1, 1, 1))*osg::Matrixf::rotate(osg::Quat(.3, osg::Vec3f(1, 0, 0)))*osg::Matrixf::translate(v[0]);
//	keys->push_back(osgAnimation::MatrixKeyframe(0, *f));
//	*f = osg::Matrixf::scale(osg::Vec3f(1, 1, 1))*osg::Matrixf::rotate(osg::Quat(.9, osg::Vec3f(1, 0, 0)))*osg::Matrixf::translate(v[1]);
//	keys->push_back(osgAnimation::MatrixKeyframe(1, *f));
//
//	*f = osg::Matrixf::scale(osg::Vec3f(1, 1, 1))*osg::Matrixf::rotate(osg::Quat(0, osg::Vec3f(1, 0, 0)))*osg::Matrixf::translate(v[2]);
//	keys->push_back(osgAnimation::MatrixKeyframe(2, *f));
//
//	*f = osg::Matrixf::scale(osg::Vec3f(1, 1, 1))*osg::Matrixf::rotate(osg::Quat(1.9, osg::Vec3f(0, 0, 1)))*osg::Matrixf::translate(v[3]);
//	keys->push_back(osgAnimation::MatrixKeyframe(3, *f));
//
//	*f = osg::Matrixf::scale(osg::Vec3f(1, 1, 1))*osg::Matrixf::rotate(osg::Quat(0, osg::Vec3f(0, 0, 1)))*osg::Matrixf::translate(v[4]);
//	keys->push_back(osgAnimation::MatrixKeyframe(4, *f));
//
//	callback->start();
//	node->setUpdateCallback(callback);
//
//	/*AnimtkStateSetUpdateCallback* call2 = new AnimtkStateSetUpdateCallback();
//	osgAnimation::Vec4KeyframeContainer* keys2 = call2->_sampler->getOrCreateKeyframeContainer();
//
//	keys2->push_back(osgAnimation::Vec4Keyframe(0, osg::Vec4(1, 0, 0, 1.0)));
//	keys2->push_back(osgAnimation::Vec4Keyframe(1, osg::Vec4(.1, 0.8, 0.0, 1.0)));
//	keys2->push_back(osgAnimation::Vec4Keyframe(2, osg::Vec4(.0, 0.8, 0.9, 1.0)));
//	keys2->push_back(osgAnimation::Vec4Keyframe(3, osg::Vec4(.8, 0.9, 0.9,1.00)));
//	keys2->push_back(osgAnimation::Vec4Keyframe(4, osg::Vec4(1, 0.0, 0.0, 1.0)));
//
//	osg::StateSet* st = new osg::StateSet();
//
//	st->setAttributeAndModes(new osg::Material(), true);
//	st->setMode(GL_BLEND, true);
//	st->setUpdateCallback(call2);
//
//	call2->start();
//	geode->setStateSet(st);*/
//
//
//	node->addChild(geode);
//
//	return node;
//}
//
//int main2(int argc, char** argv)
//{
//	osg::ArgumentParser arguments(&argc, argv);
//	osgViewer::Viewer viewer(arguments);
//
//	osgGA::TrackballManipulator* tbm = new osgGA::TrackballManipulator();
//
//	viewer.setCameraManipulator(tbm);
//
//	viewer.addEventHandler(new osgViewer::StatsHandler());
//	viewer.addEventHandler(new osgViewer::WindowSizeHandler());
//
//	osg::Group* root = new osg::Group();
//	osg::Geode* geode = new osg::Geode();
//
//	//	geode->setStateSet(setupStateSet());
//
//	root->setInitialBound(osg::BoundingSphere(osg::Vec3(10, 0, 20), 100));
//	root->addChild(setupAnimtkNode(geode));
//	//root->addChild(geode);
//
//	viewer.setSceneData(root);
//
//	tbm->setDistance(150);
//
//	return viewer.run();
//}
