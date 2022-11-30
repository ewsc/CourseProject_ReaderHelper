//---------------------------------------------------------------------------

#include <vcl.h>
#include <vector>
#include <filesystem>
#include <iostream>
#include <fstream>
#pragma hdrstop

#include "Bookmarks.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#pragma comment(lib, "shell32.lib")


using namespace std;

extern vector<string> bookNames;
extern vector<string> bookmarks;

const string mainFolder = "readerdata";
const string logFilePath = "logs.readerdata";
const string preferenceFilePath = "preferences.readerdata";
const string bookmarksFilePath = "bookmarks.readerdata";
const string booksFilePath = "books.readerdata";
const string appVersion = "0.0";

TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}

void fillComboBox(TComboBox *comboBox) {
    comboBox->Items->Clear();
	for (int i = 0; i < bookNames.size(); i++) {
        comboBox->Items->Add(bookNames[i].c_str());
	}
}

void loadBooks() {
	ifstream booksFile(mainFolder + "\\" + booksFilePath);
	string line;
	while (getline(booksFile, line)) {
		bookNames.push_back(line);
	}
	booksFile.close();
}

void loadBookmarks() {
	ifstream bookmarksFile(mainFolder + "\\" + bookmarksFilePath);
	string line;
	while (getline(bookmarksFile, line)) {
		bookmarks.push_back(line);
	}
	bookmarksFile.close();
}

void updateMemo(TMemo *bookmarksMemo) {
	bookmarksMemo->Lines->Clear();
	for (int i = 0; i < bookNames.size(); i++) {
		bookmarksMemo->Lines->Add(("[" + bookNames[i] + "] Page: " + bookmarks[i]).c_str());
    }
}

void importBookMarks(TMemo *bookmarksMemo, TComboBox *comboBox) {
	loadBooks();
	loadBookmarks();
	fillComboBox(comboBox);
	updateMemo(bookmarksMemo);
}
//---------------------------------------------------------------------------
