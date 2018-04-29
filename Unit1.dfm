object Form1: TForm1
  Left = 96
  Top = 122
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsDialog
  Caption = 'Zmiana parametrów ekranu.'
  ClientHeight = 243
  ClientWidth = 438
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnPaint = FormPaint
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 438
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    FullRepaint = False
    TabOrder = 0
    object SpeedButton1: TSpeedButton
      Left = 358
      Top = 4
      Width = 29
      Height = 29
      Hint = 'Zwin/rozwin okno.'
      AllowAllUp = True
      Font.Charset = EASTEUROPE_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      Glyph.Data = {
        16050000424D160500000000000036040000280000000F0000000E0000000100
        080000000000E000000000000000000000000001000000000000000000000000
        BF0000BF000000BFBF00BF000000BF00BF00BFBF0000C0C0C000C0DCC000F0CA
        A600000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        000000000000000000000000000000000000F0FBFF00A4A0A000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00030303030303
        0303030303030303030003030303030303030303030303030300030303030303
        0303030303030303030003030303030300000003030303030300030303030300
        00FF0000030303030300030303030000FFFFFF000003030303000303030000FF
        FFFFFFFF00000303030003030000FFFFFFFFFFFFFF0000030300030000FFFFFF
        FFFFFFFFFFFF000003000000FFFFFFFFFFFFFFFFFFFFFF000000000000000000
        0000000000000000000003030303030303030303030303030300030303030303
        0303030303030303030003030303030303030303030303030300}
      ParentFont = False
      Transparent = False
      OnClick = SpeedButton1Click
    end
    object Label2: TLabel
      Left = 294
      Top = 12
      Width = 14
      Height = 13
      Caption = 'Hz'
      Font.Charset = EASTEUROPE_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton2: TSpeedButton
      Left = 391
      Top = 4
      Width = 31
      Height = 29
      Hint = 'USTAW'
      Anchors = [akTop, akRight]
      Glyph.Data = {
        06020000424D0602000000000000760000002800000028000000140000000100
        0400000000009001000000000000000000001000000000000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4FFFFFFFFFFFFFFFFFF7FFFFFFF
        FFFFFFFFFFFFF44FFFFFFFFFFFFFFFFF77FFFFFFFFFFFFFFFFFFF444FFFFFFFF
        FFFFFFFF777FFFFFFFFFFFFFFFF4F4444FFFFFFFFFFFFF7F7777FFFFFFFFFFFF
        FFF4F44444FFFFFFFFFFFF7F77777FFFFFFFFFFFF4F4F444444FFFFFFFFF7F7F
        777777FFFFFFF4F4F4F4F4444444FFFF7F7F7F7F7777777FFFFFF4F4F4F4F444
        44444FFF7F7F7F7F77777777FFFFF4F4F4F4F444444444FF7F7F7F7F77777777
        7FFFF4F4F4F4F444444444FF7F7F7F7F777777777FFFF4F4F4F4F44444444FFF
        7F7F7F7F77777777FFFFFFFFF4F4F4444444FFFFFFFF7F7F7777777FFFFFFFFF
        FFF4F444444FFFFFFFFFFF7F777777FFFFFFFFFFFFF4F44444FFFFFFFFFFFF7F
        77777FFFFFFFFFFFFFFFF4444FFFFFFFFFFFFFFF7777FFFFFFFFFFFFFFFFF444
        FFFFFFFFFFFFFFFF777FFFFFFFFFFFFFFFFFF44FFFFFFFFFFFFFFFFF77FFFFFF
        FFFFFFFFFFFFF4FFFFFFFFFFFFFFFFFF7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFF}
      NumGlyphs = 2
      OnClick = SpeedButton2Click
    end
    object SpeedButton3: TSpeedButton
      Left = 325
      Top = 4
      Width = 29
      Height = 29
      Hint = 'POMOC'
      Anchors = [akTop, akRight]
      Caption = '?'
      Font.Charset = EASTEUROPE_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      OnClick = SpeedButton3Click
    end
    object ComboBox4: TComboBox
      Left = 237
      Top = 8
      Width = 52
      Height = 21
      Hint = 'Hz'
      Font.Charset = EASTEUROPE_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ItemHeight = 13
      ParentFont = False
      TabOrder = 0
      Text = '60'
      Items.Strings = (
        '50'
        '60'
        '65'
        '70'
        '75'
        '80'
        '85'
        '90'
        '100'
        '110'
        '120'
        '144'
        '160')
    end
    object ComboBox3: TComboBox
      Left = 185
      Top = 8
      Width = 44
      Height = 21
      Hint = '8,16,24,32 bit'
      Font.Charset = EASTEUROPE_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ItemHeight = 13
      ParentFont = False
      TabOrder = 1
      Text = '32'
      Items.Strings = (
        '8'
        '16'
        '24'
        '32')
    end
    object ComboBox1: TComboBox
      Left = 76
      Top = 8
      Width = 97
      Height = 21
      Hint = 'X*Y pixeli'
      Font.Charset = EASTEUROPE_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ItemHeight = 13
      ParentFont = False
      TabOrder = 2
      Text = '1024x768'
      Items.Strings = (
        '320x200'
        '320x240'
        '400x300'
        '512x384'
        '600x800'
        '640x400'
        '640x480'
        '720x480'
        '720x576'
        '768x1024'
        '800x600'
        '800x800'
        '960x540'
        '960x720'
        '1024x576'
        '1024x768'
        '1024x1024'
        '1152x864'
        '1280x768'
        '1280x800'
        '1280x960'
        '1280x1024'
        '1280x1080'
        '1440x900'
        '1440x960'
        '1440x1024'
        '1440x1080'
        '1600x1024'
        '1600x1200'
        '1600x900'
        '1920x1080'
        '2048x1556'
        '2560x1080'
        '2560x1440'
        '2560x1600'
        '2560x1920'
        '2880x1800'
        '3200x1800'
        '3200x2400'
        '3656x2664'
        '4096x2304'
        '4096x3112')
    end
    object ComboBox2: TComboBox
      Left = 20
      Top = 8
      Width = 41
      Height = 21
      Hint = 'Monitor nr.'
      ItemHeight = 13
      TabOrder = 3
      Text = '1'
      OnChange = ComboBox2Change
      Items.Strings = (
        '1'
        '2'
        '3')
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 41
    Width = 438
    Height = 202
    Align = alClient
    BevelInner = bvRaised
    BevelOuter = bvLowered
    FullRepaint = False
    TabOrder = 1
    object Image1: TImage
      Left = 16
      Top = 18
      Width = 406
      Height = 137
      Anchors = [akLeft, akTop, akRight, akBottom]
    end
    object SpeedButton4: TSpeedButton
      Left = 16
      Top = 16
      Width = 65
      Height = 29
      Hint = 'Pokaz liste'
      Caption = 'LISTA'
      Enabled = False
    end
    object Button2: TButton
      Left = 285
      Top = 166
      Width = 67
      Height = 27
      Hint = 'NIZSZA'
      Anchors = [akRight, akBottom]
      Caption = '<'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      OnClick = Button2Click
    end
    object Button3: TButton
      Left = 357
      Top = 166
      Width = 67
      Height = 27
      Hint = 'WYZSZA'
      Anchors = [akRight, akBottom]
      Caption = '>'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      OnClick = Button3Click
    end
  end
end
