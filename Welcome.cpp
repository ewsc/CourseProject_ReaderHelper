//---------------------------------------------------------------------------

#include <vcl.h>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#pragma hdrstop

#include "Welcome.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

using namespace std;

const string mainFolder = "readerdata";
const string preferenceFilePath = "preferences.readerdata";

TWelcomeForm *WelcomeForm;
//---------------------------------------------------------------------------
__fastcall TWelcomeForm::TWelcomeForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TWelcomeForm::GoalEditChange(TObject *Sender)
{
	SubmitButton->Enabled = (StrToInt(GoalEdit->Text) > 0);
}

void addDataToFiles(int dailyGoal) {
	ofstream preferenceFile(mainFolder + "\\" + preferenceFilePath);
	preferenceFile << "[" << (dailyGoal) << "]";
	preferenceFile << "[" << (0) << "]";
	preferenceFile.close();
}

//---------------------------------------------------------------------------
void __fastcall TWelcomeForm::SubmitButtonClick(TObject *Sender)
{
	int dailyGoal = StrToInt(GoalEdit->Text);
	addDataToFiles(dailyGoal);
    Close();
}
//---------------------------------------------------------------------------
