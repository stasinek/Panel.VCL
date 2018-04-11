object Form6: TForm6
  Left = 684
  Top = 162
  Width = 339
  Height = 188
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  object Label2: TLabel
    Left = 36
    Top = 14
    Width = 103
    Height = 16
    Caption = '.\PROGRAM.exe'
    Font.Charset = EASTEUROPE_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object UpDown1: TUpDown
    Left = 106
    Top = 52
    Width = 43
    Height = 57
    Min = 0
    Position = 0
    TabOrder = 0
    Wrap = False
  end
  object UpDown2: TUpDown
    Left = 274
    Top = 52
    Width = 41
    Height = 57
    Min = 0
    Position = 0
    TabOrder = 1
    Wrap = False
  end
  object Edit1: TEdit
    Left = 34
    Top = 52
    Width = 67
    Height = 62
    Font.Charset = EASTEUROPE_CHARSET
    Font.Color = clWindowText
    Font.Height = -48
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    Text = '00'
  end
  object Edit2: TEdit
    Left = 198
    Top = 52
    Width = 69
    Height = 62
    Font.Charset = EASTEUROPE_CHARSET
    Font.Color = clWindowText
    Font.Height = -48
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 3
    Text = '00'
  end
  object Button1: TButton
    Left = 228
    Top = 126
    Width = 89
    Height = 25
    Caption = 'OK'
    TabOrder = 4
  end
  object Button2: TButton
    Left = 134
    Top = 126
    Width = 87
    Height = 25
    Caption = 'Never mind..'
    TabOrder = 5
    OnClick = Button2Click
  end
end
