#include "LoaderXML.h"

bool LoaderXML::LoadLevelXML(Level* level)
{
	unique_ptr <XMLDocument> xmlDocument(new XMLDocument(PRESERVE_WHITESPACE));

	try
	{
		xmlDocument->LoadFile(filename);
	}
	catch (const exception&)
	{
		return false;
	}

	rootElement = xmlDocument->FirstChildElement();

	if (rootElement != 0 && level != NULL)
	{
		GetLevelSetting(level);
		GetBrickTypes(level->BrickTypes);
		GetBricks(level->Bricks);
	}
	else return false;

	return true;
}

void LoaderXML::GetLevelSetting(Level* level)
{
	level->RowCount = (rootElement->FindAttribute("RowCount"))->IntValue();
	level->ColumnCount = (rootElement->FindAttribute("ColumnCount"))->IntValue();
	level->RowSpacing = (rootElement->FindAttribute("RowSpacing"))->IntValue();
	level->ColumnSpacing = (rootElement->FindAttribute("ColumnSpacing"))->IntValue();
	level->BackgroundTexture = (rootElement->FindAttribute("BackgroundTexture"))->Value();
}

void LoaderXML::GetBrickTypes(vector<Brick>* brickTypes)
{
	XMLElement* brickTypesElement = rootElement->FirstChildElement("BrickTypes");

	for (XMLElement* brickType = brickTypesElement->FirstChildElement(); brickType != nullptr; brickType = brickType->NextSiblingElement())
	{
		Brick brick(
			brickType->FindAttribute("Id")->Value(),
			brickType->FindAttribute("Texture")->Value(),
			brickType->FindAttribute("HitPoints")->IntValue(),
			brickType->FindAttribute("HitSound")->Value(),
			brickType->FindAttribute("BreakSound")->Value(),
			brickType->FindAttribute("BreakScore")->IntValue()
		);

		brickTypes->push_back(brick);
	}
}

void LoaderXML::GetBricks(vector<string>* bricks) 
{
	const char* bricksElementValue = (rootElement->FirstChildElement("Bricks"))->GetText();
	string allbricks = bricksElementValue;

	int newLineLocation = 0;
	while (allbricks.size() != 0)
	{
		newLineLocation = allbricks.find('\n', 0);
		if(allbricks.substr(0, newLineLocation+1) != "\n")
			bricks->push_back(allbricks.substr(0, newLineLocation));

		newLineLocation = newLineLocation + 1;
		allbricks = allbricks.substr(newLineLocation, allbricks.size());
	}

}



