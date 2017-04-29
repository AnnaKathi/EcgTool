object fmAnalysis: TfmAnalysis
  Left = 0
  Top = 0
  Caption = 'Daten analysieren'
  ClientHeight = 537
  ClientWidth = 476
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
  object Bevel1: TBevel
    Left = 0
    Top = 41
    Width = 476
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -10
    ExplicitWidth = 549
  end
  object Bevel2: TBevel
    Left = 0
    Top = 492
    Width = 476
    Height = 4
    Align = alBottom
    Shape = bsBottomLine
    ExplicitLeft = -10
    ExplicitTop = 533
    ExplicitWidth = 549
  end
  object Bevel3: TBevel
    Left = 0
    Top = 94
    Width = 476
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitTop = 49
    ExplicitWidth = 539
  end
  object imgData: TImage
    Left = 8
    Top = 152
    Width = 460
    Height = 121
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 476
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    ExplicitLeft = -10
    ExplicitWidth = 549
    DesignSize = (
      476
      41)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 460
      Height = 25
      Anchors = [akLeft, akTop, akRight]
      BorderStyle = bsNone
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsItalic]
      Lines.Strings = (
        'EKG-Tool..., Todo: Text einf'#252'gen')
      ParentColor = True
      ParentFont = False
      ReadOnly = True
      TabOrder = 0
      ExplicitWidth = 533
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 496
    Width = 476
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    ExplicitLeft = -10
    ExplicitWidth = 549
    DesignSize = (
      476
      41)
    object Button1: TButton
      Left = 393
      Top = 6
      Width = 75
      Height = 25
      Action = acClose
      Anchors = [akTop, akRight]
      TabOrder = 0
      ExplicitLeft = 466
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 45
    Width = 476
    Height = 49
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 2
    ExplicitLeft = -8
    ExplicitTop = 145
    ExplicitWidth = 539
    object Label1: TLabel
      Left = 9
      Top = 2
      Width = 62
      Height = 13
      Caption = 'EKG Inputfile'
    end
    object btInputfile: TSpeedButton
      Left = 407
      Top = 14
      Width = 23
      Height = 23
      Caption = '...'
      OnClick = btInputfileClick
    end
    object Label3: TLabel
      Left = 433
      Top = 1
      Width = 38
      Height = 13
      Caption = 'Trenner'
    end
    object edInputfile: TEdit
      Left = 8
      Top = 15
      Width = 397
      Height = 21
      TabOrder = 0
      Text = 'edInputfile'
    end
    object cbDelim: TComboBox
      Left = 434
      Top = 15
      Width = 36
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      ItemIndex = 0
      TabOrder = 1
      Text = ';'
      Items.Strings = (
        ';'
        ','
        '\t')
    end
  end
  object Button2: TButton
    Left = 8
    Top = 104
    Width = 105
    Height = 25
    Action = acReadFile
    TabOrder = 3
  end
  object tStartup: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tStartupTimer
    Left = 224
    Top = 8
  end
  object ActionList1: TActionList
    Left = 256
    Top = 8
    object acClose: TAction
      Caption = '&Schlie'#223'en'
      OnExecute = acCloseExecute
    end
    object acLoadFile: TAction
      Caption = 'Datei laden...'
      OnExecute = acLoadFileExecute
    end
    object acReadFile: TAction
      Caption = 'Datei &einlesen'
      OnExecute = acReadFileExecute
    end
  end
  object OpenDialog: TOpenDialog
    Filter = 'TXT-Dateien|*.txt|CSV-Dateien|*.csv'
    Left = 288
    Top = 8
  end
end
