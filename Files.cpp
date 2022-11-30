//---------------------------------------------------------------------------

#include <vcl.h>
#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#pragma hdrstop

#include "Files.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

using namespace std;
namespace fs = std::filesystem;

extern vector<string> bookNames;
extern vector<string> bookmarks;
extern int dailyGoal;
extern int currentGoalStat;

const string mainFolder = "readerdata";
const string logFilePath = "logs.readerdata";
const string preferenceFilePath = "preferences.readerdata";
const string bookmarksFilePath = "bookmarks.readerdata";
const string booksFilePath = "books.readerdata";
const string appVersion = "0.0";

TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
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

void updateBookmarksFileData() {
	ofstream bookmarksFile(mainFolder + "\\" + bookmarksFilePath);
	for (int i = 0; i < bookmarks.size(); i++) {
		bookmarksFile << bookmarks[i] << endl;
	}
	bookmarksFile.close();
}
//---------------------------------------------------------------------------
