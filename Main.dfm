object fmMain: TfmMain
  Left = 0
  Top = 0
  Caption = 'fmMain'
  ClientHeight = 666
  ClientWidth = 1034
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
    Width = 1034
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
    Height = 621
    Align = alLeft
    Shape = bsLeftLine
    ExplicitTop = 26
    ExplicitHeight = 640
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 1034
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    ExplicitLeft = -43
    ExplicitWidth = 1077
    DesignSize = (
      1034
      41)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 1018
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
      ExplicitWidth = 1061
    end
  end
  object pnLeft: TPanel
    Left = 0
    Top = 45
    Width = 409
    Height = 621
    Align = alLeft
    BevelOuter = bvNone
    TabOrder = 1
    ExplicitTop = 26
    ExplicitHeight = 640
    DesignSize = (
      409
      621)
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
      Top = 154
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
      ExplicitTop = 173
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
      Top = 173
      Width = 409
      Height = 448
      Align = alBottom
      ReadOnly = True
      ScrollBars = ssBoth
      TabOrder = 1
      ExplicitTop = 192
    end
    object pbJob: TProgressBar
      Left = 8
      Top = 75
      Width = 395
      Height = 17
      TabOrder = 2
    end
    object btRead: TButton
      Left = 8
      Top = 98
      Width = 180
      Height = 25
      Caption = '&1 - Werte einlesen'
      TabOrder = 3
    end
    object btDraw: TButton
      Left = 8
      Top = 129
      Width = 180
      Height = 25
      Caption = '&2 - Draw Image Gesamt'
      Enabled = False
      TabOrder = 4
    end
  end
  object pnClient: TPanel
    Left = 413
    Top = 45
    Width = 621
    Height = 621
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 2
    ExplicitLeft = 370
    ExplicitTop = 26
    ExplicitWidth = 664
    ExplicitHeight = 640
    object imgEcg: TImage
      Left = 0
      Top = 0
      Width = 621
      Height = 152
      Align = alTop
      ExplicitWidth = 664
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
    Filter = 'CSV-Dateien|*.csv'
    Left = 424
    Top = 8
  end
end
