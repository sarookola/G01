#include "SettingPack.h"



void SettingPack::clear()
{
	updated = true;
	//drawSettingS.clear();
}

SettingPack::SettingPack()
{
	camera = new double[13];
	updated = false;
}


SettingPack::~SettingPack()
{
}
