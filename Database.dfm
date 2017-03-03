object fmData: TfmData
  Left = 0
  Top = 0
  Caption = 'Ansicht Datenbank'
  ClientHeight = 630
  ClientWidth = 800
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
    Width = 800
    Height = 8
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = 152
    ExplicitTop = 72
    ExplicitWidth = 50
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 800
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    DesignSize = (
      800
      41)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 784
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
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 589
    Width = 800
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    DesignSize = (
      800
      41)
    object btClose: TButton
      Left = 720
      Top = 8
      Width = 75
      Height = 25
      Action = acClose
      Anchors = [akTop, akRight]
      TabOrder = 0
    end
    object Button1: TButton
      Left = 8
      Top = 6
      Width = 75
      Height = 25
      Action = acRefresh
      TabOrder = 1
    end
    object pbJob: TProgressBar
      Left = 96
      Top = 8
      Width = 609
      Height = 17
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 2
      Visible = False
    end
  end
  object lvData: TListView
    Left = 0
    Top = 129
    Width = 800
    Height = 460
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
        Caption = 'Position'
        Width = 100
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
    ReadOnly = True
    RowSelect = True
    TabOrder = 2
    ViewStyle = vsReport
  end
  object pnFilter: TPanel
    Left = 0
    Top = 49
    Width = 800
    Height = 80
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 3
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
      Left = 312
      Top = 8
      Width = 37
      Height = 13
      Caption = 'Position'
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
    object edName: TEdit
      Left = 119
      Top = 31
      Width = 144
      Height = 21
      TabOrder = 2
      OnChange = edNameChange
      OnExit = edIdVonExit
      OnKeyPress = edIdVonKeyPress
    end
    object cbPosition: TComboBox
      Left = 368
      Top = 6
      Width = 145
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      ItemIndex = 0
      TabOrder = 3
      Text = '- alle Positionen -'
      OnChange = cbPositionChange
      Items.Strings = (
        '- alle Positionen -'
        'liegend'
        'sitzend'
        'stehend'
        'gehend')
    end
  end
  object tStartup: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tStartupTimer
    Left = 392
    Top = 8
  end
  object ActionList: TActionList
    Left = 424
    Top = 8
    object acClose: TAction
      Caption = '&Schlie'#223'en'
      OnExecute = acCloseExecute
    end
    object acRefresh: TAction
      Caption = '&Neu laden'
      OnExecute = acRefreshExecute
    end
    object acFilter: TAction
      Caption = '&Filter'
      OnExecute = acFilterExecute
    end
  end
end
