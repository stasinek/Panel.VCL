object Muse_form: TMuse_form
  Left = 255
  Top = 178
  Width = 400
  Height = 300
  Align = alCustom
  BorderIcons = [biMaximize]
  BorderStyle = bsSizeToolWin
  Caption = 'DOT COUPLE OF WINDOWS'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  OnShow = FormShow
  DesignSize = (
    392
    273)
  PixelsPerInch = 96
  TextHeight = 13
  object Image1: TImage
    Left = 0
    Top = 0
    Width = 392
    Height = 273
    Align = alClient
    OnClick = Image1Click
    OnMouseMove = Image1MouseMove
  end
  object Button1: TButton
    Left = 344
    Top = 240
    Width = 43
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = '>>'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    OnClick = Button1Click
  end
end
