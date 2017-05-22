object fmFeatures: TfmFeatures
  Left = 0
  Top = 0
  Caption = 'Features bilden'
  ClientHeight = 691
  ClientWidth = 934
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
    Width = 934
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -504
    ExplicitWidth = 1073
  end
  object Bevel2: TBevel
    Left = 0
    Top = 646
    Width = 934
    Height = 4
    Align = alBottom
    Shape = bsBottomLine
    ExplicitLeft = -504
    ExplicitTop = 545
    ExplicitWidth = 1073
  end
  object Bevel4: TBevel
    Left = 457
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
    Width = 934
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    ExplicitWidth = 789
    DesignSize = (
      934
      41)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 918
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
      ExplicitWidth = 773
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 650
    Width = 934
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    ExplicitTop = 562
    ExplicitWidth = 789
    DesignSize = (
      934
      41)
    object btClose: TButton
      Left = 851
      Top = 6
      Width = 75
      Height = 25
      Action = acClose
      Anchors = [akRight, akBottom]
      TabOrder = 0
      ExplicitLeft = 718
    end
    object pbJob: TProgressBar
      Left = 8
      Top = 6
      Width = 837
      Height = 25
      TabOrder = 1
      Visible = False
    end
  end
  object pnEcg: TPanel
    Left = 0
    Top = 45
    Width = 457
    Height = 601
    Align = alLeft
    BevelOuter = bvNone
    TabOrder = 2
    ExplicitLeft = 2
    ExplicitTop = 43
  end
  object pnAuswahl: TPanel
    Left = 465
    Top = 45
    Width = 469
    Height = 601
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 3
    ExplicitLeft = 576
    ExplicitTop = 47
    ExplicitWidth = 350
    ExplicitHeight = 597
    object Bevel3: TBevel
      Left = 0
      Top = 507
      Width = 469
      Height = 8
      Align = alTop
      Shape = bsTopLine
      ExplicitLeft = 112
      ExplicitTop = 424
      ExplicitWidth = 50
    end
    object memo: TMemo
      Left = 0
      Top = 0
      Width = 469
      Height = 427
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
      ExplicitLeft = 6
      ExplicitWidth = 477
    end
    object btFeatures: TButton
      Left = 59
      Top = 528
      Width = 358
      Height = 25
      Caption = 'Feature des ausgew'#228'hlten EKGs berechnen'
      TabOrder = 1
      OnClick = btFeaturesClick
    end
    object btBuildAll: TButton
      Left = 59
      Top = 559
      Width = 358
      Height = 25
      Caption = 'Features f'#252'r alle in der Datenbank enthaltenen EKGs berechnen'
      TabOrder = 2
      OnClick = btBuildAllClick
    end
    object pnAlg: TPanel
      Left = 0
      Top = 427
      Width = 469
      Height = 80
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 3
      ExplicitTop = 313
      ExplicitWidth = 477
      object Label1: TLabel
        Left = 184
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
      object cxChoi: TCheckBox
        Left = 16
        Top = 32
        Width = 193
        Height = 17
        Caption = 'Choi 2016, acht fiduzielle Punkte'
        TabOrder = 0
      end
      object cxRandom: TCheckBox
        Left = 16
        Top = 55
        Width = 281
        Height = 17
        Caption = 'Random Points, 20 verteilte Punkte im QRS-Komplex'
        TabOrder = 1
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
