object fmChoi: TfmChoi
  Left = 0
  Top = 0
  Caption = 'Choi 2016: Feature Extraction'
  ClientHeight = 581
  ClientWidth = 516
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
    Top = 94
    Width = 516
    Height = 8
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -8
    ExplicitTop = 169
    ExplicitWidth = 721
  end
  object Bevel2: TBevel
    Left = 0
    Top = 532
    Width = 516
    Height = 8
    Align = alBottom
    Shape = bsBottomLine
    ExplicitLeft = -70
    ExplicitTop = 602
    ExplicitWidth = 791
  end
  object Bevel4: TBevel
    Left = 0
    Top = 41
    Width = 516
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = 232
    ExplicitTop = 56
    ExplicitWidth = 50
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 516
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    DesignSize = (
      516
      41)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 500
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
          'ag)')
      ParentColor = True
      ParentFont = False
      TabOrder = 0
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 540
    Width = 516
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
  object Panel3: TPanel
    Left = 0
    Top = 45
    Width = 516
    Height = 49
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 2
    object Label1: TLabel
      Left = 9
      Top = 2
      Width = 62
      Height = 13
      Caption = 'EKG Inputfile'
    end
    object btInputfile: TSpeedButton
      Left = 398
      Top = 14
      Width = 23
      Height = 23
      Caption = '...'
      OnClick = btInputfileClick
    end
    object Label3: TLabel
      Left = 467
      Top = 1
      Width = 38
      Height = 13
      Caption = 'Trenner'
    end
    object Label2: TLabel
      Left = 431
      Top = 1
      Width = 34
      Height = 13
      Caption = 'Format'
    end
    object edInputfile: TEdit
      Left = 8
      Top = 15
      Width = 388
      Height = 21
      TabOrder = 0
      Text = 'edInputfile'
    end
    object cbDelim: TComboBox
      Left = 469
      Top = 15
      Width = 36
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      ItemIndex = 0
      TabOrder = 2
      Text = ';'
      Items.Strings = (
        ';'
        ','
        '\t')
    end
    object cbFormat: TComboBox
      Left = 429
      Top = 15
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
  end
  object pnMain: TPanel
    Left = 0
    Top = 102
    Width = 516
    Height = 430
    Align = alClient
    BevelOuter = bvNone
    ParentBackground = False
    TabOrder = 3
    object Bevel6: TBevel
      Left = 0
      Top = 153
      Width = 516
      Height = 8
      Align = alTop
      Shape = bsTopLine
      ExplicitLeft = 144
      ExplicitTop = 208
      ExplicitWidth = 50
    end
    object imgBeat: TImage
      Left = 6
      Top = 174
      Width = 179
      Height = 79
    end
    object Label5: TLabel
      Left = 48
      Top = 155
      Width = 95
      Height = 13
      Caption = 'Standardherzschlag'
    end
    object Label6: TLabel
      Left = 214
      Top = 155
      Width = 116
      Height = 13
      Caption = 'Fiducial Points Averages'
    end
    object Label7: TLabel
      Left = 384
      Top = 176
      Width = 47
      Height = 13
      Caption = 'Threshold'
    end
    object Label8: TLabel
      Left = 384
      Top = 203
      Width = 59
      Height = 13
      Caption = 'Overlap(ms)'
    end
    object pnEcgGes: TPanel
      Left = 0
      Top = 0
      Width = 516
      Height = 153
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 0
      object imgEcg: TImage
        Left = 10
        Top = 37
        Width = 495
        Height = 105
      end
      object btRead: TButton
        Left = 8
        Top = 6
        Width = 137
        Height = 25
        Caption = '&ECG-Daten einlesen'
        TabOrder = 0
        OnClick = btReadClick
      end
      object Button3: TButton
        Left = 390
        Top = 6
        Width = 115
        Height = 25
        Caption = 'Gesamt-Aufruf Choi'
        TabOrder = 1
        OnClick = Button3Click
      end
    end
    object Memo: TMemo
      Left = 0
      Top = 261
      Width = 516
      Height = 169
      Align = alBottom
      ReadOnly = True
      ScrollBars = ssBoth
      TabOrder = 1
    end
    object mFid: TMemo
      Left = 191
      Top = 174
      Width = 172
      Height = 79
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -9
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 2
    end
    object edThreshold: TEdit
      Left = 445
      Top = 173
      Width = 60
      Height = 21
      TabOrder = 3
    end
    object edOverlap: TEdit
      Left = 445
      Top = 200
      Width = 60
      Height = 21
      TabOrder = 4
    end
    object Button4: TButton
      Left = 150
      Top = 6
      Width = 90
      Height = 25
      Caption = 'R-Peaks &Anna'
      TabOrder = 5
      OnClick = Button4Click
    end
    object Button2: TButton
      Left = 246
      Top = 6
      Width = 90
      Height = 25
      Caption = 'R-Peaks &Choi'
      TabOrder = 6
      OnClick = Button2Click
    end
    object btTestSVM: TButton
      Left = 384
      Top = 230
      Width = 121
      Height = 25
      Caption = 'Test libSVM'
      TabOrder = 7
      OnClick = btTestSVMClick
    end
  end
  object tStartup: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tStartupTimer
    Left = 416
    Top = 8
  end
  object ActionList1: TActionList
    Left = 448
    Top = 8
    object acClose: TAction
      Caption = '&Schlie'#223'en'
      OnExecute = acCloseExecute
    end
  end
  object OpenDialog: TOpenDialog
    Filter = 'TXT-Dateien|*.txt|CSV-Dateien|*.csv'
    Left = 480
    Top = 8
  end
end
