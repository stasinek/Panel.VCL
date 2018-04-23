object Dni_form: TDni_form
  Left = 527
  Top = 161
  BorderStyle = bsDialog
  ClientHeight = 216
  ClientWidth = 477
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  object BarGraph1: TBarGraph
    Left = 152
    Top = 0
    Width = 317
    Height = 173
    Color = clBlack
    GridColor = clGreen
  end
  object AdvancedBar1: TAdvancedBar
    Left = 152
    Top = 188
    Width = 221
    Height = 20
  end
  object ListBox1: TListBox
    Left = 8
    Top = 0
    Width = 137
    Height = 209
    ItemHeight = 13
    TabOrder = 0
  end
  object Button1: TButton
    Left = 392
    Top = 184
    Width = 75
    Height = 25
    Caption = 'OK'
    TabOrder = 1
    OnClick = Button1Click
  end
  object Timer1: TTimer
    Left = 152
    Top = 16
  end
end
