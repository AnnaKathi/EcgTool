object fmWizSession: TfmWizSession
  Left = 0
  Top = 0
  Caption = 'Session-Wizard'
  ClientHeight = 665
  ClientWidth = 629
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnClose = FormClose
  OnKeyPress = FormKeyPress
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 0
    Top = 41
    Width = 629
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -41
    ExplicitWidth = 784
  end
  object Bevel3: TBevel
    Left = 0
    Top = 620
    Width = 629
    Height = 4
    Align = alBottom
    Shape = bsBottomLine
    ExplicitTop = 596
    ExplicitWidth = 655
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 629
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    ExplicitWidth = 747
    DesignSize = (
      629
      41)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 613
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
      ExplicitWidth = 731
    end
  end
  object pnBottom: TPanel
    Left = 0
    Top = 624
    Width = 629
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    ExplicitTop = 559
    ExplicitWidth = 655
    DesignSize = (
      629
      41)
    object Button1: TButton
      Left = 546
      Top = 6
      Width = 75
      Height = 25
      Action = acNext
      Anchors = [akRight, akBottom]
      TabOrder = 0
      ExplicitLeft = 572
    end
    object Button2: TButton
      Left = 8
      Top = 8
      Width = 75
      Height = 25
      Action = acBack
      TabOrder = 1
    end
  end
  object pcSession: TPageControl
    Left = 0
    Top = 45
    Width = 629
    Height = 575
    ActivePage = tbBasics
    Align = alClient
    TabOrder = 2
    object tbBasics: TTabSheet
      Caption = 'Session-Daten'
      ExplicitWidth = 601
      ExplicitHeight = 237
      DesignSize = (
        621
        547)
      object Label1: TLabel
        Left = 16
        Top = 16
        Width = 83
        Height = 13
        Caption = 'Date-Time-Stamp'
      end
      object btNow: TSpeedButton
        Left = 376
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
        Width = 74
        Height = 13
        Caption = 'Ort der Session'
      end
      object Label3: TLabel
        Left = 16
        Top = 80
        Width = 60
        Height = 13
        Caption = 'Researchers'
      end
      object SpeedButton1: TSpeedButton
        Left = 376
        Top = 80
        Width = 33
        Height = 24
        Action = acAddResearcher
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object SpeedButton2: TSpeedButton
        Left = 376
        Top = 110
        Width = 33
        Height = 24
        Action = acDelResearcher
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label4: TLabel
        Left = 16
        Top = 197
        Width = 111
        Height = 13
        Caption = 'Kommentar zur Session'
      end
      object edStamp: TEdit
        Left = 138
        Top = 13
        Width = 237
        Height = 21
        TabOrder = 0
        OnChange = edStampChange
      end
      object cbOrte: TComboBox
        Left = 138
        Top = 42
        Width = 271
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 1
      end
      object lvResearchers: TListView
        Left = 138
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
      end
      object mKommentar: TMemo
        Left = 138
        Top = 194
        Width = 240
        Height = 207
        Anchors = [akLeft, akTop, akRight]
        ScrollBars = ssBoth
        TabOrder = 3
      end
    end
    object tbPersonen: TTabSheet
      Caption = 'Personen-Daten'
      ImageIndex = 1
    end
  end
  object ActionList1: TActionList
    Left = 216
    Top = 8
    object acNext: TAction
      Caption = '&Weiter'
      Enabled = False
      OnExecute = acNextExecute
    end
    object acBack: TAction
      Caption = '&Zur'#252'ck'
      Enabled = False
      OnExecute = acBackExecute
    end
    object acClose: TAction
      Caption = 'Schlie'#223'en'
      OnExecute = acCloseExecute
    end
  end
  object tStartup: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tStartupTimer
    Left = 248
    Top = 8
  end
  object ActionListBasics: TActionList
    Left = 40
    Top = 208
    object acAddResearcher: TAction
      Caption = 'add'
      OnExecute = acAddResearcherExecute
    end
    object acDelResearcher: TAction
      Caption = 'del'
      OnExecute = acDelResearcherExecute
    end
  end
end
