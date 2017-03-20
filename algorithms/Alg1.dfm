object fmAlg1: TfmAlg1
  Left = 0
  Top = 0
  Caption = 'Algorithmus 1: Grundlagentest'
  ClientHeight = 651
  ClientWidth = 735
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnKeyPress = FormKeyPress
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object img: TImage
    Left = 8
    Top = 56
    Width = 457
    Height = 73
  end
  object imgBeat: TImage
    Left = 8
    Top = 215
    Width = 257
    Height = 66
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 735
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    ExplicitLeft = -357
    ExplicitWidth = 1092
    DesignSize = (
      735
      41)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 719
      Height = 25
      Anchors = [akLeft, akTop, akRight]
      BorderStyle = bsNone
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsItalic]
      Lines.Strings = (
        
          'Ansicht und Ausf'#252'hrung von Algoritmus 1 (Test der Grundfunktiona' +
          'lit'#228'ten).')
      ParentColor = True
      ParentFont = False
      TabOrder = 0
      ExplicitWidth = 1076
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 610
    Width = 735
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    ExplicitLeft = 168
    ExplicitTop = 504
    ExplicitWidth = 185
    object Button1: TButton
      Left = 8
      Top = 8
      Width = 75
      Height = 25
      Action = acClose
      TabOrder = 0
    end
  end
  object Memo: TMemo
    Left = 480
    Top = 41
    Width = 255
    Height = 569
    Align = alRight
    ReadOnly = True
    ScrollBars = ssBoth
    TabOrder = 2
  end
  object btStep1: TButton
    Left = 8
    Top = 184
    Width = 257
    Height = 25
    Caption = 'Schritt 1 - Standardherzschlag finden'
    TabOrder = 3
    OnClick = btStep1Click
  end
  object btStep2: TButton
    Left = 8
    Top = 336
    Width = 257
    Height = 25
    Caption = 'Schritt 2 - Berechne Range'
    TabOrder = 4
    OnClick = btStep2Click
  end
  object edRange: TEdit
    Left = 288
    Top = 338
    Width = 121
    Height = 21
    TabOrder = 5
  end
  object tStartup: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tStartupTimer
    Left = 440
    Top = 8
  end
  object ActionList1: TActionList
    Left = 472
    Top = 8
    object acClose: TAction
      Caption = '&Schlie'#223'en'
      OnExecute = acCloseExecute
    end
  end
end
