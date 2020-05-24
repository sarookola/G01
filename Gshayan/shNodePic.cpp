#include "shNodePic.h"


osgDB::DirectoryContents shNodePic::getSuitableFiles(string arguments)
{
	osgDB::DirectoryContents files;



	const std::string& directory = osgDB::getFilePath(arguments);
	osgDB::DirectoryContents dc = osgDB::getSortedDirectoryContents(directory);
	if (dc.size() > 0)
	{
		for (osgDB::DirectoryContents::iterator itr = dc.begin(); itr != dc.end(); ++itr)
		{
			std::string full_file_name = directory + "/" + (*itr);
			std::string ext = osgDB::getLowerCaseFileExtension(full_file_name);
			if ((ext == "jpg") || (ext == "png") || (ext == "gif") || (ext == "rgb") || (ext == "dds"))
			{
				files.push_back(full_file_name);
			}
		}
	}
	return files;
}

void shNodePic::readSettingpackImageOrSeq(SettingPack settingp, int draw)
{
	if (settingp.drawSettingS[draw].imageSequency) {
		imageSequence = new osg::ImageSequence;
		imageSequence->setMode(osg::ImageSequence::PRE_LOAD_ALL_IMAGES);
		osgDB::DirectoryContents files = getSuitableFiles(settingp.drawSettingS[draw].image);
		if (!files.empty())
		{
			for (osgDB::DirectoryContents::iterator itr = files.begin();
				itr != files.end();
				++itr)
			{
				const std::string& filename = *itr;
				if (preLoad)
				{
					osg::ref_ptr<osg::Image> image = osgDB::readRefImageFile(filename);
					if (image.valid())
					{
						imageSequence->addImage(image.get());
					}
				}
				else
				{
					osg::ref_ptr<osg::Image> image = osgDB::readRefImageFile(filename);
					if (image.valid())
					{
						imageSequence->addImageFile(filename);
					}
				}

			}


			unsigned int maxNum = imageSequence->getNumImageData();
			if (maxNum > 0) {
				imageSequence->setLength(double(maxNum)*(1.0 / 25)); //fps));
				isImagesequentially = true;
				image = imageSequence->getImage(0);
			}
		}
		//	imageSequence->play();

	}
	else {
		image = osgDB::readRefImageFile(settingp.drawSettingS[draw].image);
	}


	if (image)
	{
		//isImage = true;
		//	osg::notify(osg::NOTICE) << "settingp.drawSettingS[draw].image" << settingp.drawSettingS[draw].image << "    image->s()" << osgDB::readRefImageFile(settingp.drawSettingS[draw].image)->s() << " image-t()=" << image->t() << " aspectRatio=" << image->getPixelAspectRatio() << std::endl;

			//	if (!foundid) {

		osg::ref_ptr<osg::Drawable> drawable = myCreateTexturedQuadGeometry(settingp.drawSettingS[draw].alignment); 

		//	if (image->isImageTranslucent())
		//	{
			//	osg::notify(osg::NOTICE) << "Transparent movie, enabling blending." << std::endl;

		drawable->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
	//	drawable->getOrCreateStateSet()->setMode(ANTIALIASED_QUALITY, osg::StateAttribute::ON);
		drawable->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

		//	}
		geode = new osg::Geode;
		geode->addDrawable(drawable.get());
		//		osg::PositionAttitudeTransform *trans2 = new osg::PositionAttitudeTransform;
		//		trans2->addChild(drawable.get());
		trans->addChild(geode);
		geodevis = true;
		//		trans->addChild(trans2);
		//		}


		if (useTextureRectangle)
		{
			osg::TextureRectangle* texture = new osg::TextureRectangle(image);
			texture->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE);
			texture->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE);
			texture->setShadowTextureMode(osg::Texture::ShadowTextureMode::ALPHA);
			pictureQuad->getStateSet()->setTextureAttribute(0,
				texture,
				osg::StateAttribute::OVERRIDE);
			pictureQuad->getStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
//			pictureQuad->getStateSet()->setMode(ANTIALIASED_QUALITY, osg::StateAttribute::ON);
			pictureQuad->getStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
		}
		else
		{

			osg::Texture2D* texture = new osg::Texture2D(image);
			texture->setResizeNonPowerOfTwoHint(false);
			texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
			texture->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE);
			texture->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE);
			texture->setShadowTextureMode(osg::Texture::ShadowTextureMode::ALPHA);
			pictureQuad->getStateSet()->setTextureAttribute(0,
				texture,
				osg::StateAttribute::OVERRIDE);
			pictureQuad->getStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
			//pictureQuad->getStateSet()->setMode(ANTIALIASED_QUALITY, osg::StateAttribute::ON);
			pictureQuad->getStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

		}

	}
}

void shNodePic::readSettingPackText(SettingPack settingp, int draw)
{
	convertutf8 con;
	fontResulation = settingp.drawSettingS[draw].fontResulation;
	charSize = settingp.drawSettingS[draw].CharacterSize;
	fback = settingp.drawSettingS[draw].fback;
	textmaxwide = settingp.drawSettingS[draw].fontMAxwide;
	switch (settingp.drawSettingS[draw].alignment / 100) {
	case 0:
		direction = 0;
		//	alignmnet = osgText::TextBase::RIGHT_BOTTOM;
		break;
	case 1:
		//alignmnet = osgText::TextBase::RIGHT_CENTER;
		direction = 1;
		break;
	}
	switch (settingp.drawSettingS[draw].alignment % 100)
	{
	case 0:
		alignmnet = osgText::TextBase::LEFT_BOTTOM;
		break;
	case 1:
		alignmnet = osgText::TextBase::LEFT_CENTER;
		break;
	case 2:
		alignmnet = osgText::TextBase::LEFT_TOP;
		break;
	case 3:
		alignmnet = osgText::TextBase::CENTER_BOTTOM;
		break;
	case 4:
		alignmnet = osgText::TextBase::CENTER_CENTER;
		break;
	case 5:
		alignmnet = osgText::TextBase::CENTER_TOP;
		break;
	case 6:
		alignmnet = osgText::TextBase::RIGHT_BOTTOM;
		break;
	case 7:
		alignmnet = osgText::TextBase::RIGHT_CENTER;
		break;
	case 8:
		alignmnet = osgText::TextBase::RIGHT_TOP;
		break;


	case 9:
		alignmnet = osgText::TextBase::LEFT_BOTTOM_BASE_LINE;
		break;
	case 10:
		alignmnet = osgText::TextBase::LEFT_BASE_LINE;
		break;
	case 11:
		alignmnet = osgText::TextBase::LEFT_BASE_LINE;
		break;
	case 12:
		alignmnet = osgText::TextBase::CENTER_BOTTOM_BASE_LINE;
		break;
	case 13:
		alignmnet = osgText::TextBase::CENTER_BASE_LINE;
		break;
	case 14:
		alignmnet = osgText::TextBase::CENTER_BASE_LINE;
		break;
	case 15:
		alignmnet = osgText::TextBase::RIGHT_BOTTOM_BASE_LINE;
		break;
	case 16:
		alignmnet = osgText::TextBase::RIGHT_BASE_LINE;
		break;
	case 17:
		alignmnet = osgText::TextBase::RIGHT_BASE_LINE;
		break;

	default:
		break;
	}
	//cout << "980222-direction=" << direction << endl;
	//isText = true;
	textst = con.Convertp(osgText::String(settingp.drawSettingS[draw].text1, osgText::String::ENCODING_UTF8), direction);
	//textst = (osgText::String(settingp.drawSettingS[draw].text1, osgText::String::ENCODING_UTF8));
	geode = myCreateTextGeode();
	trans->addChild(geode);
	geodevis = true;

}

bool shNodePic::readSettingPackObj(SettingPack settingp, int draw)
{
	osg::Node * n = NULL;
	try
	{
		n = osgDB::readNodeFile(settingp.drawSettingS[draw].image);
	}
	catch (const std::exception&)
	{

	}
	if (n != NULL) {
		geode = new osg::Geode;
		geode->addChild(n);
		//		osg::PositionAttitudeTransform *trans2 = new osg::PositionAttitudeTransform;
		//		trans2->addChild(drawable.get());
		trans->addChild(geode);
		geodevis = true;
		return true;
	}
	return false;
}


bool shNodePic::readLight(SettingPack settingp, int draw, int lightnum)
{
	//	osg::Group* lightGroup = new osg::Group;
	osg::Light* myLight2 = new osg::Light;
	myLight2->setLightNum(lightnum);
	myLight2->setPosition(osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f)); //osg::Vec4(settingp.drawSettingS[draw].drawingDimsList[0][0].pos[0], settingp.drawSettingS[draw].drawingDimsList[0][0].pos[1], settingp.drawSettingS[draw].drawingDimsList[0][0].pos[2], 1.0f));// osg::Vec4(0.0, 0.0, 300.0, 1.0f));
	osg::Vec4 v = osg::Vec4f((((settingp.drawSettingS[draw].drawingDimsList[0][0].textC & 0x00ff0000) >> 16) / 255), ((float)((settingp.drawSettingS[draw].drawingDimsList[0][0].textC & 0x0000ff00) >> 8) / 255), ((float)((settingp.drawSettingS[draw].drawingDimsList[0][0].textC & 0x00000ff)) / 255), ((float)((settingp.drawSettingS[draw].drawingDimsList[0][0].opac)) / 255));
	osg::Vec4 v2 = osg::Vec4f((((settingp.drawSettingS[draw].drawingDimsList[0][0].strokC & 0x00ff0000) >> 16) / 255), ((float)((settingp.drawSettingS[draw].drawingDimsList[0][0].strokC & 0x0000ff00) >> 8) / 255), ((float)((settingp.drawSettingS[draw].drawingDimsList[0][0].strokC & 0x00000ff)) / 255), ((float)((settingp.drawSettingS[draw].drawingDimsList[0][0].opac)) / 255));
	myLight2->setAmbient(v2);// osg::Vec4(settingp.drawSettingS[draw].drawingDimsList[0][0].textC));// 1.0f, 1.0f, 1.0f, 1.0f));
	myLight2->setDiffuse(v);// osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));//
	myLight2->setSpecular(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));

	osg::LightSource* lightS2 = new osg::LightSource;
	lightS2->setLight(myLight2);
	//	lightS2->setLocalStateSetModes(osg::StateAttribute::ON);
	trans->addChild(lightS2);

	geodevis = true;
	//cout << "981105- lightnum=" << lightnum << endl;
	return true;

}


bool shNodePic::MotionCallBackCerate(vector<SettingPack::drawSettingDims> dims)
{
	animcallback = NULL;

	switch (motion_Linear_Bezier_)
	{
	case 1:
	{

		//	AnimBezierKeyCallback*	animcallback = NULL;
			//	animcallback->motion_Linear_Bezier_ = AnimCallback::Motion_Linear_Bezier_::Bezier;
		osg::Vec3f f, mscale, mpos, mquad;
		float duration = 0;
		//	for (size_t animatek = 0; animatek < settingp.drawSettingS[i].drawingDimsList.size(); animatek++)
	//		{

		animcallback = new AnimBezierKeyCallback();
		osgAnimation::Vec3CubicBezierKeyframeContainer* keyPos = animcallback->_samplerPosB->getOrCreateKeyframeContainer();
		osgAnimation::Vec3CubicBezierKeyframeContainer* keyRot = animcallback->_samplerRotB->getOrCreateKeyframeContainer();
		osgAnimation::Vec3CubicBezierKeyframeContainer* keysSca = animcallback->_samplerScaB->getOrCreateKeyframeContainer();

		duration = 0;
		int keyframe = dims.size();
		if (keyframe > 1)
		{
			for (int j = 0; j < keyframe; j++)
			{
				mscale = (osg::Vec3f(dims[j].scale[0], dims[j].scale[1], dims[j].scale[2]));
				mpos = (osg::Vec3f(dims[j].pos[0], dims[j].pos[1], dims[j].pos[2]));
				mquad = osg::Vec3f(dims[j].angle[0], dims[j].angle[1], dims[j].angle[2]);
				keyPos->push_back(osgAnimation::Vec3CubicBezierKeyframe(duration, mpos));
				keyRot->push_back(osgAnimation::Vec3CubicBezierKeyframe(duration, mquad));
				keysSca->push_back(osgAnimation::Vec3CubicBezierKeyframe(duration, mscale));
				duration = duration + dims[j].frames *frame_duration;
			}
			animcallback->_loop = animloop;

		}
		else return false;
		//		}
	}
	break;
	case 0:
	{
		//	AnimLinearKeyCallback*	animcallback = NULL;

		osg::Vec3f f, mscale, mpos, mquad;
		float duration = 0;
		//	for (size_t animatek = 0; animatek < settingp.drawSettingS[i].drawingDimsList.size(); animatek++)
		//	{

		animcallback = new AnimLinearKeyCallback();
		osgAnimation::Vec3KeyframeContainer* keyPos = animcallback->_samplerPos->getOrCreateKeyframeContainer();
		osgAnimation::Vec3KeyframeContainer* keyRot = animcallback->_samplerRot->getOrCreateKeyframeContainer();
		osgAnimation::Vec3KeyframeContainer* keysSca = animcallback->_samplerSca->getOrCreateKeyframeContainer();

		duration = 0;
		//	cout << " dims.size()=" << dims.size() << endl;
		int keyframe = dims.size();
		if (keyframe > 1)
		{
			for (int j = 0; j < keyframe; j++)
			{
				mscale = (osg::Vec3f(dims[j].scale[0], dims[j].scale[1], dims[j].scale[2]));
				mpos = (osg::Vec3f(dims[j].pos[0], dims[j].pos[1], dims[j].pos[2]));
				mquad = osg::Vec3f(dims[j].angle[0], dims[j].angle[1], dims[j].angle[2]);
				keyPos->push_back(osgAnimation::Vec3Keyframe(duration, mpos));
				keyRot->push_back(osgAnimation::Vec3Keyframe(duration, mquad));
				keysSca->push_back(osgAnimation::Vec3Keyframe(duration, mscale));
				duration = duration + dims[j].frames *frame_duration;
			}
			animcallback->_loop = animloop;
		}
		else return false;
	}

	break;
	case 2: {

		//	AnimBezierKeyCallback*	animcallback = NULL;
			//animcallback->motion_Linear_Bezier_ = AnimCallback::Motion_Linear_Bezier_::Beziercubic;
		osg::Vec3f mscale, mpos, mquad, mscale0, mpos0, mquad0, mscale2, mpos2, mquad2;
		float duration = 0;
		//	for (size_t animatek = 0; animatek < settingp.drawSettingS[i].drawingDimsList.size(); animatek++)
		//	{
		animcallback = new AnimBezierKeyCallback();
		osgAnimation::Vec3CubicBezierKeyframeContainer* keyPos = animcallback->_samplerPosB->getOrCreateKeyframeContainer();
		osgAnimation::Vec3CubicBezierKeyframeContainer* keyRot = animcallback->_samplerRotB->getOrCreateKeyframeContainer();
		osgAnimation::Vec3CubicBezierKeyframeContainer* keysSca = animcallback->_samplerScaB->getOrCreateKeyframeContainer();

		duration = 0;
		int keyframe = dims.size();
		if (keyframe > 1)
		{
			for (int j = 0; j < keyframe; j++)
			{
				mscale = (osg::Vec3f(dims[j].scale[0], dims[j].scale[1], dims[j].scale[2]));
				mpos = (osg::Vec3f(dims[j].pos[0], dims[j].pos[1], dims[j].pos[2]));
				mquad = (osg::Vec3f(dims[j].angle[0], dims[j].angle[1], dims[j].angle[2]));
				int p = j - 1;
				if (j == 0)p = keyframe - 1;
				mscale0 = (osg::Vec3f(dims[p].scale[0], dims[p].scale[1], dims[p].scale[2]));
				mpos0 = (osg::Vec3f(dims[p].pos[0], dims[p].pos[1], dims[p].pos[2]));
				mquad0 = (osg::Vec3f(dims[p].angle[0], dims[p].angle[1], dims[p].angle[2]));
				p = (j == keyframe - 1) ? 0 : j + 1;
				mscale2 = (osg::Vec3f(dims[p].scale[0], dims[p].scale[1], dims[p].scale[2]));
				mpos2 = (osg::Vec3f(dims[p].pos[0], dims[p].pos[1], dims[p].pos[2]));
				mquad2 = (osg::Vec3f(dims[p].angle[0], dims[p].angle[1], dims[p].angle[2]));
				keyPos->push_back(osgAnimation::Vec3CubicBezierKeyframe(duration, osgAnimation::Vec3CubicBezier(mpos, mpos + (mpos - mpos0), mpos2 - (mpos2 - mpos))));
				keyRot->push_back(osgAnimation::Vec3CubicBezierKeyframe(duration, osgAnimation::Vec3CubicBezier(mquad, mquad + (mquad - mquad0), mquad2 - (mquad2 - mquad))));
				keysSca->push_back(osgAnimation::Vec3CubicBezierKeyframe(duration, osgAnimation::Vec3CubicBezier(mscale, mscale + (mscale - mscale0), mscale2 - (mscale2 - mscale))));
				duration = duration + dims[j].frames *frame_duration;
			}
			animcallback->_loop = animloop;
		}
		else return false;
		//	}

	}
			break;
	default:
		return false;
		break;
	}
	return true;
}

void shNodePic::Motionsave(SettingPack settingp, int draw)
{
	drawingDims = settingp.drawSettingS[draw].drawingDimsList;
	switch (settingp.drawSettingS[draw].bezierLinear)
	{
	case 1:
	{
		motion_Linear_Bezier_ = Motion_Linear_Bezier_::Bezier;
	}
	break;
	case 0:
	{
		motion_Linear_Bezier_ = Motion_Linear_Bezier_::Linear;
	}
	break;
	case 2: {
		motion_Linear_Bezier_ = Motion_Linear_Bezier_::Beziercubic;
	}
			break;
	default:
		break;
	}

}

bool shNodePic::stateCallbackCerate(vector<SettingPack::drawSettingDims> dims)
{

	statecallback = new AnimtkStateSetUpdateCallback(text);
	osgAnimation::Vec4KeyframeContainer* keys2 = statecallback->_sampler->getOrCreateKeyframeContainer();
	statecallback->istext = (ito == 1);
	float duration = 0;
	int keyframe = dims.size();
	if (keyframe > 1)
	{
		for (int j = 0; j < keyframe; j++)
		{
			osg::Vec4f v = osg::Vec4f(((float)((dims[j].textC & 0x00ff0000) >> 16) / 255), ((float)((dims[j].textC & 0x0000ff00) >> 8) / 255), ((float)((dims[j].textC & 0x00000ff)) / 255), ((float)((dims[j].opac)) / 255));
			keys2->push_back(osgAnimation::Vec4Keyframe(duration, v));
			duration = duration + dims[j].frames *frame_duration;
		}
		statecallback->_loop = animloop;
		return true;
	}
	//osg::StateSet* st = new osg::StateSet();

	//	st->setAttributeAndModes(new osg::Material(), true);
	//	//	st->setMode(GL_BLEND, true);
	//	st->setUpdateCallback(statecallback);
	//	st->setMode(GL_BLEND, osg::StateAttribute::ON);
	//	st->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
	//	trans->setStateSet(st);



		// if (isText) trans->setStateSet(st);
		//else trans->setStateSet(st);
	return false;
}

void shNodePic::stateCallback_ImageSequence(SettingPack settingp, int draw)
{

	//if (isImage && isImagesequentially && imageSequence   && imageSequence->getLength() > 0) {

	imageSeqCallBack = new stateSetCallback_ImageSequence(imageSequence);

	imageSeqCallBack->_loop = settingp.drawSettingS[draw].seqLoop;
	imageSeqCallBack->frameRate = settingp.drawSettingS[draw].AnimateRate;
	imageSeqCallBack->animLength = imageSequence->getNumImageData();
	imageSeqCallBack->useTextureRectangle = useTextureRectangle;
	imageSeqCallBack->endframe = imageSequence->getNumImageData() - 1;
	//osg::StateSet* st = new osg::StateSet();

	//st->setAttributeAndModes(new osg::Material(), true);
	//st->setMode(GL_BLEND, true);
	//st->setUpdateCallback(call2);
	pictureQuad->getStateSet()->setUpdateCallback(imageSeqCallBack);

	/*imageSeqCallBack->start();*/
	//	trans->setStateSet(st);
//	}

}
void shNodePic::setVisible(bool vis)
{
	if (ito == 1 || ito == 2 || ito == 3) {
		if (vis && !geodevis) {
			if (geode != NULL) {
				geode->setNodeMask(0xffffffff);
				//trans->addChild(geode); 
				geodevis = true;
				//cout << "sh node pic vis trure" << endl;
			}
		}
		else if (!vis && geodevis) {
			//	trans->removeChild(geode);
			if (geode != NULL) {
				geode->setNodeMask(0);
				geodevis = false;
				//cout << "sh node pic vis FAlse  and geode=" << geode << endl;
			}

		}
	}
}
void shNodePic::imagePlay(bool play)
{
	if ((ito == 3) && isImagesequentially) {
		if (play) imageSeqCallBack->start();
		else imageSeqCallBack->stop();
	}
}
//void shNodePic::objectanim(bool play, int dim)
//{
//
//	if (play) {
//		if (dim < animcallbacks.size()) {
//			switch (animcallbacks.at(dim)->motion_Linear_Bezier_)
//			{
//			case  AnimCallback::Motion_Linear_Bezier_::Linear:
//				animcallback = new AnimLinearKeyCallback(*(AnimLinearKeyCallback*)animcallbacks.at(dim));
//				//	animcallback = (AnimLinearKeyCallback*)animcallbacks.at(dim);
//				//	cout << "animcallback=" << animcallback << "\ttrans="<<trans<<endl;
//				trans->setUpdateCallback(animcallback);
//				animcallback->start();
//				break;
//			default:
//				break;
//			}
//
//		}
//
//		//if (dim >= statecallbacks.size())dim = 0;
//		//statecallback = (statecallbacks.at(dim));
//		//osg::StateSet* st = new osg::StateSet();
//
//		//st->setAttributeAndModes(new osg::Material(), true);
//		////	st->setMode(GL_BLEND, true);
//		//st->setUpdateCallback(statecallback);
//		//st->setMode(GL_BLEND, osg::StateAttribute::ON);
//		//st->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
//		//trans->setStateSet(st);
//		//statecallback->start();
//	}
//	else {
//		if (animcallback != NULL)
//		{
//			animcallback->stop();
//		}
//		//if (statecallback != NULL)	statecallback->stop();
//	}
//
//
//}

void shNodePic::objectanim(bool play, int dim)
{

	if (play)
	{
		//	cout << "dim=" << dim << "     drawingDims.size()=" << drawingDims.size() <<"     this id = " << id << endl;
		if (dim < drawingDims.size())
			if (MotionCallBackCerate(drawingDims.at(dim)))
		{
		//	cout << "paaased" << endl;

			trans->setUpdateCallback(animcallback);
			animcallback->start();
			//switch (motion_Linear_Bezier_)
			//{
			//case  AnimCallback::Motion_Linear_Bezier_::Linear:
			//	//imcallback = new AnimLinearKeyCallback(*(AnimLinearKeyCallback*)animcallback);
			//	//	animcallback = (AnimLinearKeyCallback*)animcallbacks.at(dim);
			//	//	cout << "animcallback=" << animcallback << "\ttrans="<<trans<<endl;
			//	trans->setUpdateCallback(animcallback);
			//	animcallback->start();
			//	break;
			//default:
			//	break;
			//}

		}


	}
	else {
		//cout << " anim stop this id = " << id << endl;
		if (animcallback != NULL)
		{
			animcallback->stop();
		}
		//if (statecallback != NULL)	statecallback->stop();
	}


}

void shNodePic::objectColor(bool play, int dim)
{
	if (ito == 1 || (ito == 3 && !isImagesequentially) || ito == 2) {
		if (play)
		{
			if (dim < drawingDims.size())
				if (stateCallbackCerate(drawingDims.at(dim)))
			//if (dim < statecallbacks.size())
			{
				//	statecallback = (statecallbacks.at(dim));
				osg::StateSet* st = new osg::StateSet();

				st->setAttributeAndModes(new osg::Material(), true);
				//	st->setMode(GL_BLEND, true);
				st->setUpdateCallback(statecallback);
				st->setMode(GL_BLEND, osg::StateAttribute::ON);
				st->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
				trans->setStateSet(st);
				statecallback->start();
			}
		}
		else {

			if (statecallback != NULL)	statecallback->stop();
		}
	}

}

osg::Geometry *shNodePic::myCreateTexturedQuadGeometry(int alignment)
{
	alignment = alignment % 100; // for left to right texts

	bool flip = image->getOrigin() == osg::Image::TOP_LEFT;
	if (option_flip) flip = !flip;
	float width = 100;
	float height = 100;
	if (imageaspectuse) {

		width = image->s() * image->getPixelAspectRatio();
		height = image->t();
	}

	osg::Vec3 pos = osg::Vec3(0.0f, 0.0f, 0.0f) - (osg::Vec3(width, 0.0f, 0.0f)*0.5*(alignment / 3)) - ((xyPlane ? osg::Vec3(0.0f, height, 0.0f) : osg::Vec3(0.0f, 0.0f, height))*0.5*(alignment % 3));
	if (useTextureRectangle)
	{
		pictureQuad = osg::createTexturedQuadGeometry(pos,
			osg::Vec3(width, 0.0f, 0.0f),
			xyPlane ? osg::Vec3(0.0f, height, 0.0f) : osg::Vec3(0.0f, 0.0f, height),
			//0.0f, flip ? height : 0.0, width, flip ? 0.0 : height);
			0.0f, flip ? image->t() : 0.0, image->s(), flip ? 0.0 : image->t());

		osg::TextureRectangle* texture = new osg::TextureRectangle(image);
		//	texture->setTextureSize(width/2, height/2);
		texture->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE);
		texture->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE);


		pictureQuad->getOrCreateStateSet()->setTextureAttributeAndModes(0,
			texture,
			osg::StateAttribute::ON);
		pictureQuad->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
		pictureQuad->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

		return pictureQuad;
	}
	else
	{
		pictureQuad = osg::createTexturedQuadGeometry(pos,
			osg::Vec3(width, 0.0f, 0.0f),
			xyPlane ? osg::Vec3(0.0f, height, 0.0f) : osg::Vec3(0.0f, 0.0f, height),
			0.0f, flip ? 1.0f : 0.0f, 1.0f, flip ? 0.0f : 1.0f);

		osg::Texture2D* texture = new osg::Texture2D(image);
		texture->setResizeNonPowerOfTwoHint(false);
		texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
		texture->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE);
		texture->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE);


		pictureQuad->getOrCreateStateSet()->setTextureAttributeAndModes(0,
			texture,
			osg::StateAttribute::ON);
		pictureQuad->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
		pictureQuad->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

		return pictureQuad;
	}



}

osg::Geode * shNodePic::myCreateTextGeode()
{
	osg::Geode* alignmentGeode = new osg::Geode;
	//sequence->addChild(alignmentGeode);
	//sequence->setTime(sequence->getNumChildren(), 1.0f);

	text = new osgText::Text;
	text->setFont(font);
	text->setColor(textColor);
	text->setCharacterSize(charSize);
	text->setFontResolution(fontResulation, fontResulation);
	text->setMaximumWidth(textmaxwide);
	//	text->setPosition(trans->getPosition());
	if (fback)	text->setDrawMode(osgText::Text::TEXT | osgText::Text::ALIGNMENT | osgText::Text::BOUNDINGBOX);

	text->setAlignment(alignmnet);
	//text->setText(UTF8toUnicode(textst));
	text->setText(textst);// , osgText::String::ENCODING_UTF8);
	text->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
	text->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
	//cout << textst << "shayan RAnjbar 980520" << endl;
//	string tt ("\u0001");
//	text->setText("ن \ufe07\ufe68 \ufe07\ufe5e ", osgText::String::ENCODING_UTF8);
	//cout << "direction =" << direction << endl;



	if (direction == 1)
	{
		text->setLayout(osgText::Text::RIGHT_TO_LEFT);
	}
	else
	{
		text->setLayout(osgText::Text::LEFT_TO_RIGHT);
	}

	alignmentGeode->addDrawable(text);

	return alignmentGeode;
}

template<class T>
void shNodePic::crateMotion(SettingPack settingp, int i, T crateMotion, T keyRot, T keysSca)
{
	//motionLB = motion::bezier;
	AnimBezierKeyCallback*	animcallback;
	osg::Vec3f  mscale, mpos, mquad;
	float duration = 0;
	for (size_t animatek = 0; animatek < settingp.drawSettingS[i].drawingDimsList.size(); animatek++)
	{
		animcallback = new AnimBezierKeyCallback();
		keyPos = animcallback->_samplerPosB->getOrCreateKeyframeContainer();
		keyRot = animcallback->_samplerRotB->getOrCreateKeyframeContainer();
		keysSca = animcallback->_samplerScaB->getOrCreateKeyframeContainer();
		duration = 0;
		int keyframe = settingp.drawSettingS[i].drawingDimsList[animatek].size();
		if (keyframe > 1)
		{
			for (int j = 0; j < keyframe; j++)
			{
				mscale = (osg::Vec3f(settingp.drawSettingS[i].drawingDimsList[animatek][j].scale[0], settingp.drawSettingS[i].drawingDimsList[animatek][j].scale[1], settingp.drawSettingS[i].drawingDimsList[animatek][j].scale[2]));
				mpos = (osg::Vec3f(settingp.drawSettingS[i].drawingDimsList[animatek][j].pos[0], settingp.drawSettingS[i].drawingDimsList[animatek][j].pos[1], settingp.drawSettingS[i].drawingDimsList[animatek][j].pos[2]));
				mquad = osg::Vec3f(settingp.drawSettingS[i].drawingDimsList[animatek][j].angle[0], settingp.drawSettingS[i].drawingDimsList[animatek][j].angle[1], settingp.drawSettingS[i].drawingDimsList[animatek][j].angle[2]);
				keyPos->push_back(osgAnimation::Vec3CubicBezierKeyframe(duration, mpos));
				keyRot->push_back(osgAnimation::Vec3CubicBezierKeyframe(duration, mquad));
				keysSca->push_back(osgAnimation::Vec3CubicBezierKeyframe(duration, mscale));
				duration = duration + settingp.drawSettingS[i].drawingDimsList[animatek][j].frames *frame_duration;
			}
			animcallback->_loop = settingp.drawSettingS[i].anloop;
			animcallbacks.push_back(animcallback);
		}
	}
}
shNodePic::shNodePic()
{


	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	//trans = new osg::PositionAttitudeTransform;
	trans = new osg::MatrixTransform();
	//

}


shNodePic::~shNodePic()
{
}

