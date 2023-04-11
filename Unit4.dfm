object Uruchom: TUruchom
  Left = 239
  Top = 201
  BorderStyle = bsNone
  Caption = 'Uruchom'
  ClientHeight = 111
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
  object Ramka1: TRamka
    Width = 754
    Height = 126
    Align = alTop
    BorderKind = bRaised
    Color = clNone
    Caption = 'Ramka1'
    ControlStyle = [csCaptureMouse, csClickEvents, csFramed, csSetCaption, csDoubleClicks, csReplicatable]
    Parent = Owner
    ScalingFlags = [sfLeft, sfTop, sfWidth, sfHeight, sfFont]
  end
  object TabControl1: TTabControl
    Left = 0
    Top = 24
    Width = 754
    Height = 87
    Align = alBottom
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
