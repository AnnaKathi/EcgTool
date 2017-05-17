object fmChoiFeatures: TfmChoiFeatures
  Left = 0
  Top = 0
  Caption = 'Choi-Features bilden'
  ClientHeight = 603
  ClientWidth = 658
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
  DesignSize = (
    658
    603)
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 0
    Top = 41
    Width = 658
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -504
    ExplicitWidth = 1073
  end
  object Bevel2: TBevel
    Left = 0
    Top = 558
    Width = 658
    Height = 4
    Align = alBottom
    Shape = bsBottomLine
    ExplicitLeft = -504
    ExplicitTop = 545
    ExplicitWidth = 1073
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 658
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    DesignSize = (
      658
      41)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 642
      Height = 25
      Anchors = [akLeft, akTop, akRight]
      BorderStyle = bsNone
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsItalic]
      Lines.Strings = (
        'Choi-Features bilden und in DB speichern')
      ParentColor = True
      ParentFont = False
      ReadOnly = True
      TabOrder = 0
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 562
    Width = 658
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    DesignSize = (
      658
      41)
    object btClose: TButton
      Left = 575
      Top = 6
      Width = 75
      Height = 25
      Action = acClose
      Anchors = [akRight, akBottom]
      TabOrder = 0
    end
  end
  object pnEcg: TPanel
    Left = 0
    Top = 45
    Width = 457
    Height = 513
    Align = alLeft
    TabOrder = 2
  end
  object memo: TMemo
    Left = 463
    Top = 47
    Width = 185
    Height = 242
    Anchors = [akLeft, akTop, akRight]
    ReadOnly = True
    ScrollBars = ssBoth
    TabOrder = 3
  end
  object btFeatures: TButton
    Left = 463
    Top = 304
    Width = 187
    Height = 25
    Caption = 'Features berechnen'
    TabOrder = 4
    OnClick = btFeaturesClick
  end
  object btBuildAll: TButton
    Left = 463
    Top = 344
    Width = 187
    Height = 25
    Caption = 'Alle Features erstellen'
    TabOrder = 5
    OnClick = btBuildAllClick
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
