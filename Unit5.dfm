object Form5: TForm5
  Left = 160
  Top = 97
  Width = 714
  Height = 471
  Caption = 'Alarm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 16
    Top = 28
    Width = 448
    Height = 136
    Caption = '12:00:01'
    Font.Charset = EASTEUROPE_CHARSET
    Font.Color = clWindowText
    Font.Height = -96
    Font.Name = 'Arial Black'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 16
    Top = 172
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
    Left = 280
    Top = 228
    Width = 106
    Height = 16
    Caption = 'Alarm dzi'#347' za 8h'
    Font.Charset = EASTEUROPE_CHARSET
    Font.Color = clGreen
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object CheckBox1: TCheckBox
    Left = 280
    Top = 172
    Width = 181
    Height = 17
    Caption = 'DRZEMKA'
    TabOrder = 0
  end
  object ComboBoxEx1: TComboBoxEx
    Left = 388
    Top = 169
    Width = 77
    Height = 22
    ItemsEx.CaseSensitive = False
    ItemsEx.SortType = stNone
    ItemsEx = <
      item
        Caption = '10 minut'
      end
      item
        Caption = '20 minut'
      end
      item
        Caption = '30 minut'
      end
      item
        Caption = '60 minut'
      end
      item
        Caption = '90 minut'
      end>
    StyleEx = []
    ItemHeight = 16
    TabOrder = 1
    Text = '10 minut'
    DropDownCount = 8
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
    Left = 468
    Top = 24
    Width = 229
    Height = 361
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
  end
  object Button2: TButton
    Left = 620
    Top = 400
    Width = 75
    Height = 25
    Caption = 'Cancel'
    TabOrder = 5
  end
  object CheckBox2: TCheckBox
    Left = 16
    Top = 400
    Width = 497
    Height = 17
    Caption = 'AKTYWUJ WSZYSTKIE ALARMY'
    TabOrder = 6
  end
  object OpenDialog1: TOpenDialog
    Left = 16
    Top = 8
  end
end
