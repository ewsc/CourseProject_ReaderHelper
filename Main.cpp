//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#pragma hdrstop
#include <ShlObj.h>
#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <vector>

#include "Main.h"
#include "Welcome.h"
#include "Bookmarks.h"
#include "Files.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvSmoothProgressBar"
#pragma resource "*.dfm"
#pragma comment(lib, "shell32.lib")

using namespace std;

const string mainFolder = "readerdata";
const string logFilePath = "logs.readerdata";
const string preferenceFilePath = "preferences.readerdata";
const string userDataPath = "userdata.readerdata";
const string appVersion = "0.0";

int dailyGoal = 0;
int currentGoalStat = 0;

vector<userBook> userBooks;

//Bookmarks.cpp
void updateMemo(TMemo *bookmarksMemo);
void importBookMarks(TMemo *bookmarksMemo, TComboBox *comboBox);
void fillComboBox(TComboBox *comboBox);

//Files.cpp
void createLogFile();
bool checkFirstLaunch();
void rewriteFileData();
void getDailyGoal();
void getUserData();
void saveFilePref();

TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void setProgress(TAdvSmoothProgressBar *progressBar, TLabel *reportLabel) {
	double d_percentage;
	d_percentage = ((double)currentGoalStat / dailyGoal);
	d_percentage = d_percentage * 100;
	int percentage = d_percentage;
	progressBar->Position = percentage;
	reportLabel->Caption = ("Daily progress: " + IntToStr(currentGoalStat) + " of " + IntToStr(dailyGoal) + " (" + percentage + "%)").c_str();
}

void setLogEdit(TEdit *edit) {
	edit->Text = 1;
}

void setStringGrid(TStringGrid *grid, int clWidth) {
    grid->Width = clWidth;
	grid->ColWidths[0] = round(clWidth * 0.1);
	grid->ColWidths[1] = round(clWidth * 0.3);
	grid->ColWidths[2] = round(clWidth * 0.3);
	grid->ColWidths[3] = round(clWidth * 0.3);
}

void drawFixedRows(TStringGrid *grid) {
	grid->Cells[0][0] = "#";
	grid->Cells[1][0] = "Name";
	grid->Cells[2][0] = "Started at";
	grid->Cells[3][0] = "Finished at";
}

void clearStringGrid(TStringGrid *grid) {
	grid->RowCount = 2;
	for (int i = 0; i < 4; i++) {
		grid->Cells[i][1] = "";
		grid->Cells[i][1] = "";
		grid->Cells[i][1] = "";
		grid->Cells[i][1] = "";
	}
}

void updateStringGrid(TStringGrid *grid) {
	clearStringGrid(grid);
	drawFixedRows(grid);
	for (int i = 0; i < userBooks.size(); i++) {
		grid->Cells[0][i+1] = i+1;
		grid->Cells[1][i+1] = userBooks[i].bookName.c_str();
		if (userBooks[i].startedReading == "0") {
			grid->Cells[2][i+1] = "Not started yet";
		}
		else {
			grid->Cells[2][i+1] = userBooks[i].startedReading.c_str();
		}

		if (userBooks[i].finishedReading == "0") {
			grid->Cells[3][i+1] = "Not finished yet";
		}
		else {
			grid->Cells[3][i+1] = userBooks[i].finishedReading.c_str();
		}
        grid->RowCount += 1;
	}
}


void __fastcall TMainForm::FormCreate(TObject *Sender)
{
   bool isFirstLaunch = checkFirstLaunch();
   if (isFirstLaunch) {
	   TWelcomeForm *Form = new TWelcomeForm(this);
	   Form->ShowModal();
   }
   getDailyGoal();
   getUserData();
   setStringGrid(HistoryGrid, HistorySheet->Width);
   setProgress(DailyProgressBar, ReportLabel1);
   setLogEdit(LogEdit);
   importBookMarks(BookmarksMemo, BookList);
   updateStringGrid(HistoryGrid);
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::BookListChange(TObject *Sender)
{
	BookmarkEdit->Text = userBooks[BookList->ItemIndex].bookmark;
}
//---------------------------------------------------------------------------

string returnStr(AnsiString output) {
	const size_t len = (output.Length() + 1) * sizeof(System::AnsiChar);
	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
	if (hMem) {
		memcpy(GlobalLock(hMem), output.c_str(), len);
	}
	return output.c_str();
}

void __fastcall TMainForm::EditButtonClick(TObject *Sender)
{
	string output = returnStr(BookmarkEdit->Text);
	userBooks[BookList->ItemIndex].bookmark = stoi(output.c_str());
	updateMemo(BookmarksMemo);
	rewriteFileData();
	BookList->ItemIndex = -1;
    BookmarkEdit->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::LogUpButtonClick(TObject *Sender)
{
	string output = returnStr(LogEdit->Text);
	currentGoalStat += stoi(output.c_str());
	setLogEdit(LogEdit);
	saveFilePref();
	setProgress(DailyProgressBar, ReportLabel1);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::LogDownButtonClick(TObject *Sender)
{
	string output = returnStr(LogEdit->Text);
	currentGoalStat -= stoi(output.c_str());
	setLogEdit(LogEdit);
	saveFilePref();
	setProgress(DailyProgressBar, ReportLabel1);
}
//---------------------------------------------------------------------------

