//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UserControls.h"
#include "Main.h"
#include "UserData.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

using namespace std;
namespace fs = std::filesystem;

extern vector<userBook> userBooks;

vector<double> readingTime;

const int seconds_per_day = 60*60*24;

//Main.cpp
string returnStr(AnsiString output);
void saveFilePref();
void updateDisplays(TComboBox *genreComboBox, TComboBox *booksComboBox, TStringGrid *historyGrid, TMemo *statMemo, TLabel *label);


//UserData.cpp
void rewriteFileData();


TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

struct byGenre {
	bool operator()(userBook const &a, userBook const &b) const {
		return a.genre < b.genre;
	}
};

bool genreIsAlreadyAdded(string compareStr, TComboBox *comboBox) {
	for (int i = 0; i < comboBox->Items->Count; i++) {
		if (returnStr(comboBox->Items->operator[](i)) == compareStr.c_str()) {
			return true;
        }
    }
	return false;
}

void setAddNewComboBox(TComboBox *comboBox, string selected) {
	comboBox->Items->Clear();
	for (int i = 0; i < userBooks.size(); i++) {
		bool isAlreadyAdded;
		if (i != 0) {
			isAlreadyAdded = genreIsAlreadyAdded(userBooks[i].genre, comboBox);
		}
		else {
			isAlreadyAdded = false;
        }
		if (!isAlreadyAdded) {
			comboBox->Items->Add(userBooks[i].genre.c_str());
            if (selected == userBooks[i].genre.c_str()) {
				comboBox->ItemIndex = comboBox->Items->Count - 1;
			}
		}
	}
}

void fillComboBox(TComboBox *comboBox) {
	comboBox->Items->Clear();
	comboBox->ItemIndex = -1;
    comboBox->Text = "Select a book";
	for (int i = 0; i < userBooks.size(); i++) {
		//if (userBooks[i].finishedReading == "0") {
			comboBox->Items->Add(userBooks[i].bookName.c_str());
		//}
	}
}

void setLogEdit(TEdit *edit) {
	edit->Text = 1;
}

void deleteRow(TStringGrid *grid) {
	int index = grid->Row - 1;
	userBooks.erase(userBooks.begin() + index);
}

void setStringGrid(TStringGrid *grid, int clWIdth, int gridWidth, int height) {
	grid->Width = clWIdth;
	grid->Height = height;

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
	grid->Cells[4][0] = "Progress";
}

void clearStringGrid(TStringGrid *grid) {
	grid->RowCount = 2;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 5; j++) {
			grid->Cells[i][j] = "";
		}
	}
}

void fillStatArr() {
	readingTime.clear();
    for (int i = 0; i < userBooks.size(); i++) {
		if (userBooks[i].startedReading != "0" && userBooks[i].finishedReading != "0") {
			time_t finTime = stoi(userBooks[i].finishedReading.c_str());
			time_t startTime = stoi(userBooks[i].startedReading.c_str());
			double hours = difftime(finTime, startTime) / 60 / 60;
			readingTime.push_back(hours);
		}
	}
}

double getAverage() {
	double sum = 0;
	int i;
	if (readingTime.size() > 0) {
		for (i = 0; i < readingTime.size(); i++) {
			sum += readingTime[i];
		}
		return ((double)sum / i);
	}
    return 0;
}

double getTotal() {
	double sum = 0;;
	for (int i = 0; i < readingTime.size(); i++) {
		sum += readingTime[i];
	}
	return sum;
}

void printReadingStat(TLabel *label) {
	fillStatArr();
	double weeklyAverage = getAverage();
	double totalHours = getTotal();
    stringstream stream;
	stream << "Average book reading time: " << fixed << setprecision(2) << weeklyAverage << " hours" << endl << "Total reading time: " << fixed << setprecision(2) << totalHours << " hours";
	string line = stream.str();

	label->Caption = line.c_str();
}

string currProgress(int index) {
	double result = ((double)userBooks[index].currPage / userBooks[index].bookLength * 100);
    return to_string((int)result);
}

void updateStringGrid(TStringGrid *grid) {
	clearStringGrid(grid);
	drawFixedRows(grid);
	for (int i = 0; i < userBooks.size(); i++) {
		grid->Cells[0][i+1] = i+1;
		grid->Cells[1][i+1] = userBooks[i].bookName.c_str();
		grid->Cells[2][i+1] = userBooks[i].bookAuthor.c_str();
		grid->Cells[3][i+1] = userBooks[i].genre.c_str();
		grid->Cells[4][i+1] = currProgress(i).c_str();
        grid->RowCount += 1;
	}
}

void setReadingStat(TMemo *memo) {
	memo->Clear();
	for (int i = 0; i < userBooks.size(); i++) {
		if (userBooks[i].startedReading != "0" && userBooks[i].finishedReading != "0") {
			time_t finTime = stoi(userBooks[i].finishedReading.c_str());
			time_t startTime = stoi(userBooks[i].startedReading.c_str());
			double hours = difftime(finTime, startTime) / 60 / 60;

			stringstream stream;
			stream << fixed << setprecision(2) << hours;
			string sthours = stream.str();
			string tempLine = "[" + userBooks[i].bookName + "] -> read in " + sthours + " hours.";
			memo->Lines->Add(tempLine.c_str());
        }
    }
}

void clearAllInputs(TEdit *BookNameEdit1, TEdit *BookAuthorEdit1, TEdit *CustomBookGenre, TComboBox *BookGenreComboBox, TEdit *BookLengthEdit1) {
	BookNameEdit1->Text = "";
	BookAuthorEdit1->Text = "";
	CustomBookGenre->Text = "";
    BookLengthEdit1->Text = "";
    BookGenreComboBox->ItemIndex = -1;
}

void statProgressBarSet(TAdvSmoothProgressBar *bar, TComboBox *cbbox) {
	bar->Position = stoi(currProgress(cbbox->ItemIndex));
}

void setPrecentageLabel(TLabel *label, TComboBox *cbbox) {
	string tempStr = currProgress(cbbox->ItemIndex) + "%\n" + to_string(userBooks[cbbox->ItemIndex].currPage) + " pages of " + to_string(userBooks[cbbox->ItemIndex].bookLength);
	label->Caption = tempStr.c_str();
}

void enableLoggingButtons(TButton *butt1, TButton *butt2, TComboBox *cbbox) {
	butt1->Enabled = cbbox->ItemIndex != -1;
	butt2->Enabled = cbbox->ItemIndex != -1;
}

void __fastcall TMainForm::BookListChange(TObject *Sender)
{
	statProgressBarSet(ReadProgressBar, BookList);
	setPrecentageLabel(ProgressLabel2, BookList);
	enableLoggingButtons(LogUpButton, LogDownButton, BookList);
}


bool checkLogability(int index, int value, bool isAdding) {
	int currValue = userBooks[index].currPage;
	int maxValue = userBooks[index].bookLength;
	userBook temp = userBooks[index];
	if (isAdding) {
		if (currValue + value <= maxValue) {
			return true;
		}
		return false;
	}

	else {
		if (currValue - value >= 0) {
			return true;
		}
		return false;
    }
}

bool checkCompletetion(int index) {
	if (userBooks[index].currPage == userBooks[index].bookLength) {
		return true;
	}
	else {
		return false;
    }
}

void markAsDone(int index) {
	if (userBooks[index].finishedReading == "0") {
		long int t = static_cast<long int> (time(0));
		string finishedReadingTime = to_string(t);
		userBooks[index].finishedReading = finishedReadingTime;
    }
}

void __fastcall TMainForm::LogUpButtonClick(TObject *Sender)
{
	bool isEditable = checkLogability(BookList->ItemIndex, stoi(returnStr(LogEdit->Text)), true);
	if (isEditable) {
		string output = returnStr(LogEdit->Text);
		userBooks[BookList->ItemIndex].currPage += stoi(output.c_str());
		setLogEdit(LogEdit);
		statProgressBarSet(ReadProgressBar, BookList);

		if (checkCompletetion(BookList->ItemIndex)) {
			markAsDone(BookList->ItemIndex);
		}

		rewriteFileData();
		setPrecentageLabel(ProgressLabel2, BookList);
		updateDisplays(BookGenreComboBox, BookList, HistoryGrid, ReadStatMemo, ReportLabel5);
		enableLoggingButtons(LogUpButton, LogDownButton, BookList);
	}
}

void __fastcall TMainForm::LogDownButtonClick(TObject *Sender)
{
	bool isEditable = checkLogability(BookList->ItemIndex, stoi(returnStr(LogEdit->Text)), false);
	if (isEditable) {
		string output = returnStr(LogEdit->Text);
		userBooks[BookList->ItemIndex].currPage -= stoi(output.c_str());
		setLogEdit(LogEdit);
		statProgressBarSet(ReadProgressBar, BookList);
		rewriteFileData();
		setPrecentageLabel(ProgressLabel2, BookList);
		updateDisplays(BookGenreComboBox, BookList, HistoryGrid, ReadStatMemo, ReportLabel5);
        enableLoggingButtons(LogUpButton, LogDownButton, BookList);
	}
}
