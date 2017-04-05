object fmDetails: TfmDetails
  Left = 0
  Top = 0
  BorderStyle = bsToolWindow
  Caption = 'Detailansicht'
  ClientHeight = 686
  ClientWidth = 419
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
    Width = 419
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -602
    ExplicitTop = 41
    ExplicitWidth = 1092
  end
  object Bevel2: TBevel
    Left = 0
    Top = 89
    Width = 419
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitTop = 41
    ExplicitWidth = 490
  end
  object Bevel4: TBevel
    Left = 0
    Top = 327
    Width = 419
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitTop = 238
    ExplicitWidth = 490
  end
  object imgData: TImage
    Left = 0
    Top = 123
    Width = 419
    Height = 85
    Align = alTop
    ExplicitTop = 140
    ExplicitWidth = 494
  end
  object imgBeats: TImage
    Left = 0
    Top = 361
    Width = 419
    Height = 85
    Align = alTop
    ExplicitTop = 386
    ExplicitWidth = 494
  end
  object Bevel5: TBevel
    Left = 0
    Top = 446
    Width = 419
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -8
    ExplicitTop = 575
    ExplicitWidth = 490
  end
  object imgHerz: TImage
    Left = 0
    Top = 480
    Width = 419
    Height = 85
    Align = alTop
    ExplicitTop = 509
    ExplicitWidth = 494
  end
  object Bevel6: TBevel
    Left = 0
    Top = 565
    Width = 419
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = 8
    ExplicitTop = 632
    ExplicitWidth = 494
  end
  object imgAC: TImage
    Left = 0
    Top = 242
    Width = 419
    Height = 85
    Align = alTop
    ExplicitTop = 263
    ExplicitWidth = 494
  end
  object Bevel7: TBevel
    Left = 0
    Top = 208
    Width = 419
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -8
    ExplicitTop = 233
    ExplicitWidth = 494
  end
  object imgAcHerz: TImage
    Left = 0
    Top = 599
    Width = 419
    Height = 85
    Align = alTop
    ExplicitTop = 632
    ExplicitWidth = 494
  end
  object Bevel3: TBevel
    Left = 0
    Top = 684
    Width = 419
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitTop = 777
    ExplicitWidth = 494
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 419
    Height = 33
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    ExplicitWidth = 494
    DesignSize = (
      419
      33)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 403
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
      ExplicitWidth = 478
    end
  end
  object pnCombo: TPanel
    Left = 0
    Top = 37
    Width = 419
    Height = 52
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 1
    DesignSize = (
      419
      52)
    object Label1: TLabel
      Left = 8
      Top = 5
      Width = 71
      Height = 13
      Caption = 'Auswahl Kurve'
    end
    object cbKurve: TComboBox
      Left = 89
      Top = 2
      Width = 319
      Height = 21
      Style = csDropDownList
      Anchors = [akLeft, akTop, akRight]
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
      Top = 29
      Width = 319
      Height = 17
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 1
      Visible = False
    end
  end
  object pnHeader1: TPanel
    Left = 0
    Top = 93
    Width = 419
    Height = 30
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 2
    ExplicitTop = 106
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
    Top = 331
    Width = 419
    Height = 30
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 3
    ExplicitTop = 348
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
    Top = 450
    Width = 419
    Height = 30
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 4
    ExplicitTop = 475
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
    Top = 212
    Width = 419
    Height = 30
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 5
    ExplicitTop = 229
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
    Top = 569
    Width = 419
    Height = 30
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 6
    ExplicitTop = 598
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
