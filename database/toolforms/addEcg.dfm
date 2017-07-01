object fmAddEcg: TfmAddEcg
  Left = 0
  Top = 0
  Caption = 'Personen-EKG hinzuf'#252'gen'
  ClientHeight = 647
  ClientWidth = 499
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
    Width = 499
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -193
    ExplicitWidth = 834
  end
  object Bevel2: TBevel
    Left = 0
    Top = 602
    Width = 499
    Height = 4
    Align = alBottom
    Shape = bsBottomLine
    ExplicitTop = 49
    ExplicitWidth = 664
  end
  object Bevel3: TBevel
    Left = 0
    Top = 137
    Width = 499
    Height = 8
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -170
    ExplicitTop = 233
    ExplicitWidth = 834
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 499
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    DesignSize = (
      499
      41)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 483
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
    end
  end
  object pnBottom: TPanel
    Left = 0
    Top = 606
    Width = 499
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    object Button1: TButton
      Left = 416
      Top = 6
      Width = 75
      Height = 25
      Action = acClose
      TabOrder = 0
    end
    object Button2: TButton
      Left = 8
      Top = 6
      Width = 161
      Height = 25
      Action = acSelect
      TabOrder = 1
    end
  end
  object pnData: TPanel
    Left = 0
    Top = 45
    Width = 499
    Height = 92
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 2
    object Label2: TLabel
      Left = 16
      Top = 9
      Width = 76
      Height = 13
      Caption = 'Erfasste Person'
    end
    object Label1: TLabel
      Left = 16
      Top = 36
      Width = 94
      Height = 13
      Caption = 'Zustand der Person'
    end
    object Label3: TLabel
      Left = 16
      Top = 63
      Width = 78
      Height = 13
      Caption = 'Lage der Person'
    end
    object cbPerson: TComboBox
      Left = 136
      Top = 6
      Width = 271
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 0
      OnChange = cbPersonChange
    end
    object cbState: TComboBox
      Left = 136
      Top = 33
      Width = 271
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 1
      OnChange = cbPersonChange
    end
    object cbLage: TComboBox
      Left = 136
      Top = 60
      Width = 271
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 2
      OnChange = cbPersonChange
    end
  end
  object lvEcg: TListView
    Left = 0
    Top = 145
    Width = 499
    Height = 457
    Align = alClient
    Columns = <
      item
        Caption = 'Nr'
      end
      item
        Caption = 'Anz. Werte'
        Width = 75
      end
      item
        Caption = 'Position'
        Width = 90
      end
      item
        Caption = 'File'
        Width = 250
      end
      item
        Caption = 'Format'
        Width = 0
      end
      item
        Caption = 'Delim'
        Width = 0
      end>
    GridLines = True
    MultiSelect = True
    ReadOnly = True
    RowSelect = True
    PopupMenu = PopupMenu
    TabOrder = 3
    ViewStyle = vsReport
    OnChange = lvEcgChange
    OnClick = lvEcgClick
  end
  object tStartup: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tStartupTimer
    Left = 264
    Top = 16
  end
  object ActionList1: TActionList
    Left = 296
    Top = 16
    object acClose: TAction
      Caption = '&Schlie'#223'en'
      OnExecute = acCloseExecute
    end
    object acAdd: TAction
      Caption = 'EKG-Dateien &hinzuf'#252'gen'
      OnExecute = acAddExecute
    end
    object acDel: TAction
      Caption = 'EKG-Dateien &l'#246'schen'
      Enabled = False
      OnExecute = acDelExecute
    end
    object acSelect: TAction
      Caption = '&Personen-Daten hinzuf'#252'gen'
      Enabled = False
      OnExecute = acSelectExecute
    end
  end
  object PopupMenu: TPopupMenu
    Left = 88
    Top = 200
    object EKGhinzufgen1: TMenuItem
      Action = acAdd
    end
    object EKGlschen1: TMenuItem
      Action = acDel
    end
  end
  object TimerCallback: TTimer
    Enabled = False
    Interval = 100
    OnTimer = TimerCallbackTimer
    Left = 136
    Top = 208
  end
end
