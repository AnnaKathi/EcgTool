object fmFeatChoi: TfmFeatChoi
  Left = 0
  Top = 0
  Caption = 'Choi-Features bilden'
  ClientHeight = 705
  ClientWidth = 879
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poDesktopCenter
  OnKeyPress = FormKeyPress
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object imgEcg1: TImage
    Left = 8
    Top = 80
    Width = 489
    Height = 105
  end
  object laEcg1: TLabel
    Left = 8
    Top = 80
    Width = 31
    Height = 13
    Caption = 'laEcg1'
    Visible = False
  end
  object imgEcg2: TImage
    Left = 8
    Top = 312
    Width = 489
    Height = 105
  end
  object laEcg2: TLabel
    Left = 8
    Top = 312
    Width = 31
    Height = 13
    Caption = 'laEcg1'
    Visible = False
  end
  object iHeartEcg1: TImage
    Left = 503
    Top = 24
    Width = 178
    Height = 105
  end
  object Label2: TLabel
    Left = 503
    Top = 5
    Width = 166
    Height = 13
    Caption = 'Standard-Herzschlag (normalisiert)'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsUnderline]
    ParentFont = False
  end
  object iHeartEcg2: TImage
    Left = 503
    Top = 256
    Width = 178
    Height = 105
  end
  object Label3: TLabel
    Left = 687
    Top = 5
    Width = 169
    Height = 13
    Caption = 'Features (aus Standardherzschlag)'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsUnderline]
    ParentFont = False
  end
  object iHeAblEcg1: TImage
    Left = 503
    Top = 130
    Width = 178
    Height = 105
  end
  object iHeAblEcg2: TImage
    Left = 503
    Top = 362
    Width = 178
    Height = 105
  end
  object imgEcg3: TImage
    Left = 8
    Top = 544
    Width = 489
    Height = 105
  end
  object laEcg3: TLabel
    Left = 16
    Top = 552
    Width = 31
    Height = 13
    Caption = 'laEcg1'
    Visible = False
  end
  object iHeartEcg3: TImage
    Left = 503
    Top = 488
    Width = 178
    Height = 105
  end
  object iHeAblEcg3: TImage
    Left = 503
    Top = 594
    Width = 178
    Height = 105
  end
  object laElke: TLabel
    Left = 8
    Top = 8
    Width = 95
    Height = 13
    Caption = 'Pre-Load Proband 8'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsUnderline]
    ParentFont = False
    OnClick = laElkeClick
  end
  object btLoadEkg1: TButton
    Left = 8
    Top = 191
    Width = 105
    Height = 25
    Caption = 'EKG laden'
    TabOrder = 0
    OnClick = btLoadEkg1Click
  end
  object cbLead1: TComboBox
    Left = 119
    Top = 193
    Width = 105
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 1
    OnChange = cbLead1Change
    Items.Strings = (
      'Channel 1'
      'Channel 2'
      'Channel 3'
      'Channel 4'
      'Channel 5'
      'Channel 6'
      'Channel 7'
      'Channel 8'
      'Ableitung 12'
      'Ableitung 34'
      'Ableitung 56')
  end
  object btFeat1: TButton
    Left = 392
    Top = 191
    Width = 105
    Height = 25
    Caption = 'Get Features'
    TabOrder = 2
    OnClick = btFeat1Click
  end
  object mFeatO1: TMemo
    Left = 687
    Top = 24
    Width = 185
    Height = 105
    Lines.Strings = (
      'mFeat1')
    TabOrder = 3
  end
  object mFeatO2: TMemo
    Left = 687
    Top = 256
    Width = 185
    Height = 105
    Lines.Strings = (
      'mFeat1')
    TabOrder = 4
  end
  object btLoadEkg2: TButton
    Left = 8
    Top = 423
    Width = 105
    Height = 25
    Caption = 'EKG laden'
    TabOrder = 5
    OnClick = btLoadEkg2Click
  end
  object cbLead2: TComboBox
    Left = 119
    Top = 425
    Width = 105
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 6
    OnChange = cbLead2Change
    Items.Strings = (
      'Channel 1'
      'Channel 2'
      'Channel 3'
      'Channel 4'
      'Channel 5'
      'Channel 6'
      'Channel 7'
      'Channel 8'
      'Ableitung 12'
      'Ableitung 34'
      'Ableitung 56')
  end
  object btFeat2: TButton
    Left = 392
    Top = 423
    Width = 105
    Height = 25
    Caption = 'Get Features'
    TabOrder = 7
    OnClick = btFeat2Click
  end
  object mFeatA1: TMemo
    Left = 687
    Top = 130
    Width = 185
    Height = 105
    Lines.Strings = (
      'mFeat1')
    TabOrder = 8
  end
  object mFeatA2: TMemo
    Left = 687
    Top = 362
    Width = 185
    Height = 105
    Lines.Strings = (
      'mFeat1')
    TabOrder = 9
  end
  object btGlatt1: TButton
    Left = 304
    Top = 191
    Width = 82
    Height = 25
    Caption = 'Gl'#228'tten um 10'
    TabOrder = 10
    OnClick = btGlatt1Click
  end
  object btGlatt2: TButton
    Left = 304
    Top = 423
    Width = 82
    Height = 25
    Caption = 'Gl'#228'tten um 10'
    TabOrder = 11
    OnClick = btGlatt2Click
  end
  object mFeatO3: TMemo
    Left = 687
    Top = 488
    Width = 185
    Height = 105
    Lines.Strings = (
      'mFeat1')
    TabOrder = 12
  end
  object btLoadEcg3: TButton
    Left = 8
    Top = 655
    Width = 105
    Height = 25
    Caption = 'EKG laden'
    TabOrder = 13
    OnClick = btLoadEcg3Click
  end
  object cbLead3: TComboBox
    Left = 119
    Top = 657
    Width = 105
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 14
    OnChange = cbLead3Change
    Items.Strings = (
      'Channel 1'
      'Channel 2'
      'Channel 3'
      'Channel 4'
      'Channel 5'
      'Channel 6'
      'Channel 7'
      'Channel 8'
      'Ableitung 12'
      'Ableitung 34'
      'Ableitung 56')
  end
  object btFeat3: TButton
    Left = 392
    Top = 655
    Width = 105
    Height = 25
    Caption = 'Get Features'
    TabOrder = 15
    OnClick = btFeat3Click
  end
  object mFeatA3: TMemo
    Left = 687
    Top = 594
    Width = 185
    Height = 105
    Lines.Strings = (
      'mFeat1')
    TabOrder = 16
  end
  object btGlatt3: TButton
    Left = 304
    Top = 655
    Width = 82
    Height = 25
    Caption = 'Gl'#228'tten um 10'
    TabOrder = 17
    OnClick = btGlatt3Click
  end
  object pbJob: TProgressBar
    Left = 8
    Top = 27
    Width = 489
    Height = 17
    TabOrder = 18
    Visible = False
  end
  object OpenDialog: TOpenDialog
    Left = 464
    Top = 2
  end
end
