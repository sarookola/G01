#include "ImagesequenceEvent.h"



bool ImagesequenceEvent::handle(const osgGA::GUIEventAdapter & ea, osgGA::GUIActionAdapter & aa, osg::Object *, osg::NodeVisitor * nv)
{
	switch (ea.getEventType())
	{
	case(osgGA::GUIEventAdapter::FRAME):
	{
		double t = ea.getTime();
		/*	bool printed(false);

			ImageStreamPlayBackSpeedList::iterator fps_itr = _imageStreamPlayBackSpeedList.begin();
			for (ImageStreamList::iterator itr = _imageStreamList.begin();
				itr != _imageStreamList.end();
				++itr, ++fps_itr)
			{
				if (((*itr)->getStatus() == osg::ImageStream::PLAYING) && ((*itr)->data() != (*fps_itr).lastData))
				{
					ImageStreamPlaybackSpeedData& data(*fps_itr);
					double dt = (data.timeStamp > 0) ? t - data.timeStamp : 1 / 60.0;
					data.lastData = (*itr)->data();
					data.fps = (*fps_itr).fps * 0.8 + 0.2 * (1 / dt);
					data.timeStamp = t;

					if (t - data.lastOutput > 1)
					{
						std::cout << data.fps << " ";
						data.lastOutput = t;
						printed = true;
					}

				}
			}
			if (printed)*/
			//	std::cout << " this is printed t="<<  t << std::endl;
		if (sh.isImagesequentially) {
			osg::StateAttribute* attr = sh.pictureQuad->getStateSet()->getTextureAttribute(0, osg::StateAttribute::TEXTURE);
			if (attr)
			{
				osg::Texture2D* texture2D = dynamic_cast<osg::Texture2D*>(attr);
				//	if (texture2D) apply(dynamic_cast<osg::ImageStream*>(texture2D->getImage()));

				osg::TextureRectangle* textureRec = dynamic_cast<osg::TextureRectangle*>(attr);
				//	if (textureRec) apply(dynamic_cast<osg::ImageStream*>(textureRec->getImage()));
				textureRec->setImage(sh.imageSequence->getImage(2));
			//	int k = sh.imageSequence->getLength();
			//	n = (n + 1) %  k ;
			}
		}
	}
	break;
	

	default:
		return false;
	}

	return false;
}

ImagesequenceEvent::ImagesequenceEvent()
{

}


ImagesequenceEvent::~ImagesequenceEvent()
{
}

void ImagesequenceEvent::set(shNodePic sh1)
{
	sh = sh1;
	cout << "set sh= " << sh.textst << endl;
	n = 0;
//	_imageStreamList.clear();
//	sh.pictureQuad->accept()
//	_imageStreamPlayBackSpeedList.resize(_imageStreamList.size());
}
