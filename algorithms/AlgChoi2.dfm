object fmChoi2: TfmChoi2
  Left = 0
  Top = 0
  Caption = 'ECG-Classification Choi 2016'
  ClientHeight = 696
  ClientWidth = 1081
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poDesktopCenter
  OnClose = FormClose
  OnKeyPress = FormKeyPress
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel4: TBevel
    Left = 0
    Top = 41
    Width = 1081
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = 232
    ExplicitTop = 56
    ExplicitWidth = 50
  end
  object Bevel2: TBevel
    Left = 0
    Top = 647
    Width = 1081
    Height = 8
    Align = alBottom
    Shape = bsBottomLine
    ExplicitLeft = -70
    ExplicitTop = 602
    ExplicitWidth = 791
  end
  object Bevel5: TBevel
    Left = 0
    Top = 602
    Width = 1081
    Height = 4
    Align = alBottom
    Shape = bsBottomLine
    ExplicitTop = 94
    ExplicitWidth = 948
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 1081
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    DesignSize = (
      1081
      41)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 1065
      Height = 25
      Anchors = [akLeft, akTop, akRight]
      BorderStyle = bsNone
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsItalic]
      Lines.Strings = (
        
          'Feature Extraction nach Choi 2016 (acht fid. points pro Herzschl' +
          'ag), dann libSVM als Klassifikation')
      ParentColor = True
      ParentFont = False
      TabOrder = 0
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 655
    Width = 1081
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    DesignSize = (
      1081
      41)
    object Button1: TButton
      Left = 998
      Top = 6
      Width = 75
      Height = 25
      Action = acClose
      Anchors = [akRight, akBottom]
      TabOrder = 0
    end
    object btReset: TButton
      Left = 8
      Top = 6
      Width = 75
      Height = 25
      Action = acReset
      TabOrder = 1
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 606
    Width = 1081
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 2
    object Label3: TLabel
      Left = 46
      Top = 3
      Width = 38
      Height = 13
      Caption = 'Trenner'
    end
    object Label2: TLabel
      Left = 10
      Top = 3
      Width = 34
      Height = 13
      Caption = 'Format'
    end
    object laFold: TLabel
      Left = 849
      Top = 17
      Width = 50
      Height = 13
      Caption = 'Cross Fold'
    end
    object cbDelim: TComboBox
      Left = 48
      Top = 14
      Width = 36
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      ItemIndex = 0
      TabOrder = 0
      Text = ';'
      Items.Strings = (
        ';'
        ','
        '\t')
    end
    object cbFormat: TComboBox
      Left = 8
      Top = 14
      Width = 36
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      ItemIndex = 0
      TabOrder = 1
      Text = '---'
      Items.Strings = (
        '---'
        'ADS')
    end
    object Button2: TButton
      Left = 104
      Top = 10
      Width = 97
      Height = 25
      Action = acCheckEcgs
      TabOrder = 2
    end
    object Button3: TButton
      Left = 416
      Top = 10
      Width = 146
      Height = 25
      Action = acDoEcgs
      TabOrder = 3
    end
    object cxCrossvalidation: TCheckBox
      Left = 738
      Top = 16
      Width = 97
      Height = 17
      Caption = 'Crossvalidation'
      TabOrder = 4
    end
    object edFold: TEdit
      Left = 914
      Top = 14
      Width = 60
      Height = 21
      TabOrder = 5
    end
    object btAlt: TButton
      Left = 217
      Top = 10
      Width = 179
      Height = 25
      Caption = 'EKGs einlesen ALT'
      TabOrder = 6
      OnClick = btAltClick
    end
    object btExeFiles: TButton
      Left = 568
      Top = 10
      Width = 153
      Height = 25
      Caption = 'Use EXE-Files'
      TabOrder = 7
      OnClick = btExeFilesClick
    end
  end
  object pnClassification: TPanel
    Left = 0
    Top = 45
    Width = 800
    Height = 557
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 3
    object lvData: TListView
      Left = 0
      Top = 65
      Width = 800
      Height = 492
      Align = alClient
      Columns = <
        item
          Caption = 'Nr'
          Width = 30
        end
        item
          Caption = 'Anna'
          Width = 190
        end
        item
          Caption = 'Manni'
          Width = 190
        end
        item
          Caption = 'Manuela'
          Width = 190
        end
        item
          Caption = 'Martin'
          Width = 190
        end>
      GridLines = True
      TabOrder = 0
      ViewStyle = vsReport
    end
    object Panel2: TPanel
      Left = 0
      Top = 0
      Width = 800
      Height = 65
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 1
      object Label1: TLabel
        Left = 376
        Top = 6
        Width = 186
        Height = 16
        Caption = 'EKG-Daten f'#252'r die Klassifizierung'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object btAddAnna: TButton
        Left = 34
        Top = 24
        Width = 170
        Height = 25
        Action = acAddAnna
        TabOrder = 0
      end
      object btAddManni: TButton
        Left = 219
        Top = 24
        Width = 170
        Height = 25
        Action = acAddManni
        TabOrder = 1
      end
      object btAddManu: TButton
        Left = 412
        Top = 24
        Width = 170
        Height = 25
        Action = acAddManu
        TabOrder = 2
      end
      object btAddMartin: TButton
        Left = 602
        Top = 24
        Width = 170
        Height = 25
        Action = acAddMartin
        TabOrder = 3
      end
    end
  end
  object memo: TMemo
    Left = 800
    Top = 45
    Width = 281
    Height = 557
    Align = alRight
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
    ReadOnly = True
    ScrollBars = ssBoth
    TabOrder = 4
  end
  object tStartup: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tStartupTimer
    Left = 416
    Top = 8
  end
  object OpenDialog: TOpenDialog
    Filter = 'TXT-Dateien|*.txt|CSV-Dateien|*.csv'
    Left = 448
    Top = 8
  end
  object ActionList1: TActionList
    Left = 480
    Top = 8
    object acClose: TAction
      Caption = '&Schliessen'
      OnExecute = acCloseExecute
    end
    object acReset: TAction
      Caption = '&Reset'
      OnExecute = acResetExecute
    end
    object acAddAnna: TAction
      Caption = 'Add ECG &Anna'
      OnExecute = acAddAnnaExecute
    end
    object acAddManni: TAction
      Caption = 'Add ECG &Manfred'
      OnExecute = acAddManniExecute
    end
    object acAddManu: TAction
      Caption = 'Add ECG Man&uela'
      OnExecute = acAddManuExecute
    end
    object acAddMartin: TAction
      Caption = 'Add ECG Mar&tin'
      OnExecute = acAddMartinExecute
    end
    object acDelAnna: TAction
      Caption = 'Datensatz Anna l'#246'schen'
    end
    object acDelManni: TAction
      Caption = 'Datensatz Manfred l'#246'schen'
    end
    object acDelManu: TAction
      Caption = 'Datensatz Manuela l'#246'schen'
    end
    object acDelMartin: TAction
      Caption = 'Datensatz Martin l'#246'schen'
    end
    object acCheckEcgs: TAction
      Caption = 'EKGs pr'#252'fen'
      OnExecute = acCheckEcgsExecute
    end
    object acDoEcgs: TAction
      Caption = 'EKGs einlesen NEU'
      OnExecute = acDoEcgsExecute
    end
  end
  object PopupMenu: TPopupMenu
    Left = 512
    Top = 144
  end
end
