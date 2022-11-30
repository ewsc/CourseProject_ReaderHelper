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
const string preferenceFile = "preferences.readerdata";
const string appVersion = "0.0";

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

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
   bool isFirstLaunch = checkFirstLaunch();
   if (isFirstLaunch) {
	   TWelcomeForm *Form = new TWelcomeForm(this);
	   Form->ShowModal();
   }
}
//---------------------------------------------------------------------------

