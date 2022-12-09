#include <vcl.h>
#pragma hdrstop

#include "UserData.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

using namespace std;
namespace fs = std::filesystem;

extern vector<userBook> userBooks;

//Main.cpp
string returnStr(AnsiString output);
void clearAllInputs(TEdit *BookNameEdit1, TEdit *BookAuthorEdit1, TEdit *CustomBookGenre, TComboBox *BookGenreComboBox);
void updateDisplays(TComboBox *genreComboBox, TMemo *bookmarkMemo, TComboBox *booksComboBox, TStringGrid *historyGrid, TMemo *statMemo, TLabel *label);

TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

string getNext(string currLine, int *index) {
	*index += + 2;
	string result = "";
	while(currLine[*index] != ']') {
		result = result + currLine[*index];
		(*index)++;
	}
	return result;
}

void rewriteFileData() {
	ofstream userDataFile(mainFolder + "\\" + userDataPath);
	for (int i = 0; i < userBooks.size(); i++) {
		string tempString;
		if (userBooks[i].isFinished) {
			tempString = "[" + userBooks[i].bookName + "][" + to_string(userBooks[i].bookmark) + "][" + userBooks[i].bookAuthor + "][" + userBooks[i].genre + "][" + userBooks[i].startedReading + "][" + userBooks[i].finishedReading + "][F]";
		}
		else {
			tempString = "[" + userBooks[i].bookName + "][" + to_string(userBooks[i].bookmark) + "][" + userBooks[i].bookAuthor + "][" + userBooks[i].genre + "][" + userBooks[i].startedReading + "][" + userBooks[i].finishedReading + "][N]";
		}
		userDataFile << tempString << endl;
	}
	userDataFile.close();
}

void distributeString(string currLine) {
	int index = -1;
	string newBookName = getNext(currLine, &index);
	string newBookmarkPage = getNext(currLine, &index);
	string newBookAuthor = getNext(currLine, &index);
	string newBookGenre = getNext(currLine, &index);
	string newStartedReading = getNext(currLine, &index);
	string newFinishedReading = getNext(currLine, &index);
	string finished_reading = getNext(currLine, &index);
	userBook newBook;
	newBook.bookName = newBookName;
	newBook.bookmark = stoi(newBookmarkPage);
	newBook.bookAuthor = newBookAuthor;
	newBook.genre = newBookGenre;
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

void __fastcall TMainForm::AddNewButton1Click(TObject *Sender)
{
	userBook newBook;
	newBook.bookName = returnStr(BookNameEdit1->Text);
	newBook.bookAuthor = returnStr(BookAuthorEdit1->Text);
	if (CustomBookGenre->Text != "") {
		newBook.genre = returnStr(CustomBookGenre->Text);
	}
	else {
		newBook.genre = returnStr(BookGenreComboBox->Text);
	}

	long int t = static_cast<long int> (time(0));
	string startedReadingTime = to_string(t);
	newBook.startedReading = startedReadingTime;

	newBook.finishedReading = "0";
	newBook.isFinished = false;
    newBook.bookmark = 0;

	userBooks.push_back(newBook);
	rewriteFileData();
	clearAllInputs(BookNameEdit1, BookAuthorEdit1, CustomBookGenre, BookGenreComboBox);
	updateDisplays(BookGenreComboBox, BookmarksMemo, BookList, HistoryGrid, ReadStatMemo, ReportLabel5);
}
