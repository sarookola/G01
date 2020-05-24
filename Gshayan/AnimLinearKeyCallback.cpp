#include "AnimLinearKeyCallback.h"



AnimLinearKeyCallback::AnimLinearKeyCallback() 
{
	_samplerPos = new osgAnimation::Vec3LinearSampler;
	_samplerRot = new osgAnimation::Vec3LinearSampler;
	_samplerSca = new osgAnimation::Vec3LinearSampler;
	_playing = false;
	_loop = false;
	_lastUpdate = 0;
}


void AnimLinearKeyCallback::operator()(osg::Node * node, osg::NodeVisitor * nv)
{
	//cout << " AnimLinearKeyCallback" << nv->getFrameStamp()->getFrameNumber() << "\t time=" << osg::Timer::instance()->tick() << "     starttime="<<_startTime<< endl;
	{
		if (nv->getVisitorType() == osg::NodeVisitor::UPDATE_VISITOR &&
			nv->getFrameStamp() &&
			nv->getFrameStamp()->getFrameNumber() != _lastUpdate)
		{
			//cout << " AnimLinearKeyCallback 1       _playing=" << _playing <<  "   _samplerPos.get()" << _samplerPos.get()<<"    _samplerPos->getKeyframeContainer()"<< _samplerPos->getKeyframeContainer()<< endl;
			_lastUpdate = nv->getFrameStamp()->getFrameNumber();
			_currentTime = osg::Timer::instance()->tick();

			if (_playing && _samplerPos.get() && _samplerPos->getKeyframeContainer()
							&& _samplerRot.get() && _samplerRot->getKeyframeContainer()
							&& _samplerSca.get() && _samplerSca->getKeyframeContainer())
			{
				//cout << " AnimLinearKeyCallback        " << 2 << endl;
				osg::MatrixTransform* transform = dynamic_cast<osg::MatrixTransform*>(node);
				if (transform) {
					
					osg::Vec3f resultpos, resultRot, resultSca;
					float t = osg::Timer::instance()->delta_s(_startTime, _currentTime);
					float duration = _samplerPos->getEndTime() - _samplerPos->getStartTime();
				//	cout << " AnimLinearKeyCallback       t= " << t<<   "            Duration="<<duration << endl;
					if (_loop) {
						t = fmod(t, duration);
						t += _samplerPos->getStartTime();
						_samplerPos->getValueAt(t, resultpos);
						_samplerRot->getValueAt(t, resultRot);
						_samplerSca->getValueAt(t, resultSca);
					}
					else {
						if (t >= duration) {
							_playing = false;
							_samplerPos->getValueAt(_samplerPos->getEndTime(), resultpos);
							_samplerRot->getValueAt(_samplerPos->getEndTime(), resultRot);
							_samplerSca->getValueAt(_samplerPos->getEndTime(), resultSca);
						}
						else {
							t += _samplerPos->getStartTime();
							_samplerPos->getValueAt(t, resultpos);
							_samplerRot->getValueAt(t, resultRot);
							_samplerSca->getValueAt(t, resultSca);
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
}

void AnimLinearKeyCallback::operateAttime(osg::MatrixTransform * transform, float t)
{
	if (transform) {
		osg::Vec3f resultpos, resultRot, resultSca;
	//	float t = osg::Timer::instance()->delta_s(_startTime, _currentTime);
		float duration = _samplerPos->getEndTime() - _samplerPos->getStartTime();
		if (_loop) {
			t = fmod(t, duration);
			t += _samplerPos->getStartTime();
			_samplerPos->getValueAt(t, resultpos);
			_samplerRot->getValueAt(t, resultRot);
			_samplerSca->getValueAt(t, resultSca);
		}
		else {
			if (t >= duration) {
				_playing = false;
				_samplerPos->getValueAt(_samplerPos->getEndTime(), resultpos);
				_samplerRot->getValueAt(_samplerPos->getEndTime(), resultRot);
				_samplerSca->getValueAt(_samplerPos->getEndTime(), resultSca);
			}
			else {
				t += _samplerPos->getStartTime();
				_samplerPos->getValueAt(t, resultpos);
				_samplerRot->getValueAt(t, resultRot);
				_samplerSca->getValueAt(t, resultSca);
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

AnimLinearKeyCallback::~AnimLinearKeyCallback()
{
}
