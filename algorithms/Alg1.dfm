object fmAlg1: TfmAlg1
  Left = 0
  Top = 0
  Caption = 'Algorithmus 1: SIMULATION'
  ClientHeight = 651
  ClientWidth = 791
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnKeyPress = FormKeyPress
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object imgBeat1: TImage
    Left = 8
    Top = 287
    Width = 257
    Height = 66
  end
  object imgTemplate1: TImage
    Left = 8
    Top = 447
    Width = 257
    Height = 66
  end
  object imgBeat2: TImage
    Left = 271
    Top = 287
    Width = 257
    Height = 66
  end
  object imgTemplate2: TImage
    Left = 271
    Top = 447
    Width = 257
    Height = 66
  end
  object img1: TImage
    Left = 8
    Top = 143
    Width = 257
    Height = 66
  end
  object img2: TImage
    Left = 271
    Top = 143
    Width = 257
    Height = 66
  end
  object Bevel1: TBevel
    Left = 0
    Top = 41
    Width = 791
    Height = 8
    Align = alTop
    Shape = bsTopLine
  end
  object Bevel2: TBevel
    Left = 0
    Top = 602
    Width = 791
    Height = 8
    Align = alBottom
    Shape = bsBottomLine
    ExplicitTop = 49
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 791
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    DesignSize = (
      791
      41)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 775
      Height = 25
      Anchors = [akLeft, akTop, akRight]
      BorderStyle = bsNone
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsItalic]
      Lines.Strings = (
        
          'Ansicht und Ausf'#252'hrung von Algoritmus 1 (Test der Grundfunktiona' +
          'lit'#228'ten).')
      ParentColor = True
      ParentFont = False
      TabOrder = 0
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 610
    Width = 791
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    object Button1: TButton
      Left = 8
      Top = 8
      Width = 75
      Height = 25
      Action = acClose
      TabOrder = 0
    end
  end
  object Memo: TMemo
    Left = 536
    Top = 49
    Width = 255
    Height = 553
    Align = alRight
    ReadOnly = True
    ScrollBars = ssBoth
    TabOrder = 2
    ExplicitTop = 41
    ExplicitHeight = 569
  end
  object btStep1: TButton
    Left = 8
    Top = 256
    Width = 257
    Height = 25
    Caption = 'Schritt 1 - Standardherzschl'#228'ge finden'
    TabOrder = 3
    OnClick = btStep1Click
  end
  object btStep2: TButton
    Left = 8
    Top = 416
    Width = 257
    Height = 25
    Caption = 'Schritt 2 - Templates bilden'
    TabOrder = 4
    OnClick = btStep2Click
  end
  object btStep3: TButton
    Left = 8
    Top = 568
    Width = 257
    Height = 25
    Caption = 'Schritt 3 - Klassifizierung'
    TabOrder = 5
    OnClick = btStep3Click
  end
  object ed3: TEdit
    Left = 407
    Top = 570
    Width = 121
    Height = 21
    TabOrder = 6
  end
  object cbMode: TComboBox
    Left = 271
    Top = 570
    Width = 130
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    ItemIndex = 0
    TabOrder = 7
    Text = 'Intraindividuell'
    Items.Strings = (
      'Intraindividuell'
      'Interindividuell'
      'Kreuzvergleich')
  end
  object Panel3: TPanel
    Left = 0
    Top = 47
    Width = 265
    Height = 49
    BevelOuter = bvNone
    TabOrder = 8
    object Label1: TLabel
      Left = 9
      Top = 2
      Width = 68
      Height = 13
      Caption = 'EKG Inputfile1'
    end
    object btInputfile1: TSpeedButton
      Left = 239
      Top = 14
      Width = 23
      Height = 23
      Caption = '...'
      OnClick = btInputfile1Click
    end
    object edInput1: TEdit
      Left = 8
      Top = 15
      Width = 229
      Height = 21
      TabOrder = 0
      Text = 'edInput1'
    end
  end
  object Panel2: TPanel
    Left = 268
    Top = 47
    Width = 265
    Height = 49
    BevelOuter = bvNone
    TabOrder = 9
    object Label2: TLabel
      Left = 3
      Top = 0
      Width = 68
      Height = 13
      Caption = 'EKG Inputfile2'
    end
    object btInputfile2: TSpeedButton
      Left = 239
      Top = 14
      Width = 23
      Height = 23
      Caption = '...'
      OnClick = btInputfile2Click
    end
    object edInput2: TEdit
      Left = 8
      Top = 15
      Width = 229
      Height = 21
      TabOrder = 0
      Text = 'edInput2'
    end
  end
  object btStep0: TButton
    Left = 8
    Top = 90
    Width = 257
    Height = 25
    Caption = 'Schritt 0 - EKGs einlesen'
    TabOrder = 10
    OnClick = btStep0Click
  end
  object tStartup: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tStartupTimer
    Left = 440
    Top = 8
  end
  object ActionList1: TActionList
    Left = 472
    Top = 8
    object acClose: TAction
      Caption = '&Schlie'#223'en'
      OnExecute = acCloseExecute
    end
  end
  object OpenDialog: TOpenDialog
    Filter = 'TXT-Dateien|*.txt|CSV-Dateien|*.csv'
    Left = 504
    Top = 8
  end
end
