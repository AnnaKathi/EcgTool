object fmData: TfmData
  Left = 0
  Top = 0
  Caption = 'Ansicht Datenbank'
  ClientHeight = 627
  ClientWidth = 1063
  Color = clWhite
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
    Width = 1063
    Height = 8
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = 152
    ExplicitTop = 72
    ExplicitWidth = 50
  end
  object Splitter1: TSplitter
    Left = 549
    Top = 49
    Height = 537
    ExplicitLeft = 120
    ExplicitTop = 184
    ExplicitHeight = 100
  end
  object Splitter2: TSplitter
    Left = 273
    Top = 49
    Height = 537
    ExplicitLeft = 270
    ExplicitTop = 51
    ExplicitHeight = 645
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 1063
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    ExplicitWidth = 1356
    DesignSize = (
      1063
      41)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 1047
      Height = 25
      Anchors = [akLeft, akTop, akRight]
      BorderStyle = bsNone
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsItalic]
      Lines.Strings = (
        'Bietet eine '#220'bersicht '#252'ber die verwendete Datenbank ECG.')
      ParentColor = True
      ParentFont = False
      TabOrder = 0
      ExplicitWidth = 1340
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 586
    Width = 1063
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    ExplicitTop = 694
    ExplicitWidth = 1356
    DesignSize = (
      1063
      41)
    object btClose: TButton
      Left = 983
      Top = 8
      Width = 75
      Height = 25
      Action = acClose
      Anchors = [akTop, akRight]
      TabOrder = 0
      ExplicitLeft = 1276
    end
    object pbJob: TProgressBar
      Left = 8
      Top = 8
      Width = 960
      Height = 17
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 1
      Visible = False
      ExplicitWidth = 1253
    end
  end
  object pnPeople: TPanel
    Left = 0
    Top = 49
    Width = 273
    Height = 537
    Align = alLeft
    TabOrder = 2
    ExplicitHeight = 645
    object Bevel3: TBevel
      Left = 1
      Top = 80
      Width = 271
      Height = 8
      Align = alTop
      Shape = bsTopLine
      ExplicitLeft = 176
      ExplicitTop = 176
      ExplicitWidth = 50
    end
    object Panel2: TPanel
      Left = 1
      Top = 1
      Width = 271
      Height = 79
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 0
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
      object Label14: TLabel
        Left = 95
        Top = 59
        Width = 61
        Height = 16
        Caption = 'Personen'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold, fsUnderline]
        ParentFont = False
      end
      object edPeopleIdVon: TEdit
        Left = 119
        Top = 5
        Width = 57
        Height = 21
        TabOrder = 0
        OnExit = edPeopleNameExit
        OnKeyPress = edPeopleNameKeyPress
      end
      object edPeopleIdBis: TEdit
        Left = 206
        Top = 6
        Width = 57
        Height = 21
        TabOrder = 1
        OnExit = edPeopleNameExit
        OnKeyPress = edPeopleNameKeyPress
      end
      object edPeopleName: TEdit
        Left = 119
        Top = 32
        Width = 144
        Height = 21
        TabOrder = 2
        OnChange = edPeopleNameChange
        OnExit = edPeopleNameExit
        OnKeyPress = edPeopleNameKeyPress
      end
    end
    object lvPeople: TListView
      Left = 1
      Top = 88
      Width = 271
      Height = 448
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
      PopupMenu = PopupMenuPeople
      TabOrder = 1
      ViewStyle = vsReport
      OnClick = lvPeopleClick
      OnDblClick = lvPeopleDblClick
      ExplicitHeight = 556
    end
  end
  object pnEcgData: TPanel
    Left = 552
    Top = 49
    Width = 509
    Height = 537
    Align = alLeft
    TabOrder = 3
    ExplicitHeight = 645
    object Bevel2: TBevel
      Left = 1
      Top = 84
      Width = 507
      Height = 8
      Align = alTop
      Shape = bsTopLine
      ExplicitLeft = 176
      ExplicitTop = 176
      ExplicitWidth = 50
    end
    object pnFilter: TPanel
      Left = 1
      Top = 1
      Width = 507
      Height = 83
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 0
      object Label1: TLabel
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
      object Label2: TLabel
        Left = 64
        Top = 8
        Width = 47
        Height = 13
        Caption = 'Ident von'
      end
      object Label3: TLabel
        Left = 184
        Top = 8
        Width = 13
        Height = 13
        Caption = 'bis'
      end
      object Label4: TLabel
        Left = 64
        Top = 34
        Width = 27
        Height = 13
        Caption = 'Name'
      end
      object Label5: TLabel
        Left = 279
        Top = 7
        Width = 37
        Height = 13
        Caption = 'Position'
      end
      object Label16: TLabel
        Left = 223
        Top = 58
        Width = 68
        Height = 16
        Caption = 'EKG-Daten'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold, fsUnderline]
        ParentFont = False
      end
      object edIdVon: TEdit
        Left = 119
        Top = 5
        Width = 57
        Height = 21
        TabOrder = 0
        OnExit = edIdVonExit
        OnKeyPress = edIdVonKeyPress
      end
      object edIdBis: TEdit
        Left = 206
        Top = 6
        Width = 57
        Height = 21
        TabOrder = 1
        OnExit = edIdVonExit
        OnKeyPress = edIdVonKeyPress
      end
      object edEcgName: TEdit
        Left = 119
        Top = 31
        Width = 144
        Height = 21
        TabOrder = 2
        OnChange = edEcgNameChange
        OnExit = edIdVonExit
        OnKeyPress = edIdVonKeyPress
      end
      object cbPosition: TComboBox
        Left = 335
        Top = 5
        Width = 106
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 3
        OnChange = cbPositionChange
      end
    end
    object lvData: TListView
      Left = 1
      Top = 92
      Width = 507
      Height = 444
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
          Caption = 'Position'
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
      PopupMenu = PopupMenuEcgData
      TabOrder = 1
      ViewStyle = vsReport
      OnClick = lvDataClick
      ExplicitHeight = 552
    end
  end
  object pnDiseases: TPanel
    Left = 276
    Top = 49
    Width = 273
    Height = 537
    Align = alLeft
    TabOrder = 4
    ExplicitHeight = 645
  end
  object Panel5: TPanel
    Left = 1061
    Top = 49
    Width = 276
    Height = 537
    Align = alLeft
    TabOrder = 5
    ExplicitHeight = 645
  end
  object tStartup: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tStartupTimer
    Left = 392
    Top = 8
  end
  object ActionList: TActionList
    Left = 432
    Top = 8
    object acClose: TAction
      Caption = '&Schlie'#223'en'
      OnExecute = acCloseExecute
    end
    object acRefresh: TAction
      Caption = '&Neu laden'
      OnExecute = acRefreshExecute
    end
  end
  object PopupMenuEcgData: TPopupMenu
    Left = 592
    Top = 200
    object EkgDatensatzlschen1: TMenuItem
      Action = acEcgDel
    end
  end
  object PopupMenuPeople: TPopupMenu
    Left = 48
    Top = 208
    object Peronhinzufgen1: TMenuItem
      Action = acPeopleAdd
    end
    object Personndern1: TMenuItem
      Action = acPeopleChange
    end
    object MenuItem1: TMenuItem
      Action = acPeopleDel
    end
    object N1: TMenuItem
      Caption = '-'
    end
    object Personauswhlen1: TMenuItem
      Action = acPeopleSelect
    end
    object Auswahlaufheben1: TMenuItem
      Action = acPeopleDisselect
    end
  end
  object ActionListPeople: TActionList
    Left = 16
    Top = 208
    object acPeopleDel: TAction
      Caption = 'Person l'#246'schen'
      Enabled = False
      OnExecute = acPeopleDelExecute
    end
    object acPeopleAdd: TAction
      Caption = 'Peron hinzuf'#252'gen'
      OnExecute = acPeopleAddExecute
    end
    object acPeopleChange: TAction
      Caption = 'Person &'#228'ndern'
      Enabled = False
      OnExecute = acPeopleChangeExecute
    end
    object acPeopleSelect: TAction
      Caption = 'Person ausw&'#228'hlen'
      Enabled = False
      OnExecute = acPeopleSelectExecute
    end
    object acPeopleDisselect: TAction
      Caption = '&Auswahl aufheben'
      OnExecute = acPeopleDisselectExecute
    end
    object acPeopleFilter: TAction
      Caption = 'Personen filtern'
      OnExecute = acPeopleFilterExecute
    end
  end
  object ActionListEcgData: TActionList
    Left = 560
    Top = 200
    object acEcgAdd: TAction
      Caption = 'EKG-Datensatz hinzuf'#252'gen'
      OnExecute = acEcgAddExecute
    end
    object acEcgDel: TAction
      Caption = 'Ekg-Datensatz l'#246'schen'
      Enabled = False
      OnExecute = acEcgDelExecute
    end
    object acEcgFilter: TAction
      Caption = 'EKG-Daten filtern'
      OnExecute = acEcgFilterExecute
    end
  end
end
