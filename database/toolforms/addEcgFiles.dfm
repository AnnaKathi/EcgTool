object fmEcgFiles: TfmEcgFiles
  Left = 0
  Top = 0
  Caption = 'EKG-Datei hinzuf'#252'gen'
  ClientHeight = 456
  ClientWidth = 418
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
    Width = 418
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -193
    ExplicitWidth = 834
  end
  object Bevel2: TBevel
    Left = 0
    Top = 411
    Width = 418
    Height = 4
    Align = alBottom
    Shape = bsBottomLine
    ExplicitTop = 301
    ExplicitWidth = 499
  end
  object Bevel3: TBevel
    Left = 0
    Top = 105
    Width = 418
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
    Width = 418
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    DesignSize = (
      418
      41)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 402
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
    Top = 415
    Width = 418
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    DesignSize = (
      418
      41)
    object Button1: TButton
      Left = 335
      Top = 6
      Width = 75
      Height = 25
      Action = acClose
      Anchors = [akRight, akBottom]
      TabOrder = 0
    end
    object Button2: TButton
      Left = 8
      Top = 6
      Width = 161
      Height = 25
      Action = acEnd
      TabOrder = 1
    end
  end
  object pnData: TPanel
    Left = 0
    Top = 45
    Width = 418
    Height = 60
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 2
    object Label2: TLabel
      Left = 16
      Top = 9
      Width = 80
      Height = 13
      Caption = 'Erfasste Position'
    end
    object Label1: TLabel
      Left = 136
      Top = 36
      Width = 34
      Height = 13
      Caption = 'Format'
    end
    object Label3: TLabel
      Left = 308
      Top = 36
      Width = 38
      Height = 13
      Caption = 'Trenner'
    end
    object Label4: TLabel
      Left = 16
      Top = 41
      Width = 92
      Height = 13
      Caption = 'Datei-Einstellungen'
    end
    object cbPosition: TComboBox
      Left = 136
      Top = 6
      Width = 271
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 0
      OnChange = cbPositionChange
    end
    object cbFormat: TComboBox
      Left = 182
      Top = 33
      Width = 50
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 1
      Items.Strings = (
        '---'
        'ADS')
    end
    object cbDelim: TComboBox
      Left = 357
      Top = 33
      Width = 50
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 2
      Items.Strings = (
        ';'
        ','
        '\t')
    end
  end
  object lvEcg: TListView
    Left = 0
    Top = 113
    Width = 418
    Height = 298
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
      Caption = 'EKG-Datei &hinzuf'#252'gen'
      OnExecute = acAddExecute
    end
    object acDel: TAction
      Caption = 'EKG-Datei &l'#246'schen'
      Enabled = False
      OnExecute = acDelExecute
    end
    object acEnd: TAction
      Caption = 'EKG-Dateien &ausw'#228'hlen'
      Enabled = False
      OnExecute = acEndExecute
    end
  end
  object PopupMenu: TPopupMenu
    Left = 56
    Top = 136
    object EKGhinzufgen1: TMenuItem
      Action = acAdd
    end
    object EKGlschen1: TMenuItem
      Action = acDel
    end
  end
  object OpenDialog: TOpenDialog
    Left = 24
    Top = 136
  end
end
