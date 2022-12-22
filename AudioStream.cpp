//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AudioStream.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

using namespace std;
namespace fs = std::filesystem;
HSTREAM audiostream;

string returnStr(AnsiString output);

TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PlayButtonClick(TObject *Sender)
{
	string link = returnStr(RadioEdit1->Text);
	BASS_Init(-1, 44100, BASS_DEVICE_3D, 0, NULL);
	audiostream = BASS_StreamCreateURL(PAnsiChar(link.c_str()), 0, 0, NULL, 0);
	BASS_ChannelPlay(audiostream, false);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PauseButtonClick(TObject *Sender)
{
    BASS_ChannelPause(audiostream);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioEdit1Change(TObject *Sender)
{
	PlayButton->Enabled = returnStr(RadioEdit1->Text).length != 0;
}
//---------------------------------------------------------------------------
