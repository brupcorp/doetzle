object Form1: TForm1
  Width = 1000
  Height = 600
  Caption = 'Dötzle sind Toll!'
  Color = 0
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  OnPaint = DrawIt
  OnResize = FormResize
  OnCreate = FormResize
  OnKeyDown = KeyD
  object Timer1: TTimer
    Interval = 10
    OnTimer = Physics
  end
end
