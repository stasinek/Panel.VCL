object Alarm_form: TAlarm_form
  Left = 335
  Top = 179
  Width = 721
  Height = 471
  Caption = 'Alarm'
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 12
    Top = 84
    Width = 453
    Height = 305
    Shape = bsTopLine
  end
  object Label1: TLabel
    Left = 292
    Top = 16
    Width = 174
    Height = 52
    Caption = '12:00:01'
    Font.Charset = EASTEUROPE_CHARSET
    Font.Color = clWindowText
    Font.Height = -37
    Font.Name = 'Arial Black'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 16
    Top = 96
    Width = 256
    Height = 77
    Caption = '15:00:00'
    Font.Charset = EASTEUROPE_CHARSET
    Font.Color = clWindowText
    Font.Height = -64
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 284
    Top = 112
    Width = 181
    Height = 23
    Caption = 'Alarm dzis za 8h'
    Font.Charset = EASTEUROPE_CHARSET
    Font.Color = clGreen
    Font.Height = -19
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object SpeedButton1: TSpeedButton
    Left = 16
    Top = 192
    Width = 23
    Height = 22
    Caption = '1'
    Font.Charset = EASTEUROPE_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object SpeedButton2: TSpeedButton
    Left = 44
    Top = 192
    Width = 23
    Height = 22
    Caption = '2'
    Font.Charset = EASTEUROPE_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object SpeedButton3: TSpeedButton
    Left = 72
    Top = 192
    Width = 23
    Height = 22
    Caption = '3'
    Font.Charset = EASTEUROPE_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object SpeedButton4: TSpeedButton
    Left = 100
    Top = 192
    Width = 23
    Height = 22
    Caption = '4'
    Font.Charset = EASTEUROPE_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object SpeedButton5: TSpeedButton
    Left = 128
    Top = 192
    Width = 23
    Height = 22
    Caption = '5'
    Font.Charset = EASTEUROPE_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object SpeedButton6: TSpeedButton
    Left = 156
    Top = 192
    Width = 23
    Height = 22
    Caption = '6'
    Font.Charset = EASTEUROPE_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object SpeedButton7: TSpeedButton
    Left = 200
    Top = 192
    Width = 33
    Height = 22
    Caption = 'S'
    Font.Charset = EASTEUROPE_CHARSET
    Font.Color = clGreen
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object SpeedButton8: TSpeedButton
    Left = 236
    Top = 192
    Width = 33
    Height = 22
    Caption = 'S'
    Font.Charset = EASTEUROPE_CHARSET
    Font.Color = clRed
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object SpeedButton9: TSpeedButton
    Left = 388
    Top = 192
    Width = 77
    Height = 22
  end
  object CheckBox1: TCheckBox
    Left = 284
    Top = 160
    Width = 181
    Height = 17
    Caption = 'DRZEMKA'
    TabOrder = 0
  end
  object ComboBoxEx1: TComboBox
    Left = 388
    Top = 157
    Width = 77
    Height = 21
    ItemHeight = 13
    TabOrder = 1
    Text = '10 minut'
  end
  object StringGrid1: TStringGrid
    Left = 12
    Top = 256
    Width = 451
    Height = 128
    Color = clBtnFace
    ColCount = 8
    DefaultColWidth = 55
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goThumbTracking]
    ScrollBars = ssNone
    TabOrder = 2
  end
  object CheckListBox1: TCheckListBox
    Left = 484
    Top = 12
    Width = 213
    Height = 373
    ItemHeight = 13
    TabOrder = 3
  end
  object Button1: TButton
    Left = 536
    Top = 400
    Width = 75
    Height = 25
    Caption = 'OK'
    TabOrder = 4
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 620
    Top = 400
    Width = 75
    Height = 25
    Caption = 'Cancel'
    TabOrder = 5
    OnClick = Button2Click
  end
  object CheckBox2: TCheckBox
    Left = 16
    Top = 400
    Width = 445
    Height = 17
    Caption = 'AKTYWUJ WSZYSTKIE ALARMY'
    TabOrder = 6
  end
  object OpenDialog1: TOpenDialog
    Left = 16
    Top = 8
  end
end
