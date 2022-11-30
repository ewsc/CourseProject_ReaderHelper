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
#pragma resource "*.dfm"
#pragma comment(lib, "shell32.lib")

using namespace std;

const string mainFolder = "readerdata";
const string logFilePath = "logs.readerdata";
const string preferenceFilePath = "preferences.readerdata";
const string bookmarksFilePath = "bookmarks.readerdata";
const string booksFilePath = "books.readerdata";
const string appVersion = "0.0";

int dailyGoal = 0;
int currentGoalStat = 0;
vector<string> bookNames;
vector<string> bookmarks;

//Bookmarks.cpp
void updateMemo(TMemo *bookmarksMemo);
void importBookMarks(TMemo *bookmarksMemo, TComboBox *comboBox);
void loadBookmarks();
void loadBooks();
void fillComboBox(TComboBox *comboBox);

//Files.cpp
void createLogFile();
bool checkFirstLaunch();
void updateBookmarksFileData();
void getDailyGoal();

TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void setProgress(TAdvSmoothProgressBar *progressBar, TLabel *reportLabel) {
	double d_percentage = currentGoalStat / dailyGoal;
	d_percentage = d_percentage * 100;
	int percentage = round(d_percentage);

	progressBar->Position = percentage;
	reportLabel->Caption = ("Daily progress: " + IntToStr(currentGoalStat) + " of " + IntToStr(dailyGoal) + " (" + IntToStr(percentage) + "%)").c_str();
}

void setSpinEdit(TSpinEdit *spinEdit) {
	spinEdit->Value = currentGoalStat;
}

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
   bool isFirstLaunch = checkFirstLaunch();
   if (isFirstLaunch) {
	   TWelcomeForm *Form = new TWelcomeForm(this);
	   Form->ShowModal();
   }
   getDailyGoal();
   setProgress(DailyProgressBar, ReportLabel1);
   setSpinEdit(LogNewEdit);
   importBookMarks(BookmarksMemo, BookList);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::LogNewEditChange(TObject *Sender)
{
	currentGoalStat = LogNewEdit->Value;
	setProgress(DailyProgressBar, ReportLabel1);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BookListChange(TObject *Sender)
{
	BookmarkEdit->Text = bookmarks[BookList->ItemIndex].c_str();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::EditButtonClick(TObject *Sender)
{
	AnsiString output = BookmarkEdit->Text;
	const size_t len = (output.Length() + 1) * sizeof(System::AnsiChar);
	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
	if (hMem) {
		memcpy(GlobalLock(hMem), output.c_str(), len);
	}
	bookmarks[BookList->ItemIndex] = output.c_str();
	updateMemo(BookmarksMemo);
	updateBookmarksFileData();
	BookList->ItemIndex = -1;
    BookmarkEdit->Text = "";
}
//---------------------------------------------------------------------------

