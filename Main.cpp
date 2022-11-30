//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#pragma hdrstop
#include <ShlObj.h>
#include <string>
#include <direct.h>
#include <sys/stat.h>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <vector>

#include "Main.h"
#include "Welcome.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvSmoothGauge"
#pragma link "AdvSmoothProgressBar"
#pragma link "AdvProgr"
#pragma link "AdvCircularProgress"
#pragma link "AdvProgressBar"
#pragma resource "*.dfm"
#pragma comment(lib, "shell32.lib")

using namespace std;
namespace fs = std::filesystem;

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

TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void createLogFile() {
	time_t now = time(0);
	string launchTime = ctime(&now);

	ofstream logFile(mainFolder + "\\" + logFilePath);
	logFile << "ReaderHelper v." + appVersion << endl;
	logFile << "Last Launched: " + launchTime;
	logFile.close();
}

bool checkFirstLaunch() {

	bool isFirstLaunch;
	struct stat sb;

	fs::path filepath = string(mainFolder + "\\" + logFilePath);
	bool filepathExists = fs::is_directory(filepath.parent_path());
	if (filepathExists) {
		isFirstLaunch = false;
	}
	else {
		isFirstLaunch = true;
		fs::create_directory(mainFolder);
	}
	createLogFile();
	return isFirstLaunch;
}

void getDailyGoal() {
	ifstream preferenceFile(mainFolder + "\\" + preferenceFilePath);
	string goals;
	getline(preferenceFile, goals);
	dailyGoal = StrToInt((goals).c_str());
	getline(preferenceFile, goals);
	currentGoalStat = StrToInt((goals).c_str());
	preferenceFile.close();
}

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

void loadBooks() {
	ifstream booksFile(mainFolder + "\\" + booksFilePath);
	string line;
	while (getline(booksFile, line)) {
		bookNames.push_back(line);
	}
	booksFile.close();
}

void loadBookmarks() {
	ifstream bookmarksFile(mainFolder + "\\" + bookmarksFilePath);
	string line;
	while (getline(bookmarksFile, line)) {
		bookmarks.push_back(line);
	}
	bookmarksFile.close();
}

void fillComboBox(TComboBox *comboBox) {
    comboBox->Items->Clear();
	for (int i = 0; i < bookNames.size(); i++) {
        comboBox->Items->Add(bookNames[i].c_str());
	}
}

void updateMemo(TMemo *bookmarksMemo) {
	bookmarksMemo->Lines->Clear();
	for (int i = 0; i < bookNames.size(); i++) {
		bookmarksMemo->Lines->Add(("[" + bookNames[i] + "] Page: " + bookmarks[i]).c_str());
    }
}

void importBookMarks(TMemo *bookmarksMemo, TComboBox *comboBox) {
	loadBooks();
	loadBookmarks();
	fillComboBox(comboBox);
	updateMemo(bookmarksMemo);
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

void updateBookmarksFileData() {
	ofstream bookmarksFile(mainFolder + "\\" + bookmarksFilePath);
	for (int i = 0; i < bookmarks.size(); i++) {
		bookmarksFile << bookmarks[i] << endl;
	}
    bookmarksFile.close();
}

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

