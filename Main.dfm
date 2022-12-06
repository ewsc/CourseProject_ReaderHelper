object MainForm: TMainForm
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize, biMaximize, biHelp]
  Caption = 'Reader Helper'
  ClientHeight = 348
  ClientWidth = 668
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Calibri'
  Font.Style = []
  Menu = MainMenu
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCreate = FormCreate
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 14
  object MainPageControl: TPageControl
    Left = 0
    Top = -3
    Width = 500
    Height = 345
    ActivePage = HistorySheet
    MultiLine = True
    ScrollOpposite = True
    TabOrder = 1
    object ActionsSheet: TTabSheet
      Caption = 'Actions'
    end
    object AddNewSheet: TTabSheet
      Caption = 'Add New'
      ImageIndex = 5
      object AddNewLabel1: TLabel
        Left = 0
        Top = 3
        Width = 76
        Height = 24
        Caption = 'Add New'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -20
        Font.Name = 'Calibri'
        Font.Style = []
        ParentFont = False
      end
      object AddNewLabel2: TLabel
        Left = 0
        Top = 36
        Width = 93
        Height = 14
        Caption = 'Input book name'
      end
      object AddNewLabel3: TLabel
        Left = 208
        Top = 36
        Width = 98
        Height = 14
        Caption = 'Input book author'
      end
      object AddNewLabel4: TLabel
        Left = 0
        Top = 100
        Width = 93
        Height = 14
        Caption = 'Input book genre'
      end
      object AddNewLabel5: TLabel
        Left = 167
        Top = 123
        Width = 11
        Height = 14
        Caption = 'or'
      end
      object BookNameEdit1: TEdit
        Left = 0
        Top = 56
        Width = 145
        Height = 22
        TabOrder = 0
      end
      object BookAuthorEdit1: TEdit
        Left = 208
        Top = 56
        Width = 145
        Height = 22
        TabOrder = 1
      end
      object BookGenreComboBox: TComboBox
        Left = 208
        Top = 120
        Width = 145
        Height = 22
        TabOrder = 2
        Text = 'Select genre'
      end
      object CustomBookGenre: TEdit
        Left = 0
        Top = 120
        Width = 145
        Height = 22
        TabOrder = 3
      end
      object AddNewButton1: TButton
        Left = 278
        Top = 168
        Width = 75
        Height = 25
        Caption = 'Add'
        TabOrder = 4
        OnClick = AddNewButton1Click
      end
    end
    object ReportsSheet: TTabSheet
      Caption = 'Report'
      ImageIndex = 1
      object ReportLabel1: TLabel
        Left = 3
        Top = 36
        Width = 81
        Height = 14
        Caption = 'Daily progress:'
      end
      object ReportLabel2: TLabel
        Left = 272
        Top = 36
        Width = 21
        Height = 14
        Caption = 'Log:'
      end
      object ReportLabel3: TLabel
        Left = 3
        Top = 3
        Width = 57
        Height = 24
        Caption = 'Report'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -20
        Font.Name = 'Calibri'
        Font.Style = []
        ParentFont = False
      end
      object DailyProgressBar: TAdvSmoothProgressBar
        Left = 3
        Top = 56
        Width = 174
        Height = 24
        Step = 10.000000000000000000
        Maximum = 100.000000000000000000
        Appearance.BackGroundFill.Color = 11974326
        Appearance.BackGroundFill.ColorTo = 11974326
        Appearance.BackGroundFill.ColorMirror = clNone
        Appearance.BackGroundFill.ColorMirrorTo = clNone
        Appearance.BackGroundFill.GradientType = gtVertical
        Appearance.BackGroundFill.GradientMirrorType = gtSolid
        Appearance.BackGroundFill.BorderColor = clSilver
        Appearance.BackGroundFill.Rounding = 0
        Appearance.BackGroundFill.ShadowOffset = 0
        Appearance.BackGroundFill.Glow = gmNone
        Appearance.ProgressFill.Color = clWhite
        Appearance.ProgressFill.ColorTo = clBtnFace
        Appearance.ProgressFill.ColorMirror = clNone
        Appearance.ProgressFill.ColorMirrorTo = clNone
        Appearance.ProgressFill.GradientType = gtVertical
        Appearance.ProgressFill.GradientMirrorType = gtVertical
        Appearance.ProgressFill.BorderColor = clBlack
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
        UIStyle = tsWindowsXP
        TMSStyle = 0
      end
      object LogEdit: TEdit
        Left = 272
        Top = 56
        Width = 121
        Height = 22
        NumbersOnly = True
        TabOrder = 1
        Text = 'LogEdit'
      end
      object LogUpButton: TButton
        Left = 399
        Top = 55
        Width = 26
        Height = 25
        Caption = '+'
        TabOrder = 2
        OnClick = LogUpButtonClick
      end
      object LogDownButton: TButton
        Left = 431
        Top = 55
        Width = 26
        Height = 25
        Caption = '-'
        TabOrder = 3
        OnClick = LogDownButtonClick
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
        Left = 0
        Top = 48
        Width = 486
        Height = 270
        DefaultColAlignment = taCenter
        RowCount = 2
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSelect, goFixedRowDefAlign]
        ScrollBars = ssVertical
        TabOrder = 0
        OnDblClick = HistoryGridDblClick
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
  object ToolBar1: TToolBar
    Left = 639
    Top = 0
    Width = 29
    Height = 348
    Align = alRight
    TabOrder = 0
  end
  object MainMenu: TMainMenu
    Left = 592
    Top = 280
    object FileButton: TMenuItem
      Caption = 'File'
      object OpenButton: TMenuItem
        Caption = 'Open...'
      end
    end
  end
  object MainApplicationEvents: TApplicationEvents
    OnException = MainApplicationEventsException
    Left = 592
    Top = 232
  end
end
