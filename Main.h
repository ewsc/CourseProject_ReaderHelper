//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "AdvSmoothProgressBar.hpp"
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Samples.Spin.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.AppEvnts.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <string>
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

#include <vcl.h>
#include <sstream>
#include <windows.h>
#pragma hdrstop
#include <ShlObj.h>
#include <string>
#include <filesystem>
#include <cmath>
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <exception>
#include <iomanip>
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
	TMemo *BookmarksMemo;
	TComboBox *BookList;
	TEdit *BookmarkEdit;
	TButton *EditButton;
	TLabel *BookmarkLabel1;
	TStringGrid *HistoryGrid;
	TLabel *HistoryLabel1;
	TLabel *ReportLabel3;
	TEdit *LogEdit;
	TButton *LogUpButton;
	TButton *LogDownButton;
	TTabSheet *AddNewSheet;
	TApplicationEvents *MainApplicationEvents;
	TImageList *MainImageList;
	TEdit *BookNameEdit1;
	TEdit *BookAuthorEdit1;
	TComboBox *BookGenreComboBox;
	TEdit *CustomBookGenre;
	TButton *AddNewButton1;
	TLabel *AddNewLabel1;
	TLabel *AddNewLabel2;
	TLabel *AddNewLabel3;
	TLabel *AddNewLabel4;
	TLabel *AddNewLabel5;
	TActionList *MainActionList;
	TAction *aDeleteItem;
	TAction *aEditItem;
	TMemo *ReadStatMemo;
	TLabel *ReportLabel4;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall BookListChange(TObject *Sender);
	void __fastcall EditButtonClick(TObject *Sender);
	void __fastcall LogUpButtonClick(TObject *Sender);
	void __fastcall LogDownButtonClick(TObject *Sender);
	void __fastcall AddNewButton1Click(TObject *Sender);
	void __fastcall MainApplicationEventsException(TObject *Sender, Exception *E);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall HistoryGridDblClick(TObject *Sender);
	void __fastcall aDeleteItemExecute(TObject *Sender);
	void __fastcall aEditItemExecute(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
using namespace std;

extern PACKAGE TMainForm *MainForm;
extern const string mainFolder;
extern const string logFilePath;
extern const string preferenceFilePath;
extern const string bookmarksFilePath;
extern const string booksFilePath;
extern const string userDataPath;
extern const string appVersion;

typedef struct userBook{
	string bookName;
	int bookmark;
	string bookAuthor;
    string genre;
	string startedReading;
	string finishedReading;
    bool isFinished;
}userBook;

//---------------------------------------------------------------------------
#endif
