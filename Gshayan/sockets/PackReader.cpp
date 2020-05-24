#include "PackReader.h"
#include <osgDB/fstream>

bool PackReader::decode(string text, SettingPack &s, ControolPack &c)
{


	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(text, root);

	if (!parsingSuccessful)
	{
		cout << "Error parsing the string" << endl;
		ofstream myfile;
		myfile.open("s:\\example.txt");
		myfile << text;
		myfile.close();

		return false;
	}

	//cout << root << "This is h1" << endl;
	if (root.type() == Json::objectValue) {
		int x = root.get("x", 0).asInt();
		if (x == 0) {
			s.updated = false;
			s.backcolor = root["settingpack"].get("backcolor", 0).asInt();
			s.SeetingCode = root["settingpack"].get("SeetingCode", 0).asInt();
			s.strok = root["settingpack"].get("strok", 0).asInt();
			s.font = root["settingpack"].get("font", "ARIAL").asString();
			s.fontpath = (root["settingpack"].get("fontpath", "ARIAL").asString());
			s.exit = (root["settingpack"].get("exit", 0).asInt());
			s.screenDim = new int[4];
			for (size_t i = 0; i < 4; i++)
			{
				s.screenDim[i] = root["settingpack"]["scr"][i].asInt();
			}
			for (size_t i = 0; i < 13; i++)
			{
				s.camera[i] = root["settingpack"]["cam"][i].asDouble();
			}

			//	cout << "s.s.screenDim[i]" << s.screenDim[0] << "   \ty=" << s.screenDim[1] << endl;

			int id = 0;
			int dimSsize, dimsize;
			vector<SettingPack::DrawSettingS>drawsettingList;
			for (uint8_t i = 0; i < root["settingpack"]["drawSettingS"].size(); i++) {
				SettingPack::DrawSettingS d;
				d.id = root["settingpack"]["drawSettingS"][i].get("id", 0).asInt();
				//d.isImage = root["settingpack"]["drawSettingS"][i].get("imagevisiblity", false).asBool();
				d.vis = root["settingpack"]["drawSettingS"][i].get("vis", false).asBool();
				d.ito = root["settingpack"]["drawSettingS"][i].get("ito", 0).asInt();
				//	cout << "981105    settinh reader  draw = " << i<< "    ito"<< d.ito << endl;
				d.parent = root["settingpack"]["drawSettingS"][i].get("parent", 0).asInt();
				//UtfConverter::FromUtf8
				d.text1 = ((root["settingpack"]["drawSettingS"][i].get("text1", 0).asString()));
				d.image = (root["settingpack"]["drawSettingS"][i].get("image", 0).asString());
				d.font = root["settingpack"]["drawSettingS"][i].get("font", 0).asString();
				d.fback = root["settingpack"]["drawSettingS"][i].get("fback", false).asBool();
				d.fItalic = root["settingpack"]["drawSettingS"][i].get("fItalic", false).asBool();
				d.fBold = root["settingpack"]["drawSettingS"][i].get("fBold", false).asBool();
				d.imageSequency = root["settingpack"]["drawSettingS"][i].get("imageSequency", false).asBool();
				d.seqLoop = root["settingpack"]["drawSettingS"][i].get("seqLoop", false).asBool();
				d.anloop = root["settingpack"]["drawSettingS"][i].get("anLoop", false).asBool();
				d.AnimateRate = root["settingpack"]["drawSettingS"][i].get("AnimateRate", 100).asInt();
				d.bezierLinear = root["settingpack"]["drawSettingS"][i].get("bezierLinear", 0).asInt();

				d.alignment = root["settingpack"]["drawSettingS"][i].get("align", 0).asInt();
				d.CharacterSize = root["settingpack"]["drawSettingS"][i].get("cSize", 0).asInt();
				d.fontResulation = root["settingpack"]["drawSettingS"][i].get("fRes", 0).asInt();
				d.fontMAxwide = root["settingpack"]["drawSettingS"][i].get("fmax", 0).asInt();


				dimSsize = root["settingpack"]["drawSettingS"][i]["drawingDimsList"].size();

				vector<SettingPack::drawSettingDims>dims;
				vector<vector<SettingPack::drawSettingColors>> drawingColorList;
				for (int j = 0; j < dimSsize; j++)
				{
					dims.clear();
					drawingColorList.clear();
					dimsize = root["settingpack"]["drawSettingS"][i]["drawingDimsList"][j].size();
					SettingPack::drawSettingDims dim;
					for (int k = 0; k < dimsize; k++)
					{
						dim.frames = root["settingpack"]["drawSettingS"][i]["drawingDimsList"][j][k].get("frames", 0).asInt();
						dim.opac = root["settingpack"]["drawSettingS"][i]["drawingDimsList"][j][k].get("opac", 0).asInt();
						dim.strokC = root["settingpack"]["drawSettingS"][i]["drawingDimsList"][j][k].get("strokC", 0).asInt();
						dim.textC = root["settingpack"]["drawSettingS"][i]["drawingDimsList"][j][k].get("textC", 0).asInt();
						dim.acceleratein = root["settingpack"]["drawSettingS"][i]["drawingDimsList"][j][k].get("acceleratein", 0).asInt();
						dim.accelerateout = root["settingpack"]["drawSettingS"][i]["drawingDimsList"][j][k].get("accelerateout", 0).asInt();
						for (size_t l = 0; l < 3; l++)
						{
							dim.pos[l] = root["settingpack"]["drawSettingS"][i]["drawingDimsList"][j][k]["pos"][l].asDouble();// .get("pos", 0).asInt();
							dim.scale[l] = root["settingpack"]["drawSettingS"][i]["drawingDimsList"][j][k]["scale"][l].asDouble();
							dim.angle[l] = (root["settingpack"]["drawSettingS"][i]["drawingDimsList"][j][k]["angle"][l].asDouble()) *M_PI / 180.0;
						}
						dims.push_back(dim);
					}
					d.drawingDimsList.push_back(dims);
				}
				drawsettingList.push_back(d);
			}
			s.drawSettingS = drawsettingList;
		}
		else if (x == 1) {
			//	cout << "   before pack reader  size = " << c.vis_Anim_Bool.size() << endl;
			for (uint8_t i = 0; i < root["controolPack"]["vis_Anim_Bool"].size(); i++) {
				ControolPack::Vis_Anim_Bool v;
				v.id = root["controolPack"]["vis_Anim_Bool"][i].get("id", 0).asInt();
				v.vis = root["controolPack"]["vis_Anim_Bool"][i].get("vis", false).asBool();
				v.visactive = root["controolPack"]["vis_Anim_Bool"][i].get("vac", false).asBool();
				v.objectanim = root["controolPack"]["vis_Anim_Bool"][i].get("ani", false).asBool();
				v.motionDimIndex = root["controolPack"]["vis_Anim_Bool"][i].get("dim", 0).asInt();
				v.colorAnim = root["controolPack"]["vis_Anim_Bool"][i].get("col", false).asBool();
				v.imagePlay = root["controolPack"]["vis_Anim_Bool"][i].get("seq", false).asBool();
				c.vis_Anim_Bool.push_back(v);
				//	cout << " vismoid= " << v.id << "\tvis= " << v.vis << "\tanim= " << v.objectanim << "\\imagePlay= " << v.imagePlay << endl;
			}

			for (uint8_t i = 0; i < root["controolPack"]["datapackString"].size(); i++) {
				ControolPack::DataPackString v;
				v.id = root["controolPack"]["datapackString"][i].get("id", 0).asInt();
				v.st = (root["controolPack"]["datapackString"][i].get("st", "").asString());
				c.datapackString.push_back(v);
				//cout << " datapackString= " << v.id << "\st= " << v.st << endl;
			}

			for (uint8_t i = 0; i < root["controolPack"]["datapackImage"].size(); i++)
			{
				ControolPack::DataPackString v;
				v.id = root["controolPack"]["datapackImage"][i].get("id", 0).asInt();
				v.st = (root["controolPack"]["datapackImage"][i].get("st", "").asString());
				c.datapackImage.push_back(v);
				//	cout << " datapackImage= " << v.id << "\st= " << v.st << endl;
			}


			for (uint8_t i = 0; i < root["controolPack"]["dataPackanimationStartEnds"].size(); i++) {
				ControolPack::DataPackanimationStartEnd v;
				v.id = root["controolPack"]["dataPackanimationStartEnds"][i].get("id", 0).asInt();
				v.animRate = root["controolPack"]["dataPackanimationStartEnds"][i].get("animRate", 0).asInt();
				v.end = root["controolPack"]["dataPackanimationStartEnds"][i].get("end", 0).asInt();
				v.start = root["controolPack"]["dataPackanimationStartEnds"][i].get("start", 0).asInt();
				v.live = root["controolPack"]["dataPackanimationStartEnds"][i].get("live", false).asBool();
				v.liveEn = root["controolPack"]["dataPackanimationStartEnds"][i].get("liveEn", false).asBool();
				v.play = root["controolPack"]["dataPackanimationStartEnds"][i].get("play", false).asBool();
				v.playEn = root["controolPack"]["dataPackanimationStartEnds"][i].get("playEn", false).asBool();
				v.sequenceNotMovie = root["controolPack"]["dataPackanimationStartEnds"][i].get("sequenceNotMovie", false).asBool();
				v.startEndEnable = root["controolPack"]["dataPackanimationStartEnds"][i].get("startEndEnable", false).asBool();
				c.dataPackanimationStartEnds.push_back(v);
				//	cout << "981105  id=" << v.id << "\t en=" << v.startEndEnable << "\tstart=" << v.start << "\t end=" << v.end << endl;
			}



			int dimSsize = root["controolPack"]["dataPackDimsLists"].size();
			ControolPack::DataPackDims dims;
			c.dataPackDims.clear();
			int dimsize = 0, dimsize2=0;
			SettingPack::drawSettingDims dim;
			vector<SettingPack::drawSettingDims > dim2;
			for (int j = 0; j < dimSsize; j++)
			{
				//	cout <<"j="<<j<< " _2 ";
				dims.DimsList.clear();
				//	drawingColorList.clear();
				dimsize = root["controolPack"]["dataPackDimsLists"][j]["drawingDimsList"].size();
				//	 cout << "990211 _3 dimsize="<< dimsize<<endl;


				dims.id = root["controolPack"]["dataPackDimsLists"][j].get("id", 0).asInt();
				dims.dim1 = root["controolPack"]["dataPackDimsLists"][j].get("dim1", 0).asInt();
				dims.dim2 = root["controolPack"]["dataPackDimsLists"][j].get("dim2", 0).asInt();
				for (int k = 0; k < dimsize; k++)
				{
					dimsize2 = root["controolPack"]["dataPackDimsLists"][j]["drawingDimsList"][k].size();
					for (int m = 0; m < dimsize2; m++)
					{
					//cout << "k=" << k << "    m= "<<m<<endl;
					dim.frames = root["controolPack"]["dataPackDimsLists"][j]["drawingDimsList"][k][m].get("frames", 0).asInt();
				//	cout << " _5 ";
					dim.opac = root["controolPack"]["dataPackDimsLists"][j]["drawingDimsList"][k][m].get("opac", 0).asInt();
					dim.strokC = root["controolPack"]["dataPackDimsLists"][j]["drawingDimsList"][k][m].get("strokC", 0).asInt();
					dim.textC = root["controolPack"]["dataPackDimsLists"][j]["drawingDimsList"][k][m].get("textC", 0).asInt();
					dim.acceleratein = root["controolPack"]["dataPackDimsLists"][j]["drawingDimsList"][k][m].get("acceleratein", 0).asInt();
					dim.accelerateout = root["controolPack"]["dataPackDimsLists"][j]["drawingDimsList"][k][m].get("accelerateout", 0).asInt();
					//cout << " _6 ";
					for (size_t l = 0; l < 3; l++)
					{
					//	cout << "l=" << l << " _5 ";
						dim.pos[l] = root["controolPack"]["dataPackDimsLists"][j]["drawingDimsList"][k][m]["pos"][l].asDouble();// .get("pos", 0).asInt();
						dim.scale[l] = root["controolPack"]["dataPackDimsLists"][j]["drawingDimsList"][k][m]["scale"][l].asDouble();
						dim.angle[l] = (root["controolPack"]["dataPackDimsLists"][j]["drawingDimsList"][k][m]["angle"][l].asDouble()) *M_PI / 180.0;
					}
					dim2.push_back(dim);
					
				}
					
									dims.DimsList.push_back(dim2);
				dim2.clear();
					
			}
			c.dataPackDims.push_back(dims);
				
			}

		}

		return true;
	}
	return false;
}

string PackReader::texttoUnicode(string text)
{
	string f = "";
	int t = 0;
	for (size_t i = 0; i < text.size(); i++)
	{
		if (text[i] & 0xc0 == 0) f = f + text[i];
		else if (text[i] && (0b110 == 1)) {
			t = text[i] & 0b001;
			i++;
			t = t << 6 + text[i] & 0b00111111;
			f = f + "\\u";

		}
	}
	return string();
}


wchar_t*  PackReader::UTF8toUnicode(const string& s)
{
	wchar_t* ws;
	wchar_t wc;
	for (int i = 0; i < s.length(); )
	{
		char c = s[i];
		cout << "  c=" << c;
		if ((c & 0x80) == 0)
		{
			wc = c;
			++i;
		}
		else if ((c & 0xE0) == 0xC0)
		{
			wc = (s[i] & 0x1F) << 6;
			wc |= (s[i + 1] & 0x3F);
			i += 2;
		}
		else if ((c & 0xF0) == 0xE0)
		{
			wc = (s[i] & 0xF) << 12;
			wc |= (s[i + 1] & 0x3F) << 6;
			wc |= (s[i + 2] & 0x3F);
			i += 3;
		}
		else if ((c & 0xF8) == 0xF0)
		{
			wc = (s[i] & 0x7) << 18;
			wc |= (s[i + 1] & 0x3F) << 12;
			wc |= (s[i + 2] & 0x3F) << 6;
			wc |= (s[i + 3] & 0x3F);
			i += 4;
		}
		else if ((c & 0xFC) == 0xF8)
		{
			wc = (s[i] & 0x3) << 24;
			wc |= (s[i] & 0x3F) << 18;
			wc |= (s[i] & 0x3F) << 12;
			wc |= (s[i] & 0x3F) << 6;
			wc |= (s[i] & 0x3F);
			i += 5;
		}
		else if ((c & 0xFE) == 0xFC)
		{
			wc = (s[i] & 0x1) << 30;
			wc |= (s[i] & 0x3F) << 24;
			wc |= (s[i] & 0x3F) << 18;
			wc |= (s[i] & 0x3F) << 12;
			wc |= (s[i] & 0x3F) << 6;
			wc |= (s[i] & 0x3F);
			i += 6;
		}
		ws += wc;
		//	cout << "  wc=" << wc<<endl;
	}

	return ws;
}


PackReader::PackReader()
{
}


PackReader::~PackReader()
{
}
