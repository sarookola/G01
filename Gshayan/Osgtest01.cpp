#include "Osgtest01.h"



Osgtest01::~Osgtest01()
{
}

void Osgtest01::updatesettingpack(SettingPack settingp)
{
	if (settingp.updated) return;
	{


		typedef osgViewer::Viewer::Windows Windows;
		Windows windows;

		_viewer->getWindows(windows);
		windows[0]->setWindowRectangle(settingp.screenDim[0], settingp.screenDim[1], settingp.screenDim[2], settingp.screenDim[3]);

		_viewer->getCamera()->setViewport(0, 0, settingp.screenDim[2], settingp.screenDim[3]);

		osg::Vec3 LookFrom = osg::Vec3(settingp.camera[0], settingp.camera[1], settingp.camera[2]);
		osg::Vec3 LookAt = osg::Vec3(settingp.camera[3], settingp.camera[4], settingp.camera[5]);
		osg::Vec3 Up = osg::Vec3(settingp.camera[6], settingp.camera[7], settingp.camera[8]);
		//	_viewer->setCameraManipulator(new osgGA::TrackballManipulator(),true);
			////_viewer->getCameraManipulator()->setHomePosition(LookFrom, LookAt, Up, false);

			////Vec3d eye(1000.0, 1000.0, 0.0);
			////Vec3d center(0.0, 0.0, 0.0);
			////Vec3d up(0.0, 0.0, 1.0);
			//	cout << " 990215 - settingp.camera[0]=" << settingp.camera[0] << "   =" << LookFrom.x() << endl;
		_viewer->getCamera()->setViewMatrixAsLookAt(LookFrom, LookAt, Up);
		_viewer->getCamera()->setProjectionMatrixAsPerspective(settingp.camera[9], settingp.camera[10], settingp.camera[11], settingp.camera[12]);
	}

	//clea light
	{
		lightnum = 0;
		root->getOrCreateStateSet()->setMode(GL_LIGHT0, osg::StateAttribute::OFF);
		root->getOrCreateStateSet()->setMode(GL_LIGHT1, osg::StateAttribute::OFF);
		root->getOrCreateStateSet()->setMode(GL_LIGHT2, osg::StateAttribute::OFF);
		root->getOrCreateStateSet()->setMode(GL_LIGHT3, osg::StateAttribute::OFF);
		root->getOrCreateStateSet()->setMode(GL_LIGHT4, osg::StateAttribute::OFF);
		root->getOrCreateStateSet()->setMode(GL_LIGHT5, osg::StateAttribute::OFF);
		root->getOrCreateStateSet()->setMode(GL_LIGHT6, osg::StateAttribute::OFF);
	}
	backcolor = osg::Vec4(((float)((settingp.backcolor & 0x00ff0000) >> 16) / 255), ((float)((settingp.backcolor & 0x0000ff00) >> 8) / 255), ((float)((settingp.backcolor & 0x00000ff)) / 255), ((float)settingp.backcolor / 255));
	nodePicVectorB = vector<shNodePic>();
	convertutf8 con;
	for (size_t i = 0; i < settingp.drawSettingS.size(); i++)
	{
		int draw = i, dim1 = 0, dim2 = 0;

		shNodePic sh;

		sh.id = settingp.drawSettingS[draw].id;
		sh.ito = settingp.drawSettingS[draw].ito;
		sh.idRoot = -1;
		sh.parent = settingp.drawSettingS[draw].parent;
		sh.parentRoot = 0;
		sh.vis = settingp.drawSettingS[draw].vis;


		osg::Vec3 pos(settingp.drawSettingS[draw].drawingDimsList[dim1][dim2].pos[0], settingp.drawSettingS[draw].drawingDimsList[dim1][dim2].pos[1], settingp.drawSettingS[draw].drawingDimsList[dim1][dim2].pos[2]);
		osg::Quat quad(settingp.drawSettingS[draw].drawingDimsList[dim1][dim2].angle[0], osg::Vec3(1.0, 0.0, 0.0), settingp.drawSettingS[draw].drawingDimsList[dim1][dim2].angle[1], osg::Vec3(0.0, 1.0, 0.0), settingp.drawSettingS[draw].drawingDimsList[dim1][dim2].angle[2], osg::Vec3(0.0, 0.0, 1.0));
		osg::Vec3 scale(settingp.drawSettingS[draw].drawingDimsList[dim1][dim2].scale[0], settingp.drawSettingS[draw].drawingDimsList[dim1][dim2].scale[1], settingp.drawSettingS[draw].drawingDimsList[dim1][dim2].scale[2]);
		//sh.trans->setPosition(pos);
		//sh.trans->setAttitude(quad);
		//sh.trans->setScale(scale);
		osg::Matrixf M;
		M = osg::Matrixf::scale(scale)*osg::Matrixf::rotate(quad)*osg::Matrixf::translate(pos);
		sh.trans->setMatrix(M);
		//sh.trans->setAttitude(quad);
		//sh.trans->setScale(scale);

		sh.textColor = osg::Vec4(((float)((settingp.drawSettingS[draw].drawingDimsList[dim1][dim2].textC & 0x00ff0000) >> 16) / 255), ((float)((settingp.drawSettingS[draw].drawingDimsList[dim1][dim2].textC & 0x0000ff00) >> 8) / 255), ((float)((settingp.drawSettingS[draw].drawingDimsList[dim1][dim2].textC & 0x00000ff)) / 255), ((float)((settingp.drawSettingS[draw].drawingDimsList[dim1][dim2].opac)) / 255));
		//sh.textst = con.Convertp(osgText::String(settingp.drawSettingS[draw].text1, osgText::String::ENCODING_UTF8), sh.direction);
			 //"sdfsadf ن \ufe07 \ufe68 \ufe68 \ufe07\ufe5e ";//
		sh.font = osgText::readRefFontFile(settingp.fontpath + settingp.drawSettingS[draw].font);

		//cout << " 981106- draw=" << draw << "\tito=" << settingp.drawSettingS[draw].ito << endl;
		if (settingp.drawSettingS[draw].ito == 3) {
			sh.readSettingpackImageOrSeq(settingp, draw);

		}
		else if (settingp.drawSettingS[draw].ito == 1 && sh.font)
		{


			sh.readSettingPackText(settingp, draw);

		}
		else if (settingp.drawSettingS[draw].ito == 2) {
			sh.readSettingPackObj(settingp, draw);
		}
		else if (settingp.drawSettingS[draw].ito == 4 && lightnum < 6) {
			sh.readLight(settingp, draw, lightnum);
			switch (lightnum)
			{
			case 0:
				root->getOrCreateStateSet()->setMode(GL_LIGHT0, osg::StateAttribute::ON);
				break;
			case 1:
				root->getOrCreateStateSet()->setMode(GL_LIGHT1, osg::StateAttribute::ON);
				break;
			case 2:
				root->getOrCreateStateSet()->setMode(GL_LIGHT2, osg::StateAttribute::ON);
				break;
			case 3:
				root->getOrCreateStateSet()->setMode(GL_LIGHT3, osg::StateAttribute::ON);
				break;
			case 4:
				root->getOrCreateStateSet()->setMode(GL_LIGHT4, osg::StateAttribute::ON);
				break;
			case 5:
				root->getOrCreateStateSet()->setMode(GL_LIGHT5, osg::StateAttribute::ON);
				break;
			case 6:
				root->getOrCreateStateSet()->setMode(GL_LIGHT6, osg::StateAttribute::ON);
				break;
			default:
				break;
			}
			lightnum++;
		}
		else if (settingp.drawSettingS[draw].ito != 0)
			continue;
		sh.Motionsave(settingp, draw);
		sh.animloop = settingp.drawSettingS[draw].anloop;
		//sh.MotionCallBackCerate(settingp, draw);

		//if (settingp.drawSettingS[draw].ito == 1|| settingp.drawSettingS[draw].ito == 2|| settingp.drawSettingS[draw].ito == 3)	sh.stateCallback(settingp, draw);

		if (sh.isImagesequentially && sh.ito == 3 && sh.imageSequence   && sh.imageSequence->getLength() > 0)
			sh.stateCallback_ImageSequence(settingp, draw);

		nodePicVectorB.push_back(sh);
	}
	vector<int> tree = maketree();


	for each (int index in tree)
	{

		shNodePic sh = nodePicVectorB.at(index);
		//cout << "index=" << index << "\t parent=" << sh.parent << "\trootid=" << sh.idRoot << endl;

	//	if ( sh.parent > 0) {

			//cout << "\trootid=" << nodePicVectorB.at(index).idRoot << endl;
		//}
		//else {
		int sh_parent_index = 0;
		for (size_t i = 1; i < nodePicVectorB.size(); i++)
		{
			if (nodePicVectorB.at(i).id == sh.parent) {
				sh_parent_index = i;
				break;
			}
		}
		if (sh_parent_index != 0) {
			sh.parentRoot = nodePicVectorB.at(sh_parent_index).idRoot;
			(&nodePicVectorB.at(sh_parent_index))->trans->addChild(sh.trans);
			(&nodePicVectorB.at(index))->idRoot = (&nodePicVectorB.at(sh_parent_index))->trans->getChildIndex(sh.trans);

		}
		else {
			(&nodePicVectorB.at(0))->trans->addChild(sh.trans);
			(&nodePicVectorB.at(index))->idRoot = (&nodePicVectorB.at(0))->trans->getNumChildren() - 1;
		}





		//sh.parentRoot = nodePicVectorB.at(sh.parent).idRoot;
		//(&nodePicVectorB.at(sh.parent))->trans->addChild(sh.trans);
		//(&nodePicVectorB.at(index))->idRoot = (&nodePicVectorB.at(sh.parent))->trans->getChildIndex(sh.trans);
		////	cout << "\t parent rootid=" << nodePicVectorB.at(sh.parent).idRoot << "  ?=" << sh.parentRoot << endl;
		////	osg::Node *g = root->getChild(sh.parentRoot);
		////	osg::Transform* t = g->asTransform();
		////	osg::PositionAttitudeTransform *tt = (t->asPositionAttitudeTransform());
		////	tt->addChild(sh.trans);
		////	(&nodePicVectorB.at(index))->idRoot = t->asPositionAttitudeTransform()->getChildIndex(sh.trans);
		////	(&nodePicVectorB.at(index))->isnew = false;

//	}

	//	if (index == 0) {
			//ImagesequenceEvent* imseq = new  ImagesequenceEvent();
			//imseq->set(sh);
			//_viewer->addEventHandler(imseq);
	//}
	}
	if (nodePicVectorB.size() > 0) {
		root->removeChild(0, 1);
		root->addChild(nodePicVectorB.at(0).trans);
		_viewer->getCamera()->setClearColor(backcolor);
	}
	checkvisafterrsetting();
	//root->addChild(osgDB::readNodeFile("test.3ds"));

}

void Osgtest01::checkvisafterrsetting()
{
	int idtemp;
	bool vis;
	for (size_t j = 0; j < nodePicVectorB.size(); j++)
	{

		if (nodePicVectorB[j].parent == 0)
		{
			//nodePicVectorB[j].setVisible(nodePicVectorB[j].vis);
			vis = nodePicVectorB[j].vis;
		}
		else
		{
				idtemp = j;
			vis =  nodePicVectorB[idtemp].vis;
			while (nodePicVectorB[idtemp].parent > 0) {
				idtemp = nodePicVectorB[idtemp].parentRoot;
				if (idtemp >= nodePicVectorB.size()) 
				{
					cout << "980220 osgtest01 Osgtest01::checkvisafterrsetting  =" << idtemp<< endl;
					break;
				}
				vis = vis && nodePicVectorB[idtemp].vis;
				//nodePicVectorB[j].setVisible(vis);
			}
		}

		nodePicVectorB[j].setVisible(vis);
	}

}

void Osgtest01::updateControolgpack(ControolPack controolp)
{

	convertutf8 con;
	for (size_t i = 0; i < controolp.vis_Anim_Bool.size(); i++)
	{

		for (size_t j = 1; j < nodePicVectorB.size(); j++)
		{
			//	cout << "   981105  nodePicVectorB[j].id=" << nodePicVectorB[j].id << "   \tcontroolp.vis_Anim_Bool[i].id=" << controolp.vis_Anim_Bool[i].id << endl;
			if (nodePicVectorB[j].id == controolp.vis_Anim_Bool[i].id) {
					//cout << "updateControolgpack    OK   v.id =" << controolp.vis_Anim_Bool[i].id <<"   visactive="<< controolp.vis_Anim_Bool[i].visactive<<"     vis="<< controolp.vis_Anim_Bool[i].vis<<endl;
			if(controolp.vis_Anim_Bool[i].visactive)	nodePicVectorB[j].setVisible(controolp.vis_Anim_Bool[i].vis);
				nodePicVectorB[j].imagePlay(controolp.vis_Anim_Bool[i].imagePlay);
				nodePicVectorB[j].objectanim(controolp.vis_Anim_Bool[i].objectanim, controolp.vis_Anim_Bool[i].motionDimIndex);
				//	cout << "\tanimid ";
				nodePicVectorB[j].objectColor(controolp.vis_Anim_Bool[i].colorAnim, controolp.vis_Anim_Bool[i].motionDimIndex);
				//	cout << "\tobjectColor "<<endl;
				break;// j = nodePicVectorB.size();
			}

		}

	}
	for (size_t i = 0; i < controolp.dataPackanimationStartEnds.size(); i++)
	{
		for (size_t j = 1; j < nodePicVectorB.size(); j++)
		{
			if (nodePicVectorB[j].ito == 3 && nodePicVectorB[j].isImagesequentially  &&nodePicVectorB[j].id == controolp.dataPackanimationStartEnds[i].id) {
				nodePicVectorB[j].imageSeqCallBack->frameRate = controolp.dataPackanimationStartEnds[i].animRate;
				//	cout << "update controolp id" << nodePicVectorB[j].id <<" \t frame rate="<< nodePicVectorB[j].imageSeqCallBack->frameRate << endl;
					/*nodePicVectorB[j].imageSeqCallBack->_startTime = osg::Timer::instance()->time_m();
					nodePicVectorB[j].imageSeqCallBack->_currentTime = nodePicVectorB[j].imageSeqCallBack->_startTime;
					nodePicVectorB[j].imageSeqCallBack->startFrame = nodePicVectorB[j].imageSeqCallBack->currentframe ;
					nodePicVectorB[j].imageSeqCallBack->_playing = true;*/

				if (controolp.dataPackanimationStartEnds[i].startEndEnable) {
					//	cout << "981105 before update controolp id" << nodePicVectorB[j].id << "\t  end1"<< controolp.dataPackanimationStartEnds[i].end <<"\t lern=" << nodePicVectorB[j].imageSequence->getLength() << "\tend=" << nodePicVectorB[j].imageSeqCallBack->endframe << endl;
					nodePicVectorB[j].imageSeqCallBack->startFrame = controolp.dataPackanimationStartEnds[i].start;
					if (controolp.dataPackanimationStartEnds[i].end >= nodePicVectorB[j].imageSequence->getNumImageData())
						controolp.dataPackanimationStartEnds[i].end = nodePicVectorB[j].imageSequence->getNumImageData() - 1;
					nodePicVectorB[j].imageSeqCallBack->endframe = controolp.dataPackanimationStartEnds[i].end;
					//	cout << "981105 update controolp id" << nodePicVectorB[j].id << " \t frame rate=" << nodePicVectorB[j].imageSeqCallBack->frameRate <<"\tstart="<< nodePicVectorB[j].imageSeqCallBack->startFrame << "\tend=" << nodePicVectorB[j].imageSeqCallBack->endframe << endl;

				}

			}
		}
	}

	for (size_t i = 0; i < controolp.datapackString.size(); i++)
	{

		//cout << "updateControolgpack  v.id =" << controolp.vis_Anim_Bool[i].id << "\tv.vis " << controolp.vis_Anim_Bool[i].vis <<
		//	"\t objectanim="<< controolp.vis_Anim_Bool[i].objectanim  << endl;

		for (size_t j = 1; j < nodePicVectorB.size(); j++)
		{
			if (nodePicVectorB[j].id == controolp.datapackString[i].id) {
				if (nodePicVectorB[j].ito == 1)
				{
					//	cout << "updateControolgpack    OK   v.id =" << controolp.datapackString[i].id << "\tst=" << controolp.datapackString[i].st << endl;
						//nodePicVectorB[j].textst = (con.Convertp(controolp.datapackString[i].st));

							//nodePicVectorB[j].text->setText(con.Convertp(controolp.datapackString[i].st), osgText::String::ENCODING_UTF8);
					nodePicVectorB[j].text->setText(con.Convertp(osgText::String(controolp.datapackString[i].st, osgText::String::ENCODING_UTF8), nodePicVectorB[j].direction));
					//nodePicVectorB[j].text->setText(nodePicVectorB[j].UTF8toUnicode(controolp.datapackString[i].st));
				}
				j = nodePicVectorB.size();
			}

		}
	}
	for (size_t i = 0; i < controolp.datapackImage.size(); i++)
	{

		//cout << "updateControolgpack  v.id =" << controolp.vis_Anim_Bool[i].id << "\tv.vis " << controolp.vis_Anim_Bool[i].vis <<
		//	"\t objectanim="<< controolp.vis_Anim_Bool[i].objectanim  << endl;

		for (size_t j = 1; j < nodePicVectorB.size(); j++)
		{
			if (nodePicVectorB[j].id == controolp.datapackImage[i].id)
			{
				if (nodePicVectorB[j].ito == 3  &&  nodePicVectorB[j].textst != osgText::String( controolp.datapackImage[i].st) )
				{

					nodePicVectorB[j].textst = (controolp.datapackImage[i].st);
					osg::ref_ptr<osg::Image>	image = osgDB::readRefImageFile(controolp.datapackImage[i].st);
					//cout << " address image=" << controolp.datapackImage[i].st << "\timage=" << image <<"\t nodePicVectorB[j].useTextureRectangle="<<nodePicVectorB[j].useTextureRectangle<< endl;
				/*	if (image) {
						if (nodePicVectorB[j].useTextureRectangle)
						{
							osg::TextureRectangle* texture = new osg::TextureRectangle(image);
							texture->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE);
							texture->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE);
							texture->setShadowTextureMode(osg::Texture::ShadowTextureMode::ALPHA);
							nodePicVectorB[j].pictureQuad->getStateSet()->setTextureAttribute(0,
								texture,
								osg::StateAttribute::OVERRIDE);
							nodePicVectorB[j].pictureQuad->getStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
							nodePicVectorB[j].pictureQuad->getStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
						}
						else
						{

							osg::Texture2D* texture = new osg::Texture2D(image);
							texture->setResizeNonPowerOfTwoHint(false);
							texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
							texture->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE);
							texture->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE);
							texture->setShadowTextureMode(osg::Texture::ShadowTextureMode::ALPHA);
							nodePicVectorB[j].pictureQuad->getStateSet()->setTextureAttribute(0,
								texture,
								osg::StateAttribute::OVERRIDE);
							nodePicVectorB[j].pictureQuad->getStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
							nodePicVectorB[j].pictureQuad->getStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

						}
					}*/
					{
						//	cout << "image 222   OK   v.id =" << controolp.datapackImage[i].id << "\tst=" << controolp.datapackImage[i].st << endl;
							//osg::StateSet* s = nodePicVectorB[j].pictureQuad->getOrCreateStateSet(),
							//	*s1 = nodePicVectorB[j].geode->getDrawable(0)->getOrCreateStateSet(),
							//	*s3 = nodePicVectorB[j].pictureQuad->getStateSet(),
						//	*s2 = nodePicVectorB[j].geode->getDrawable(0)->getStateSet();

						osg::StateAttribute* attr = nodePicVectorB[j].pictureQuad->getOrCreateStateSet()->getTextureAttribute(0, osg::StateAttribute::TEXTURE);
						//	cout << "2image3333    OK   v.id =" << controolp.datapackImage[i].id << "\tst=" << controolp.datapackImage[i].st << "\t att=" << attr << "\t s=" << s << "\t s1=" << s1 << "\t s2=" << s2 << "\t s3=" << s3 << endl;
						if (attr)

						{
							if (nodePicVectorB[j].useTextureRectangle)
							{
								osg::TextureRectangle* texture = dynamic_cast<osg::TextureRectangle*>(attr);

								texture->setImage(image);
								//	texture->copyTexImage2D

								nodePicVectorB[j].pictureQuad->getOrCreateStateSet()->setTextureAttribute(0, texture, osg::StateAttribute::OVERRIDE);
							}
							else
							{
								osg::Texture2D* texture = dynamic_cast<osg::Texture2D*>(attr);
								texture->setImage(image);

								//	nodePicVectorB[j].geode->getDrawable(0)->getStateSet()->setTextureAttribute(0, texture, osg::StateAttribute::OVERRIDE);
								nodePicVectorB[j].pictureQuad->getOrCreateStateSet()->setTextureAttribute(0, texture, osg::StateAttribute::OVERRIDE);
							}

						}
					}
				}
				j = nodePicVectorB.size();
			}

		}
		//	for (size_t i = 0; i < controolp.drawsettingOne.size(); i++) {}


	}

	for (size_t i = 0; i < controolp.dataPackDims.size(); i++)
	{
		//	cout << " 990215 -i=" << i << endl;
		for (size_t j = 1; j < nodePicVectorB.size(); j++)
		{
			if (nodePicVectorB[j].id == controolp.dataPackDims[i].id)
			{
				//	cout << " 990209 -j=" << j <<"controolp.dataPackDims="<< controolp.dataPackDims.size()<< endl;
				nodePicVectorB[j].drawingDims = controolp.dataPackDims[i].DimsList;
				//cout << " 990209 - dim1=" << controolp.dataPackDims[i].dim1 << "\t dim2=" << controolp.dataPackDims[i].dim2 ;
				int dim1 = controolp.dataPackDims[i].dim1;
				int dim2 = controolp.dataPackDims[i].dim2;
				//cout << "/tpos[1]=" << controolp.dataPackDims[i].DimsList[dim1][dim2].pos[1] << endl;

				osg::Vec3 pos(controolp.dataPackDims[i].DimsList[dim1][dim2].pos[0], controolp.dataPackDims[i].DimsList[dim1][dim2].pos[1], controolp.dataPackDims[i].DimsList[dim1][dim2].pos[2]);
				osg::Quat quad(controolp.dataPackDims[i].DimsList[dim1][dim2].angle[0], osg::Vec3(1.0, 0.0, 0.0), controolp.dataPackDims[i].DimsList[dim1][dim2].angle[1], osg::Vec3(0.0, 1.0, 0.0), controolp.dataPackDims[i].DimsList[dim1][dim2].angle[2], osg::Vec3(0.0, 0.0, 1.0));
				osg::Vec3 scale(controolp.dataPackDims[i].DimsList[dim1][dim2].scale[0], controolp.dataPackDims[i].DimsList[dim1][dim2].scale[1], controolp.dataPackDims[i].DimsList[dim1][dim2].scale[2]);
				osg::Matrixf M;
				M = osg::Matrixf::scale(scale)*osg::Matrixf::rotate(quad)*osg::Matrixf::translate(pos);
				nodePicVectorB[j].trans->setMatrix(M);

			}
		}
	}
}

bool Osgtest01::visit(int index, vector<int> *vec)
{

	if (!((int)nodePicVectorB.size() > index)) return false;
	//	cout << "nodePicVectorB->at(i)=" << nodePicVectorB.at(index).id << "    index=" << index << "\tnodePicVectorB.at(index).parent" << nodePicVectorB.at(index).parent << endl;
	if (nodePicVectorB.at(index).parent == -1 || nodePicVectorB.at(index).parent == 0)
	{
		nodePicVectorB.at(index).parentRoot = 0;
		for each (int var in *vec)
		{
			//		cout << "var=" << var << "    index=" << index << endl;
			if (var == index) return true;
		}
		//cout << "=index=" << index << "       nodePicVectorB.at(index).parent=" << nodePicVectorB.at(index).parent << endl;
		vec->push_back(index);
		return true;
	}
	else
		//	if (nodePicVectorB.at(index).parent < (int)nodePicVectorB.size())
	{
		bool found = false;
		for (size_t i = 0; i < vec->size(); i++)
		{
			//		cout << "vec->at(i)=" << nodePicVectorB.at(i).id << "    index=" << index << "\tnodePicVectorB.at(index).parent" << nodePicVectorB.at(index).parent << endl;
			if (nodePicVectorB.at(vec->at(i)).id == nodePicVectorB.at(index).parent)
			{
				nodePicVectorB.at(index).parentRoot = vec->at(i);
			//	cout<<"980220 nodePicVectorB.at("<<index<<").parentRoot = "<<vec->at(i)<<endl;
				vec->push_back(index);
				found = true; break;
			}
			//else if (visit(nodePicVectorB, nodePicVectorB.at(index).parent, vec))
			//{ 
			//	vec->push_back(index);
			//	found = true; break; 
			//}
		}
		if (found)return true;
		else return false;// { vec->push_back(nodePicVectorB.at(index).parent); return true; }

	}
	//else {

	//	return false;
	//}

}

vector<int> Osgtest01::maketree()
{
	vector<int> vec;
	for (size_t i = 1; i < nodePicVectorB.size(); i++)
	{
		if (!visit( (int)i, &vec)) {
			std::cout << " NOde visited Error" << std::endl;
			return vec;
		}
		//	cout << "vecsie=" << vec.size();
	}
	return vec;
}


osgViewer::Viewer *Osgtest01::getViewer() const
{
	return _viewer;
}

void Osgtest01::setViewer(osgViewer::Viewer *viewer)
{
	_viewer = viewer;
}


Osgtest01::Osgtest01()


{

	_viewer = new osgViewer::Viewer();
}
void Osgtest01::building()
{
	bool useTextureRectangle = false;
	bool useShader = false;





	//    while (arguments.read("--texture2D"))   useTextureRectangle = true;
	//    while (arguments.read("--shader"))    useShader = true;

	//        bool mouseTracking = false;
	//    while (arguments.read("--mouse")) mouseTracking = true;




	bool fullscreen = false;
	//            !arguments.read("--interactive");
	bool flip = false;
	//            arguments.read("--flip");

	osg::ref_ptr<osg::Geode> geode = new osg::Geode;

	osg::StateSet* stateset = geode->getOrCreateStateSet();
	//stateset->setMode(GL_LIGHTING, osg::StateAttribute::ON);

	if (useShader)
	{
		//useTextureRectangle = false;

		static const char *shaderSourceTextureVertex = {
			"#ifdef GL_ES\n"
			"    precision highp float;\n"
			"    precision highp int;\n"
			"#endif\n"
			"varying vec4 texcoord;\n"
			"void main(void)\n"
			"{\n"
			"    texcoord = gl_MultiTexCoord0; \n"
			"    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\n"
			"}\n"
		};

		static const char *shaderSourceTextureRec = {
			"#ifdef GL_ES\n"
			"    precision highp float;\n"
			"    precision highp int;\n"
			"#endif\n"
			"uniform vec4 cutoff_color;\n"
			"uniform samplerRect movie_texture;\n"
			"varying vec4 texcoord;\n"
			"void main(void)\n"
			"{\n"
			"    vec4 texture_color = textureRect(movie_texture, texcoord.st); \n"
			"    if (all(lessThanEqual(texture_color,cutoff_color))) discard; \n"
			"    gl_FragColor = texture_color;\n"
			"}\n"
		};

		static const char *shaderSourceTexture2D = {
			"#ifdef GL_ES\n"
			"    precision highp float;\n"
			"    precision highp int;\n"
			"#endif\n"
			"uniform vec4 cutoff_color;\n"
			"uniform sampler2D movie_texture;\n"
			"varying vec4 texcoord;\n"
			"void main(void)\n"
			"{\n"
			"    vec4 texture_color = texture2D(movie_texture, texcoord.st); \n"
			"    if (all(lessThanEqual(texture_color,cutoff_color))) discard; \n"
			"    gl_FragColor = texture_color;\n"
			"}\n"
		};

		osg::Program* program = new osg::Program;


		program->addShader(new osg::Shader(osg::Shader::VERTEX, shaderSourceTextureVertex));

		program->addShader(new osg::Shader(osg::Shader::FRAGMENT,
			useTextureRectangle ? shaderSourceTextureRec : shaderSourceTexture2D));

		//	stateset->addUniform(new osg::Uniform("cutoff_color", osg::Vec4(0.1f, 0.1f, 0.1f, 1.0f)));
		//stateset->addUniform(new osg::Uniform("movie_texture", 0));

			//stateset->setAttribute(program);

	}


	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
	traits->x = 1200;
	traits->y = 0;
	traits->alpha = 1;
	traits->width = viewWidth;
	traits->height = viewHeight;
	traits->depth = 1;
	traits->windowDecoration = false;
	traits->doubleBuffer = true;
	traits->sharedContext = 0;
	traits->setInheritedWindowPixelFormat = true;
	traits->supportsResize = false;
	traits->samples = multidampleForAntialising;

	//traits->windowName = "osgViewer";

	//          traits->

	osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits.get());
	if (gc.valid())
	{
		osg::notify(osg::INFO) << "  GraphicsWindow has been created successfully." << std::endl;

		// need to ensure that the window is cleared make sure that the complete window is set the correct colour
		// rather than just the parts of the window that are under the camera's viewports
		gc->setClearColor(osg::Vec4f(0.0f, 0.0f, 0.20f, .000f));
		gc->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	else
	{
		osg::notify(osg::NOTICE) << "  GraphicsWindow has not been created successfully." << std::endl;
	}


	_viewer->setSceneData(root.get());

	osg::Vec3 LookFrom, LookAt, Up;

	LookFrom = osg::Vec3(0, 0.0, 1000);
	LookAt = osg::Vec3(0, 0, 0);
	Up = osg::Vec3(0, 1, 0);
	//_viewer->setCameraManipulator(new osgGA::TrackballManipulator(),false);
	//_viewer->getCameraManipulator()->setHomePosition(LookFrom, LookAt, Up, false);

	//Vec3d eye(1000.0, 1000.0, 0.0);
	//Vec3d center(0.0, 0.0, 0.0);
	//Vec3d up(0.0, 0.0, 1.0);

	_viewer->getCamera()->setViewMatrixAsLookAt(LookFrom, LookAt, Up);


	_viewer->getCamera()->setGraphicsContext(gc.get());
	_viewer->getCamera()->setClearColor(backcolor);
	_viewer->getCamera()->setClearDepth(1);
	_viewer->getCamera()->setViewport(0, 0, viewWidth, viewHeight);
	_viewer->getCamera()->setRenderOrder(osg::Camera::POST_RENDER);

	_viewer->home();

	_viewer->addEventHandler(new osgViewer::StatsHandler);
	_viewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);//ThreadPerContext
	{// give the scene some lighting
	//	_viewer->setLightingMode(osg::View::LightingMode::SKY_LIGHT);
		_viewer->setLightingMode(osg::View::LightingMode::HEADLIGHT);
		//root->getOrCreateStateSet()->setMode(GL_LIGHT1,osg::StateAttribute::ON);
		//root->getOrCreateStateSet()->setMode(GL_LIGHT2,osg::StateAttribute::ON);
		//root->getOrCreateStateSet()->setMode(GL_LIGHT3, osg::StateAttribute::ON);
		//root->getOrCreateStateSet()->setMode(GL_LIGHT4, osg::StateAttribute::ON);

 ////create a spot light.
	//	osg::Group* lightGroup = new osg::Group;
	//	osg::Light* myLight1 = new osg::Light;
	//	myLight1->setLightNum(0);
	//	myLight1->setPosition(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	//	myLight1->setAmbient(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
	//	myLight1->setDiffuse(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
	//	myLight1->setSpotCutoff(20.0f);
	//	myLight1->setSpotExponent(50.0f);
	//	myLight1->setDirection(osg::Vec3(0.0f, 0.0f, -1.0f));

	//	osg::LightSource* lightS1 = new osg::LightSource;
	//	lightS1->setLight(myLight1);
	//	lightS1->setLocalStateSetModes(osg::StateAttribute::ON);

	//	lightGroup->addChild(lightS1);


	//	// create a local light.
	//	osg::Light* myLight2 = new osg::Light;
	//	myLight2->setLightNum(1);
	//	myLight2->setPosition(osg::Vec4(0.0, 0.0, 0.0, 1.0f));
	//	myLight2->setAmbient(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
	//	myLight2->setDiffuse(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
	//	myLight2->setConstantAttenuation(1.0f);
	//	myLight2->setLinearAttenuation(2.0f);
	//	myLight2->setQuadraticAttenuation(2.0f );



	//	osg::LightSource* lightS2 = new osg::LightSource;
	//	lightS2->setLight(myLight2);
	//	lightS2->setLocalStateSetModes(osg::StateAttribute::ON);
	//	lightGroup->addChild(lightS2);


	//	osg::Light* myLight3 = new osg::Light;
	//	myLight2->setLightNum(2);
	//	myLight2->setPosition(osg::Vec4(0.0, 0.0, 300.0, 1.0f));
	//	myLight2->setAmbient(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
	//	myLight2->setDiffuse(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));

	//	osg::LightSource* lightS3 = new osg::LightSource;
	//	lightS2->setLight(myLight3);
	//	//lightS2->setLocalStateSetModes(osg::StateAttribute::ON);
	//	lightGroup->addChild(lightS2);
	//	lightGroup->addChild(lightS3);


	//	root->addChild(lightGroup);


	}

	typedef osgViewer::Viewer::Windows Windows;
	Windows windows;

	_viewer->getWindows(windows);
	windows[0]->setWindowName("Shayan windows name");
	windows[0]->setWindowDecoration(false);
	//windows[0]->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//windows[0]->setClearColor(osg::Vec4(0,0,0,0));

	image2 = new osg::Image;

	image2->allocateImage(viewWidth, viewHeight, 1, GL_RGBA, GL_UNSIGNED_BYTE);
	//image2->allocateImage(720, 576, 1, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV);
	_viewer->getCamera()->attach(osg::Camera::DEPTH_BUFFER, image2);

	_viewer->getCamera()->getDisplaySettings()->instance()->setNumMultiSamples(multidampleForAntialising);//antiliasing

	_viewer->realize();
	_viewer->frame();


	if (_viewer->getSceneData() == 0)
	{
		//        arguments.getApplicationUsage()->write(std::cout);
		return;
	}

	return;
}

int Osgtest01::getti()
{
	return ti;
}

void Osgtest01::view(int x, osg::Vec3d pos2)
{

}

void Osgtest01::runframe(int X, int Y, int W, int H)
{
	std::string s = "sss\\MahanRASA" + std::to_string(0) + ".png";

	_viewer->frame();
	//image = image2;
	//	return *image2;
	//osgDB::writeImageFile(*image2 , s);
	//    osgDB::writeImageFile(*image2 , "MahanRASA.png");
}


void Osgtest01::runframe2()
{

	_viewer->frame();

	//dckLinkKeyerDelegate->m_videoFrameGdi->GetBytes((void**)&pbDestData);
	//cout << "decklink22222444444..osg->image2.get()=" << osg->image2 << "\t and psdata=" << &pbDestData << endl;
	// get frame buffer pointer
	//memcpy(pbDestData, image2, 2500000);// dckLinkKeyerDelegate->theFrameBMIsize);// dckLinkKeyerDelegate->theFrameBMIsize);

	//x++;
	//std::string s = "c:\\sss\\MahanRASA" + std::to_string(x) + ".png";
	//image2->allocateImage(720, 576, 1, GL_RGBA, GL_UNSIGNED_BYTE);
	//osgDB::writeImageFile(*image2, s);
	//x++ ;
	//std::string s = "c:\\sss\\MahanRASA" + std::to_string(x) + ".png";
	//image2->allocateImage(720, 576, 1, GL_RGBA, GL_UNSIGNED_BYTE);
	//osgDB::writeImageFile(*image2, s);
//cout << "decklink2222211111..osg->image2.get()=" << image2.get() << endl;
	//_viewer->run();

	//image = image2;
	//	return *image2;


	  //  osgDB::writeImageFile(*image2 , "MahanRASA.png");

}

void Osgtest01::runframe3(BYTE * pbDestData3)
{
	_viewer->frame();
	memcpy(pbDestData3, image2->getDataPointer(), 2500000);// 
	osgDB::writeImageFile(*image2, "c:\\MahanRASA.png");
}

void Osgtest01::CaptureScreen()
{
	int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	HWND hDesktopWnd = GetDesktopWindow();
	HDC hDesktopDC = GetDC(hDesktopWnd);
	HDC hCaptureDC = CreateCompatibleDC(hDesktopDC);
	HBITMAP hCaptureBitmap = CreateCompatibleBitmap(hDesktopDC,
		nScreenWidth, nScreenHeight);
	SelectObject(hCaptureDC, hCaptureBitmap);
	BitBlt(hCaptureDC, 0, 0, nScreenWidth, nScreenHeight,
		hDesktopDC, 0, 0, SRCCOPY | CAPTUREBLT);
	//	SaveCapturedBitmap(hCaptureBitmap); //Place holder - Put your code
		//osgDB::writeImageFile(hCaptureBitmap, "MahanRASA.png");								//here to save the captured image to disk
	ReleaseDC(hDesktopWnd, hDesktopDC);
	DeleteDC(hCaptureDC);
	DeleteObject(hCaptureBitmap);
}
