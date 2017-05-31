object fmFeatures: TfmFeatures
  Left = 0
  Top = 0
  Caption = 'Features bilden'
  ClientHeight = 691
  ClientWidth = 1089
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
    Width = 1089
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -504
    ExplicitWidth = 1073
  end
  object Bevel2: TBevel
    Left = 0
    Top = 646
    Width = 1089
    Height = 4
    Align = alBottom
    Shape = bsBottomLine
    ExplicitLeft = -504
    ExplicitTop = 545
    ExplicitWidth = 1073
  end
  object Bevel4: TBevel
    Left = 721
    Top = 45
    Width = 8
    Height = 601
    Align = alLeft
    Shape = bsLeftLine
    ExplicitLeft = 488
    ExplicitTop = 144
    ExplicitHeight = 50
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 1089
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    ExplicitWidth = 934
    DesignSize = (
      1089
      41)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 1073
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
      ExplicitWidth = 918
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 650
    Width = 1089
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    ExplicitWidth = 934
    DesignSize = (
      1089
      41)
    object btClose: TButton
      Left = 1006
      Top = 6
      Width = 75
      Height = 25
      Action = acClose
      Anchors = [akRight, akBottom]
      TabOrder = 0
      ExplicitLeft = 851
    end
    object pbJob: TProgressBar
      Left = 8
      Top = 6
      Width = 992
      Height = 25
      TabOrder = 1
      Visible = False
    end
  end
  object pnEcg: TPanel
    Left = 0
    Top = 45
    Width = 721
    Height = 601
    Align = alLeft
    BevelOuter = bvNone
    TabOrder = 2
  end
  object pnAuswahl: TPanel
    Left = 729
    Top = 45
    Width = 360
    Height = 601
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 3
    ExplicitLeft = 465
    ExplicitWidth = 469
    object Bevel3: TBevel
      Left = 0
      Top = 516
      Width = 360
      Height = 8
      Align = alTop
      Shape = bsTopLine
      ExplicitLeft = -2
      ExplicitTop = 514
      ExplicitWidth = 469
    end
    object memo: TMemo
      Left = 0
      Top = 0
      Width = 360
      Height = 417
      Align = alTop
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Courier New'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      ScrollBars = ssBoth
      TabOrder = 0
      ExplicitWidth = 469
    end
    object btFeatures: TButton
      Left = 16
      Top = 528
      Width = 329
      Height = 25
      Caption = 'Feature des ausgew'#228'hlten EKGs berechnen'
      TabOrder = 1
      OnClick = btFeaturesClick
    end
    object btBuildAll: TButton
      Left = 16
      Top = 559
      Width = 329
      Height = 25
      Caption = 'Features f'#252'r alle ausgew'#228'hlten EKGs berechnen'
      TabOrder = 2
      OnClick = btBuildAllClick
    end
    object pnAlg: TPanel
      Left = 0
      Top = 417
      Width = 360
      Height = 99
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 3
      ExplicitWidth = 469
      object Label1: TLabel
        Left = 137
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
      object cxChoi1: TCheckBox
        Left = 16
        Top = 32
        Width = 316
        Height = 17
        Caption = 'Choi 2016, acht fiduzielle Punkte, Original R-Peak-Detection'
        TabOrder = 0
      end
      object cxRandom: TCheckBox
        Left = 16
        Top = 76
        Width = 281
        Height = 17
        Caption = 'Random Points, 20 verteilte Punkte im QRS-Komplex'
        TabOrder = 1
      end
      object cxChoi2: TCheckBox
        Left = 16
        Top = 53
        Width = 322
        Height = 17
        Caption = 'Choi 2016, acht fiduzielle Punkte, R-Peak-Verbesserung Anna'
        TabOrder = 2
      end
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
