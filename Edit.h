//---------------------------------------------------------------------------

#ifndef EditH
#define EditH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TEditForm : public TForm
{
__published:	// IDE-managed Components
	TEdit *BookNameEdit1;
	TEdit *BookAuthorEdit1;
	TComboBox *BookGenreComboBox;
	TEdit *CustomBookGenre;
	TButton *EditButton1;
	TLabel *AddNewLabel1;
	TLabel *AddNewLabel2;
	TLabel *AddNewLabel3;
	TLabel *AddNewLabel4;
	TLabel *AddNewLabel5;
	TButton *DeleteButton1;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall DeleteButton1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TEditForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TEditForm *EditForm;
//---------------------------------------------------------------------------
#endif
