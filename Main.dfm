object MainForm: TMainForm
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biHelp]
  BorderStyle = bsSingle
  Caption = 'Reader Helper'
  ClientHeight = 350
  ClientWidth = 670
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object MainPageControl: TPageControl
    Left = 0
    Top = 0
    Width = 500
    Height = 345
    ActivePage = ActionsSheet
    TabOrder = 0
    object ActionsSheet: TTabSheet
      Caption = 'Actions'
    end
    object ReportsSheet: TTabSheet
      Caption = 'Report'
      ImageIndex = 1
    end
  end
end
