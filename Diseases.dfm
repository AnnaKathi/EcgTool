object fmDiseases: TfmDiseases
  Left = 0
  Top = 0
  Caption = 'Erkrankungen'
  ClientHeight = 640
  ClientWidth = 549
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
    Width = 549
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -181
    ExplicitWidth = 822
  end
  object Bevel2: TBevel
    Left = 0
    Top = 595
    Width = 549
    Height = 4
    Align = alBottom
    Shape = bsBottomLine
    ExplicitTop = 301
    ExplicitWidth = 288
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 549
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    ExplicitWidth = 288
    DesignSize = (
      549
      41)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 533
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
      ExplicitWidth = 272
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 599
    Width = 549
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    ExplicitTop = 264
    ExplicitWidth = 288
    DesignSize = (
      549
      41)
    object Button1: TButton
      Left = 466
      Top = 6
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      TabOrder = 0
      ExplicitLeft = 205
    end
    object Button2: TButton
      Left = 7
      Top = 6
      Width = 75
      Height = 25
      TabOrder = 1
    end
  end
  object pnDiseases: TPanel
    Left = 0
    Top = 45
    Width = 549
    Height = 550
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 2
    ExplicitLeft = 200
    ExplicitTop = 112
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
end
