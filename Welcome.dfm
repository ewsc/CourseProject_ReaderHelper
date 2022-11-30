object WelcomeForm: TWelcomeForm
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = 'Welcome!'
  ClientHeight = 307
  ClientWidth = 414
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Calibri'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  PixelsPerInch = 96
  TextHeight = 13
  object WelcomeLabel1: TLabel
    Left = 8
    Top = 8
    Width = 401
    Height = 36
    Caption = 
      'Welcome to ReaderHelper! This app will help you to get better at' +
      ' reading books, by tracking your results and motivating you.'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Calibri'
    Font.Style = []
    ParentFont = False
    WordWrap = True
  end
  object WelcomeLabel2: TLabel
    Left = 8
    Top = 93
    Width = 153
    Height = 15
    Caption = 'Input your daily pages goal:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Calibri'
    Font.Style = []
    ParentFont = False
  end
  object GoalEdit: TEdit
    Left = 8
    Top = 114
    Width = 153
    Height = 23
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Calibri'
    Font.Style = []
    MaxLength = 3
    NumbersOnly = True
    ParentFont = False
    TabOrder = 0
    OnChange = GoalEditChange
  end
  object SubmitButton: TButton
    Left = 86
    Top = 160
    Width = 75
    Height = 25
    Caption = 'Start!'
    Enabled = False
    TabOrder = 1
    OnClick = SubmitButtonClick
  end
end
