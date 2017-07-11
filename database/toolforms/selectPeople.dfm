object fmSelectPerson: TfmSelectPerson
  Left = 0
  Top = 0
  Caption = 'Person ausw'#228'hlen'
  ClientHeight = 618
  ClientWidth = 493
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
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
    Width = 493
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -128
    ExplicitWidth = 775
  end
  object Bevel3: TBevel
    Left = 0
    Top = 573
    Width = 493
    Height = 4
    Align = alBottom
    Shape = bsBottomLine
    ExplicitLeft = -128
    ExplicitTop = 614
    ExplicitWidth = 775
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 493
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    ExplicitLeft = -128
    ExplicitWidth = 775
    DesignSize = (
      493
      41)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 477
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
      ExplicitWidth = 759
    end
  end
  object pnBottom: TPanel
    Left = 0
    Top = 577
    Width = 493
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    ExplicitLeft = -128
    ExplicitWidth = 775
    DesignSize = (
      493
      41)
    object Button1: TButton
      Left = 410
      Top = 6
      Width = 75
      Height = 25
      Action = acClose
      Anchors = [akRight, akBottom]
      TabOrder = 0
      ExplicitLeft = 692
    end
    object btSelect: TButton
      Left = 8
      Top = 6
      Width = 113
      Height = 25
      Action = acSelect
      TabOrder = 1
    end
  end
  object pnPeople: TPanel
    Left = 0
    Top = 45
    Width = 493
    Height = 528
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 2
    ExplicitLeft = -128
    ExplicitTop = 18
    ExplicitWidth = 775
    ExplicitHeight = 600
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
    object acSelect: TAction
      Caption = 'Person &ausw'#228'hlen'
      OnExecute = acSelectExecute
    end
  end
  object tCallback: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tCallbackTimer
    Left = 288
    Top = 8
  end
end
