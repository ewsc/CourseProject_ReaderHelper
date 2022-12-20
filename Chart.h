//---------------------------------------------------------------------------

#ifndef ChartH
#define ChartH
//---------------------------------------------------------------------------

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <windows.h>
#include <Vcl.StdCtrls.hpp>
#include <string>


//---------------------------------------------------------------------------
class TChartForm : public TForm
{
__published:	// IDE-managed Components
	TImage *MainImage;
	TMemo *GenreMemo;
	void __fastcall FormActivate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TChartForm(TComponent* Owner);
};

//---------------------------------------------------------------------------
extern PACKAGE TChartForm *ChartForm;
//---------------------------------------------------------------------------

#endif
