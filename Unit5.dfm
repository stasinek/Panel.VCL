object Alarm_form: TAlarm_form
  Left = 157
  Top = 112
  Width = 718
  Height = 489
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
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 710
    Height = 408
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 1
    object Label2: TLabel
      Left = 16
      Top = 8
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
      Left = 304
      Top = 48
      Width = 157
      Height = 23
      Caption = 'Alarm dzis za 8h'
      Font.Charset = EASTEUROPE_CHARSET
      Font.Color = clGreen
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton9: TSpeedButton
      Left = 208
      Top = 104
      Width = 61
      Height = 22
    end
    object SpeedButton8: TSpeedButton
      Left = 180
      Top = 104
      Width = 21
      Height = 22
      Caption = 'S'
      Font.Charset = EASTEUROPE_CHARSET
      Font.Color = clRed
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object SpeedButton7: TSpeedButton
      Left = 156
      Top = 104
      Width = 21
      Height = 22
      Caption = 'S'
      Font.Charset = EASTEUROPE_CHARSET
      Font.Color = clGreen
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object SpeedButton5: TSpeedButton
      Left = 128
      Top = 104
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
    object SpeedButton4: TSpeedButton
      Left = 100
      Top = 104
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
    object SpeedButton3: TSpeedButton
      Left = 72
      Top = 104
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
    object SpeedButton2: TSpeedButton
      Left = 44
      Top = 104
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
    object SpeedButton1: TSpeedButton
      Left = 16
      Top = 104
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
    object CheckBox1: TCheckBox
      Left = 292
      Top = 108
      Width = 181
      Height = 17
      Caption = 'DRZEMKA'
      TabOrder = 0
    end
    object ComboBoxEx1: TComboBox
      Left = 388
      Top = 105
      Width = 77
      Height = 21
      ItemHeight = 13
      TabOrder = 1
      Text = '10 minut'
    end
    object StringGrid1: TStringGrid
      Left = 16
      Top = 140
      Width = 451
      Height = 205
      BorderStyle = bsNone
      Color = clBtnFace
      ColCount = 8
      DefaultColWidth = 55
      RowCount = 8
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goThumbTracking]
      ScrollBars = ssNone
      TabOrder = 2
    end
    object CheckBox2: TCheckBox
      Left = 16
      Top = 364
      Width = 445
      Height = 17
      Caption = 'AKTYWUJ WSZYSTKIE ALARMY'
      TabOrder = 3
    end
    object CheckListBox1: TCheckListBox
      Left = 484
      Top = 0
      Width = 226
      Height = 408
      Align = alRight
      Anchors = [akLeft, akTop, akRight, akBottom]
      ItemHeight = 13
      TabOrder = 4
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 408
    Width = 710
    Height = 54
    Align = alBottom
    Anchors = [akLeft, akTop, akRight, akBottom]
    BevelOuter = bvLowered
    TabOrder = 0
    object Label1: TLabel
      Left = 18
      Top = 6
      Width = 148
      Height = 45
      Alignment = taRightJustify
      Caption = '12:00:01'
      Font.Charset = EASTEUROPE_CHARSET
      Font.Color = clWindowText
      Font.Height = -32
      Font.Name = 'Arial Black'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Button1: TButton
      Left = 543
      Top = 16
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'OK'
      TabOrder = 0
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 625
      Top = 16
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Cancel'
      TabOrder = 1
      OnClick = Button2Click
    end
  end
  object OpenDialog1: TOpenDialog
    Left = 16
    Top = 8
  end
end
