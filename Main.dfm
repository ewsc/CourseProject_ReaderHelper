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
  Font.Height = -12
  Font.Name = 'Calibri'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 14
  object MainPageControl: TPageControl
    Left = 0
    Top = 0
    Width = 500
    Height = 345
    ActivePage = BookmarksSheet
    TabOrder = 0
    object ActionsSheet: TTabSheet
      Caption = 'Actions'
    end
    object ReportsSheet: TTabSheet
      Caption = 'Report'
      ImageIndex = 1
      object ReportLabel1: TLabel
        Left = 3
        Top = 20
        Width = 81
        Height = 14
        Caption = 'Daily progress:'
      end
      object ReportLabel2: TLabel
        Left = 272
        Top = 20
        Width = 21
        Height = 14
        Caption = 'Log:'
      end
      object DailyProgressBar: TAdvSmoothProgressBar
        Left = 3
        Top = 40
        Width = 174
        Height = 33
        Step = 10.000000000000000000
        Maximum = 100.000000000000000000
        Appearance.BackGroundFill.Color = 15921906
        Appearance.BackGroundFill.ColorTo = 15921906
        Appearance.BackGroundFill.ColorMirror = clNone
        Appearance.BackGroundFill.ColorMirrorTo = clNone
        Appearance.BackGroundFill.GradientType = gtVertical
        Appearance.BackGroundFill.GradientMirrorType = gtSolid
        Appearance.BackGroundFill.BorderColor = clSilver
        Appearance.BackGroundFill.Rounding = 0
        Appearance.BackGroundFill.ShadowOffset = 0
        Appearance.BackGroundFill.Glow = gmNone
        Appearance.ProgressFill.Color = clWhite
        Appearance.ProgressFill.ColorTo = 13226453
        Appearance.ProgressFill.ColorMirror = clNone
        Appearance.ProgressFill.ColorMirrorTo = clNone
        Appearance.ProgressFill.GradientType = gtVertical
        Appearance.ProgressFill.GradientMirrorType = gtVertical
        Appearance.ProgressFill.BorderColor = clGray
        Appearance.ProgressFill.Rounding = 0
        Appearance.ProgressFill.ShadowOffset = 0
        Appearance.ProgressFill.Glow = gmNone
        Appearance.Font.Charset = DEFAULT_CHARSET
        Appearance.Font.Color = clWindowText
        Appearance.Font.Height = -11
        Appearance.Font.Name = 'Tahoma'
        Appearance.Font.Style = []
        Appearance.ProgressFont.Charset = DEFAULT_CHARSET
        Appearance.ProgressFont.Color = clWindowText
        Appearance.ProgressFont.Height = -11
        Appearance.ProgressFont.Name = 'Tahoma'
        Appearance.ProgressFont.Style = []
        Appearance.ValueFormat = '%.0f%%'
        Version = '1.10.1.2'
        UIStyle = tsOffice2003Classic
        TMSStyle = 0
      end
      object LogNewEdit: TSpinEdit
        Left = 272
        Top = 40
        Width = 174
        Height = 33
        MaxValue = 0
        MinValue = 0
        TabOrder = 1
        Value = 0
        OnChange = LogNewEditChange
      end
    end
    object BookmarksSheet: TTabSheet
      Caption = 'Bookmarks'
      ImageIndex = 2
      object BookmarksMemo: TMemo
        Left = 0
        Top = 3
        Width = 489
        Height = 166
        Lines.Strings = (
          'BookmarksMemo')
        TabOrder = 0
      end
    end
    object HistorySheet: TTabSheet
      Caption = 'History'
      ImageIndex = 3
    end
    object SettingsSheet: TTabSheet
      Caption = 'Settings'
      ImageIndex = 4
    end
  end
end
