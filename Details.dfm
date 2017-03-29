object fmDetails: TfmDetails
  Left = 0
  Top = 0
  BorderStyle = bsToolWindow
  Caption = 'Detailansicht'
  ClientHeight = 770
  ClientWidth = 494
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnClose = FormClose
  OnKeyDown = FormKeyDown
  OnKeyPress = FormKeyPress
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 0
    Top = 33
    Width = 494
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -602
    ExplicitTop = 41
    ExplicitWidth = 1092
  end
  object Bevel2: TBevel
    Left = 0
    Top = 102
    Width = 494
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitTop = 41
    ExplicitWidth = 490
  end
  object Bevel4: TBevel
    Left = 0
    Top = 368
    Width = 494
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitTop = 238
    ExplicitWidth = 490
  end
  object imgData: TImage
    Left = 0
    Top = 140
    Width = 494
    Height = 95
    Align = alTop
    ExplicitTop = 134
  end
  object imgBeats: TImage
    Left = 0
    Top = 406
    Width = 494
    Height = 95
    Align = alTop
  end
  object Bevel5: TBevel
    Left = 0
    Top = 501
    Width = 494
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -8
    ExplicitTop = 575
    ExplicitWidth = 490
  end
  object imgHerz: TImage
    Left = 0
    Top = 539
    Width = 494
    Height = 95
    Align = alTop
  end
  object Bevel6: TBevel
    Left = 0
    Top = 634
    Width = 494
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = 8
    ExplicitTop = 632
  end
  object imgAC: TImage
    Left = 0
    Top = 273
    Width = 494
    Height = 95
    Align = alTop
    ExplicitTop = 488
  end
  object Bevel7: TBevel
    Left = 0
    Top = 235
    Width = 494
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -8
    ExplicitTop = 233
  end
  object imgAcHerz: TImage
    Left = 0
    Top = 672
    Width = 494
    Height = 95
    Align = alTop
    ExplicitTop = 678
  end
  object Bevel3: TBevel
    Left = 0
    Top = 767
    Width = 494
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitTop = 777
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 494
    Height = 33
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    DesignSize = (
      494
      33)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 478
      Height = 17
      Anchors = [akLeft, akTop, akRight, akBottom]
      BorderStyle = bsNone
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsItalic]
      Lines.Strings = (
        'Detailansicht einer Kurve')
      ParentColor = True
      ParentFont = False
      ReadOnly = True
      TabOrder = 0
    end
  end
  object pnCombo: TPanel
    Left = 0
    Top = 37
    Width = 494
    Height = 65
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 1
    object Label1: TLabel
      Left = 8
      Top = 16
      Width = 71
      Height = 13
      Caption = 'Auswahl Kurve'
    end
    object cbKurve: TComboBox
      Left = 89
      Top = 13
      Width = 393
      Height = 21
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 13
      ItemIndex = 0
      TabOrder = 0
      Text = 'EKG-Daten'
      OnChange = cbKurveChange
      Items.Strings = (
        'EKG-Daten'
        'Erste Ableitung'
        'Zweite Ableitung')
    end
    object pbJob: TProgressBar
      Left = 89
      Top = 40
      Width = 393
      Height = 17
      TabOrder = 1
      Visible = False
    end
  end
  object pnHeader1: TPanel
    Left = 0
    Top = 106
    Width = 494
    Height = 34
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 2
    object Label2: TLabel
      Left = 8
      Top = 8
      Width = 159
      Height = 14
      Caption = 'Originaldaten mit R-Peaks'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsUnderline]
      ParentFont = False
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 372
    Width = 494
    Height = 34
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 3
    ExplicitTop = 400
    object Label4: TLabel
      Left = 8
      Top = 8
      Width = 72
      Height = 14
      Caption = 'Herzschl'#228'ge'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsUnderline]
      ParentFont = False
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 505
    Width = 494
    Height = 34
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 4
    ExplicitTop = 547
    object Label5: TLabel
      Left = 8
      Top = 8
      Width = 121
      Height = 14
      Caption = 'Standardherzschlag'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsUnderline]
      ParentFont = False
    end
  end
  object Panel4: TPanel
    Left = 0
    Top = 239
    Width = 494
    Height = 34
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 5
    ExplicitTop = 378
    object Label6: TLabel
      Left = 8
      Top = 8
      Width = 175
      Height = 14
      Caption = 'Autokorrelation mit R-Peaks'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsUnderline]
      ParentFont = False
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 638
    Width = 494
    Height = 34
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 6
    ExplicitLeft = -8
    ExplicitTop = 634
    object Label3: TLabel
      Left = 8
      Top = 8
      Width = 223
      Height = 14
      Caption = 'Autokorrelation Standardherzschlag'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsUnderline]
      ParentFont = False
    end
  end
  object tStartup: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tStartupTimer
    Left = 168
  end
  object tCombo: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tComboTimer
    Left = 200
  end
end
