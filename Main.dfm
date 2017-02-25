object fmMain: TfmMain
  Left = 0
  Top = 0
  Caption = 'Auswertung EKG-Daten - EcgTool'
  ClientHeight = 519
  ClientWidth = 1092
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
  OnKeyDown = FormKeyDown
  OnKeyPress = FormKeyPress
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 0
    Top = 41
    Width = 1092
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -43
    ExplicitWidth = 1077
  end
  object Bevel3: TBevel
    Left = 337
    Top = 45
    Width = 4
    Height = 474
    Align = alLeft
    Shape = bsLeftLine
    ExplicitLeft = 456
    ExplicitTop = 51
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 1092
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    DesignSize = (
      1092
      41)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 1076
      Height = 25
      Anchors = [akLeft, akTop, akRight]
      BorderStyle = bsNone
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsItalic]
      Lines.Strings = (
        
          'EKG-Tool, erm'#246'glicht eine Vorab-Auswertung der EKG-Daten, soll s' +
          'p'#228'ter als Bestandteil des Gesamt-Frameworks integiert werden')
      ParentColor = True
      ParentFont = False
      TabOrder = 0
    end
  end
  object pnLeft: TPanel
    Left = 0
    Top = 45
    Width = 337
    Height = 474
    Align = alLeft
    BevelOuter = bvNone
    TabOrder = 1
    DesignSize = (
      337
      474)
    object Bevel4: TBevel
      Left = 0
      Top = 49
      Width = 337
      Height = 4
      Align = alTop
      Shape = bsTopLine
      ExplicitLeft = 232
      ExplicitTop = 56
      ExplicitWidth = 50
    end
    object laCls: TLabel
      Left = 313
      Top = 232
      Width = 18
      Height = 13
      Anchors = [akTop, akRight]
      Caption = 'CLS'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsUnderline]
      ParentFont = False
      OnClick = laClsClick
    end
    object Label4: TLabel
      Left = 139
      Top = 163
      Width = 52
      Height = 13
      Caption = 'EKG-Daten'
    end
    object Label6: TLabel
      Left = 214
      Top = 163
      Width = 47
      Height = 13
      Caption = 'Erste Abl.'
    end
    object Label7: TLabel
      Left = 281
      Top = 163
      Width = 54
      Height = 13
      Caption = 'Zweite Abl.'
    end
    object Label9: TLabel
      Left = 148
      Top = 118
      Width = 35
      Height = 13
      Caption = 'Bereich'
    end
    object Label10: TLabel
      Left = 269
      Top = 118
      Width = 4
      Height = 13
      Caption = '-'
    end
    object Label8: TLabel
      Left = 146
      Top = 87
      Width = 39
      Height = 13
      Caption = 'Samples'
    end
    object Label11: TLabel
      Left = 269
      Top = 87
      Width = 4
      Height = 13
      Caption = '-'
    end
    object Panel3: TPanel
      Left = 0
      Top = 0
      Width = 337
      Height = 49
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 11
      object Label1: TLabel
        Left = 9
        Top = 2
        Width = 62
        Height = 13
        Caption = 'EKG Inputfile'
      end
      object btInputfile: TSpeedButton
        Left = 265
        Top = 14
        Width = 23
        Height = 23
        Caption = '...'
        OnClick = btInputfileClick
      end
      object Label3: TLabel
        Left = 291
        Top = 1
        Width = 38
        Height = 13
        Caption = 'Trenner'
      end
      object edInputfile: TEdit
        Left = 8
        Top = 15
        Width = 256
        Height = 21
        TabOrder = 0
        Text = 'edInputfile'
      end
      object cbDelim: TComboBox
        Left = 292
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
    object memo: TMemo
      Left = 0
      Top = 248
      Width = 337
      Height = 226
      Align = alBottom
      ReadOnly = True
      ScrollBars = ssBoth
      TabOrder = 12
    end
    object pbJob: TProgressBar
      Left = 8
      Top = 58
      Width = 320
      Height = 17
      TabOrder = 13
    end
    object btRead: TButton
      Tag = 1
      Left = 8
      Top = 81
      Width = 125
      Height = 25
      Caption = '&1 - Werte einlesen'
      TabOrder = 0
      OnClick = btReadClick
    end
    object btMovAv: TButton
      Tag = 3
      Left = 8
      Top = 176
      Width = 125
      Height = 25
      Caption = '&3 - Kurven gl'#228'tten'
      TabOrder = 6
      OnClick = btMovAvClick
    end
    object btCut: TButton
      Tag = 2
      Left = 8
      Top = 112
      Width = 125
      Height = 25
      Caption = '&2 - Kurven schneiden'
      TabOrder = 3
      OnClick = btCutClick
    end
    object edGl1: TEdit
      Left = 142
      Top = 178
      Width = 46
      Height = 21
      TabOrder = 7
    end
    object edGl2: TEdit
      Left = 212
      Top = 178
      Width = 46
      Height = 21
      TabOrder = 8
    end
    object edGl3: TEdit
      Left = 282
      Top = 178
      Width = 46
      Height = 21
      TabOrder = 9
    end
    object edCutVon: TEdit
      Left = 212
      Top = 114
      Width = 46
      Height = 21
      TabOrder = 4
    end
    object edCutBis: TEdit
      Left = 282
      Top = 114
      Width = 46
      Height = 21
      TabOrder = 5
    end
    object edVonSample: TEdit
      Left = 212
      Top = 83
      Width = 46
      Height = 21
      TabOrder = 1
    end
    object edBisSample: TEdit
      Left = 282
      Top = 83
      Width = 46
      Height = 21
      TabOrder = 2
    end
    object cxDropBegin: TCheckBox
      Left = 142
      Top = 205
      Width = 189
      Height = 17
      Caption = 'Anfangswerte '#252'berspringen'
      TabOrder = 10
    end
  end
  object pnClient: TPanel
    Left = 341
    Top = 45
    Width = 751
    Height = 474
    Align = alClient
    BevelOuter = bvNone
    Color = clWhite
    ParentBackground = False
    TabOrder = 2
    object imgEcg: TImage
      Left = 0
      Top = 0
      Width = 751
      Height = 152
      Align = alTop
      ExplicitLeft = 2
      ExplicitTop = 2
      ExplicitWidth = 728
    end
    object Bevel2: TBevel
      Left = 0
      Top = 152
      Width = 751
      Height = 4
      Align = alTop
      Shape = bsTopLine
      ExplicitLeft = 280
      ExplicitTop = 240
      ExplicitWidth = 50
    end
    object imgDeriv1: TImage
      Left = 0
      Top = 156
      Width = 751
      Height = 152
      Align = alTop
      ExplicitLeft = -4
      ExplicitTop = 352
      ExplicitWidth = 728
    end
    object imgDeriv2: TImage
      Left = 0
      Top = 312
      Width = 751
      Height = 152
      Align = alTop
      ExplicitLeft = -4
      ExplicitTop = 308
      ExplicitWidth = 728
    end
    object Bevel5: TBevel
      Left = 0
      Top = 308
      Width = 751
      Height = 4
      Align = alTop
      Shape = bsTopLine
      ExplicitLeft = 6
      ExplicitTop = 304
      ExplicitWidth = 728
    end
    object Bevel6: TBevel
      Left = 0
      Top = 464
      Width = 751
      Height = 4
      Align = alTop
      Shape = bsTopLine
      ExplicitLeft = -4
      ExplicitTop = 344
      ExplicitWidth = 728
    end
  end
  object tStartup: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tStartupTimer
    Left = 392
    Top = 8
  end
  object OpenDialog: TOpenDialog
    Filter = 'TXT-Dateien|*.txt|CSV-Dateien|*.csv'
    Left = 424
    Top = 8
  end
  object tDetails: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tDetailsTimer
    Left = 456
    Top = 8
  end
end
