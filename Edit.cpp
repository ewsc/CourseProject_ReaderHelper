//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Edit.h"
#include "Main.h"
#include "UserControls.h"
#include "UserData.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

using namespace std;
namespace fs = std::filesystem;


extern int rowId;
extern vector<userBook> userBooks;

//UserControls.cpp
void setAddNewComboBox(TComboBox *comboBox, string selected);

//Main.cpp
string returnStr(AnsiString output);

TEditForm *EditForm;
//---------------------------------------------------------------------------
__fastcall TEditForm::TEditForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TEditForm::FormActivate(TObject *Sender)
{
	BookNameEdit1->Text = userBooks[rowId - 1].bookName.c_str();
	BookAuthorEdit1->Text = userBooks[rowId - 1].bookAuthor.c_str();
	setAddNewComboBox(BookGenreComboBox, userBooks[rowId - 1].genre.c_str());
}
//---------------------------------------------------------------------------

void __fastcall TEditForm::DeleteButton1Click(TObject *Sender)
{
	bool isDeleting = MessageDlg("Are you sure that you want to delete this book from reading history?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo,0) == mrYes;
	if (isDeleting) {
		MainForm->aDeleteItem->Execute();
        Close();
	}
}
//---------------------------------------------------------------------------


void __fastcall TEditForm::EditButton1Click(TObject *Sender)
{
	userBook newBook = userBooks[rowId - 1];
	newBook.bookName = returnStr(BookNameEdit1->Text);
	newBook.bookAuthor = returnStr(BookAuthorEdit1->Text);
	if (CustomBookGenre->Text != "") {
		newBook.genre = returnStr(CustomBookGenre->Text);
	}
	else {
		newBook.genre = returnStr(BookGenreComboBox->Text);
	}

	//newBook.isFinished = IsFinishedCheckbox->Checked;
	userBooks[rowId - 1] = newBook;
	MainForm->aEditItem->Execute();
    Close();
}
//---------------------------------------------------------------------------

