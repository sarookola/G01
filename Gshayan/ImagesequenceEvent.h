#pragma once
#include <osgViewer/ViewerEventHandlers>
#include <osg/ImageSequence>
#include<iostream>
#include "shNodePic.h"

using namespace std;

class ImagesequenceEvent :
	public osgGA::GUIEventHandler
{
public:
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa, osg::Object*, osg::NodeVisitor* nv);
	shNodePic sh;
	typedef std::vector< osg::observer_ptr<osg::ImageStream> > ImageStreamList;
	struct ImageStreamPlaybackSpeedData {
		double fps;
		unsigned char* lastData;
		double timeStamp, lastOutput;
	

		ImageStreamPlaybackSpeedData() : fps(0), lastData(NULL), timeStamp(0), lastOutput(0) {}

	};

	typedef std::vector< ImageStreamPlaybackSpeedData > ImageStreamPlayBackSpeedList;
		ImagesequenceEvent();
	~ImagesequenceEvent();
	void set(shNodePic sh);

	bool            _playToggle;
	bool            _trackMouse;
	ImageStreamList _imageStreamList;
	ImageStreamPlayBackSpeedList _imageStreamPlayBackSpeedList;
	int n;
};

