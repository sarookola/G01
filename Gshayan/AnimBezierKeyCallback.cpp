#include "AnimBezierKeyCallback.h"



AnimBezierKeyCallback::AnimBezierKeyCallback()
{
	_samplerPosB = new osgAnimation::Vec3CubicBezierSampler;
	_samplerRotB = new osgAnimation::Vec3CubicBezierSampler;
	_samplerScaB = new osgAnimation::Vec3CubicBezierSampler;
	_playing = false;
	_loop = false;
	_lastUpdate = 0;
}

void AnimBezierKeyCallback::oprateAttime(osg::MatrixTransform* transform,float time) {
	
		//osg::MatrixTransform* transform = dynamic_cast<osg::MatrixTransform*>(node);
		if (transform) {
			osg::Vec3f resultpos, resultRot, resultSca;
		//	float t = osg::Timer::instance()->delta_s(_startTime, _currentTime);
			float duration = _samplerPosB->getEndTime() - _samplerPosB->getStartTime();
			if (_loop) {
				time = fmod(time, duration);
				time += _samplerPosB->getStartTime();
				_samplerPosB->getValueAt(time, resultpos);
				_samplerRotB->getValueAt(time, resultRot);
				_samplerScaB->getValueAt(time, resultSca);
			}
			else {
				if (time >= duration) {
					_playing = false;
					_samplerPosB->getValueAt(_samplerPosB->getEndTime(), resultpos);
					_samplerRotB->getValueAt(_samplerPosB->getEndTime(), resultRot);
					_samplerScaB->getValueAt(_samplerPosB->getEndTime(), resultSca);
				}
				else {
					time += _samplerPosB->getStartTime();
					_samplerPosB->getValueAt(time, resultpos);
					_samplerRotB->getValueAt(time, resultRot);
					_samplerScaB->getValueAt(time, resultSca);
				}
			}
			osg::Matrixf f, mscale, mpos, mquad;
			mscale = osg::Matrixd::scale(resultSca);
			mpos = osg::Matrixd::translate(osg::Vec3d(resultpos));
			mquad = osg::Matrixd::rotate(resultRot.x(), osg::Vec3(1.0, 0.0, 0.0), resultRot.y(), osg::Vec3(0.0, 1.0, 0.0), resultRot.z(), osg::Vec3(0.0, 0.0, 1.0));
			f = mscale*mquad*mpos;
			transform->setMatrix(f);
		}
	
}

void AnimBezierKeyCallback::operator()(osg::Node * node, osg::NodeVisitor * nv)
	{
	//	cout << " rhis ia node" << node << "\t _play= "<<_playing <<endl;
		if (nv->getVisitorType() == osg::NodeVisitor::UPDATE_VISITOR &&
			nv->getFrameStamp() &&
			nv->getFrameStamp()->getFrameNumber() != _lastUpdate)
		{

			_lastUpdate = nv->getFrameStamp()->getFrameNumber();
			_currentTime = osg::Timer::instance()->tick();

			if (_playing && _samplerPosB.get() && _samplerPosB->getKeyframeContainer()
							&& _samplerRotB.get() && _samplerRotB->getKeyframeContainer()
							&& _samplerScaB.get() && _samplerScaB->getKeyframeContainer())
			{
				osg::MatrixTransform* transform = dynamic_cast<osg::MatrixTransform*>(node);
				if (transform) {
					osg::Vec3f resultpos, resultRot, resultSca;
					float t = osg::Timer::instance()->delta_s(_startTime, _currentTime);
					float duration = _samplerPosB->getEndTime() - _samplerPosB->getStartTime();
					if (_loop) {
						t = fmod(t, duration);
						t += _samplerPosB->getStartTime();
						_samplerPosB->getValueAt(t, resultpos);
						_samplerRotB->getValueAt(t, resultRot);
						_samplerScaB->getValueAt(t, resultSca);
					}
					else {
						if (t >= duration) {
							_playing = false;
							_samplerPosB->getValueAt(_samplerPosB->getEndTime(), resultpos);
							_samplerRotB->getValueAt(_samplerPosB->getEndTime(), resultRot);
							_samplerScaB->getValueAt(_samplerPosB->getEndTime(), resultSca);
						}
						else {
							t += _samplerPosB->getStartTime();
							_samplerPosB->getValueAt(t, resultpos);
							_samplerRotB->getValueAt(t, resultRot);
							_samplerScaB->getValueAt(t, resultSca);
						}
					}
					osg::Matrixf f, mscale,mpos,mquad;
					mscale = osg::Matrixd::scale(resultSca);
					mpos = osg::Matrixd::translate(osg::Vec3d(resultpos));
					mquad = osg::Matrixd::rotate(resultRot.x(), osg::Vec3(1.0, 0.0, 0.0), resultRot.y(), osg::Vec3(0.0, 1.0, 0.0), resultRot.z(), osg::Vec3(0.0, 0.0, 1.0));
					f = mscale*mquad*mpos;
					transform->setMatrix(f);
				}
			}
		}
		// note, callback is responsible for scenegraph traversal so
		// they must call traverse(node,nv) to ensure that the
		// scene graph subtree (and associated callbacks) are traversed.
		traverse(node, nv);
	}


AnimBezierKeyCallback::~AnimBezierKeyCallback()
{
}
