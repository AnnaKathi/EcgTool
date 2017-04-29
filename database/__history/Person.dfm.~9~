object fmPerson: TfmPerson
  Left = 0
  Top = 0
  BorderStyle = bsToolWindow
  Caption = 'Person anlegen'
  ClientHeight = 380
  ClientWidth = 288
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
    Width = 288
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -181
    ExplicitWidth = 822
  end
  object Bevel2: TBevel
    Left = 0
    Top = 335
    Width = 288
    Height = 4
    Align = alBottom
    Shape = bsBottomLine
    ExplicitTop = 49
    ExplicitWidth = 503
  end
  object Label1: TLabel
    Left = 16
    Top = 64
    Width = 42
    Height = 13
    Caption = 'Vorname'
  end
  object Label2: TLabel
    Left = 16
    Top = 91
    Width = 50
    Height = 13
    Caption = 'Nachname'
  end
  object Label3: TLabel
    Left = 16
    Top = 120
    Width = 66
    Height = 13
    Caption = 'Erkrankungen'
  end
  object SpeedButton1: TSpeedButton
    Left = 49
    Top = 144
    Width = 33
    Height = 22
    Action = acDisAdd
  end
  object SpeedButton2: TSpeedButton
    Left = 49
    Top = 172
    Width = 33
    Height = 22
    Action = acDisDel
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 288
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    ExplicitWidth = 467
    DesignSize = (
      288
      41)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 272
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
      ExplicitWidth = 451
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 339
    Width = 288
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    ExplicitLeft = 192
    ExplicitTop = 336
    ExplicitWidth = 185
    DesignSize = (
      288
      41)
    object Button1: TButton
      Left = 205
      Top = 6
      Width = 75
      Height = 25
      Action = acClose
      Anchors = [akTop, akRight]
      TabOrder = 0
      ExplicitLeft = 420
    end
    object Button2: TButton
      Left = 7
      Top = 6
      Width = 75
      Height = 25
      Action = acSave
      TabOrder = 1
    end
  end
  object edVorname: TEdit
    Left = 96
    Top = 61
    Width = 180
    Height = 21
    TabOrder = 2
  end
  object edNachname: TEdit
    Left = 96
    Top = 88
    Width = 180
    Height = 21
    TabOrder = 3
  end
  object lvDiseases: TListView
    Left = 96
    Top = 120
    Width = 180
    Height = 201
    Columns = <
      item
        Caption = 'Ident'
      end
      item
        Caption = 'Bezeichnung'
        Width = 120
      end>
    GridLines = True
    ReadOnly = True
    RowSelect = True
    TabOrder = 4
    ViewStyle = vsReport
  end
  object tStartup: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tStartupTimer
    Left = 200
    Top = 8
  end
  object ActionList1: TActionList
    Left = 232
    Top = 8
    object acClose: TAction
      Caption = '&Schlie'#223'en'
      OnExecute = acCloseExecute
    end
    object acSave: TAction
      Caption = 'Speichern'
      OnExecute = acSaveExecute
    end
    object acDisAdd: TAction
      Caption = 'add'
      OnExecute = acDisAddExecute
    end
    object acDisDel: TAction
      Caption = 'del'
      OnExecute = acDisDelExecute
    end
  end
end
