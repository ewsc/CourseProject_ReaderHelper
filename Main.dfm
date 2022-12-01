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
    ActivePage = ReportsSheet
    MultiLine = True
    ScrollOpposite = True
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
        Appearance.Shadows = False
        Appearance.Overlays = False
        Appearance.BackGroundFill.Color = 16250613
        Appearance.BackGroundFill.ColorTo = 16250613
        Appearance.BackGroundFill.ColorMirror = clNone
        Appearance.BackGroundFill.ColorMirrorTo = clNone
        Appearance.BackGroundFill.GradientType = gtVertical
        Appearance.BackGroundFill.GradientMirrorType = gtSolid
        Appearance.BackGroundFill.BorderColor = 15000546
        Appearance.BackGroundFill.Rounding = 0
        Appearance.BackGroundFill.ShadowOffset = 0
        Appearance.BackGroundFill.Glow = gmNone
        Appearance.ProgressFill.Color = 16244937
        Appearance.ProgressFill.ColorTo = clNone
        Appearance.ProgressFill.ColorMirror = clNone
        Appearance.ProgressFill.ColorMirrorTo = clNone
        Appearance.ProgressFill.GradientType = gtVertical
        Appearance.ProgressFill.GradientMirrorType = gtVertical
        Appearance.ProgressFill.BorderColor = clNone
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
        UIStyle = tsWindows10
        TMSStyle = 0
      end
      object LogNewEdit: TSpinEdit
        Left = 272
        Top = 40
        Width = 174
        Height = 23
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
      object BookmarkLabel1: TLabel
        Left = 0
        Top = 5
        Width = 92
        Height = 24
        Caption = 'Bookmarks'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -20
        Font.Name = 'Calibri'
        Font.Style = []
        ParentFont = False
      end
      object BookmarksMemo: TMemo
        Left = 0
        Top = 35
        Width = 489
        Height = 166
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'Calibri'
        Font.Style = []
        Lines.Strings = (
          'BookmarksMemo')
        ParentFont = False
        ReadOnly = True
        TabOrder = 0
      end
      object AddButton: TButton
        Left = 414
        Top = 216
        Width = 75
        Height = 25
        Caption = 'Add New'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'Calibri'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
      end
      object BookList: TComboBox
        Left = 0
        Top = 217
        Width = 145
        Height = 26
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'Calibri'
        Font.Style = []
        ParentFont = False
        TabOrder = 2
        Text = 'Select a book'
        OnChange = BookListChange
      end
      object BookmarkEdit: TEdit
        Left = 151
        Top = 217
        Width = 121
        Height = 26
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'Calibri'
        Font.Style = []
        MaxLength = 3
        NumbersOnly = True
        ParentFont = False
        TabOrder = 3
      end
      object EditButton: TButton
        Left = 278
        Top = 216
        Width = 75
        Height = 25
        Caption = 'Edit'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'Calibri'
        Font.Style = []
        ParentFont = False
        TabOrder = 4
        OnClick = EditButtonClick
      end
    end
    object HistorySheet: TTabSheet
      Caption = 'History'
      ImageIndex = 3
      object HistoryLabel1: TLabel
        Left = 3
        Top = 5
        Width = 59
        Height = 24
        Caption = 'History'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -20
        Font.Name = 'Calibri'
        Font.Style = []
        ParentFont = False
      end
      object HistoryGrid: TStringGrid
        Left = 3
        Top = 48
        Width = 489
        Height = 270
        DefaultColAlignment = taCenter
        RowCount = 2
        ScrollBars = ssVertical
        TabOrder = 0
        ColWidths = (
          64
          64
          64
          64
          64)
      end
    end
    object SettingsSheet: TTabSheet
      Caption = 'Settings'
      ImageIndex = 4
    end
  end
end
