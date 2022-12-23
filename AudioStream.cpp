//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AudioStream.h"
#include "Main.h"
#include "Logs.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

using namespace std;
namespace fs = std::filesystem;
HSTREAM audiostream;

//Main.cpp
string returnStr(AnsiString output);

//Logs.cpp
void addLogLine(string exception);

vector<string> streamHistory;

const string audioStreamsPath = "streampath.readerdata";

TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void decideToAdd(string currLine) {
	bool isExists = false;
	for (int i = 0; i < streamHistory.size(); i++) {
		if (streamHistory[i] == currLine) {
			isExists = true;
            break;
        }
	}
	if (!isExists) {
		streamHistory.push_back(currLine);
    }
}

void getStreamHistory() {
	ifstream streamDataFile(mainFolder + "\\" + audioStreamsPath);
	string line;
	while (getline(streamDataFile, line)) {
		decideToAdd(line);
	}
	streamDataFile.close();
}

void setStreamComboBox(TComboBox *comboBox) {
	comboBox->Items->Clear();
	for (int i = 0; i < streamHistory.size(); i++) {
		comboBox->Items->Add(streamHistory[i].c_str());
	}
	if (streamHistory.size() > 0) {
		comboBox->ItemIndex = comboBox->Items->Count - 1;
	}
}

void saveStreamData() {
	ofstream streamDataFile(mainFolder + "\\" + audioStreamsPath);
	for (int i = 0; i < streamHistory.size(); i++) {
		string tempLine = streamHistory[i];
        streamDataFile << tempLine << endl;
	}
	streamDataFile.close();
}

void __fastcall TMainForm::PlayButtonClick(TObject *Sender)
{
	string link = returnStr(RadioEdit->Text);
	BASS_Init(-1, 44100, BASS_DEVICE_3D, 0, NULL);
	audiostream = BASS_StreamCreateURL(PAnsiChar(link.c_str()), 0, 0, NULL, 0);
	if (BASS_ChannelPlay(audiostream, false)) {
		decideToAdd(link);
		setStreamComboBox(RadioEdit);
		saveStreamData();
	}
	else {
		addLogLine("Wrong audiostream link.");
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PauseButtonClick(TObject *Sender)
{
    BASS_ChannelPause(audiostream);
}
//---------------------------------------------------------------------------
