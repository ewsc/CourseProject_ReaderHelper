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

void setAddNewComboBox(TComboBox *comboBox);
//void __fastcall aDeleteItemExecute(TObject *Sender);

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
	CustomBookGenre->Text = userBooks[rowId - 1].genre.c_str();
	setAddNewComboBox(BookGenreComboBox);
}
//---------------------------------------------------------------------------

void __fastcall TEditForm::DeleteButton1Click(TObject *Sender)
{
	bool isDeleting = MessageDlg("Are you sure that you want to delete this book from reading history?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo,0) == mrYes;
	if (isDeleting) {
		MainForm->aDeleteItem->Execute();
	}
}
//---------------------------------------------------------------------------

