object fmEcgLeads: TfmEcgLeads
  Left = 0
  Top = 0
  Caption = 'ECG-Analysis'
  ClientHeight = 867
  ClientWidth = 1600
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
    Width = 1600
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -720
    ExplicitWidth = 1190
  end
  object Bevel2: TBevel
    Left = 802
    Top = 45
    Width = 2
    Height = 822
    Align = alLeft
    Shape = bsLeftLine
    ExplicitLeft = 928
    ExplicitTop = 47
  end
  object Bevel3: TBevel
    Left = 400
    Top = 45
    Width = 2
    Height = 822
    Align = alLeft
    Shape = bsLeftLine
    ExplicitLeft = 408
  end
  object Bevel4: TBevel
    Left = 1606
    Top = 45
    Width = 2
    Height = 822
    Align = alLeft
    Shape = bsLeftLine
    ExplicitLeft = 810
  end
  object Bevel5: TBevel
    Left = 1204
    Top = 45
    Width = 2
    Height = 822
    Align = alLeft
    Shape = bsLeftLine
    ExplicitLeft = 810
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 1600
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    ExplicitWidth = 470
    object laInfo: TLabel
      Left = 8
      Top = 14
      Width = 1577
      Height = 14
      Alignment = taCenter
      AutoSize = False
      BiDiMode = bdLeftToRight
      Caption = 'laInfo'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentBiDiMode = False
      ParentFont = False
    end
  end
  object pnEcg1: TPanel
    Left = 0
    Top = 45
    Width = 400
    Height = 822
    Align = alLeft
    BevelOuter = bvNone
    TabOrder = 1
  end
  object pnEcg2: TPanel
    Left = 402
    Top = 45
    Width = 400
    Height = 822
    Align = alLeft
    BevelOuter = bvNone
    TabOrder = 2
    ExplicitLeft = 1000
    ExplicitTop = 37
  end
  object pnEcg3: TPanel
    Left = 804
    Top = 45
    Width = 400
    Height = 822
    Align = alLeft
    BevelOuter = bvNone
    TabOrder = 3
    ExplicitLeft = 1370
    ExplicitTop = 14
  end
  object pnEcg4: TPanel
    Left = 1206
    Top = 45
    Width = 400
    Height = 822
    Align = alLeft
    BevelOuter = bvNone
    TabOrder = 4
    ExplicitLeft = 1476
    ExplicitTop = 8
  end
  object tStartup: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tStartupTimer
    Left = 272
    Top = 8
  end
end