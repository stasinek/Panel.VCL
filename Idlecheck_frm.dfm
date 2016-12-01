object Form7: TForm7
  Left = 192
  Top = 106
  Width = 373
  Height = 460
  Caption = 'Lista auto ubijania po czasie..'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 268
    Top = 390
    Width = 75
    Height = 25
    Caption = 'OK'
    TabOrder = 0
  end
  object ValueListEditor1: TValueListEditor
    Left = 14
    Top = 6
    Width = 331
    Height = 371
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRowSelect, goThumbTracking]
    TabOrder = 1
    TitleCaptions.Strings = (
      'Nazwa'
      'Op'#243#378'nienie (minut)')
    ColWidths = (
      207
      118)
  end
end
