object fmChoi: TfmChoi
  Left = 0
  Top = 0
  Caption = 'Choi 2016: Feature Extraction'
  ClientHeight = 689
  ClientWidth = 916
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
    Width = 916
    Height = 8
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -8
    ExplicitTop = 169
    ExplicitWidth = 721
  end
  object Bevel2: TBevel
    Left = 0
    Top = 640
    Width = 916
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
    Width = 916
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = 232
    ExplicitTop = 56
    ExplicitWidth = 50
  end
  object Bevel7: TBevel
    Left = 723
    Top = 102
    Width = 8
    Height = 538
    Align = alRight
    Shape = bsRightLine
    ExplicitLeft = 754
    ExplicitTop = 100
  end
  object Bevel3: TBevel
    Left = 528
    Top = 102
    Width = 8
    Height = 538
    Align = alRight
    Shape = bsRightLine
    ExplicitLeft = 538
    ExplicitTop = 110
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 916
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    ExplicitWidth = 1075
    DesignSize = (
      916
      41)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 900
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
      ExplicitWidth = 1059
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 648
    Width = 916
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    ExplicitWidth = 1075
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
    Width = 916
    Height = 49
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 2
    ExplicitWidth = 1075
    object Label1: TLabel
      Left = 9
      Top = 2
      Width = 62
      Height = 13
      Caption = 'EKG Inputfile'
    end
    object btInputfile: TSpeedButton
      Left = 592
      Top = 14
      Width = 23
      Height = 23
      Caption = '...'
      OnClick = btInputfileClick
    end
    object Label3: TLabel
      Left = 661
      Top = 1
      Width = 38
      Height = 13
      Caption = 'Trenner'
    end
    object Label2: TLabel
      Left = 625
      Top = 1
      Width = 34
      Height = 13
      Caption = 'Format'
    end
    object edInputfile: TEdit
      Left = 8
      Top = 15
      Width = 583
      Height = 21
      TabOrder = 0
      Text = 'edInputfile'
    end
    object cbDelim: TComboBox
      Left = 662
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
      Left = 623
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
    Width = 528
    Height = 538
    Align = alClient
    BevelOuter = bvNone
    ParentBackground = False
    TabOrder = 3
    ExplicitLeft = 2
    ExplicitTop = 104
    object Bevel6: TBevel
      Left = 0
      Top = 153
      Width = 528
      Height = 8
      Align = alTop
      Shape = bsTopLine
      ExplicitLeft = 144
      ExplicitTop = 208
      ExplicitWidth = 50
    end
    object imgBeat: TImage
      Left = 8
      Top = 199
      Width = 179
      Height = 79
    end
    object Label5: TLabel
      Left = 50
      Top = 180
      Width = 95
      Height = 13
      Caption = 'Standardherzschlag'
    end
    object Label6: TLabel
      Left = 216
      Top = 180
      Width = 116
      Height = 13
      Caption = 'Fiducial Points Averages'
    end
    object pnEcgGes: TPanel
      Left = 0
      Top = 0
      Width = 528
      Height = 153
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 0
      ExplicitWidth = 472
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
        Caption = '1 - ECG-Daten einlesen'
        TabOrder = 0
        OnClick = btReadClick
      end
    end
    object Memo: TMemo
      Left = 0
      Top = 369
      Width = 528
      Height = 169
      Align = alBottom
      ReadOnly = True
      TabOrder = 1
      ExplicitWidth = 472
    end
    object mFid: TMemo
      Left = 193
      Top = 199
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
  end
  object Panel5: TPanel
    Left = 536
    Top = 102
    Width = 187
    Height = 538
    Align = alRight
    BevelOuter = bvNone
    TabOrder = 4
    object imgNeu1: TImage
      Left = 6
      Top = 29
      Width = 179
      Height = 79
    end
    object imgNeu2: TImage
      Left = 6
      Top = 114
      Width = 179
      Height = 79
    end
    object imgNeu3: TImage
      Left = 6
      Top = 199
      Width = 179
      Height = 79
    end
    object imgNeu4: TImage
      Left = 6
      Top = 284
      Width = 179
      Height = 79
    end
    object imgNeu5: TImage
      Left = 6
      Top = 369
      Width = 179
      Height = 79
    end
    object imgNeu6: TImage
      Left = 6
      Top = 454
      Width = 179
      Height = 79
    end
    object Button4: TButton
      Left = 6
      Top = 1
      Width = 137
      Height = 25
      Caption = '2 - Get R-Peaks NEU'
      TabOrder = 0
      OnClick = Button4Click
    end
  end
  object pnFid: TPanel
    Left = 731
    Top = 102
    Width = 185
    Height = 538
    Align = alRight
    BevelOuter = bvNone
    TabOrder = 5
    ExplicitLeft = 729
    ExplicitTop = 104
    object Label4: TLabel
      Left = 8
      Top = 8
      Width = 75
      Height = 14
      Caption = 'Fiducial Points'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsUnderline]
      ParentFont = False
    end
    object m1: TMemo
      Left = 6
      Top = 29
      Width = 172
      Height = 79
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -9
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 0
    end
    object m2: TMemo
      Left = 6
      Top = 114
      Width = 172
      Height = 79
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -9
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 1
    end
    object m3: TMemo
      Left = 6
      Top = 199
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
    object m4: TMemo
      Left = 6
      Top = 284
      Width = 172
      Height = 79
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -9
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 3
    end
    object m5: TMemo
      Left = 6
      Top = 369
      Width = 172
      Height = 79
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -9
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 4
    end
    object m6: TMemo
      Left = 6
      Top = 454
      Width = 172
      Height = 79
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -9
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 5
    end
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
