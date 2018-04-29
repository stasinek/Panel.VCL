object Dni_form: TDni_form
  Left = 157
  Top = 146
  BorderStyle = bsDialog
  ClientHeight = 388
  ClientWidth = 560
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = True
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 337
    Width = 560
    Height = 51
    Align = alBottom
    BevelOuter = bvLowered
    TabOrder = 0
    object AdvancedBar1: TAdvancedBar
      Left = 16
      Top = 13
      Width = 221
      Height = 20
    end
    object Button1: TButton
      Left = 472
      Top = 12
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'OK'
      TabOrder = 0
      OnClick = Button1Click
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 560
    Height = 337
    Align = alClient
    BevelOuter = bvLowered
    Caption = 'Panel2'
    TabOrder = 1
    object BarGraph1: TBarGraph
      Left = 193
      Top = 1
      Width = 366
      Height = 335
      BorderKind = bNone
      BorderSize = bDouble
      Align = alClient
      Color = clGray
      GridColor = clGreen
      BarCount = 10
    end
    object ListBox1: TListBox
      Left = 1
      Top = 1
      Width = 192
      Height = 335
      Align = alLeft
      BorderStyle = bsNone
      ItemHeight = 13
      TabOrder = 0
    end
  end
  object Timer1: TTimer
    Left = 152
    Top = 16
  end
end
