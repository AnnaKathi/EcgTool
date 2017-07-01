object fmLeads: TfmLeads
  Left = 0
  Top = 0
  Caption = 'Standard-Herzschl'#228'ge eines EKGs'
  ClientHeight = 785
  ClientWidth = 390
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
    Top = 41
    Width = 390
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -720
    ExplicitWidth = 1190
  end
  object iLead1: TImage
    Left = 5
    Top = 51
    Width = 380
    Height = 86
  end
  object iLead2: TImage
    Left = 5
    Top = 143
    Width = 380
    Height = 86
  end
  object iLead3: TImage
    Left = 5
    Top = 235
    Width = 380
    Height = 86
  end
  object iLead4: TImage
    Left = 5
    Top = 327
    Width = 380
    Height = 86
  end
  object iLead5: TImage
    Left = 5
    Top = 419
    Width = 380
    Height = 86
  end
  object iLead6: TImage
    Left = 5
    Top = 511
    Width = 380
    Height = 86
  end
  object iLead7: TImage
    Left = 5
    Top = 603
    Width = 380
    Height = 86
  end
  object iLead8: TImage
    Left = 5
    Top = 695
    Width = 380
    Height = 86
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 390
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    ExplicitWidth = 470
    object laInfo: TLabel
      Left = 8
      Top = 14
      Width = 377
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
  object tStartup: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tStartupTimer
    Left = 232
    Top = 8
  end
end
