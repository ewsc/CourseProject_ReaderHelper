object ChartForm: TChartForm
  Left = 0
  Top = 0
  Caption = 'Charts'
  ClientHeight = 316
  ClientWidth = 522
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnActivate = FormActivate
  PixelsPerInch = 96
  TextHeight = 13
  object MainImage: TImage
    Left = 0
    Top = 0
    Width = 376
    Height = 316
    Align = alClient
    ExplicitLeft = 8
    ExplicitTop = 8
    ExplicitWidth = 105
    ExplicitHeight = 105
  end
  object GenreMemo: TMemo
    Left = 376
    Top = 0
    Width = 146
    Height = 316
    Align = alRight
    Lines.Strings = (
      'GenreMemo')
    ReadOnly = True
    ScrollBars = ssBoth
    TabOrder = 0
  end
end
