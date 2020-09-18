#include "Layout.h"

vector<string> layout;

void Layout::asignTextures()
{
	soft = loader.LoadTexture("Assets/Breakout/Soft.png");
	medium = loader.LoadTexture("Assets/Breakout/Medium.png");
	hard = loader.LoadTexture("Assets/Breakout/Hard.png");
	impenetrable = loader.LoadTexture("Assets/Breakout/Impenetrable.png");
}

int matrixRow = 0;
int matrixCol = 0;
int columnSpacing = 0;
int rowSpacing = 0;

void Layout::LoadLayout(Level* level)
{
	matrixRow = level->RowCount;
	matrixCol = level->ColumnCount;
	columnSpacing = level->ColumnSpacing;
	rowSpacing =level->RowSpacing;

	//resize matrix
	layout.resize(level->RowCount);
	for (int i = 0; i < level->RowCount; ++i)
	{
		layout[i].resize(level->ColumnCount);
	}

	//set matrix values
	int counterRow = 0;
	for(string row : *level->Bricks)
	{ 
		int counterColumn = 0;
		for (int i = 0; i < row.size(); i++)
		{
			switch (row[i])
			{
			case 'S':
				layout[counterRow][counterColumn] = 1;
				counterColumn++;
				break;

			case 'M':
				layout[counterRow][counterColumn] = 2;
				counterColumn++;
				break;

			case 'H':
				layout[counterRow][counterColumn] = 3;
				counterColumn++;
				break;

			case 'I':
				layout[counterRow][counterColumn] = 4;
				counterColumn++;
				break;
			}
		}

		counterRow++;
	}
}

void Layout::DrawLayout()
{
	/*for (int i = 0; i < matrixRow; i++)
	{
		for (int j = 0; j < matrixCol; j++)
		{
			cout << layout[i][j];
		}
		cout << endl;
	}*/

	int type = 0;

	for (int i = 0; i < matrixRow; i++)
	{
		for (int j = 0; j < matrixCol; j++)
		{
			type = layout[i][j];
			dest.x = j * (dest.w+ columnSpacing);
			dest.y = i * (dest.h+ rowSpacing);

			switch (type)
			{
			case 1:
				loader.Draw(soft,src, dest);
				break;

			case 2:
				loader.Draw(medium, src, dest);
				break;

			case 3:
				loader.Draw(hard, src, dest);
				break;

			case 4:
				loader.Draw(impenetrable, src, dest);
				break;

			default:
				break;
			}
		}
	}
}
