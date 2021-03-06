object fmBasePeople: TfmBasePeople
  Left = 0
  Top = 0
  Caption = 'BaseForm People'
  ClientHeight = 542
  ClientWidth = 405
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel4: TBevel
    Left = 0
    Top = 63
    Width = 405
    Height = 8
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = 176
    ExplicitTop = 176
    ExplicitWidth = 50
  end
  object pnFilter: TPanel
    Left = 0
    Top = 0
    Width = 405
    Height = 63
    Align = alTop
    BevelOuter = bvNone
    ParentBackground = False
    ParentColor = True
    TabOrder = 0
    object Label10: TLabel
      Left = 8
      Top = 6
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
      Top = 8
      Width = 47
      Height = 13
      Caption = 'Ident von'
    end
    object Label12: TLabel
      Left = 184
      Top = 8
      Width = 13
      Height = 13
      Caption = 'bis'
    end
    object Label13: TLabel
      Left = 64
      Top = 34
      Width = 27
      Height = 13
      Caption = 'Name'
    end
    object edIdVon: TEdit
      Left = 119
      Top = 5
      Width = 57
      Height = 21
      TabOrder = 0
      OnExit = edIdVonExit
    end
    object edIdBis: TEdit
      Left = 206
      Top = 6
      Width = 57
      Height = 21
      TabOrder = 1
      OnExit = edIdVonExit
    end
    object edName: TEdit
      Left = 119
      Top = 32
      Width = 144
      Height = 21
      TabOrder = 2
      OnChange = edNameChange
      OnExit = edIdVonExit
    end
  end
  object lvPeople: TListView
    Left = 0
    Top = 71
    Width = 405
    Height = 471
    Align = alClient
    Columns = <
      item
        Caption = 'Ident'
      end
      item
        Caption = 'Name'
        Width = 120
      end
      item
        Caption = 'Erkrankungen'
        Width = 90
      end>
    GridLines = True
    MultiSelect = True
    ReadOnly = True
    RowSelect = True
    PopupMenu = PopupMenu
    TabOrder = 1
    ViewStyle = vsReport
    OnClick = lvPeopleClick
    OnDblClick = lvPeopleDblClick
  end
  object ActionListDiseases: TActionList
    Left = 272
    Top = 24
    object acFilter: TAction
      Caption = 'Personen filtern'
      OnExecute = acFilterExecute
    end
    object acAdd: TAction
      Caption = 'Person hinzuf'#252'gen'
      OnExecute = acAddExecute
    end
    object acDel: TAction
      Caption = 'Person l'#246'schen'
      Enabled = False
      OnExecute = acDelExecute
    end
    object acChange: TAction
      Caption = 'Person &'#228'ndern'
      Enabled = False
      OnExecute = acChangeExecute
    end
    object acSelect: TAction
      Caption = 'Person ausw'#228'hlen'
      Enabled = False
      OnExecute = acSelectExecute
    end
  end
  object PopupMenu: TPopupMenu
    Left = 304
    Top = 24
    object Erkrankunghinzufgen1: TMenuItem
      Action = acAdd
    end
    object Erkrankungndern1: TMenuItem
      Action = acChange
    end
    object Erkrankunglschen1: TMenuItem
      Action = acDel
    end
    object N1: TMenuItem
      Caption = '-'
    end
    object Personauswhlen1: TMenuItem
      Action = acSelect
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
