object Zeus_form: TZeus_form
  Left = 229
  Top = 135
  BorderIcons = []
  BorderStyle = bsSingle
  Caption = 'ZEUS'
  ClientHeight = 416
  ClientWidth = 504
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDefault
  Scaled = False
  OnActivate = FormActivate
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnHide = FormHide
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Image2: TImage
    Left = 0
    Top = 152
    Width = 505
    Height = 241
    OnClick = Image2Click
    OnMouseMove = Image2MouseMove
  end
  object SpeedButton1: TSpeedButton
    Left = 376
    Top = 356
    Width = 89
    Height = 25
    Caption = 'UBIJ!'
    Font.Charset = EASTEUROPE_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    OnClick = SpeedButton1Click
  end
  object BitBtn1: TBitBtn
    Left = 472
    Top = 356
    Width = 25
    Height = 25
    Caption = 'X'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    OnClick = BitBtn1Click
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 397
    Width = 504
    Height = 19
    Panels = <>
    SimplePanel = False
  end
  object CheckListBox1: TCheckListBox
    Left = 0
    Top = 24
    Width = 505
    Height = 129
    ItemHeight = 13
    Items.Strings = (
      '1'
      '2'
      '3'
      '4'
      '5'
      '6'
      '7'
      '8'
      '9')
    TabOrder = 2
  end
  object HeaderControl1: THeaderControl
    Left = 0
    Top = 0
    Width = 504
    Height = 17
    DragReorder = False
    Sections = <
      item
        AutoSize = True
        ImageIndex = -1
        Text = 'Proces'
        Width = 354
      end
      item
        ImageIndex = -1
        Text = 'Okno'
        Width = 100
      end
      item
        ImageIndex = -1
        Text = 'Biurko'
        Width = 50
      end>
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 200
    Left = 4
    Top = 356
  end
  object MainMenu1: TMainMenu
    Left = 32
    Top = 356
    object Window1: TMenuItem
      Caption = '&Okna'
      OnClick = Window1Click
      object Kill1: TMenuItem
        Caption = 'Jestem bogiem!'
        ShortCut = 49242
        OnClick = Kill1Click
      end
      object N3: TMenuItem
        Caption = '-'
      end
      object Cascade1: TMenuItem
        Caption = 'Cascade all Windows'
        OnClick = Cascade1Click
      end
      object Tile2: TMenuItem
        Caption = 'Tile all Windows Horizontally'
        OnClick = Tile2Click
      end
      object Tile1: TMenuItem
        Caption = 'Tile all Windows Vertically'
        OnClick = Tile1Click
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Hide1: TMenuItem
        Caption = '&Hide'
        Enabled = False
      end
    end
    object N2: TMenuItem
      Caption = '&?'
      OnClick = N2Click
    end
  end
end
