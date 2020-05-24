#include "stateSetCallback_ImageSequence.h"



void stateSetCallback_ImageSequence::operator()(osg::StateSet * state, osg::NodeVisitor * nv)
{
	if (_playing && state &&
		nv->getVisitorType() == osg::NodeVisitor::UPDATE_VISITOR &&
		nv->getFrameStamp() &&
		nv->getFrameStamp()->getFrameNumber() != _lastUpdate)
	{

		_lastUpdate = nv->getFrameStamp()->getFrameNumber();
		_currentTime = osg::Timer::instance()->time_m();

		if (_playing)
		{
			int currentf =(int) (_currentTime - _startTime)*frameRate / 1000;
			//cout << "currentf=" << currentf;
			//	if(currentf<0)
			currentf = startFrame + currentf;
			//cout << "      currentf2=" << currentf;
			if (frameRate<0 )
			{

				if (_loop) currentf = animLength - 1 - fmod((-currentf), animLength);
				else if( currentf<= endframe){
					currentf = endframe;
				_playing = false;
				}
			}
			else {
				if (_loop) currentf = startFrame+ fmod((currentf), endframe-startFrame);
				else if (currentf >=endframe) {
					currentf = endframe;
					_playing = false;

				}
			}
			//	cout << "980506  here c urentframe=" << currentframe << "\t currentf=" << currentf <<"\t endframe="<<endframe<< "\t frameRate=" << frameRate << endl;

			if (currentf != currentframe)
			{
				currentframe = currentf;
				osg::StateAttribute* attr = state->getTextureAttribute(0, osg::StateAttribute::TEXTURE);
				if (attr)

				{
					if (useTextureRectangle)
					{
						osg::TextureRectangle* texture = dynamic_cast<osg::TextureRectangle*>(attr);
						//cout << "980506  here c urentframe=" << currentframe << "\t currentf=" << currentf << "\t frameRate=" << frameRate << endl;


						texture->setImage(imageSequence->getImage(currentframe));

						state->setTextureAttribute(0, texture, osg::StateAttribute::OVERRIDE);

					}
					else
					{
						osg::Texture2D* texture = dynamic_cast<osg::Texture2D*>(attr);
						texture->setImage(imageSequence->getImage(currentframe));

						state->setTextureAttribute(0, texture, osg::StateAttribute::OVERRIDE);
					}

				}
			}

				}


	}
}

void stateSetCallback_ImageSequence::start()
{
	_startTime = osg::Timer::instance()->time_m();
	_currentTime = _startTime;
	startFrame = 0;
	currentframe = 0;
	_playing = true;
}

void stateSetCallback_ImageSequence::stop()
{
	_currentTime = _startTime;
	_playing = false;
}

stateSetCallback_ImageSequence::stateSetCallback_ImageSequence(osg::ImageSequence*  imageSequence1)
{
	imageSequence = imageSequence1;
	currentframe = 0;
	frameRate = 25;
	_playing = false;

}


stateSetCallback_ImageSequence::~stateSetCallback_ImageSequence()
{
}
