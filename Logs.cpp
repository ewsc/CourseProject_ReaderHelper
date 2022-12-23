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

string returnCurrTime() {
	time_t now = time(0);
	tm* tmNow = localtime(&now);
	char tempLine[100];
	strftime(tempLine, 50, "%H:%M:%S %d.%m.%Y", tmNow);
	return (tempLine);
}

void createLogFile() {
	ofstream logFile(mainFolder + "\\" + logFilePath);
	logFile << "ReaderHelper v." + appVersion << endl;
	logFile << "Last Launched: [" + returnCurrTime() + "]" << endl;
	logFile.close();
}

void addLogLine(string exception) {
	ofstream logFile;
	logFile.open(mainFolder + "\\" + logFilePath, ios_base::app);

	logFile << "[" << returnCurrTime() << "] " << exception << ";" << endl;
	logFile.close();
}
