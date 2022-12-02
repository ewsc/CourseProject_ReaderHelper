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

extern vector<userBook> userBooks;

extern int dailyGoal;
extern int currentGoalStat;

TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}

string getNext(string currLine, int *index) {
	*index += + 2;
	string result = "";
	while(currLine[*index] != ']') {
		result = result + currLine[*index];
		(*index)++;
	}
	return result;
}

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

void createLogFile() {
	time_t now = time(0);
	string launchTime = ctime(&now);

	ofstream logFile(mainFolder + "\\" + logFilePath);
	logFile << "ReaderHelper v." + appVersion << endl;
	logFile << "Last Launched: [" + launchTime + "]" << endl;
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

void rewriteFileData() {
	ofstream userDataFile(mainFolder + "\\" + userDataPath);
	for (int i = 0; i < userBooks.size(); i++) {
		string tempString = "[" + userBooks[i].bookName + "][" + to_string(userBooks[i].bookmark) + "][" + userBooks[i].startedReading + "][" + userBooks[i].finishedReading + "][" + "F" + "]";
		userDataFile << tempString << endl;
	}
	userDataFile.close();
}

void distributeString(string currLine) {
	int index = -1;
	string newBookName = getNext(currLine, &index);
	string newBookmarkPage = getNext(currLine, &index);
	string newStartedReading = getNext(currLine, &index);
	string newFinishedReading = getNext(currLine, &index);
	string finished_reading = getNext(currLine, &index);

	userBook newBook;
	newBook.bookName = newBookName;
	newBook.bookmark = stoi(newBookmarkPage);
	newBook.startedReading = newStartedReading;
	newBook.finishedReading = newFinishedReading;
	if (finished_reading == "F") {
		newBook.isFinished = true;
	}
	else if (finished_reading == "N") {
        newBook.isFinished = false;
	}
    userBooks.push_back(newBook);
}

void getUserData() {
	ifstream userDataFile(mainFolder + "\\" + userDataPath);
	string currLine;
	while (getline(userDataFile, currLine)) {
		distributeString(currLine);
	}
	userDataFile.close();
}
//---------------------------------------------------------------------------
