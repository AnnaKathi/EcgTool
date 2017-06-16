object fmDatabases: TfmDatabases
  Left = 0
  Top = 0
  Caption = 'Datenbank - Allgemeine '#220'bersicht'
  ClientHeight = 696
  ClientWidth = 1054
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
    Width = 1054
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -41
    ExplicitWidth = 784
  end
  object Bevel3: TBevel
    Left = 0
    Top = 651
    Width = 1054
    Height = 4
    Align = alBottom
    Shape = bsBottomLine
    ExplicitLeft = -41
    ExplicitTop = 662
    ExplicitWidth = 784
  end
  object Splitter1: TSplitter
    Left = 241
    Top = 45
    Height = 606
    ExplicitLeft = 312
    ExplicitTop = 200
    ExplicitHeight = 100
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 1054
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    ExplicitWidth = 775
    DesignSize = (
      1054
      41)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 1038
      Height = 25
      Anchors = [akLeft, akTop, akRight]
      BorderStyle = bsNone
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsItalic]
      Lines.Strings = (
        'EKG-Tool..., Todo: Text einf'#252'gen')
      ParentColor = True
      ParentFont = False
      ReadOnly = True
      TabOrder = 0
      ExplicitWidth = 759
    end
  end
  object pnBottom: TPanel
    Left = 0
    Top = 655
    Width = 1054
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    ExplicitTop = 649
    ExplicitWidth = 775
    DesignSize = (
      1054
      41)
    object Button1: TButton
      Left = 971
      Top = 6
      Width = 75
      Height = 25
      Action = acClose
      Anchors = [akRight, akBottom]
      TabOrder = 0
      ExplicitLeft = 692
    end
  end
  object pnTabellen: TPanel
    Left = 0
    Top = 45
    Width = 241
    Height = 606
    Align = alLeft
    BevelOuter = bvNone
    TabOrder = 2
    DesignSize = (
      241
      606)
    object Label1: TLabel
      Left = 32
      Top = 6
      Width = 180
      Height = 16
      Caption = 'verf'#252'gbare Datenbank-Tabellen'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsUnderline]
      ParentFont = False
    end
    object lvData: TListView
      Left = 8
      Top = 42
      Width = 225
      Height = 562
      Anchors = [akLeft, akTop, akRight, akBottom]
      Columns = <
        item
          AutoSize = True
          Caption = 'Tabelle'
        end
        item
          Alignment = taRightJustify
          Caption = 'Datens'#228'tze'
          Width = 75
        end>
      GridLines = True
      ReadOnly = True
      RowSelect = True
      TabOrder = 0
      ViewStyle = vsReport
      OnDblClick = lvDataDblClick
    end
  end
  object pnTabelle: TPanel
    Left = 244
    Top = 45
    Width = 810
    Height = 606
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 3
    ExplicitLeft = 536
    ExplicitTop = 104
    ExplicitWidth = 185
    ExplicitHeight = 41
    object pnNoTab: TPanel
      Left = 40
      Top = 32
      Width = 321
      Height = 89
      Caption = 'Tabellen-Ansicht wurde noch nicht implementiert'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsItalic]
      ParentFont = False
      TabOrder = 0
      Visible = False
    end
    object pnSelectDb: TPanel
      Left = 40
      Top = 152
      Width = 321
      Height = 89
      Caption = '- bitte w'#228'hle links eine Tabelle aus -'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsItalic]
      ParentFont = False
      TabOrder = 1
      Visible = False
    end
  end
  object tStartup: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tStartupTimer
    Left = 224
    Top = 8
  end
  object ActionList1: TActionList
    Left = 256
    Top = 8
    object acClose: TAction
      Caption = '&Schlie'#223'en'
      OnExecute = acCloseExecute
    end
  end
end
