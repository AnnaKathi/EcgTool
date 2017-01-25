object fmMain: TfmMain
  Left = 0
  Top = 0
  Caption = 'EcgTool: Main'
  ClientHeight = 685
  ClientWidth = 1077
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
    Width = 1077
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = 232
    ExplicitTop = 56
    ExplicitWidth = 50
  end
  object Bevel3: TBevel
    Left = 409
    Top = 45
    Width = 4
    Height = 640
    Align = alLeft
    Shape = bsLeftLine
    ExplicitLeft = 576
    ExplicitTop = 136
    ExplicitHeight = 50
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 1077
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    ExplicitWidth = 1036
    DesignSize = (
      1077
      41)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 1061
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
      ExplicitWidth = 1020
    end
  end
  object pnLeft: TPanel
    Left = 0
    Top = 45
    Width = 409
    Height = 640
    Align = alLeft
    BevelOuter = bvNone
    TabOrder = 1
    ExplicitLeft = -6
    ExplicitTop = 41
    DesignSize = (
      409
      640)
    object Bevel4: TBevel
      Left = 0
      Top = 97
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
      Top = 437
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
      Height = 97
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 0
      ExplicitLeft = 96
      ExplicitTop = 138
      ExplicitWidth = 417
      object Label1: TLabel
        Left = 8
        Top = 13
        Width = 63
        Height = 13
        Caption = 'ECG Inputfile'
      end
      object btInputfile: TSpeedButton
        Left = 378
        Top = 9
        Width = 23
        Height = 22
        Caption = '...'
        OnClick = btInputfileClick
      end
      object Label2: TLabel
        Left = 8
        Top = 40
        Width = 49
        Height = 13
        Caption = 'Von Index'
      end
      object Label5: TLabel
        Left = 8
        Top = 67
        Width = 44
        Height = 13
        Caption = 'Bis Index'
      end
      object Label4: TLabel
        Left = 156
        Top = 40
        Width = 50
        Height = 13
        Caption = 'Von M.Sek'
      end
      object Label6: TLabel
        Left = 156
        Top = 67
        Width = 45
        Height = 13
        Caption = 'Bis M.Sek'
      end
      object Label7: TLabel
        Left = 289
        Top = 40
        Width = 47
        Height = 13
        Caption = 'Min. Wert'
      end
      object Label8: TLabel
        Left = 289
        Top = 67
        Width = 51
        Height = 13
        Caption = 'Max. Wert'
      end
      object edInputfile: TEdit
        Left = 77
        Top = 10
        Width = 301
        Height = 21
        TabOrder = 0
        Text = 'edInputfile'
      end
      object edVonIdx: TEdit
        Left = 77
        Top = 37
        Width = 60
        Height = 21
        TabOrder = 1
      end
      object edBisIdx: TEdit
        Left = 77
        Top = 64
        Width = 60
        Height = 21
        TabOrder = 2
      end
      object edVonMsec: TEdit
        Left = 214
        Top = 37
        Width = 60
        Height = 21
        TabOrder = 3
      end
      object edBisMsec: TEdit
        Left = 214
        Top = 64
        Width = 60
        Height = 21
        TabOrder = 4
      end
      object edMinWert: TEdit
        Left = 341
        Top = 37
        Width = 60
        Height = 21
        TabOrder = 5
      end
      object edMaxWert: TEdit
        Left = 341
        Top = 64
        Width = 60
        Height = 21
        TabOrder = 6
      end
    end
    object memo: TMemo
      Left = 0
      Top = 456
      Width = 409
      Height = 184
      Align = alBottom
      ReadOnly = True
      ScrollBars = ssBoth
      TabOrder = 1
    end
    object pbJob: TProgressBar
      Left = 0
      Top = 101
      Width = 409
      Height = 17
      Align = alTop
      TabOrder = 2
      ExplicitLeft = 10
      ExplicitTop = 103
      ExplicitWidth = 393
    end
    object btRead: TButton
      Left = 6
      Top = 128
      Width = 180
      Height = 25
      Caption = '&1 - Werte einlesen'
      TabOrder = 3
      OnClick = btReadClick
    end
    object btMaxMin: TButton
      Left = 6
      Top = 159
      Width = 180
      Height = 25
      Caption = '&2 - Draw Image Gesamt'
      Enabled = False
      TabOrder = 4
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
