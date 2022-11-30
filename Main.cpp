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
const string appVersion = "0.0";

int dailyGoal = 0;
int currentGoalStat = 0;

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

void openAndLoadBookMarks(TMemo *openAndLoadBookMarks) {

}

void importBookMarks(TMemo *bookmarksMemo) {
	fs::path filepath = string(mainFolder + "\\" + bookmarksFilePath);
	bool filepathExists = fs::is_directory(filepath);
	if (filepathExists) {
		openAndLoadBookMarks(bookmarksMemo);
	}
	else {
		ofstream bookmarksFile(mainFolder + "\\" + bookmarksFilePath);
		bookmarksFile.close();
		bookmarksMemo->Lines->Add("Your bookmarks will appear here");
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
   setProgress(DailyProgressBar, ReportLabel1);
   setSpinEdit(LogNewEdit);
   importBookMarks(BookmarksMemo);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::LogNewEditChange(TObject *Sender)
{
	currentGoalStat = LogNewEdit->Value;
	setProgress(DailyProgressBar, ReportLabel1);
}
//---------------------------------------------------------------------------

