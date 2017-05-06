object fmBaseDesc: TfmBaseDesc
  Left = 0
  Top = 0
  Caption = 'BaseForm DescDb'
  ClientHeight = 658
  ClientWidth = 453
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel4: TBevel
    Left = 0
    Top = 97
    Width = 453
    Height = 8
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = 176
    ExplicitTop = 176
    ExplicitWidth = 50
  end
  object lvData: TListView
    Left = 0
    Top = 105
    Width = 453
    Height = 553
    Align = alClient
    Columns = <
      item
        Caption = 'Ident'
      end
      item
        Caption = 'Bezeichnung'
        Width = 150
      end>
    GridLines = True
    MultiSelect = True
    ReadOnly = True
    RowSelect = True
    PopupMenu = PopupMenu
    TabOrder = 0
    ViewStyle = vsReport
    OnClick = lvDataClick
    OnDblClick = lvDataDblClick
    ExplicitTop = 71
    ExplicitHeight = 587
  end
  object pnFilter: TPanel
    Left = 0
    Top = 0
    Width = 453
    Height = 97
    Align = alTop
    BevelOuter = bvNone
    ParentBackground = False
    ParentColor = True
    TabOrder = 1
    object Label10: TLabel
      Left = 8
      Top = 31
      Width = 29
      Height = 13
      Caption = 'Filter'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsUnderline]
      ParentFont = False
    end
    object Label11: TLabel
      Left = 64
      Top = 33
      Width = 47
      Height = 13
      Caption = 'Ident von'
    end
    object Label12: TLabel
      Left = 184
      Top = 33
      Width = 13
      Height = 13
      Caption = 'bis'
    end
    object Label13: TLabel
      Left = 64
      Top = 59
      Width = 21
      Height = 13
      Caption = 'Bez.'
    end
    object laTabelle: TLabel
      Left = 64
      Top = 7
      Width = 47
      Height = 14
      Caption = 'laTabelle'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsUnderline]
      ParentFont = False
    end
    object edIdVon: TEdit
      Left = 119
      Top = 30
      Width = 57
      Height = 21
      TabOrder = 0
      OnExit = edIdVonExit
    end
    object edIdBis: TEdit
      Left = 206
      Top = 31
      Width = 57
      Height = 21
      TabOrder = 1
      OnExit = edIdVonExit
    end
    object edBez: TEdit
      Left = 119
      Top = 57
      Width = 144
      Height = 21
      TabOrder = 2
      OnChange = edBezChange
      OnExit = edIdVonExit
    end
  end
  object ActionList: TActionList
    Left = 144
    Top = 80
    object acFilter: TAction
      Caption = 'Datens'#228'tze &filtern'
      OnExecute = acFilterExecute
    end
    object acAdd: TAction
      Caption = 'Datensatz &hinzuf'#252'gen'
      OnExecute = acAddExecute
    end
    object acDel: TAction
      Caption = 'Datensatz &l'#246'schen'
      Enabled = False
      OnExecute = acDelExecute
    end
    object acEdit: TAction
      Caption = 'Datensatz &'#228'ndern'
      Enabled = False
      OnExecute = acEditExecute
    end
  end
  object PopupMenu: TPopupMenu
    Left = 176
    Top = 80
    object Erkrankunghinzufgen1: TMenuItem
      Action = acAdd
    end
    object Erkrankungndern1: TMenuItem
      Action = acEdit
    end
    object Erkrankunglschen1: TMenuItem
      Action = acDel
    end
  end
  object tStartup: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tStartupTimer
    Left = 8
    Top = 24
  end
end
