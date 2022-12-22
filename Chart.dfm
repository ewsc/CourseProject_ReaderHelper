object ChartForm: TChartForm
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Charts'
  ClientHeight = 238
  ClientWidth = 418
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
    Width = 272
    Height = 238
    Align = alClient
    ExplicitLeft = 8
    ExplicitTop = 8
    ExplicitWidth = 105
    ExplicitHeight = 105
  end
  object GenreMemo: TMemo
    Left = 272
    Top = 0
    Width = 146
    Height = 238
    Align = alRight
    Lines.Strings = (
      'GenreMemo')
    ReadOnly = True
    ScrollBars = ssBoth
    TabOrder = 0
    ExplicitLeft = 376
    ExplicitHeight = 316
  end
end
