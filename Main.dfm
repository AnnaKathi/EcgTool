object fmMain: TfmMain
  Left = 0
  Top = 0
  Caption = 'EcgTool: Main'
  ClientHeight = 305
  ClientWidth = 641
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
  object tStartup: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tStartupTimer
    Left = 8
    Top = 8
  end
end
