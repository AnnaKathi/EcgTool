object fmWavelet: TfmWavelet
  Left = 0
  Top = 0
  Caption = 'Wavelet-Features'
  ClientHeight = 702
  ClientWidth = 706
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
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 0
    Top = 657
    Width = 706
    Height = 4
    Align = alBottom
    Shape = bsBottomLine
    ExplicitLeft = 128
    ExplicitTop = 608
    ExplicitWidth = 50
  end
  object mInfo: TMemo
    Left = 159
    Top = 0
    Width = 547
    Height = 657
    Align = alRight
    ScrollBars = ssBoth
    TabOrder = 0
    ExplicitTop = 8
    ExplicitHeight = 545
  end
  object btPrint1: TButton
    Left = 8
    Top = 16
    Width = 145
    Height = 25
    Caption = 'Print WaveObjekt-Summary'
    TabOrder = 1
    OnClick = btPrint1Click
  end
  object btPrint2: TButton
    Left = 8
    Top = 47
    Width = 145
    Height = 25
    Caption = 'Print WaveTrans-Summary'
    TabOrder = 2
    OnClick = btPrint2Click
  end
  object btDwt: TButton
    Left = 8
    Top = 112
    Width = 145
    Height = 25
    Caption = 'Do DWT'
    TabOrder = 3
    OnClick = btDwtClick
  end
  object pnBottom: TPanel
    Left = 0
    Top = 661
    Width = 706
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 4
    ExplicitLeft = 192
    ExplicitTop = 608
    ExplicitWidth = 185
    object pbProgress: TProgressBar
      Left = 8
      Top = 6
      Width = 689
      Height = 27
      TabOrder = 0
      Visible = False
    end
  end
end
