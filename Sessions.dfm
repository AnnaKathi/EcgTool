object fmSessions: TfmSessions
  Left = 0
  Top = 0
  Caption = 'Sessions'
  ClientHeight = 690
  ClientWidth = 775
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
    Width = 775
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -41
    ExplicitWidth = 784
  end
  object Bevel3: TBevel
    Left = 0
    Top = 645
    Width = 775
    Height = 4
    Align = alBottom
    Shape = bsBottomLine
    ExplicitLeft = -41
    ExplicitTop = 662
    ExplicitWidth = 784
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 775
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    ExplicitWidth = 747
    DesignSize = (
      775
      41)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 759
      Height = 25
      Anchors = [akLeft, akTop, akRight]
      BorderStyle = bsNone
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsItalic]
      Lines.Strings = (
        'EKG-Tool..., Todo: Text einf'#252'gen')
      ParentColor = True
      ParentFont = False
      ReadOnly = True
      TabOrder = 0
    end
  end
  object pnBottom: TPanel
    Left = 0
    Top = 649
    Width = 775
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    ExplicitWidth = 747
    DesignSize = (
      775
      41)
    object Button1: TButton
      Left = 692
      Top = 6
      Width = 75
      Height = 25
      Action = acClose
      Anchors = [akRight, akBottom]
      TabOrder = 0
      ExplicitLeft = 664
    end
  end
  object pnSession: TPanel
    Left = 0
    Top = 45
    Width = 775
    Height = 600
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 2
    ExplicitLeft = 104
    ExplicitTop = 272
    ExplicitWidth = 185
    ExplicitHeight = 41
  end
  object tStartup: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tStartupTimer
    Left = 224
    Top = 8
  end
  object ActionList1: TActionList
    Left = 256
    Top = 8
    object acClose: TAction
      Caption = '&Schlie'#223'en'
      OnExecute = acCloseExecute
    end
  end
end
