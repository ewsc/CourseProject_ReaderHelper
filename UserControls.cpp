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
extern int dailyGoal;
extern int currentGoalStat;

//Main.cpp
string returnStr(AnsiString output);
void saveFilePref();

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

bool genreIsAlreadyAdded() {
	vector<userBook> duplicateVector;
    duplicateVector = userBooks;
	sort(duplicateVector.begin(), duplicateVector.end(), byGenre());
	return false;
}

void setAddNewComboBox(TComboBox *comboBox) {
	comboBox->Items->Clear();
	for (int i = 0; i < userBooks.size(); i++) {
		bool isAlreadyAdded = genreIsAlreadyAdded();
		if (!isAlreadyAdded) {
			comboBox->Items->Add(userBooks[i].genre.c_str());
		}
	}
}

void fillComboBox(TComboBox *comboBox) {
    comboBox->Items->Clear();
	for (int i = 0; i < userBooks.size(); i++) {
		comboBox->Items->Add(userBooks[i].bookName.c_str());
	}
}

void updateMemo(TMemo *bookmarksMemo) {
	bookmarksMemo->Lines->Clear();
	for (int i = 0; i < userBooks.size(); i++) {
		string tempString = "[" + userBooks[i].bookName + "], Page: " + to_string(userBooks[i].bookmark);
		bookmarksMemo->Lines->Add(tempString.c_str());
	}
}

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

void deleteRow(TStringGrid *grid) {
	int index = grid->Row - 1;
	userBooks.erase(userBooks.begin() + index);
}

void setStringGrid(TStringGrid *grid, int width, int height) {
	grid->Width = width - 30;
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
	grid->Cells[4][0] = "Finished";
}

void clearStringGrid(TStringGrid *grid) {
	grid->RowCount = 2;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 5; j++) {
			grid->Cells[i][j] = "";
		}
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

		if (!userBooks[i].isFinished) {
			grid->Cells[4][i+1] = "Still reading";
		}
		else {
			grid->Cells[4][i+1] = userBooks[i].finishedReading.c_str();
		}
        grid->RowCount += 1;
	}
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

void clearAllInputs(TEdit *BookNameEdit1, TEdit *BookAuthorEdit1, TEdit *CustomBookGenre, TComboBox *BookGenreComboBox) {
	BookNameEdit1->Text = "";
	BookAuthorEdit1->Text = "";
	CustomBookGenre->Text = "";
    BookGenreComboBox->ItemIndex = -1;
}

void __fastcall TMainForm::BookListChange(TObject *Sender)
{
	BookmarkEdit->Text = userBooks[BookList->ItemIndex].bookmark;
}

void __fastcall TMainForm::LogUpButtonClick(TObject *Sender)
{
	string output = returnStr(LogEdit->Text);
	currentGoalStat += stoi(output.c_str());
	setLogEdit(LogEdit);
	saveFilePref();
	setProgress(DailyProgressBar, ReportLabel1);
}

void __fastcall TMainForm::LogDownButtonClick(TObject *Sender)
{
	string output = returnStr(LogEdit->Text);
	currentGoalStat -= stoi(output.c_str());
	setLogEdit(LogEdit);
	saveFilePref();
	setProgress(DailyProgressBar, ReportLabel1);
}
