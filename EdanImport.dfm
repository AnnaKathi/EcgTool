object fmEdan: TfmEdan
  Left = 0
  Top = 0
  Caption = 'Edan-Datens'#228'tze umwandeln'
  ClientHeight = 698
  ClientWidth = 648
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
    Width = 648
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -323
    ExplicitWidth = 1054
  end
  object Bevel3: TBevel
    Left = 0
    Top = 653
    Width = 648
    Height = 4
    Align = alBottom
    Shape = bsBottomLine
    ExplicitLeft = -1
    ExplicitTop = 628
  end
  object Label2: TLabel
    Left = 8
    Top = 51
    Width = 89
    Height = 13
    Caption = 'Export-Verzeichnis'
  end
  object Label1: TLabel
    Left = 6
    Top = 137
    Width = 32
    Height = 13
    Caption = 'Lead 1'
  end
  object Label3: TLabel
    Left = 6
    Top = 204
    Width = 32
    Height = 13
    Caption = 'Lead 2'
  end
  object Label4: TLabel
    Left = 6
    Top = 271
    Width = 32
    Height = 13
    Caption = 'Lead 3'
  end
  object Label5: TLabel
    Left = 6
    Top = 338
    Width = 32
    Height = 13
    Caption = 'Lead 4'
  end
  object Label6: TLabel
    Left = 6
    Top = 405
    Width = 32
    Height = 13
    Caption = 'Lead 5'
  end
  object Label7: TLabel
    Left = 6
    Top = 472
    Width = 32
    Height = 13
    Caption = 'Lead 6'
  end
  object Label8: TLabel
    Left = 6
    Top = 539
    Width = 32
    Height = 13
    Caption = 'Lead 7'
  end
  object Label9: TLabel
    Left = 6
    Top = 606
    Width = 32
    Height = 13
    Caption = 'Lead 8'
  end
  object Label10: TLabel
    Left = 8
    Top = 75
    Width = 51
    Height = 13
    Caption = 'Dateiname'
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 648
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 10
    ExplicitLeft = -323
    ExplicitWidth = 1054
    DesignSize = (
      648
      41)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 632
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
      ExplicitWidth = 1038
    end
    object btTest: TButton
      Left = 520
      Top = 10
      Width = 118
      Height = 25
      Caption = 'Testdaten eintragen'
      TabOrder = 1
      OnClick = btTestClick
    end
    object btLoad: TButton
      Left = 392
      Top = 10
      Width = 122
      Height = 25
      Caption = 'Datei laden'
      TabOrder = 2
      OnClick = btLoadClick
    end
  end
  object pnBottom: TPanel
    Left = 0
    Top = 657
    Width = 648
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 11
    ExplicitLeft = -323
    ExplicitTop = 609
    ExplicitWidth = 1054
    DesignSize = (
      648
      41)
    object Button1: TButton
      Left = 565
      Top = 8
      Width = 75
      Height = 25
      Action = acClose
      Anchors = [akRight, akBottom]
      TabOrder = 0
    end
    object Button2: TButton
      Left = 8
      Top = 8
      Width = 75
      Height = 25
      Action = acImport
      TabOrder = 1
    end
    object pbProgress: TProgressBar
      Left = 89
      Top = 8
      Width = 472
      Height = 25
      TabOrder = 2
      Visible = False
    end
  end
  object mLead1: TMemo
    Left = 44
    Top = 117
    Width = 595
    Height = 61
    ScrollBars = ssBoth
    TabOrder = 2
  end
  object edPath: TEdit
    Left = 104
    Top = 47
    Width = 536
    Height = 21
    TabOrder = 0
  end
  object mLead2: TMemo
    Left = 43
    Top = 184
    Width = 595
    Height = 61
    ScrollBars = ssBoth
    TabOrder = 3
  end
  object mLead3: TMemo
    Left = 43
    Top = 251
    Width = 595
    Height = 61
    ScrollBars = ssBoth
    TabOrder = 4
  end
  object mLead4: TMemo
    Left = 43
    Top = 318
    Width = 595
    Height = 61
    ScrollBars = ssBoth
    TabOrder = 5
  end
  object mLead5: TMemo
    Left = 43
    Top = 385
    Width = 595
    Height = 61
    ScrollBars = ssBoth
    TabOrder = 6
  end
  object mLead6: TMemo
    Left = 44
    Top = 452
    Width = 595
    Height = 61
    ScrollBars = ssBoth
    TabOrder = 7
  end
  object mLead7: TMemo
    Left = 43
    Top = 519
    Width = 595
    Height = 61
    ScrollBars = ssBoth
    TabOrder = 8
  end
  object mLead8: TMemo
    Left = 43
    Top = 586
    Width = 595
    Height = 61
    ScrollBars = ssBoth
    TabOrder = 9
  end
  object edFile: TEdit
    Left = 104
    Top = 72
    Width = 536
    Height = 21
    TabOrder = 1
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
    object acImport: TAction
      Caption = '&Einlesen'
      OnExecute = acImportExecute
    end
  end
  object OpenDialog: TOpenDialog
    Left = 288
    Top = 8
  end
end
