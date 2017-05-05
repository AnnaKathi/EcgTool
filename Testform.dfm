object fmTest: TfmTest
  Left = 0
  Top = 0
  Caption = 'PreTest MySql'
  ClientHeight = 590
  ClientWidth = 1073
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
    Width = 1073
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -181
    ExplicitWidth = 822
  end
  object Bevel2: TBevel
    Left = 0
    Top = 545
    Width = 1073
    Height = 4
    Align = alBottom
    Shape = bsBottomLine
    ExplicitTop = 49
    ExplicitWidth = 701
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 1073
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    DesignSize = (
      1073
      41)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 1057
      Height = 25
      Anchors = [akLeft, akTop, akRight]
      BorderStyle = bsNone
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsItalic]
      Lines.Strings = (
        
          'Testformular: Dient dazu, verschiedene Funktionen auszutesten, b' +
          'evor diese implementiert werden.')
      ParentColor = True
      ParentFont = False
      ReadOnly = True
      TabOrder = 0
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 549
    Width = 1073
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    DesignSize = (
      1073
      41)
    object btClose: TButton
      Left = 990
      Top = 6
      Width = 75
      Height = 25
      Anchors = [akRight, akBottom]
      Caption = '&Schlie'#223'en'
      TabOrder = 0
    end
  end
  object pnDesc1: TPanel
    Left = 377
    Top = 45
    Width = 348
    Height = 500
    Align = alRight
    Color = clWhite
    ParentBackground = False
    TabOrder = 2
    ExplicitLeft = 192
  end
  object pnDesc2: TPanel
    Left = 725
    Top = 45
    Width = 348
    Height = 500
    Align = alRight
    Color = clWhite
    ParentBackground = False
    TabOrder = 3
    ExplicitLeft = 540
  end
  object pnDesc3: TPanel
    Left = 0
    Top = 45
    Width = 377
    Height = 500
    Align = alClient
    Color = clWhite
    ParentBackground = False
    TabOrder = 4
    ExplicitLeft = -209
    ExplicitTop = 2
    ExplicitWidth = 348
    ExplicitHeight = 498
  end
  object tStartup: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tStartupTimer
    Left = 264
    Top = 16
  end
end
