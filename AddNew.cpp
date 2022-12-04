//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <string>
#include <vector>

#include "AddNew.h"
#include "Files.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;

using namespace std;

extern vector<userBook> userBooks;

//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
}

void setAddNewComboBox(TComboBox *comboBox) {
	comboBox->Items->Clear();
	for (int i = 0; i < userBooks.size(); i++) {
		comboBox->Items->Add(userBooks[i].genre.c_str());
	}
}
//---------------------------------------------------------------------------
