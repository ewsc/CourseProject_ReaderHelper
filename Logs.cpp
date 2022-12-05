#include <vcl.h>
#pragma hdrstop

#include "Logs.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

using namespace std;

TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void createLogFile() {
	time_t now = time(0);
	string launchTime = ctime(&now);
	launchTime[launchTime.length() - 1] = ' ';

	ofstream logFile(mainFolder + "\\" + logFilePath);
	logFile << "ReaderHelper v." + appVersion << endl;
	logFile << "Last Launched: [" + launchTime + "]" << endl;
	logFile.close();
}

void addLogLine(string exception) {
	ofstream logFile;
	logFile.open(mainFolder + "\\" + logFilePath, ios_base::app);

    time_t now = time(0);
	string errTime = ctime(&now);
	errTime[errTime.length() - 1] = ' ';

	logFile << "[" << errTime << "]" << exception << ";" << endl;
	logFile.close();
}
