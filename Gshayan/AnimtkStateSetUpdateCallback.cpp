#include "AnimtkStateSetUpdateCallback.h"



AnimtkStateSetUpdateCallback::AnimtkStateSetUpdateCallback(osgText::Text* text)
{
	_sampler = new osgAnimation::Vec4LinearSampler;
	_loop = true;
	_lastUpdate = 0;
	_playing = false;
	_text = text;
	istext = false;
}

AnimtkStateSetUpdateCallback::AnimtkStateSetUpdateCallback(const AnimtkStateSetUpdateCallback& val, const osg::CopyOp& copyop) :
	osg::Object(val, copyop),
	osg::Callback(val, copyop),
	osg::StateSet::Callback(val, copyop),
	_sampler(val._sampler),
	_startTime(val._startTime),
	_currentTime(val._currentTime),
	_playing(val._playing),
	_lastUpdate(val._lastUpdate)
{

}

void AnimtkStateSetUpdateCallback::operator()(osg::StateSet* state, osg::NodeVisitor* nv)
{
	if (_playing && state &&
		nv->getVisitorType() == osg::NodeVisitor::UPDATE_VISITOR &&
		nv->getFrameStamp() &&
		nv->getFrameStamp()->getFrameNumber() != _lastUpdate) {

		_lastUpdate = nv->getFrameStamp()->getFrameNumber();
		_currentTime = osg::Timer::instance()->tick();

		if (_sampler.get() && _sampler->getKeyframeContainer())
		{
			osg::Material* material = dynamic_cast<osg::Material*>(state->getAttribute(osg::StateAttribute::MATERIAL));
			if (material)
			{
				osg::Vec4 result;
				float t = osg::Timer::instance()->delta_s(_startTime, _currentTime);
				float duration = _sampler->getEndTime() - _sampler->getStartTime();
				if (t >= duration && !_loop) {
					_playing = false;
					_sampler->getValueAt(_sampler->getEndTime(), result);
				}else {
					t = fmod(t, duration);
					t += _sampler->getStartTime();
					_sampler->getValueAt(t, result);
				}
				
				if (istext) { _text->setColor(result); }
				else {
					material->setDiffuse(osg::Material::FRONT_AND_BACK, result);
					material->setAmbient(osg::Material::FRONT_AND_BACK, result);
					material->setSpecular(osg::Material::FRONT_AND_BACK, result);
				material->setTransparency(osg::Material::FRONT_AND_BACK, result.w());
				material->setAlpha(osg::Material::FRONT_AND_BACK, result.w());}
			}
		}
	}

	
}
/*
void AnimtkStateSetUpdateCallback::operator()(osg::StateSet* state, osg::NodeVisitor* nv)
{

	_lastUpdate = nv->getFrameStamp()->getFrameNumber();

	_currentTime = osg::Timer::instance()->tick();


			osg::Material* material = dynamic_cast<osg::Material*>(state->getAttribute(osg::StateAttribute::MATERIAL));
		//	if (material)
			{	std::cout << " here is AnimtkStateSetUpdateCallback and  nv->getFrameStamp()->getFrameNumber()=" << (fmod(_currentTime, 5000000)) / 5000000 << std::endl;
				osg::Vec4 result;
				//float t = osg::Timer::instance()->delta_s(_startTime, _currentTime);
				//float duration = _sampler->getEndTime() - _sampler->getStartTime();
				//t = fmod(t, duration);
				//t += _sampler->getStartTime();
				////	_sampler->getValueAt(t, result);
				material->setDiffuse(osg::Material::FRONT, osg::Vec4((fmod(_currentTime,5000000))/5000000,  0.1, 0.715, 1));
			//	osg::StateSet *s = new osg::StateSet;
			//	s->setAttribute(material);
				//geode->setStateSet(state);
				osg::Material* material2= dynamic_cast<osg::Material*>(	geode->getStateSet()->getAttribute(osg::StateAttribute::MATERIAL));
				osg::Vec4 x = material2->getDiffuse(osg::Material::FRONT);
				std::cout << " here is AnimtkStateSetUpdateCallback and  nv->getFrameStamp()->getFrameNumber()=:" <<  x.x()<< std::endl;;


	}

}
*/
void AnimtkStateSetUpdateCallback::start() { _startTime = osg::Timer::instance()->tick(); _currentTime = _startTime; _playing = true; }
void AnimtkStateSetUpdateCallback::stop() { _currentTime = _startTime; _playing = false; }





AnimtkStateSetUpdateCallback::~AnimtkStateSetUpdateCallback()
{
}
