object Zoom_form: TZoom_form
  Left = 393
  Top = 355
  BorderStyle = bsDialog
  Caption = 'Advanced: Zoom...'
  ClientHeight = 106
  ClientWidth = 306
  Color = clBtnFace
  DefaultMonitor = dmDesktop
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = True
  Position = poDefault
  PrintScale = poNone
  Scaled = False
  OnActivate = FormActivate
  OnHide = FormHide
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object OKBtn: TButton
    Left = 147
    Top = 76
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 0
  end
  object CancelBtn: TButton
    Left = 227
    Top = 76
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 1
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 294
    Height = 58
    Caption = '2 : 1'
    TabOrder = 2
    object TrackBar1: TTrackBar
      Left = 6
      Top = 16
      Width = 282
      Height = 32
      Max = 8
      Min = 1
      Orientation = trHorizontal
      PageSize = 1
      Frequency = 1
      Position = 1
      SelEnd = 0
      SelStart = 0
      TabOrder = 0
      ThumbLength = 16
      TickMarks = tmBoth
      TickStyle = tsAuto
      OnChange = TrackBar1Change
    end
  end
end
