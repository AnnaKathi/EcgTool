object fmRequest: TfmRequest
  Left = 0
  Top = 0
  BorderStyle = bsToolWindow
  Caption = 'RequestBox'
  ClientHeight = 147
  ClientWidth = 343
  Color = clBtnHighlight
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
  DesignSize = (
    343
    147)
  PixelsPerInch = 96
  TextHeight = 13
  object mRequest: TMemo
    Left = 8
    Top = 8
    Width = 327
    Height = 41
    Anchors = [akLeft, akTop, akRight]
    BorderStyle = bsNone
    Lines.Strings = (
      'mRequest')
    TabOrder = 0
  end
  object edAnswer: TEdit
    Left = 8
    Top = 71
    Width = 327
    Height = 21
    TabOrder = 1
    Text = 'edAnswer'
    OnKeyPress = edAnswerKeyPress
  end
  object Panel1: TPanel
    Left = 0
    Top = 106
    Width = 343
    Height = 41
    Align = alBottom
    TabOrder = 2
    object btOk: TButton
      Left = 16
      Top = 8
      Width = 75
      Height = 25
      Caption = '&OK'
      TabOrder = 0
      OnClick = btOkClick
    end
    object btAbort: TButton
      Left = 256
      Top = 8
      Width = 75
      Height = 25
      Caption = '&Abbrechen'
      TabOrder = 1
      OnClick = btAbortClick
    end
  end
end
