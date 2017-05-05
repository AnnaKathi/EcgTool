object fmDescAdd: TfmDescAdd
  Left = 0
  Top = 0
  BorderStyle = bsToolWindow
  Caption = 'Datensatz anlegen/'#228'ndern'
  ClientHeight = 188
  ClientWidth = 293
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
    Width = 293
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -181
    ExplicitWidth = 822
  end
  object Bevel2: TBevel
    Left = 0
    Top = 143
    Width = 293
    Height = 4
    Align = alBottom
    Shape = bsBottomLine
    ExplicitTop = 301
    ExplicitWidth = 288
  end
  object Label1: TLabel
    Left = 16
    Top = 61
    Width = 26
    Height = 13
    Caption = 'Ident'
  end
  object Label2: TLabel
    Left = 16
    Top = 96
    Width = 60
    Height = 13
    Caption = 'Bezeichnung'
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 293
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    DesignSize = (
      293
      41)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 277
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
  object Panel1: TPanel
    Left = 0
    Top = 147
    Width = 293
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    DesignSize = (
      293
      41)
    object Button1: TButton
      Left = 210
      Top = 6
      Width = 75
      Height = 25
      Action = acClose
      Anchors = [akTop, akRight]
      TabOrder = 0
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
  object edIdent: TEdit
    Left = 96
    Top = 58
    Width = 121
    Height = 21
    Enabled = False
    TabOrder = 2
  end
  object edBez: TEdit
    Left = 96
    Top = 93
    Width = 185
    Height = 21
    TabOrder = 3
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
      Caption = '&Abbrechen'
      OnExecute = acCloseExecute
    end
    object acSave: TAction
      Caption = 'S&peichern'
      ShortCut = 16467
      OnExecute = acSaveExecute
    end
  end
end
