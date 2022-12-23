//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "Chart.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

using namespace std;

typedef struct genreStruct {
	int amountRepeated;
	string genreName;
} genreStruct;

extern vector<userBook> userBooks;
vector<genreStruct> genreVector;

TChartForm *ChartForm;
//---------------------------------------------------------------------------
__fastcall TChartForm::TChartForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
//
void getGenreArray() {
    genreVector.clear();
	for (int i = 0; i < userBooks.size(); i++) {
		bool isExists = false;
		for (int j = 0; j < genreVector.size(); j++) {
			if (userBooks[i].genre == genreVector[j].genreName) {
				genreVector[j].amountRepeated += 1;
				isExists = true;
			}
		}
		if (!isExists) {
			genreStruct tempGenre;
			tempGenre.genreName = userBooks[i].genre;
			tempGenre.amountRepeated = 1;
			genreVector.push_back(tempGenre);
		}
	}
}

//
void drawBars(TImage *Image) {
	int xAxix = 10;
	int yAxix = 230;
    Image->Picture = NULL;

	for (int i = 0; i < genreVector.size(); i++) {
		Image->Canvas->Brush->Color = clSkyBlue;
		Image->Canvas->Rectangle(xAxix, yAxix, xAxix + 20, yAxix - (20 * (genreVector[i].amountRepeated)));
		xAxix += 30;
    }
}

void fillGenreMemo(TMemo *memo) {
	memo->Clear();
    memo->Lines->Add("Most read Genres:");
	for (int i = 0; i < genreVector.size(); i++) {
		string tempLine = "Genre: " + genreVector[i].genreName + "; Read: " + to_string(genreVector[i].amountRepeated);
        memo->Lines->Add(tempLine.c_str());
    }
}


void __fastcall TChartForm::FormActivate(TObject *Sender)
{
 	getGenreArray();
	drawBars(MainImage);
	fillGenreMemo(GenreMemo);
}
//---------------------------------------------------------------------------

