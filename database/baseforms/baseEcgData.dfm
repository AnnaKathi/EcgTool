object fmBaseEcg: TfmBaseEcg
  Left = 0
  Top = 0
  Caption = 'BaseForm EcgData'
  ClientHeight = 542
  ClientWidth = 629
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
    Top = 97
    Width = 629
    Height = 8
    Align = alTop
    Shape = bsTopLine
    ExplicitTop = 65
    ExplicitWidth = 568
  end
  object lvData: TListView
    Left = 0
    Top = 105
    Width = 629
    Height = 437
    Align = alClient
    Columns = <
      item
        Caption = 'Ident'
        Width = 45
      end
      item
        Caption = 'Session'
        Width = 125
      end
      item
        Caption = 'Ort'
        Width = 100
      end
      item
        Caption = 'Person'
        Width = 100
      end
      item
        Caption = 'Position'
        Width = 100
      end
      item
        Caption = 'Zustand'
        Width = 75
      end
      item
        Caption = 'Lage'
        Width = 75
      end>
    GridLines = True
    MultiSelect = True
    ReadOnly = True
    RowSelect = True
    TabOrder = 0
    ViewStyle = vsReport
    OnClick = lvDataClick
    OnDblClick = lvDataDblClick
    ExplicitTop = 103
    ExplicitWidth = 662
  end
  object pnFilter: TPanel
    Left = 0
    Top = 0
    Width = 629
    Height = 97
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 1
    ExplicitWidth = 587
    object Label6: TLabel
      Left = 8
      Top = 33
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
      Top = 35
      Width = 47
      Height = 13
      Caption = 'Ident von'
    end
    object Label8: TLabel
      Left = 184
      Top = 35
      Width = 13
      Height = 13
      Caption = 'bis'
    end
    object Label9: TLabel
      Left = 64
      Top = 61
      Width = 27
      Height = 13
      Caption = 'Name'
    end
    object Label10: TLabel
      Left = 450
      Top = 61
      Width = 23
      Height = 13
      Caption = 'Lage'
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
    object Label1: TLabel
      Left = 450
      Top = 9
      Width = 37
      Height = 13
      Caption = 'Position'
    end
    object Label2: TLabel
      Left = 450
      Top = 36
      Width = 39
      Height = 13
      Caption = 'Zustand'
    end
    object Label3: TLabel
      Left = 280
      Top = 36
      Width = 36
      Height = 13
      Caption = 'Session'
    end
    object Label4: TLabel
      Left = 280
      Top = 61
      Width = 16
      Height = 13
      Caption = 'Ort'
    end
    object laAuswahl: TLabel
      Left = 280
      Top = 8
      Width = 62
      Height = 14
      Caption = 'laAuswahl'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsUnderline]
      ParentFont = False
    end
    object edIdVon: TEdit
      Left = 119
      Top = 32
      Width = 57
      Height = 21
      TabOrder = 0
      OnExit = edIdVonExit
    end
    object edIdBis: TEdit
      Left = 206
      Top = 33
      Width = 57
      Height = 21
      TabOrder = 1
      OnExit = edIdVonExit
    end
    object edName: TEdit
      Left = 119
      Top = 58
      Width = 144
      Height = 21
      TabOrder = 2
      OnChange = edNameChange
      OnExit = edIdVonExit
    end
    object cbLage: TComboBox
      Left = 495
      Top = 58
      Width = 106
      Height = 21
      Style = csDropDownList
      ItemHeight = 0
      TabOrder = 7
      OnChange = cbLageChange
    end
    object cbPosition: TComboBox
      Left = 495
      Top = 6
      Width = 106
      Height = 21
      Style = csDropDownList
      ItemHeight = 0
      TabOrder = 5
      OnChange = cbLageChange
    end
    object cbState: TComboBox
      Left = 495
      Top = 33
      Width = 106
      Height = 21
      Style = csDropDownList
      ItemHeight = 0
      TabOrder = 6
      OnChange = cbLageChange
    end
    object cbSession: TComboBox
      Left = 322
      Top = 33
      Width = 106
      Height = 21
      Style = csDropDownList
      ItemHeight = 0
      TabOrder = 3
      OnChange = cbLageChange
    end
    object cbOrt: TComboBox
      Left = 322
      Top = 58
      Width = 106
      Height = 21
      Style = csDropDownList
      ItemHeight = 0
      TabOrder = 4
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
    Top = 56
  end
end
