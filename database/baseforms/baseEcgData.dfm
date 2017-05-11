object fmBaseEcg: TfmBaseEcg
  Left = 0
  Top = 0
  Caption = 'BaseForm EcgData'
  ClientHeight = 542
  ClientWidth = 568
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
  object Bevel1: TBevel
    Left = 0
    Top = 65
    Width = 568
    Height = 8
    Align = alTop
    Shape = bsTopLine
  end
  object lvData: TListView
    Left = 0
    Top = 73
    Width = 568
    Height = 469
    Align = alClient
    Columns = <
      item
        Caption = 'Ident'
      end
      item
        Caption = 'Person'
        Width = 150
      end
      item
        Caption = 'Session'
      end
      item
        Caption = 'Lage'
      end
      item
        Caption = 'T1'
      end
      item
        Caption = 'T2'
      end
      item
        Caption = 'T3'
      end
      item
        Caption = 'T4'
      end
      item
        Caption = 'T5'
      end>
    GridLines = True
    MultiSelect = True
    ReadOnly = True
    RowSelect = True
    TabOrder = 0
    ViewStyle = vsReport
    OnClick = lvDataClick
  end
  object pnFilter: TPanel
    Left = 0
    Top = 0
    Width = 568
    Height = 65
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 1
    object Label6: TLabel
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
    object Label7: TLabel
      Left = 64
      Top = 8
      Width = 47
      Height = 13
      Caption = 'Ident von'
    end
    object Label8: TLabel
      Left = 184
      Top = 8
      Width = 13
      Height = 13
      Caption = 'bis'
    end
    object Label9: TLabel
      Left = 64
      Top = 34
      Width = 27
      Height = 13
      Caption = 'Name'
    end
    object Label10: TLabel
      Left = 279
      Top = 7
      Width = 23
      Height = 13
      Caption = 'Lage'
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
      Top = 31
      Width = 144
      Height = 21
      TabOrder = 2
      OnChange = edNameChange
      OnExit = edIdVonExit
    end
    object cbLage: TComboBox
      Left = 335
      Top = 5
      Width = 106
      Height = 21
      Style = csDropDownList
      ItemHeight = 0
      TabOrder = 3
      OnChange = cbLageChange
    end
  end
  object ActionListDiseases: TActionList
    Left = 136
    Top = 128
    object acFilter: TAction
      Caption = 'EKG-Daten filtern'
      OnExecute = acFilterExecute
    end
    object acAdd: TAction
      Caption = 'EKG hinzuf'#252'gen'
      OnExecute = acAddExecute
    end
    object acDel: TAction
      Caption = 'EKG l'#246'schen'
      Enabled = False
      OnExecute = acDelExecute
    end
    object acChange: TAction
      Caption = 'EKG &'#228'ndern'
      Enabled = False
      OnExecute = acChangeExecute
    end
  end
  object PopupMenuDiseases: TPopupMenu
    Left = 168
    Top = 128
    object Erkrankunghinzufgen1: TMenuItem
      Action = acAdd
    end
    object Erkrankungndern1: TMenuItem
      Action = acChange
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
    Top = 32
  end
end
