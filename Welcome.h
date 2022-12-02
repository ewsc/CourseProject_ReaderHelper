//---------------------------------------------------------------------------

#ifndef WelcomeH
#define WelcomeH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TWelcomeForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *WelcomeLabel1;
	TEdit *GoalEdit;
	TLabel *WelcomeLabel2;
	TButton *SubmitButton;
	void __fastcall GoalEditChange(TObject *Sender);
	void __fastcall SubmitButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TWelcomeForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TWelcomeForm *WelcomeForm;
//---------------------------------------------------------------------------
#endif