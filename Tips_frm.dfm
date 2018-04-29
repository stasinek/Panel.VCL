object Tips_form: TTips_form
  Left = 179
  Top = 131
  BorderIcons = []
  BorderStyle = bsNone
  Caption = 'Progress...'
  ClientHeight = 32
  ClientWidth = 254
  Color = clInfoBk
  DefaultMonitor = dmMainForm
  Enabled = False
  Font.Charset = EASTEUROPE_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'Trebuchet MS'
  Font.Style = [fsBold]
  OldCreateOrder = True
  Position = poDefault
  PrintScale = poNone
  Scaled = False
  OnActivate = FormActivate
  OnClick = Ramka1Click
  OnDblClick = Ramka1Click
  OnHide = FormHide
  OnPaint = FormPaint
  PixelsPerInch = 96
  TextHeight = 22
  object Ramka1: TRamka
    Width = 254
    Height = 32
    Align = alClient
    BorderKind = bRect
    Color = clNone
    OnMouseDown = Ramka1MouseDown
    OnClick = Ramka1Click
    OnDblClick = Ramka1Click
    Caption = 'Ramka1'
    ControlStyle = [csCaptureMouse, csClickEvents, csFramed, csSetCaption, csDoubleClicks, csReplicatable]
    Parent = Owner
  end
end
