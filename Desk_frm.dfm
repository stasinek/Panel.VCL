object Desk_form: TDesk_form
  Left = 163
  Top = 36
  BorderIcons = [biSystemMenu, biMaximize]
  BorderStyle = bsDialog
  Caption = 'Biurka...'
  ClientHeight = 422
  ClientWidth = 552
  Color = clBtnFace
  Constraints.MinHeight = 20
  Constraints.MinWidth = 20
  DefaultMonitor = dmMainForm
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = True
  Position = poDefault
  PrintScale = poNone
  Scaled = False
  WindowMenu = SubMenuOkna
  OnActivate = FormActivate
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnHide = FormHide
  OnKeyDown = FormKeyDown
  OnMouseDown = FormMouseDown
  OnMouseMove = FormMouseMove
  OnMouseUp = FormMouseUp
  OnPaint = FormPaint
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object DeskPopupMenu: TPopupMenu
    Left = 28
    Top = 64
    object MenuItemZwin: TMenuItem
      Caption = 'Show'
      Default = True
      GroupIndex = 2
      OnClick = MenuItemZwinClick
    end
    object N8: TMenuItem
      Caption = '-'
      GroupIndex = 2
    end
    object SubMenuSize: TMenuItem
      Caption = 'Window size...'
      GroupIndex = 3
      OnClick = SubMenuSizeClick
      object MenuItemSizeAdvanced: TMenuItem
        Caption = 'Custom'
        GroupIndex = 1
        RadioItem = True
        OnClick = MenuItemSizeAdvancedClick
      end
      object N4: TMenuItem
        Caption = '-'
        GroupIndex = 1
      end
      object MenuItemSize32: TMenuItem
        Caption = '48x16'
        GroupIndex = 1
        RadioItem = True
        OnClick = MenuItemSize32Click
      end
      object MenuItemSize48: TMenuItem
        Caption = '72x24'
        Checked = True
        GroupIndex = 1
        RadioItem = True
        OnClick = MenuItemSize48Click
      end
      object MenuItemSize64: TMenuItem
        Caption = '96x32'
        GroupIndex = 1
        RadioItem = True
        OnClick = MenuItemSize64Click
      end
      object MenuItemSize96: TMenuItem
        Caption = '142x48'
        GroupIndex = 1
        RadioItem = True
        OnClick = MenuItemSize96Click
      end
      object MenuItemSize144: TMenuItem
        Break = mbBreak
        Caption = '282x96'
        GroupIndex = 1
        RadioItem = True
        OnClick = MenuItemSize144Click
      end
      object MenuItemSize192: TMenuItem
        Caption = '420x160'
        GroupIndex = 1
        RadioItem = True
        OnClick = MenuItemSize192Click
      end
      object MenuItemSize256: TMenuItem
        Caption = '720x240'
        GroupIndex = 1
        RadioItem = True
        OnClick = MenuItemSize256Click
      end
      object MenuItemSize384: TMenuItem
        Caption = '1002x334'
        GroupIndex = 1
        RadioItem = True
        OnClick = MenuItemSize384Click
      end
    end
    object SubMenuPrzeswit: TMenuItem
      Caption = 'Window transparency...'
      GroupIndex = 3
      OnClick = SubMenuPrzeswitClick
      object MenuItemTrans: TMenuItem
        Caption = 'Unclickable'
        GroupIndex = 2
        OnClick = MenuItemTransClick
      end
      object NOFF: TMenuItem
        Caption = 'OFF'
        Checked = True
        GroupIndex = 2
        RadioItem = True
        OnClick = NOFFClick
      end
      object N1: TMenuItem
        Caption = '-'
        GroupIndex = 2
      end
      object N101: TMenuItem
        Caption = '10%'
        GroupIndex = 2
        RadioItem = True
        OnClick = N101Click
      end
      object N201: TMenuItem
        Caption = '20%'
        GroupIndex = 2
        RadioItem = True
        OnClick = N201Click
      end
      object N301: TMenuItem
        Caption = '30%'
        GroupIndex = 2
        RadioItem = True
        OnClick = N301Click
      end
      object N401: TMenuItem
        Caption = '40%'
        GroupIndex = 2
        RadioItem = True
        OnClick = N401Click
      end
      object N501: TMenuItem
        Caption = '50%'
        GroupIndex = 2
        RadioItem = True
        OnClick = N501Click
      end
      object N601: TMenuItem
        Caption = '60%'
        GroupIndex = 2
        RadioItem = True
        OnClick = N601Click
      end
      object N701: TMenuItem
        Caption = '70%'
        GroupIndex = 2
        RadioItem = True
        OnClick = N701Click
      end
      object N801: TMenuItem
        Caption = '80%'
        GroupIndex = 2
        RadioItem = True
        OnClick = N801Click
      end
    end
    object MenuItemTop: TMenuItem
      Caption = 'Keep window always on top'
      GroupIndex = 3
      OnClick = MenuItemTopClick
    end
    object N3: TMenuItem
      Caption = '-'
      GroupIndex = 3
    end
    object SubMenuOkna: TMenuItem
      Caption = 'Active windows..'
      GroupIndex = 3
      OnClick = SubMenuOknaClick
      object MenuItemZbierz: TMenuItem
        Caption = 'Move all windows here'
        OnClick = MenuItemZbierzClick
      end
      object MenuItemPrzenies: TMenuItem
        Caption = 'Move to...'
        Hint = 'Przenosi okna na...'
        OnClick = MenuItemBiurko1Click
      end
      object MenuItemBiurko1: TMenuItem
        Caption = 'Desk 1'
        Hint = 'Przenosi okna na...'
      end
      object MenuItemBiurko2: TMenuItem
        Caption = 'Desk 2'
        Hint = 'Przenosi okna na...'
        OnClick = MenuItemBiurko2Click
      end
      object MenuItemBiurko3: TMenuItem
        Caption = 'Desk 3'
        Hint = 'Przenosi okna na...'
        OnClick = MenuItemBiurko3Click
      end
      object MenuItemBiurko4: TMenuItem
        Caption = 'Desk 4'
        Hint = 'Przenosi okna na...'
        OnClick = MenuItemBiurko4Click
      end
      object MenuItemBiurko0: TMenuItem
        Caption = 'Shared desk'
        Hint = 'Przenosi okna na...'
      end
    end
  end
  object Timer1: TTimer
    Left = 248
    Top = 48
  end
end
