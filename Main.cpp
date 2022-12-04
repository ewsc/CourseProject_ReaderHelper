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

#include <chrono>
#include <iomanip>

#include "Main.h"
#include "Welcome.h"
#include "Bookmarks.h"
#include "Files.h"
#include "AddNew.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvSmoothProgressBar"
#pragma resource "*.dfm"
#pragma comment(lib, "shell32.lib")

using namespace std;
using namespace chrono;

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

//AddNew.cpp
void setAddNewComboBox(TComboBox *comboBox);

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

void setStringGrid(TStringGrid *grid) {
	grid->ColWidths[0] = round(grid->Width * 0.05);
	grid->ColWidths[1] = round(grid->Width * 0.3);
	grid->ColWidths[2] = round(grid->Width * 0.25);
	grid->ColWidths[3] = round(grid->Width * 0.2);
	grid->ColWidths[4] = round(grid->Width * 0.2);
}

void drawFixedRows(TStringGrid *grid) {
	grid->Cells[0][0] = "#";
	grid->Cells[1][0] = "Name";
	grid->Cells[2][0] = "Author";
	grid->Cells[3][0] = "Genre";
	grid->Cells[4][0] = "Finished";
}

void clearStringGrid(TStringGrid *grid) {
	grid->RowCount = 2;
	for (int i = 0; i < 5; i++) {
		grid->Cells[i][1] = "";
	}
}

void updateStringGrid(TStringGrid *grid) {
	clearStringGrid(grid);
	drawFixedRows(grid);
	for (int i = 0; i < userBooks.size(); i++) {
		grid->Cells[0][i+1] = i+1;
		grid->Cells[1][i+1] = userBooks[i].bookName.c_str();
		grid->Cells[2][i+1] = userBooks[i].bookAuthor.c_str();
		grid->Cells[3][i+1] = userBooks[i].genre.c_str();

		if (userBooks[i].isFinished) {
			grid->Cells[4][i+1] = "Still reading";
		}
		else {
			grid->Cells[4][i+1] = userBooks[i].finishedReading.c_str();
		}
        grid->RowCount += 1;
	}
}

void updateDisplays(TComboBox *genreComboBox, TMemo *memo, TComboBox *booksComboBox, TStringGrid *historyGrid) {
	setAddNewComboBox(genreComboBox);
	importBookMarks(memo, booksComboBox);
	updateStringGrid(historyGrid);
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
   setStringGrid(HistoryGrid);
   setProgress(DailyProgressBar, ReportLabel1);
   //setAddNewComboBox(BookGenreComboBox);
   setLogEdit(LogEdit);
   //importBookMarks(BookmarksMemo, BookList);
   //updateStringGrid(HistoryGrid);

   updateDisplays(BookGenreComboBox, BookmarksMemo, BookList, HistoryGrid);
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

void clearAllInputs(TEdit *BookNameEdit1, TEdit *BookAuthorEdit1, TEdit *CustomBookGenre, TComboBox *BookGenreComboBox) {
	BookNameEdit1->Text = "";
	BookAuthorEdit1->Text = "";
	CustomBookGenre->Text = "";
    BookGenreComboBox->ItemIndex = -1;
}

void __fastcall TMainForm::AddNewButton1Click(TObject *Sender)
{
	userBook newBook;
	newBook.bookName = returnStr(BookNameEdit1->Text);
	newBook.bookAuthor = returnStr(BookAuthorEdit1->Text);
	if (CustomBookGenre->Text != "") {
		newBook.genre = returnStr(CustomBookGenre->Text);
	}
	else {
		newBook.genre = returnStr(BookGenreComboBox->Text);
	}

	time_t now = time(0);
	string startedReadingTime = ctime(&now);

	startedReadingTime[startedReadingTime.length() - 1] = '\0';
	newBook.startedReading = startedReadingTime;

	newBook.finishedReading = "0";
	newBook.isFinished = false;
    newBook.bookmark = 0;

	userBooks.push_back(newBook);
	rewriteFileData();
	clearAllInputs(BookNameEdit1, BookAuthorEdit1, CustomBookGenre, BookGenreComboBox);
	updateDisplays(BookGenreComboBox, BookmarksMemo, BookList, HistoryGrid);
}
//---------------------------------------------------------------------------



