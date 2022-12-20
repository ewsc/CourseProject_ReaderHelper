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
#include "AdvSmoothTabPager.hpp"
#include "AdvSmoothSlider.hpp"
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
#include "bass.h"
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TApplicationEvents *MainApplicationEvents;
	TImageList *MainImageList;
	TAdvSmoothTabPager *SmoothTabPager;
	TAdvSmoothTabPage *AddNewSheet;
	TAdvSmoothTabPage *ReportSheet;
	TAdvSmoothTabPage *ProgressSheet;
	TAdvSmoothTabPage *HistorySheet;
	TStringGrid *HistoryGrid;
	TEdit *BookLenghtEdit1;
	TLabel *AddNewLabel6;
	TEdit *BookNameEdit1;
	TEdit *BookAuthorEdit1;
	TComboBox *BookGenreComboBox;
	TEdit *CustomBookGenre;
	TButton *AddNewButton1;
	TLabel *AddNewLabel2;
	TLabel *AddNewLabel3;
	TLabel *AddNewLabel4;
	TLabel *AddNewLabel5;
	TLabel *ProgressLabel2;
	TComboBox *BookList;
	TAdvSmoothProgressBar *ReadProgressBar;
	TEdit *LogEdit;
	TButton *LogUpButton;
	TButton *LogDownButton;
	TMemo *ReadStatMemo;
	TLabel *ReportLabel5;
	TLabel *ReportLabel4;
	TLabel *ProgressLabel3;
	TAdvSmoothTabPage *SettingsSheet;
	TAdvSmoothSlider *AdvSmoothSlider1;
	TLabel *SettingsLabel2;
	TButton *ProgressButton1;
	TLabel *ProgressLabel4;
	TLabel *Label1;
	TLabel *Label2;
	TAction *aDeleteItem;
	TAction *aEditItem;
	TActionList *MainActionList;
	TLabel *SettingsLabel3;
	TButton *PlayButton;
	TLabel *SettingsLabel1;
	TLabel *AddNewLabel1;
	TLabel *HistoryLabel;
	TEdit *RadioEdit1;
	TButton *PauseButton;
	TLabel *SettingsLabel4;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall BookListChange(TObject *Sender);
	void __fastcall LogUpButtonClick(TObject *Sender);
	void __fastcall LogDownButtonClick(TObject *Sender);
	void __fastcall AddNewButton1Click(TObject *Sender);
	void __fastcall MainApplicationEventsException(TObject *Sender, Exception *E);
	void __fastcall HistoryGridDblClick(TObject *Sender);
	void __fastcall aDeleteItemExecute(TObject *Sender);
	void __fastcall aEditItemExecute(TObject *Sender);
	void __fastcall AdvSmoothSlider1StateChanged(TObject *Sender, TAdvSmoothSliderState State,
          double Value);
	void __fastcall ProgressButton1Click(TObject *Sender);
	void __fastcall PlayButtonClick(TObject *Sender);
	void __fastcall PauseButtonClick(TObject *Sender);
	void __fastcall RadioEdit1Change(TObject *Sender);


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
	int currPage;
	int bookLength;
}userBook;

//---------------------------------------------------------------------------
#endif
