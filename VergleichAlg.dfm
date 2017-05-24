object fmVergleich: TfmVergleich
  Left = 0
  Top = 0
  Caption = 'Algorithmen-Vergleich'
  ClientHeight = 699
  ClientWidth = 1190
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
    Width = 1190
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -504
    ExplicitWidth = 1073
  end
  object Bevel2: TBevel
    Left = 0
    Top = 654
    Width = 1190
    Height = 4
    Align = alBottom
    Shape = bsBottomLine
    ExplicitLeft = -504
    ExplicitTop = 545
    ExplicitWidth = 1073
  end
  object Bevel4: TBevel
    Left = 417
    Top = 45
    Width = 8
    Height = 609
    Align = alLeft
    Shape = bsLeftLine
    ExplicitLeft = 488
    ExplicitTop = 144
    ExplicitHeight = 50
  end
  object Bevel5: TBevel
    Left = 800
    Top = 45
    Width = 8
    Height = 609
    Align = alRight
    Shape = bsRightLine
    ExplicitLeft = 809
    ExplicitTop = 43
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 1190
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    DesignSize = (
      1190
      41)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 1174
      Height = 25
      Anchors = [akLeft, akTop, akRight]
      BorderStyle = bsNone
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsItalic]
      Lines.Strings = (
        
          'Verschiedenen Feature- und Klassifizierungs-Algorithmen vergleic' +
          'hen')
      ParentColor = True
      ParentFont = False
      ReadOnly = True
      TabOrder = 0
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 658
    Width = 1190
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    DesignSize = (
      1190
      41)
    object btClose: TButton
      Left = 1107
      Top = 6
      Width = 75
      Height = 25
      Action = acClose
      Anchors = [akRight, akBottom]
      TabOrder = 0
    end
    object pbJob: TProgressBar
      Left = 8
      Top = 6
      Width = 1093
      Height = 25
      TabOrder = 1
      Visible = False
    end
  end
  object pnAuswahl: TPanel
    Left = 425
    Top = 45
    Width = 375
    Height = 609
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 2
    ExplicitLeft = 423
    ExplicitTop = 51
    object Bevel3: TBevel
      Left = 0
      Top = 115
      Width = 375
      Height = 8
      Align = alTop
      Shape = bsTopLine
      ExplicitLeft = 112
      ExplicitTop = 424
      ExplicitWidth = 50
    end
    object Bevel6: TBevel
      Left = 0
      Top = 238
      Width = 375
      Height = 8
      Align = alTop
      Shape = bsTopLine
      ExplicitLeft = -2
      ExplicitTop = 232
    end
    object Bevel7: TBevel
      Left = 0
      Top = 361
      Width = 375
      Height = 8
      Align = alTop
      Shape = bsTopLine
      ExplicitLeft = -2
      ExplicitTop = 424
    end
    object pnAlg: TPanel
      Left = 0
      Top = 0
      Width = 375
      Height = 115
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 0
      object Label1: TLabel
        Left = 120
        Top = 6
        Width = 118
        Height = 16
        Caption = 'Feature-Algorithmen'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsUnderline]
        ParentFont = False
      end
      object cxChoi: TCheckBox
        Left = 16
        Top = 32
        Width = 193
        Height = 17
        Caption = 'Choi 2016, acht fiduzielle Punkte'
        TabOrder = 0
        OnClick = cxClassifySvmClick
      end
      object cxRandom: TCheckBox
        Left = 16
        Top = 55
        Width = 281
        Height = 17
        Caption = 'Random Points, 20 verteilte Punkte im QRS-Komplex'
        TabOrder = 1
        OnClick = cxClassifySvmClick
      end
    end
    object pnClassify: TPanel
      Left = 0
      Top = 123
      Width = 375
      Height = 115
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 1
      object Label2: TLabel
        Left = 120
        Top = 6
        Width = 161
        Height = 16
        Caption = 'Klassifizierungs-Algorithmen'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsUnderline]
        ParentFont = False
      end
      object cxClassifySvm: TCheckBox
        Left = 16
        Top = 36
        Width = 281
        Height = 17
        Caption = 'SVM nach Choi 2016 (libSVM)'
        TabOrder = 0
        OnClick = cxClassifySvmClick
      end
    end
    object btVergleich: TButton
      Left = 112
      Top = 578
      Width = 169
      Height = 25
      Caption = 'Vergleich starten'
      Enabled = False
      TabOrder = 2
      OnClick = btVergleichClick
    end
    object pnSvm: TPanel
      Left = 0
      Top = 246
      Width = 375
      Height = 115
      Align = alTop
      BevelOuter = bvNone
      Enabled = False
      TabOrder = 3
      object Label3: TLabel
        Left = 120
        Top = 6
        Width = 125
        Height = 16
        Caption = 'Einstellungen f'#252'r SVM'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsUnderline]
        ParentFont = False
      end
      object Label4: TLabel
        Left = 6
        Top = 48
        Width = 113
        Height = 13
        Caption = 'Datens'#228'tze f'#252'r Training'
      end
      object Label6: TLabel
        Left = 253
        Top = 48
        Width = 13
        Height = 13
        Caption = 'bis'
      end
      object Label7: TLabel
        Left = 6
        Top = 72
        Width = 142
        Height = 13
        Caption = 'Datens'#228'tze f'#252'r Klassifizierung'
      end
      object Label9: TLabel
        Left = 253
        Top = 72
        Width = 13
        Height = 13
        Caption = 'bis'
      end
      object edTrainingVon: TEdit
        Left = 181
        Top = 45
        Width = 66
        Height = 21
        TabOrder = 0
        OnChange = cxClassifySvmClick
      end
      object edTrainingBis: TEdit
        Left = 272
        Top = 45
        Width = 66
        Height = 21
        TabOrder = 1
        OnChange = cxClassifySvmClick
      end
      object edClassifyVon: TEdit
        Left = 181
        Top = 69
        Width = 66
        Height = 21
        TabOrder = 2
        OnChange = cxClassifySvmClick
      end
      object edClassifyBis: TEdit
        Left = 272
        Top = 69
        Width = 66
        Height = 21
        TabOrder = 3
        OnChange = cxClassifySvmClick
      end
    end
  end
  object pnEcg: TPanel
    Left = 0
    Top = 45
    Width = 417
    Height = 609
    Align = alLeft
    BevelOuter = bvNone
    TabOrder = 3
  end
  object memo: TMemo
    Left = 808
    Top = 45
    Width = 382
    Height = 609
    Align = alRight
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
  end
  object tStartup: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tStartupTimer
    Left = 256
    Top = 8
  end
  object ActionList1: TActionList
    Left = 288
    Top = 8
    object acClose: TAction
      Caption = '&Schlie'#223'en'
      OnExecute = acCloseExecute
    end
    object acClassify: TAction
      Caption = '&Klassifizierung durchf'#252'hren'
    end
  end
end
