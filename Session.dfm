object fmSession: TfmSession
  Left = 0
  Top = 0
  Caption = 'Session anlegen: SIMULATION'
  ClientHeight = 707
  ClientWidth = 834
  Color = clInfoBk
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poDesktopCenter
  OnKeyPress = FormKeyPress
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 14
  object Bevel1: TBevel
    Left = 0
    Top = 41
    Width = 834
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -181
    ExplicitWidth = 822
  end
  object Bevel2: TBevel
    Left = 0
    Top = 233
    Width = 834
    Height = 8
    Align = alTop
    Shape = bsTopLine
  end
  object Bevel3: TBevel
    Left = 0
    Top = 662
    Width = 834
    Height = 4
    Align = alBottom
    Shape = bsBottomLine
    ExplicitTop = 49
    ExplicitWidth = 664
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 834
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    DesignSize = (
      834
      41)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 818
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
  object pnSession: TPanel
    Left = 0
    Top = 45
    Width = 834
    Height = 188
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 1
    object Label1: TLabel
      Left = 16
      Top = 16
      Width = 96
      Height = 14
      Caption = 'Date-Time-Stamp'
    end
    object btNow: TSpeedButton
      Left = 374
      Top = 12
      Width = 33
      Height = 24
      Caption = 'now'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      OnClick = btNowClick
    end
    object Label2: TLabel
      Left = 16
      Top = 45
      Width = 84
      Height = 14
      Caption = 'Ort der Session'
    end
    object Label3: TLabel
      Left = 16
      Top = 80
      Width = 65
      Height = 14
      Caption = 'Researchers'
    end
    object SpeedButton1: TSpeedButton
      Left = 374
      Top = 80
      Width = 33
      Height = 24
      Action = acReAdd
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object SpeedButton2: TSpeedButton
      Left = 374
      Top = 110
      Width = 33
      Height = 24
      Action = acReDel
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object Label4: TLabel
      Left = 432
      Top = 22
      Width = 127
      Height = 14
      Caption = 'Kommentar zur Session'
    end
    object edStamp: TEdit
      Left = 136
      Top = 13
      Width = 237
      Height = 22
      TabOrder = 0
    end
    object cbOrte: TComboBox
      Left = 136
      Top = 42
      Width = 271
      Height = 22
      Style = csDropDownList
      ItemHeight = 14
      TabOrder = 1
    end
    object lvResearchers: TListView
      Left = 136
      Top = 80
      Width = 237
      Height = 97
      Columns = <
        item
          Caption = 'Nr'
        end
        item
          Caption = 'Researcher'
          Width = 175
        end>
      GridLines = True
      ReadOnly = True
      TabOrder = 2
      ViewStyle = vsReport
      OnClick = lvResearchersClick
    end
    object mKommentar: TMemo
      Left = 432
      Top = 42
      Width = 345
      Height = 135
      ScrollBars = ssBoth
      TabOrder = 3
    end
  end
  object lvEcg: TListView
    Left = 8
    Top = 247
    Width = 769
    Height = 346
    Columns = <
      item
        Caption = 'Nr'
      end
      item
        Caption = 'Anz. Werte'
        Width = 75
      end
      item
        Caption = 'Person'
        Width = 90
      end
      item
        Caption = 'State'
        Width = 90
      end
      item
        Caption = 'Lage'
        Width = 90
      end
      item
        Caption = 'Position'
        Width = 90
      end
      item
        Caption = 'File'
        Width = 250
      end>
    GridLines = True
    ReadOnly = True
    PopupMenu = PopupMenu
    TabOrder = 2
    ViewStyle = vsReport
    OnClick = lvEcgClick
  end
  object pnBottom: TPanel
    Left = 0
    Top = 666
    Width = 834
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 3
    ExplicitTop = 606
    ExplicitWidth = 499
    DesignSize = (
      834
      41)
    object Button1: TButton
      Left = 751
      Top = 6
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
      Action = acSave
      TabOrder = 1
    end
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
    object acReAdd: TAction
      Caption = 'add'
      OnExecute = acReAddExecute
    end
    object acReDel: TAction
      Caption = 'del'
      Enabled = False
      OnExecute = acReDelExecute
    end
    object acSave: TAction
      Caption = 'Speichern'
      OnExecute = acSaveExecute
    end
  end
  object PopupMenu: TPopupMenu
    Left = 80
    Top = 328
    object EKGhinzufgen1: TMenuItem
      Action = acEcgAdd
    end
    object EKGlschen1: TMenuItem
      Action = acEcgDel
    end
  end
  object ActionList2: TActionList
    Left = 80
    Top = 296
    object acEcgAdd: TAction
      Caption = 'EKG hinzuf'#252'gen'
      OnExecute = acEcgAddExecute
    end
    object acEcgDel: TAction
      Caption = 'EKG l'#246'schen'
      Enabled = False
      OnExecute = acEcgDelExecute
    end
  end
  object TimerCallback: TTimer
    Enabled = False
    Interval = 100
    OnTimer = TimerCallbackTimer
    Left = 112
    Top = 296
  end
end
