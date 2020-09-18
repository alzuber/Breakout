#include "StandardIncludes.h"
#include "tinyxml2.h"
#include "Level.h"
#include "Brick.h"
#pragma once

using namespace tinyxml2;

class LoaderXML
{
public:

	LoaderXML(const LoaderXML&) = delete;

	static LoaderXML& GetLoaderInstance()
	{
		static unique_ptr<LoaderXML> loaderInstance(new LoaderXML());
		return *loaderInstance;
	}

	~LoaderXML(){}

	void SetFileName(const char* filename)
	{
		this->filename = filename;
	}

	bool LoadLevelXML(Level* level);
	

private:
	LoaderXML(){}

	const char* filename = NULL;
	XMLDocument* xmlDocument = NULL;
	XMLElement* rootElement = NULL;

	void GetLevelSetting(Level* level);
	void GetBrickTypes(vector<Brick>* brickTypes);
	void GetBricks(vector<string>* bricks);
};

