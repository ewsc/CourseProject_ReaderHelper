//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UserPreferences.h"
#include "Main.h"
#include "UserData.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

using namespace std;
namespace fs = std::filesystem;

extern vector<userBook> userBooks;
extern int dailyGoal;
extern int currentGoalStat;

TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

//UserData.cpp
string getNext(string currLine, int *index);

void saveFilePref() {
	ofstream preferenceFile(mainFolder + "\\" + preferenceFilePath);
	preferenceFile << "[" << to_string(dailyGoal) << "][" << to_string(currentGoalStat) << "]";
	preferenceFile.close();
}

void getDailyGoal() {
	ifstream preferenceFile(mainFolder + "\\" + preferenceFilePath);
	string line;
	int prIndex = -1;
	getline(preferenceFile, line);

	dailyGoal = StrToInt((getNext(line, &prIndex)).c_str());
	currentGoalStat = StrToInt((getNext(line, &prIndex)).c_str());
	preferenceFile.close();
}
