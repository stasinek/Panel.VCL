object Clock_form: TClock_form
  Left = 678
  Top = 235
  BorderStyle = bsToolWindow
  Caption = 'Clock_form'
  ClientHeight = 138
  ClientWidth = 270
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 270
    Height = 89
    Align = alTop
    BevelOuter = bvNone
    Caption = '12:10'
    Font.Charset = EASTEUROPE_CHARSET
    Font.Color = clWindowText
    Font.Height = -64
    Font.Name = 'Arial Black'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
  end
  object Panel2: TPanel
    Left = 0
    Top = 90
    Width = 270
    Height = 48
    Align = alBottom
    TabOrder = 1
  end
  object Timer1: TTimer
    Left = 4
    Top = 4
  end
end
