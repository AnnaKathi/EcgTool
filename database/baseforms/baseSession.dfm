object fmBaseSession: TfmBaseSession
  Left = 0
  Top = 0
  Caption = 'baseForm Sessions'
  ClientHeight = 698
  ClientWidth = 647
  Color = clBtnFace
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
    Top = 63
    Width = 647
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
    Width = 647
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
      Left = 189
      Top = 8
      Width = 13
      Height = 13
      Caption = 'bis'
    end
    object Label13: TLabel
      Left = 64
      Top = 34
      Width = 54
      Height = 13
      Caption = 'Kommentar'
    end
    object Label1: TLabel
      Left = 344
      Top = 8
      Width = 16
      Height = 13
      Caption = 'Ort'
    end
    object edIdVon: TEdit
      Left = 124
      Top = 5
      Width = 57
      Height = 21
      TabOrder = 0
      OnExit = edIdVonExit
    end
    object edIdBis: TEdit
      Left = 211
      Top = 6
      Width = 57
      Height = 21
      TabOrder = 1
      OnExit = edIdVonExit
    end
    object edKommentar: TEdit
      Left = 124
      Top = 32
      Width = 144
      Height = 21
      TabOrder = 2
      OnChange = acFilterExecute
      OnExit = acFilterExecute
    end
    object cbOrt: TComboBox
      Left = 376
      Top = 3
      Width = 145
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 3
      OnChange = acFilterExecute
    end
  end
  object lvSession: TListView
    Left = 0
    Top = 71
    Width = 647
    Height = 627
    Align = alClient
    Columns = <
      item
        Caption = 'Ident'
      end
      item
        Caption = 'Datum'
        Width = 120
      end
      item
        Caption = 'Ort'
        Width = 125
      end
      item
        Caption = 'Kommentar'
        Width = 200
      end
      item
        Alignment = taRightJustify
        Caption = 'Anz. EKG'
        Width = 75
      end>
    GridLines = True
    MultiSelect = True
    ReadOnly = True
    RowSelect = True
    PopupMenu = PopupMenu
    TabOrder = 1
    ViewStyle = vsReport
    OnClick = lvSessionClick
    OnDblClick = lvSessionDblClick
  end
  object ActionListDiseases: TActionList
    Left = 272
    Top = 24
    object acFilter: TAction
      Caption = 'Sessions filtern'
      OnExecute = acFilterExecute
    end
    object acAdd: TAction
      Caption = 'Session hinzuf'#252'gen'
      OnExecute = acAddExecute
    end
    object acDel: TAction
      Caption = 'Session l'#246'schen'
      Enabled = False
      OnExecute = acDelExecute
    end
    object acChange: TAction
      Caption = 'Session &'#228'ndern'
      Enabled = False
      OnExecute = acChangeExecute
    end
    object acSelect: TAction
      Caption = 'Session ausw'#228'hlen'
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
