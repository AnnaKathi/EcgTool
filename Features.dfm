object fmFeatures: TfmFeatures
  Left = 0
  Top = 0
  Caption = 'Features bilden'
  ClientHeight = 691
  ClientWidth = 1290
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
    Width = 1290
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -504
    ExplicitWidth = 1073
  end
  object Bevel2: TBevel
    Left = 0
    Top = 646
    Width = 1290
    Height = 4
    Align = alBottom
    Shape = bsBottomLine
    ExplicitLeft = -504
    ExplicitTop = 545
    ExplicitWidth = 1073
  end
  object Bevel4: TBevel
    Left = 625
    Top = 45
    Width = 8
    Height = 601
    Align = alLeft
    Shape = bsLeftLine
    ExplicitLeft = 488
    ExplicitTop = 144
    ExplicitHeight = 50
  end
  object Bevel6: TBevel
    Left = 921
    Top = 45
    Width = 8
    Height = 601
    Align = alLeft
    Shape = bsLeftLine
    ExplicitLeft = 753
    ExplicitTop = 49
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 1290
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    DesignSize = (
      1290
      41)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 1274
      Height = 25
      Anchors = [akLeft, akTop, akRight]
      BorderStyle = bsNone
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsItalic]
      Lines.Strings = (
        
          'Features f'#252'r die in der Datenbank vorhandenen EKG-Daten erstelle' +
          'n')
      ParentColor = True
      ParentFont = False
      ReadOnly = True
      TabOrder = 0
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 650
    Width = 1290
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    DesignSize = (
      1290
      41)
    object btClose: TButton
      Left = 1207
      Top = 6
      Width = 75
      Height = 25
      Action = acClose
      Anchors = [akRight, akBottom]
      TabOrder = 0
    end
    object pbJob: TProgressBar
      Left = 8
      Top = 6
      Width = 1193
      Height = 25
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 1
      Visible = False
    end
  end
  object pnEcg: TPanel
    Left = 0
    Top = 45
    Width = 625
    Height = 601
    Align = alLeft
    BevelOuter = bvNone
    TabOrder = 2
  end
  object pnAuswahl: TPanel
    Left = 633
    Top = 45
    Width = 288
    Height = 601
    Align = alLeft
    BevelOuter = bvNone
    TabOrder = 3
    DesignSize = (
      288
      601)
    object Bevel3: TBevel
      Left = 0
      Top = 337
      Width = 288
      Height = 8
      Align = alTop
      Shape = bsTopLine
      ExplicitLeft = -40
      ExplicitTop = 392
      ExplicitWidth = 400
    end
    object Bevel5: TBevel
      Left = 0
      Top = 229
      Width = 288
      Height = 8
      Align = alTop
      Shape = bsTopLine
      ExplicitLeft = -2
      ExplicitTop = 194
      ExplicitWidth = 400
    end
    object Bevel7: TBevel
      Left = 0
      Top = 121
      Width = 288
      Height = 8
      Align = alTop
      Shape = bsTopLine
      ExplicitLeft = 6
      ExplicitTop = 64
      ExplicitWidth = 400
    end
    object btBuildAll: TButton
      Left = 6
      Top = 559
      Width = 265
      Height = 25
      Anchors = [akLeft, akBottom]
      Caption = 'Features f'#252'r alle ausgew'#228'hlten EKGs berechnen'
      TabOrder = 0
      OnClick = btBuildAllClick
    end
    object pnFeatures: TPanel
      Left = 0
      Top = 237
      Width = 288
      Height = 100
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 1
      object Label1: TLabel
        Left = 93
        Top = 6
        Width = 118
        Height = 16
        Caption = 'Feature-Algorithmen'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsUnderline]
        ParentFont = False
      end
      object cxFeatChoi: TCheckBox
        Left = 6
        Top = 32
        Width = 316
        Height = 17
        Caption = 'Choi 2016, acht fiduzielle Punkte'
        TabOrder = 0
      end
      object cxFeatRandom: TCheckBox
        Left = 6
        Top = 55
        Width = 281
        Height = 17
        Caption = 'Random Points, 20 verteilte Punkte im QRS-Komplex'
        TabOrder = 1
      end
    end
    object pnRPeaks: TPanel
      Left = 0
      Top = 129
      Width = 288
      Height = 100
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 2
      object Label2: TLabel
        Left = 103
        Top = 6
        Width = 98
        Height = 16
        Caption = 'R-Peak-Detection'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsUnderline]
        ParentFont = False
      end
      object cxRpeaksAnna: TCheckBox
        Left = 6
        Top = 32
        Width = 233
        Height = 17
        Caption = 'Anna, absteigende Sortierung verwenden'
        TabOrder = 0
      end
      object cxRpeaksChoi: TCheckBox
        Left = 6
        Top = 55
        Width = 233
        Height = 17
        Caption = 'Choi 2016, Kandidaten und '#220'berlappungen'
        TabOrder = 1
      end
    end
    object pnPreprocessing: TPanel
      Left = 0
      Top = 0
      Width = 288
      Height = 121
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 3
      object Label3: TLabel
        Left = 110
        Top = 6
        Width = 80
        Height = 16
        Caption = 'Preprocessing'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsUnderline]
        ParentFont = False
      end
      object Label4: TLabel
        Left = 46
        Top = 28
        Width = 219
        Height = 13
        Caption = '...wird im Moment noch nicht ber'#252'cksichtigt...'
      end
      object cxPreFourier: TCheckBox
        Left = 6
        Top = 86
        Width = 281
        Height = 17
        Caption = 'Fourier Transform ???'
        Enabled = False
        TabOrder = 0
      end
      object cxPreNone: TCheckBox
        Left = 6
        Top = 39
        Width = 281
        Height = 17
        Caption = 'ohne Preprocessing'
        Checked = True
        State = cbChecked
        TabOrder = 1
      end
      object cxSmooth: TCheckBox
        Left = 6
        Top = 62
        Width = 206
        Height = 17
        Caption = 'Kurve gl'#228'tten (gleitender Durchschnitt)'
        TabOrder = 2
        OnClick = cxSmoothClick
      end
      object edSmooth: TEdit
        Left = 216
        Top = 60
        Width = 57
        Height = 21
        TabOrder = 3
        OnExit = edSmoothExit
      end
    end
    object rgFehler: TRadioGroup
      Left = 6
      Top = 480
      Width = 265
      Height = 73
      Caption = ' Fehlerhandling '
      ItemIndex = 0
      Items.Strings = (
        'Bei Fehler sofort abbrechen'
        'Bei Fehler Vorgang fortzusetzen')
      TabOrder = 4
    end
  end
  object pnMemo: TPanel
    Left = 929
    Top = 45
    Width = 361
    Height = 601
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 4
    object memo: TMemo
      Left = 0
      Top = 0
      Width = 361
      Height = 601
      Align = alClient
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Courier New'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      ScrollBars = ssBoth
      TabOrder = 0
    end
  end
  object tStartup: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tStartupTimer
    Left = 256
    Top = 8
  end
  object ActionList1: TActionList
    Left = 288
    Top = 8
    object acClose: TAction
      Caption = '&Schlie'#223'en'
      OnExecute = acCloseExecute
    end
  end
  object CallbackEcg: TTimer
    Enabled = False
    Interval = 100
    OnTimer = CallbackEcgTimer
    Left = 320
    Top = 8
  end
end
