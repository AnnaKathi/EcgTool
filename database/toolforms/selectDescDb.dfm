object fmSelectDesc: TfmSelectDesc
  Left = 0
  Top = 0
  Caption = 'Select DescDb'
  ClientHeight = 635
  ClientWidth = 569
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
    Width = 569
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -504
    ExplicitWidth = 1073
  end
  object Bevel2: TBevel
    Left = 0
    Top = 590
    Width = 569
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
    Width = 569
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    ExplicitLeft = -504
    ExplicitWidth = 1073
    DesignSize = (
      569
      41)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 553
      Height = 25
      Anchors = [akLeft, akTop, akRight]
      BorderStyle = bsNone
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsItalic]
      Lines.Strings = (
        'Auswahl eines oder mehrerer Datens'#228'tze')
      ParentColor = True
      ParentFont = False
      ReadOnly = True
      TabOrder = 0
      ExplicitWidth = 1057
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 594
    Width = 569
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    ExplicitLeft = -504
    ExplicitTop = 549
    ExplicitWidth = 1073
    DesignSize = (
      569
      41)
    object btClose: TButton
      Left = 486
      Top = 6
      Width = 75
      Height = 25
      Action = acClose
      Anchors = [akRight, akBottom]
      TabOrder = 0
      ExplicitLeft = 990
    end
  end
  object pnListe: TPanel
    Left = 0
    Top = 45
    Width = 569
    Height = 545
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 2
    ExplicitLeft = 96
    ExplicitTop = 264
    ExplicitWidth = 185
    ExplicitHeight = 41
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
  object TimerCallback: TTimer
    Enabled = False
    Interval = 100
    OnTimer = TimerCallbackTimer
    Left = 320
    Top = 8
  end
end
