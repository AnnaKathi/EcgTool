object fmFeatChoi: TfmFeatChoi
  Left = 0
  Top = 0
  Caption = 'Choi-Features bilden'
  ClientHeight = 675
  ClientWidth = 918
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
    Left = 119
    Top = 8
    Width = 489
    Height = 105
  end
  object laEcg1: TLabel
    Left = 119
    Top = 13
    Width = 31
    Height = 13
    Caption = 'laEcg1'
  end
  object btLoadEkg1: TButton
    Left = 8
    Top = 8
    Width = 105
    Height = 25
    Caption = 'EKG laden'
    TabOrder = 0
    OnClick = btLoadEkg1Click
  end
  object cbLead1: TComboBox
    Left = 8
    Top = 39
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
    Left = 8
    Top = 88
    Width = 105
    Height = 25
    Caption = 'Get Features'
    TabOrder = 2
    OnClick = btFeat1Click
  end
  object mFeat1: TMemo
    Left = 614
    Top = 8
    Width = 185
    Height = 105
    Lines.Strings = (
      'mFeat1')
    TabOrder = 3
  end
  object OpenDialog: TOpenDialog
    Left = 24
    Top = 144
  end
end
