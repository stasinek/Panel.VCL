object Uruchom: TUruchom
  Left = 69
  Top = 131
  BorderStyle = bsNone
  Caption = 'Uruchom'
  ClientHeight = 90
  ClientWidth = 754
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = [fsBold]
  OldCreateOrder = False
  Position = poDesktopCenter
  PixelsPerInch = 96
  TextHeight = 13
  object TabControl1: TTabControl
    Left = 0
    Top = 0
    Width = 754
    Height = 90
    Align = alClient
    MultiLine = True
    RaggedRight = True
    ScrollOpposite = True
    TabOrder = 0
    TabPosition = tpBottom
    Tabs.Strings = (
      'AKCESORIA'
      'AUDIO'
      'VIDEO'
      'OFFICE'
      'INTERNET'
      '2D'
      '3D'
      'SYSTEM'
      'DEV')
    TabIndex = 0
    TabWidth = 80
  end
end
