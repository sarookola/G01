#include "AnimMatrixKeyCallback.h"



AnimMatrixKeyCallback::AnimMatrixKeyCallback()
{
	_sampler = new osgAnimation::MatrixLinearSampler;
	_playing = false;
	_lastUpdate = 0;
}


void AnimMatrixKeyCallback::operator()(osg::Node * node, osg::NodeVisitor * nv)
{
	{
		if (nv->getVisitorType() == osg::NodeVisitor::UPDATE_VISITOR &&
			nv->getFrameStamp() &&
			nv->getFrameStamp()->getFrameNumber() != _lastUpdate)
		{

			_lastUpdate = nv->getFrameStamp()->getFrameNumber();
			_currentTime = osg::Timer::instance()->tick();

			if (_playing && _sampler.get() && _sampler->getKeyframeContainer())
			{
				osg::MatrixTransform* transform = dynamic_cast<osg::MatrixTransform*>(node);
				if (transform) {
					osg::Matrixf result;
					float t = osg::Timer::instance()->delta_s(_startTime, _currentTime);
					float duration = _sampler->getEndTime() - _sampler->getStartTime();
					if (_loop) {
						t = fmod(t, duration);
						t += _sampler->getStartTime();
						_sampler->getValueAt(t, result);
					}
					else {
						if (t >= duration) {
							_playing = false;
							_sampler->getValueAt(_sampler->getEndTime(), result);
						}
						else {
							t += _sampler->getStartTime();
							_sampler->getValueAt(t, result);
						}
					}
					transform->setMatrix((result));
				}
			}
		}
		// note, callback is responsible for scenegraph traversal so
		// they must call traverse(node,nv) to ensure that the
		// scene graph subtree (and associated callbacks) are traversed.
		traverse(node, nv);
	}
}

AnimMatrixKeyCallback::~AnimMatrixKeyCallback()
{
}
