object Clock_form: TClock_form
  Left = 516
  Top = 310
  BorderStyle = bsDialog
  Caption = 'Clock'
  ClientHeight = 240
  ClientWidth = 398
  Color = clBtnFace
  Constraints.MinHeight = 240
  Constraints.MinWidth = 320
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 313
    Height = 77
    Align = alClient
    BevelOuter = bvLowered
    Caption = '12:10:00'
    Font.Charset = EASTEUROPE_CHARSET
    Font.Color = clWindowText
    Font.Height = -64
    Font.Name = 'Arial Black'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
  end
  object Panel2: TPanel
    Left = 0
    Top = 77
    Width = 398
    Height = 163
    Align = alBottom
    BevelOuter = bvLowered
    TabOrder = 1
    object CCalendar1: TCCalendar
      Left = 12
      Top = 12
      Width = 375
      Height = 137
      TabStop = True
      Anchors = [akLeft, akTop, akRight, akBottom]
      Font.Charset = EASTEUROPE_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      TabOrder = 0
    end
  end
  object Panel3: TPanel
    Left = 313
    Top = 0
    Width = 85
    Height = 77
    Align = alRight
    BevelOuter = bvLowered
    TabOrder = 2
    object SpeedButton1: TSpeedButton
      Left = 8
      Top = 8
      Width = 69
      Height = 25
      AllowAllUp = True
      OnClick = SpeedButton1Click
    end
    object SpeedButton2: TSpeedButton
      Left = 8
      Top = 40
      Width = 69
      Height = 25
      AllowAllUp = True
      OnClick = SpeedButton2Click
    end
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 12
    Top = 8
  end
end
