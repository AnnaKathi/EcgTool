object fmEcgLeads: TfmEcgLeads
  Left = 0
  Top = 0
  Caption = 'ECG-Analysis'
  ClientHeight = 735
  ClientWidth = 1269
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
    Top = 0
    Width = 1269
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -720
    ExplicitTop = 41
    ExplicitWidth = 1190
  end
  object Bevel2: TBevel
    Left = 632
    Top = 42
    Width = 2
    Height = 693
    Align = alLeft
    Shape = bsLeftLine
    ExplicitLeft = 928
    ExplicitTop = 47
    ExplicitHeight = 822
  end
  object Bevel3: TBevel
    Left = 315
    Top = 42
    Width = 2
    Height = 693
    Align = alLeft
    Shape = bsLeftLine
    ExplicitLeft = 408
    ExplicitTop = 45
    ExplicitHeight = 822
  end
  object Bevel4: TBevel
    Left = 1266
    Top = 42
    Width = 2
    Height = 693
    Align = alLeft
    Shape = bsLeftLine
    ExplicitLeft = 810
    ExplicitTop = 45
    ExplicitHeight = 822
  end
  object Bevel5: TBevel
    Left = 949
    Top = 42
    Width = 2
    Height = 693
    Align = alLeft
    Shape = bsLeftLine
    ExplicitLeft = 810
    ExplicitTop = 45
    ExplicitHeight = 822
  end
  object Bevel6: TBevel
    Left = 0
    Top = 39
    Width = 1269
    Height = 3
    Align = alTop
    Shape = bsTopLine
    ExplicitTop = 45
  end
  object pnEcg1: TPanel
    Left = 0
    Top = 42
    Width = 315
    Height = 693
    Align = alLeft
    BevelOuter = bvNone
    TabOrder = 0
    ExplicitTop = 4
    ExplicitHeight = 703
  end
  object pnEcg2: TPanel
    Left = 317
    Top = 42
    Width = 315
    Height = 693
    Align = alLeft
    BevelOuter = bvNone
    TabOrder = 1
    ExplicitTop = 4
    ExplicitHeight = 703
  end
  object pnEcg3: TPanel
    Left = 634
    Top = 42
    Width = 315
    Height = 693
    Align = alLeft
    BevelOuter = bvNone
    TabOrder = 2
    ExplicitTop = 4
    ExplicitHeight = 703
  end
  object pnEcg4: TPanel
    Left = 951
    Top = 42
    Width = 315
    Height = 693
    Align = alLeft
    BevelOuter = bvNone
    TabOrder = 3
    ExplicitTop = 4
    ExplicitHeight = 703
  end
  object Panel1: TPanel
    Left = 0
    Top = 4
    Width = 1269
    Height = 35
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 4
    object Label1: TLabel
      Left = 8
      Top = 6
      Width = 35
      Height = 13
      Caption = 'Ansicht'
    end
    object cbAnsicht: TComboBox
      Left = 56
      Top = 3
      Width = 137
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      ItemIndex = 0
      TabOrder = 0
      Text = 'Original-Daten'
      OnChange = cbAnsichtChange
      Items.Strings = (
        'Original-Daten'
        '1. Ableitung'
        '2. Ableitung')
    end
  end
  object tStartup: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tStartupTimer
    Left = 608
    Top = 8
  end
end
