object fmBaseDiseases: TfmBaseDiseases
  Left = 0
  Top = 0
  Caption = 'BaseForm Diseases'
  ClientHeight = 542
  ClientWidth = 405
  Color = clBtnFace
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
  object lvDiseases: TListView
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
        Caption = 'Bezeichnung'
        Width = 150
      end>
    GridLines = True
    MultiSelect = True
    ReadOnly = True
    RowSelect = True
    PopupMenu = PopupMenuDiseases
    TabOrder = 0
    ViewStyle = vsReport
    OnClick = lvDiseasesClick
    OnDblClick = lvDiseasesDblClick
  end
  object Panel4: TPanel
    Left = 0
    Top = 0
    Width = 405
    Height = 63
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
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
      Width = 21
      Height = 13
      Caption = 'Bez.'
    end
    object edDisIdVon: TEdit
      Left = 119
      Top = 5
      Width = 57
      Height = 21
      TabOrder = 0
      OnExit = edDisIdVonExit
    end
    object edDisIdBis: TEdit
      Left = 206
      Top = 6
      Width = 57
      Height = 21
      TabOrder = 1
      OnExit = edDisIdVonExit
    end
    object edDisName: TEdit
      Left = 119
      Top = 32
      Width = 144
      Height = 21
      TabOrder = 2
      OnChange = edDisNameChange
      OnExit = edDisIdVonExit
    end
  end
  object ActionListDiseases: TActionList
    Left = 144
    Top = 80
    object acDisFilter: TAction
      Caption = 'Erkrankungen filtern'
      OnExecute = acDisFilterExecute
    end
    object acDisAdd: TAction
      Caption = 'Erkrankung hinzuf'#252'gen'
      OnExecute = acDisAddExecute
    end
    object acDisDel: TAction
      Caption = 'Erkrankung l'#246'schen'
      Enabled = False
      OnExecute = acDisDelExecute
    end
    object acDisChange: TAction
      Caption = 'Erkrankung &'#228'ndern'
      Enabled = False
      OnExecute = acDisChangeExecute
    end
  end
  object PopupMenuDiseases: TPopupMenu
    Left = 176
    Top = 80
    object Erkrankunghinzufgen1: TMenuItem
      Action = acDisAdd
    end
    object Erkrankungndern1: TMenuItem
      Action = acDisChange
    end
    object Erkrankunglschen1: TMenuItem
      Action = acDisDel
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
