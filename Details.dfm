object fmDetails: TfmDetails
  Left = 0
  Top = 0
  Caption = 'Detailansicht'
  ClientHeight = 712
  ClientWidth = 490
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
    Top = 33
    Width = 490
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -602
    ExplicitTop = 41
    ExplicitWidth = 1092
  end
  object Bevel2: TBevel
    Left = 0
    Top = 83
    Width = 490
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitTop = 41
  end
  object imgRpeaks: TImage
    Left = 0
    Top = 268
    Width = 490
    Height = 109
    Align = alTop
    ExplicitTop = 523
  end
  object Bevel3: TBevel
    Left = 0
    Top = 377
    Width = 490
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -8
    ExplicitTop = 422
  end
  object Bevel4: TBevel
    Left = 0
    Top = 230
    Width = 490
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitTop = 238
  end
  object imgData: TImage
    Left = 0
    Top = 121
    Width = 490
    Height = 109
    Align = alTop
    ExplicitTop = 129
  end
  object imgBeats: TImage
    Left = 0
    Top = 415
    Width = 490
    Height = 109
    Align = alTop
    ExplicitTop = 625
  end
  object Bevel5: TBevel
    Left = 0
    Top = 524
    Width = 490
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -8
    ExplicitTop = 575
  end
  object imgHerz: TImage
    Left = 0
    Top = 562
    Width = 490
    Height = 109
    Align = alTop
    ExplicitLeft = -8
    ExplicitTop = 643
  end
  object Bevel6: TBevel
    Left = 0
    Top = 671
    Width = 490
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -8
    ExplicitTop = 700
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 490
    Height = 33
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    DesignSize = (
      490
      33)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 474
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
      TabOrder = 0
      ExplicitWidth = 1125
      ExplicitHeight = 25
    end
  end
  object pnCombo: TPanel
    Left = 0
    Top = 37
    Width = 490
    Height = 46
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
  end
  object pnHeader1: TPanel
    Left = 0
    Top = 87
    Width = 490
    Height = 34
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 2
    ExplicitTop = 89
    object Label2: TLabel
      Left = 8
      Top = 8
      Width = 82
      Height = 14
      Caption = 'Originaldaten'
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
    Top = 234
    Width = 490
    Height = 34
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 3
    ExplicitTop = 270
    object Label3: TLabel
      Left = 8
      Top = 8
      Width = 49
      Height = 14
      Caption = 'R-Peaks'
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
    Top = 381
    Width = 490
    Height = 34
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 4
    ExplicitTop = 383
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
    Top = 528
    Width = 490
    Height = 34
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 5
    ExplicitTop = 530
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
