object fmLeads: TfmLeads
  Left = 0
  Top = 0
  Caption = 'Standard-Herzschl'#228'ge eines EKGs'
  ClientHeight = 687
  ClientWidth = 305
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnClose = FormClose
  OnKeyPress = FormKeyPress
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 0
    Top = 23
    Width = 305
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -720
    ExplicitTop = 41
    ExplicitWidth = 1190
  end
  object iLead1: TImage
    Left = 7
    Top = 29
    Width = 289
    Height = 58
  end
  object iLead2: TImage
    Left = 7
    Top = 88
    Width = 289
    Height = 58
  end
  object iLead3: TImage
    Left = 7
    Top = 147
    Width = 289
    Height = 58
  end
  object iLead4: TImage
    Left = 7
    Top = 206
    Width = 289
    Height = 58
  end
  object iLead5: TImage
    Left = 7
    Top = 265
    Width = 289
    Height = 58
  end
  object iLead6: TImage
    Left = 7
    Top = 324
    Width = 289
    Height = 58
  end
  object iLead7: TImage
    Left = 7
    Top = 383
    Width = 289
    Height = 58
  end
  object iLead8: TImage
    Left = 7
    Top = 443
    Width = 289
    Height = 58
  end
  object iAbl12: TImage
    Left = 7
    Top = 514
    Width = 289
    Height = 58
  end
  object iAbl34: TImage
    Left = 7
    Top = 573
    Width = 289
    Height = 58
  end
  object iAbl56: TImage
    Left = 7
    Top = 632
    Width = 289
    Height = 58
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 305
    Height = 23
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    ExplicitWidth = 325
    object laInfo: TLabel
      Left = 8
      Top = 3
      Width = 288
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
      OnClick = laInfoClick
    end
  end
  object tStartup: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tStartupTimer
    Left = 232
    Top = 8
  end
  object OpenDialog: TOpenDialog
    Left = 200
    Top = 8
  end
end
