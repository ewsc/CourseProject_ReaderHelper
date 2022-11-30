//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Tabs.hpp>
#include "AdvSmoothGauge.hpp"
#include "AdvSmoothProgressBar.hpp"
#include "AdvProgr.hpp"
#include "AdvCircularProgress.hpp"
#include "AdvProgressBar.hpp"
#include "W7Classes.hpp"
#include "W7ProgressBars.hpp"
#include <Vcl.Samples.Spin.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TPageControl *MainPageControl;
	TTabSheet *ActionsSheet;
	TTabSheet *BookmarksSheet;
	TTabSheet *HistorySheet;
	TTabSheet *SettingsSheet;
	TTabSheet *ReportsSheet;
	TLabel *ReportLabel1;
	TLabel *ReportLabel2;
	TAdvSmoothProgressBar *DailyProgressBar;
	TSpinEdit *LogNewEdit;
	TMemo *BookmarksMemo;
	TButton *AddButton;
	TComboBox *BookList;
	TEdit *BookmarkEdit;
	TButton *EditButton;
	TLabel *BookmarkLabel1;
	TStringGrid *StringGrid1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall LogNewEditChange(TObject *Sender);
	void __fastcall BookListChange(TObject *Sender);
	void __fastcall EditButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
