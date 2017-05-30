object fmSingle: TfmSingle
  Left = 0
  Top = 0
  Caption = 'Einzel-Auswertung'
  ClientHeight = 666
  ClientWidth = 1067
  Color = clWhite
  Font.Charset = ANSI_CHARSET
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
  object Bevel1: TBevel
    Left = 0
    Top = 41
    Width = 1067
    Height = 8
    Align = alTop
    Shape = bsTopLine
    ExplicitWidth = 947
  end
  object Bevel2: TBevel
    Left = 0
    Top = 617
    Width = 1067
    Height = 8
    Align = alBottom
    Shape = bsBottomLine
    ExplicitTop = 57
    ExplicitWidth = 947
  end
  object Bevel3: TBevel
    Left = 289
    Top = 49
    Width = 2
    Height = 568
    Align = alLeft
    Shape = bsLeftLine
    ExplicitLeft = 360
    ExplicitTop = 216
    ExplicitHeight = 50
  end
  object Bevel4: TBevel
    Left = 702
    Top = 49
    Width = 2
    Height = 568
    Align = alLeft
    Shape = bsLeftLine
    ExplicitLeft = 313
    ExplicitTop = 57
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 1067
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    DesignSize = (
      1067
      41)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 1051
      Height = 25
      Anchors = [akLeft, akTop, akRight]
      BorderStyle = bsNone
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsItalic]
      Lines.Strings = (
        
          'Einzel-Auswertung: Ein bestimmtes EKG mit allen anderen vergleic' +
          'hen.')
      ParentColor = True
      ParentFont = False
      ReadOnly = True
      TabOrder = 0
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 625
    Width = 1067
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    DesignSize = (
      1067
      41)
    object Button1: TButton
      Left = 984
      Top = 6
      Width = 75
      Height = 25
      Action = acClose
      Anchors = [akTop, akRight]
      TabOrder = 0
    end
  end
  object pnAuswertung: TPanel
    Left = 704
    Top = 49
    Width = 363
    Height = 568
    Align = alClient
    BevelOuter = bvNone
    Color = clWhite
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Verdana'
    Font.Style = []
    ParentBackground = False
    ParentFont = False
    TabOrder = 2
    object Label4: TLabel
      Left = 16
      Top = 24
      Width = 113
      Height = 18
      Caption = 'Intra-Individuell'
      Color = clMoneyGreen
      Font.Charset = ANSI_CHARSET
      Font.Color = clGreen
      Font.Height = -15
      Font.Name = 'Verdana'
      Font.Style = [fsUnderline]
      ParentColor = False
      ParentFont = False
    end
    object Memo1: TMemo
      Left = 16
      Top = 48
      Width = 185
      Height = 73
      TabStop = False
      BorderStyle = bsNone
      Font.Charset = ANSI_CHARSET
      Font.Color = clGreen
      Font.Height = -12
      Font.Name = 'Verdana'
      Font.Style = [fsItalic]
      Lines.Strings = (
        'Vergleich der ausgew'#228'hlten '
        'Platzierung mit allen anderen '
        'Platzierungen der gleichen '
        'Person.')
      ParentColor = True
      ParentFont = False
      ReadOnly = True
      TabOrder = 0
    end
    object mAus: TMemo
      Left = 6
      Top = 136
      Width = 339
      Height = 426
      Lines.Strings = (
        'mAus')
      TabOrder = 1
    end
  end
  object pnFilterEcg: TPanel
    Left = 291
    Top = 49
    Width = 411
    Height = 568
    Align = alLeft
    BevelOuter = bvNone
    Caption = 'pnFilterEcg'
    Color = clWhite
    ParentBackground = False
    TabOrder = 3
  end
  object pnFilterPerson: TPanel
    Left = 0
    Top = 49
    Width = 289
    Height = 568
    Align = alLeft
    BevelOuter = bvNone
    Caption = 'pnFilterPerson'
    Color = clWhite
    ParentBackground = False
    TabOrder = 4
  end
  object tStartup: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tStartupTimer
    Left = 232
    Top = 8
  end
  object ActionList1: TActionList
    Left = 264
    Top = 8
    object acClose: TAction
      Caption = '&Schlie'#223'en'
      OnExecute = acCloseExecute
    end
  end
end
