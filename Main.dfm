object fmMain: TfmMain
  Left = 0
  Top = 0
  Caption = 'fmMain'
  ClientHeight = 696
  ClientWidth = 1141
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
    Width = 1141
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -43
    ExplicitWidth = 1077
  end
  object Bevel3: TBevel
    Left = 409
    Top = 45
    Width = 4
    Height = 651
    Align = alLeft
    Shape = bsLeftLine
    ExplicitTop = 26
    ExplicitHeight = 640
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 1141
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    DesignSize = (
      1141
      41)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 1125
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
    Width = 409
    Height = 651
    Align = alLeft
    BevelOuter = bvNone
    TabOrder = 1
    DesignSize = (
      409
      651)
    object Bevel4: TBevel
      Left = 0
      Top = 65
      Width = 409
      Height = 4
      Align = alTop
      Shape = bsTopLine
      ExplicitLeft = 232
      ExplicitTop = 56
      ExplicitWidth = 50
    end
    object laCls: TLabel
      Left = 385
      Top = 269
      Width = 18
      Height = 13
      Anchors = [akRight, akBottom]
      Caption = 'CLS'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsUnderline]
      ParentFont = False
      OnClick = laClsClick
    end
    object Panel3: TPanel
      Left = 0
      Top = 0
      Width = 409
      Height = 65
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 0
      object Label1: TLabel
        Left = 8
        Top = 13
        Width = 63
        Height = 13
        Caption = 'ECG Inputfile'
      end
      object btInputfile: TSpeedButton
        Left = 380
        Top = 9
        Width = 23
        Height = 22
        Caption = '...'
        OnClick = btInputfileClick
      end
      object Label2: TLabel
        Left = 8
        Top = 40
        Width = 55
        Height = 13
        Caption = 'Von Sample'
      end
      object Label5: TLabel
        Left = 168
        Top = 40
        Width = 50
        Height = 13
        Caption = 'Bis Sample'
      end
      object Label3: TLabel
        Left = 323
        Top = 40
        Width = 38
        Height = 13
        Caption = 'Trenner'
      end
      object edInputfile: TEdit
        Left = 77
        Top = 10
        Width = 303
        Height = 21
        TabOrder = 0
        Text = 'edInputfile'
      end
      object edVonSample: TEdit
        Left = 77
        Top = 37
        Width = 60
        Height = 21
        TabOrder = 1
      end
      object edBisSample: TEdit
        Left = 237
        Top = 37
        Width = 60
        Height = 21
        TabOrder = 2
      end
      object cbDelim: TComboBox
        Left = 367
        Top = 37
        Width = 36
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        ItemIndex = 0
        TabOrder = 3
        Text = ';'
        Items.Strings = (
          ';'
          ','
          '\t')
      end
    end
    object memo: TMemo
      Left = 0
      Top = 288
      Width = 409
      Height = 363
      Align = alBottom
      ReadOnly = True
      ScrollBars = ssBoth
      TabOrder = 1
    end
    object pbJob: TProgressBar
      Left = 8
      Top = 75
      Width = 395
      Height = 17
      TabOrder = 2
    end
    object btRead: TButton
      Tag = 1
      Left = 8
      Top = 98
      Width = 125
      Height = 25
      Caption = '&1 - Werte einlesen'
      TabOrder = 3
      OnClick = btReadClick
    end
    object btMovAv: TButton
      Tag = 2
      Left = 8
      Top = 127
      Width = 125
      Height = 25
      Caption = '&2 - Kurve gl'#228'tten'
      TabOrder = 4
      OnClick = btMovAvClick
    end
    object btCut: TButton
      Tag = 3
      Left = 8
      Top = 158
      Width = 125
      Height = 25
      Caption = '&3 - Kurve schneiden'
      TabOrder = 5
      OnClick = btCutClick
    end
    object btRpeaks: TButton
      Tag = 4
      Left = 8
      Top = 189
      Width = 125
      Height = 25
      Caption = '&4 - R-Peaks'
      TabOrder = 6
      OnClick = btRpeaksClick
    end
    object btDerivates: TButton
      Tag = 6
      Left = 144
      Top = 98
      Width = 125
      Height = 25
      Caption = '&q - 1. Ableitung bilden'
      TabOrder = 8
      OnClick = btDerivatesClick
    end
    object btAblMovAv: TButton
      Tag = 7
      Left = 144
      Top = 127
      Width = 125
      Height = 25
      Caption = '&w - Kurve gl'#228'tten'
      TabOrder = 9
      OnClick = btAblMovAvClick
    end
    object btAblCut: TButton
      Tag = 8
      Left = 144
      Top = 158
      Width = 125
      Height = 25
      Caption = '&e - Kurve schneiden'
      TabOrder = 10
      OnClick = btAblCutClick
    end
    object btAblTurns: TButton
      Tag = 9
      Left = 144
      Top = 189
      Width = 125
      Height = 25
      Caption = '&r - R-Peaks'
      TabOrder = 11
      OnClick = btAblTurnsClick
    end
    object btAbl2: TButton
      Tag = 10
      Left = 278
      Top = 98
      Width = 125
      Height = 25
      Caption = '&a - 2. Ableitung bilden'
      TabOrder = 12
      OnClick = btAbl2Click
    end
    object btAbl2MovAv: TButton
      Tag = 11
      Left = 278
      Top = 127
      Width = 125
      Height = 25
      Caption = '&s - Kurve gl'#228'tten'
      TabOrder = 13
      OnClick = btAbl2MovAvClick
    end
    object btAbl2Cut: TButton
      Tag = 12
      Left = 278
      Top = 158
      Width = 125
      Height = 25
      Caption = '&d - Kurve schneiden'
      TabOrder = 14
      OnClick = btAbl2CutClick
    end
    object btAbl2Turns: TButton
      Tag = 13
      Left = 278
      Top = 189
      Width = 125
      Height = 25
      Caption = '&f - R-Peaks'
      TabOrder = 15
      OnClick = btAbl2TurnsClick
    end
    object btHeartbeat: TButton
      Tag = 5
      Left = 8
      Top = 220
      Width = 125
      Height = 25
      Caption = '&5 - Heartbeat'
      TabOrder = 7
      OnClick = btHeartbeatClick
    end
  end
  object pnClient: TPanel
    Left = 413
    Top = 45
    Width = 728
    Height = 651
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 2
    object imgEcg: TImage
      Left = 0
      Top = 0
      Width = 728
      Height = 152
      Align = alTop
      ExplicitLeft = 2
      ExplicitTop = 2
    end
    object Bevel2: TBevel
      Left = 0
      Top = 152
      Width = 728
      Height = 4
      Align = alTop
      Shape = bsTopLine
      ExplicitLeft = 280
      ExplicitTop = 240
      ExplicitWidth = 50
    end
    object img2: TImage
      Left = 0
      Top = 156
      Width = 728
      Height = 152
      Align = alTop
      ExplicitLeft = -4
      ExplicitTop = 352
    end
    object img3: TImage
      Left = 0
      Top = 312
      Width = 728
      Height = 152
      Align = alTop
      ExplicitLeft = -4
      ExplicitTop = 308
    end
    object Bevel5: TBevel
      Left = 0
      Top = 308
      Width = 728
      Height = 4
      Align = alTop
      Shape = bsTopLine
      ExplicitLeft = 6
      ExplicitTop = 304
    end
    object Bevel6: TBevel
      Left = 0
      Top = 464
      Width = 728
      Height = 4
      Align = alTop
      Shape = bsTopLine
      ExplicitLeft = -4
      ExplicitTop = 344
    end
    object img4: TImage
      Left = 0
      Top = 468
      Width = 728
      Height = 152
      Align = alTop
      ExplicitLeft = 2
      ExplicitTop = 314
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
end
