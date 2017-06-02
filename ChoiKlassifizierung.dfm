object fmChoiClassification: TfmChoiClassification
  Left = 0
  Top = 0
  Caption = 'Choi-Klassifizierung durchf'#252'hren'
  ClientHeight = 687
  ClientWidth = 777
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
  DesignSize = (
    777
    687)
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 0
    Top = 41
    Width = 777
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -504
    ExplicitWidth = 1073
  end
  object Bevel2: TBevel
    Left = 0
    Top = 642
    Width = 777
    Height = 4
    Align = alBottom
    Shape = bsBottomLine
    ExplicitLeft = -504
    ExplicitTop = 545
    ExplicitWidth = 1073
  end
  object Label1: TLabel
    Left = 464
    Top = 408
    Width = 204
    Height = 13
    Caption = 'F'#252'r SVM-Training verwenden, Datens'#228'tze:'
  end
  object Label2: TLabel
    Left = 463
    Top = 430
    Width = 18
    Height = 13
    Caption = 'von'
  end
  object Label3: TLabel
    Left = 578
    Top = 430
    Width = 13
    Height = 13
    Caption = 'bis'
  end
  object Label4: TLabel
    Left = 464
    Top = 472
    Width = 209
    Height = 13
    Caption = 'F'#252'r Klassifizierung verwenden, Datens'#228'tze:'
  end
  object Label5: TLabel
    Left = 463
    Top = 494
    Width = 18
    Height = 13
    Caption = 'von'
  end
  object Label6: TLabel
    Left = 578
    Top = 494
    Width = 13
    Height = 13
    Caption = 'bis'
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 777
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    DesignSize = (
      777
      41)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 761
      Height = 25
      Anchors = [akLeft, akTop, akRight]
      BorderStyle = bsNone
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsItalic]
      Lines.Strings = (
        'Choi-Klassifizierung durchf'#252'hren')
      ParentColor = True
      ParentFont = False
      ReadOnly = True
      TabOrder = 0
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 646
    Width = 777
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    DesignSize = (
      777
      41)
    object btClose: TButton
      Left = 694
      Top = 6
      Width = 75
      Height = 25
      Action = acClose
      Anchors = [akRight, akBottom]
      TabOrder = 0
    end
  end
  object pnEcg: TPanel
    Left = 0
    Top = 45
    Width = 457
    Height = 597
    Align = alLeft
    TabOrder = 2
  end
  object memo: TMemo
    Left = 463
    Top = 47
    Width = 306
    Height = 338
    Anchors = [akLeft, akTop, akRight]
    ReadOnly = True
    ScrollBars = ssBoth
    TabOrder = 3
  end
  object edTrainingVon: TEdit
    Left = 487
    Top = 427
    Width = 66
    Height = 21
    TabOrder = 4
  end
  object edTrainingBis: TEdit
    Left = 602
    Top = 427
    Width = 66
    Height = 21
    TabOrder = 5
  end
  object edClassifyVon: TEdit
    Left = 487
    Top = 491
    Width = 66
    Height = 21
    TabOrder = 6
  end
  object edClassifyBis: TEdit
    Left = 602
    Top = 491
    Width = 66
    Height = 21
    TabOrder = 7
  end
  object Button1: TButton
    Left = 463
    Top = 536
    Width = 205
    Height = 25
    Action = acClassify
    TabOrder = 8
  end
  object tStartup: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tStartupTimer
    Left = 256
    Top = 8
  end
  object ActionList1: TActionList
    Left = 288
    Top = 8
    object acClose: TAction
      Caption = '&Schlie'#223'en'
      OnExecute = acCloseExecute
    end
    object acClassify: TAction
      Caption = '&Klassifizierung durchf'#252'hren'
      OnExecute = acClassifyExecute
    end
  end
end
