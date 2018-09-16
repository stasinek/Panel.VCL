object Lupa_form: TLupa_form
  Left = 353
  Top = 334
  BorderIcons = []
  BorderStyle = bsNone
  Caption = 'Magnifier...'
  ClientHeight = 330
  ClientWidth = 380
  Color = clBtnFace
  DefaultMonitor = dmMainForm
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = [fsBold]
  OldCreateOrder = True
  PrintScale = poNone
  Scaled = False
  WindowMenu = SubMenuZoom
  OnActivate = FormActivate
  OnCreate = FormCreate
  OnDblClick = MenuItemZwinClick
  OnDestroy = FormDestroy
  OnHide = FormHide
  OnMouseDown = FormMouseDown
  OnMouseMove = FormMouseMove
  OnMouseUp = FormMouseUp
  OnPaint = FormPaint
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object LupaPopupMenu: TPopupMenu
    OnPopup = LupaPopupMenuPopup
    Left = 28
    Top = 12
    object MenuItemZwin: TMenuItem
      Caption = 'Show'
      Default = True
      GroupIndex = 2
      OnClick = MenuItemZwinClick
    end
    object N5: TMenuItem
      Caption = '-'
      GroupIndex = 2
    end
    object SubMenuPrzeswit: TMenuItem
      Caption = 'Window transparency...'
      GroupIndex = 2
      OnClick = SubMenuPrzeswitClick
      object MenuItemTrans: TMenuItem
        Caption = 'Unclicable'
        GroupIndex = 3
        OnClick = MenuItemTransClick
      end
      object NOFF: TMenuItem
        Caption = 'OFF'
        Checked = True
        GroupIndex = 4
        RadioItem = True
        OnClick = NOFFClick
      end
      object N1: TMenuItem
        Caption = '-'
        GroupIndex = 4
      end
      object N101: TMenuItem
        Caption = '10%'
        GroupIndex = 4
        RadioItem = True
        OnClick = N101Click
      end
      object N201: TMenuItem
        Caption = '20%'
        GroupIndex = 4
        RadioItem = True
        OnClick = N201Click
      end
      object N301: TMenuItem
        Caption = '30%'
        GroupIndex = 4
        RadioItem = True
        OnClick = N301Click
      end
      object N401: TMenuItem
        Caption = '40%'
        GroupIndex = 4
        RadioItem = True
        OnClick = N401Click
      end
      object N501: TMenuItem
        Caption = '50%'
        GroupIndex = 4
        RadioItem = True
        OnClick = N501Click
      end
      object N601: TMenuItem
        Caption = '60%'
        GroupIndex = 4
        RadioItem = True
        OnClick = N601Click
      end
      object N701: TMenuItem
        Caption = '70%'
        GroupIndex = 4
        RadioItem = True
        OnClick = N701Click
      end
      object N801: TMenuItem
        Caption = '80%'
        GroupIndex = 4
        RadioItem = True
        OnClick = N801Click
      end
    end
    object N6: TMenuItem
      Caption = '-'
      GroupIndex = 2
    end
    object SubMenuSize: TMenuItem
      Caption = 'Window size...'
      GroupIndex = 2
      OnClick = SubMenuSizeClick
      object MenuItemSizeAdvanced: TMenuItem
        Caption = 'Custom'
        GroupIndex = 2
        RadioItem = True
        OnClick = MenuItemSizeAdvancedClick
      end
      object N3: TMenuItem
        Caption = '-'
        GroupIndex = 2
      end
      object MenuItemSize180120: TMenuItem
        Caption = '180x120'
        Checked = True
        GroupIndex = 2
        RadioItem = True
        OnClick = MenuItemSize180120Click
      end
      object MenuItemSize240180: TMenuItem
        Caption = '240x180'
        GroupIndex = 2
        RadioItem = True
        OnClick = MenuItemSize240180Click
      end
      object MenuItemSize320240: TMenuItem
        Caption = '320x240'
        GroupIndex = 2
        RadioItem = True
        OnClick = MenuItemSize320240Click
      end
      object MenuItemSize384288: TMenuItem
        Caption = '384x288'
        GroupIndex = 2
        RadioItem = True
        OnClick = MenuItemSize384288Click
      end
      object MenuItemSize512384: TMenuItem
        Caption = '512x384'
        GroupIndex = 2
        RadioItem = True
        OnClick = MenuItemSize512384Click
      end
    end
    object SubMenuZoom: TMenuItem
      Caption = 'Zoom...'
      GroupIndex = 2
      OnClick = SubMenuZoomClick
      object MenuItemZoomAdvanced: TMenuItem
        Caption = 'Custom'
        GroupIndex = 1
        RadioItem = True
        OnClick = MenuItemZoomAdvancedClick
      end
      object N4: TMenuItem
        Caption = '-'
        GroupIndex = 1
      end
      object MenuItemZoom02: TMenuItem
        Caption = 'x2'
        Checked = True
        GroupIndex = 1
        RadioItem = True
        OnClick = MenuItemZoom02Click
      end
      object MenuItemZoom03: TMenuItem
        Caption = 'x3'
        GroupIndex = 1
        RadioItem = True
        OnClick = MenuItemZoom03Click
      end
      object MenuItemZoom04: TMenuItem
        Caption = 'x4'
        GroupIndex = 1
        RadioItem = True
        OnClick = MenuItemZoom04Click
      end
      object MenuItemZoom06: TMenuItem
        Caption = 'x6'
        GroupIndex = 1
        RadioItem = True
        OnClick = MenuItemZoom06Click
      end
      object MenuItemZoom08: TMenuItem
        Caption = 'x8'
        GroupIndex = 1
        RadioItem = True
        OnClick = MenuItemZoom08Click
      end
    end
    object N2: TMenuItem
      Caption = '-'
      GroupIndex = 2
    end
    object MenuItemCelownik: TMenuItem
      Caption = 'Show cross at cursor point'
      Checked = True
      GroupIndex = 2
      OnClick = MenuItemCelownikClick
    end
    object Na1: TMenuItem
      Caption = 'Move window to center of the screen'
      GroupIndex = 2
      OnClick = Na1Click
    end
    object Natopie1: TMenuItem
      Caption = 'Always keep on top'
      GroupIndex = 2
      OnClick = Natopie1Click
    end
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 30
    OnTimer = Timer1Timer
    Left = 28
    Top = 61
  end
end
