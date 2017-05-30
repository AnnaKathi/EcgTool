object fmData: TfmData
  Left = 0
  Top = 0
  Caption = 'Ansicht Datenbank'
  ClientHeight = 627
  ClientWidth = 1290
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
    Width = 1290
    Height = 8
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = 152
    ExplicitTop = 72
    ExplicitWidth = 50
  end
  object Splitter1: TSplitter
    Left = 731
    Top = 49
    Height = 537
    ExplicitLeft = 120
    ExplicitTop = 184
    ExplicitHeight = 100
  end
  object Splitter2: TSplitter
    Left = 455
    Top = 49
    Height = 537
    ExplicitLeft = 270
    ExplicitTop = 51
    ExplicitHeight = 645
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 1290
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    ExplicitWidth = 1063
    DesignSize = (
      1290
      41)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 1274
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
      ExplicitWidth = 1047
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 586
    Width = 1290
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    ExplicitWidth = 1063
    DesignSize = (
      1290
      41)
    object btClose: TButton
      Left = 1210
      Top = 8
      Width = 75
      Height = 25
      Action = acClose
      Anchors = [akTop, akRight]
      TabOrder = 0
      ExplicitLeft = 983
    end
    object pbJob: TProgressBar
      Left = 8
      Top = 8
      Width = 1187
      Height = 17
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 1
      Visible = False
      ExplicitWidth = 960
    end
  end
  object pnPeople: TPanel
    Left = 0
    Top = 49
    Width = 455
    Height = 537
    Align = alLeft
    Color = clWhite
    ParentBackground = False
    TabOrder = 2
  end
  object pnEcgData: TPanel
    Left = 734
    Top = 49
    Width = 509
    Height = 537
    Align = alLeft
    Color = clWhite
    ParentBackground = False
    TabOrder = 3
  end
  object pnDiseases: TPanel
    Left = 458
    Top = 49
    Width = 273
    Height = 537
    Align = alLeft
    Color = clWhite
    ParentBackground = False
    TabOrder = 4
  end
  object Panel5: TPanel
    Left = 1243
    Top = 49
    Width = 276
    Height = 537
    Align = alLeft
    TabOrder = 5
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
  object tCallback: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tCallbackTimer
    Left = 472
    Top = 8
  end
end
