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
#include <exception>
#include "bass/bass.h"
#pragma comment (lib,"bassx.lib")

#include "Main.h"
#include "Logs.h"
#include "UserData.h"
#include "UserControls.h"
#include "Edit.h"
#include "Chart.h"
#include "AudioStream.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvSmoothProgressBar"
#pragma link "AdvSmoothTabPager"
#pragma link "AdvSmoothSlider"
#pragma link "AdvSmoothSlider"
#pragma link "AdvSmoothTabPager"
#pragma resource "*.dfm"
#pragma comment(lib, "shell32.lib")

using namespace std;
namespace fs = std::filesystem;

const string mainFolder = "readerdata";
const string logFilePath = "logs.readerdata";
const string userDataPath = "userdata.readerdata";
const string audioStreamsPath = "streampath.readerdata";
const string appVersion = "0.9";

int rowId;

vector<userBook> userBooks;

//Logs.cpp
void createLogFile();
void addLogLine(string exception);

//UserData.cpp
bool genreIsAlreadyAdded();
string getNext(string currLine, int *index);
void rewriteFileData();
void distributeString(string currLine);
void getUserData();
void __fastcall AddNewButton1Click(TObject *Sender);

//UserControls.cpp
void setAddNewComboBox(TComboBox *comboBox, string selected);
void fillComboBox(TComboBox *comboBox);
void setProgress(TAdvSmoothProgressBar *progressBar, TLabel *reportLabel);
void setLogEdit(TEdit *edit);
void setStringGrid(TStringGrid *grid, int clWIdth, int gridWidth, int height);
void drawFixedRows(TStringGrid *grid);
void clearStringGrid(TStringGrid *grid);
void updateStringGrid(TStringGrid *grid);
void clearAllInputs(TEdit *BookNameEdit1, TEdit *BookAuthorEdit1, TEdit *CustomBookGenre, TComboBox *BookGenreComboBox, TEdit *BookLenghtEdit1);
void __fastcall BookListChange(TObject *Sender);
void __fastcall LogUpButtonClick(TObject *Sender);
void __fastcall LogDownButtonClick(TObject *Sender);
void deleteRow(TStringGrid *grid);
void setReadingStat(TMemo *memo);
void printReadingStat(TLabel *label);

//Edit.cpp
void fillForm(TEdit *bookName, TEdit *authorName, TEdit *customGenre, TComboBox *genre);

//AudioStream.cpp
void __fastcall PlayButtonClick(TObject *Sender);
void __fastcall PauseButtonClick(TObject *Sender);
void getStreamHistory();
void setStreamComboBox(TComboBox *comboBox);

TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

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
		ofstream streamDataFile(mainFolder + "\\" + audioStreamsPath);
        streamDataFile.close();
	}
	createLogFile();
	return isFirstLaunch;
}


void updateDisplays(TComboBox *genreComboBox, TComboBox *booksComboBox, TStringGrid *historyGrid, TMemo *statMemo, TLabel *label) {
	string tempBlankLine = "";
	setAddNewComboBox(genreComboBox, tempBlankLine);
	fillComboBox(booksComboBox);
	updateStringGrid(historyGrid);
	setReadingStat(statMemo);
	printReadingStat(label);
}

void setTabsLenght(TPageControl *pControl, int clWidth, int clHeight) {
	pControl->Width = clWidth;
    pControl->Height = clHeight;
}

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	bool isFirstLaunch = checkFirstLaunch();
	getStreamHistory();
	setStreamComboBox(RadioEdit);
	getUserData();
	setStringGrid(HistoryGrid, HistorySheet->ClientWidth, HistoryGrid->ClientWidth, HistorySheet->Height);
	setLogEdit(LogEdit);
	updateDisplays(BookGenreComboBox, BookList, HistoryGrid, ReadStatMemo, ReportLabel5);
}

string returnStr(AnsiString output) {
	const size_t len = (output.Length() + 1) * sizeof(System::AnsiChar);
	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
	if (hMem) {
		memcpy(GlobalLock(hMem), output.c_str(), len);
	}
	return output.c_str();
}

void __fastcall TMainForm::MainApplicationEventsException(TObject *Sender, Exception *E)
{
	addLogLine(returnStr(E->Message));
}


void __fastcall TMainForm::HistoryGridDblClick(TObject *Sender)
{
	if ((HistoryGrid->Row != 0) && (HistoryGrid->Row != HistoryGrid->RowCount - 1)) {
		rowId = HistoryGrid->Row;

		TEditForm *Form = new TEditForm(this);
		Form->ShowModal();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::aDeleteItemExecute(TObject *Sender)
{
	deleteRow(HistoryGrid);
	updateDisplays(BookGenreComboBox, BookList, HistoryGrid, ReadStatMemo, ReportLabel5);
	rewriteFileData();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::aEditItemExecute(TObject *Sender)
{
    updateDisplays(BookGenreComboBox, BookList, HistoryGrid, ReadStatMemo, ReportLabel5);
	rewriteFileData();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::ProgressButton1Click(TObject *Sender)
{
    ChartForm->ShowModal();
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::ThemeButtonClick(TObject *Sender)
{
	if (ThemeButton->Caption == "Disabled") {
		TStyleManager::TrySetStyle("Tablet Dark");
		ThemeButton->Caption = "Enabled";
	}
	else {
		TStyleManager::TrySetStyle("Tablet Light");
        ThemeButton->Caption = "Disabled";
    }
}
//---------------------------------------------------------------------------

