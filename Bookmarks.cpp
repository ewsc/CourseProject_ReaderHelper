//---------------------------------------------------------------------------

#include <vcl.h>
#include <vector>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#pragma hdrstop

#include "Bookmarks.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#pragma comment(lib, "shell32.lib")


using namespace std;

extern vector<userBook> userBooks;

TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
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

void importBookMarks(TMemo *bookmarksMemo, TComboBox *comboBox) {
	fillComboBox(comboBox);
	updateMemo(bookmarksMemo);
}
//---------------------------------------------------------------------------
