object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Mouse In Maze by'#29579#26144#32092'20191022 ver0.1'
  ClientHeight = 617
  ClientWidth = 683
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 185
    Height = 617
    Align = alLeft
    TabOrder = 0
    object Label3: TLabel
      Left = 15
      Top = 27
      Width = 37
      Height = 13
      Caption = 'Gridsize'
    end
    object Button2: TButton
      Left = 45
      Top = 168
      Width = 100
      Height = 31
      Caption = 'Generate Maze'
      TabOrder = 0
      OnClick = Button2Click
    end
    object GroupBox1: TGroupBox
      Left = -2
      Top = 57
      Width = 185
      Height = 105
      Caption = 'Size'
      TabOrder = 1
      object Label1: TLabel
        Left = 22
        Top = 24
        Width = 30
        Height = 13
        Caption = 'height'
      end
      object Label2: TLabel
        Left = 22
        Top = 65
        Width = 26
        Height = 13
        Caption = 'width'
      end
      object Edit1: TEdit
        Left = 62
        Top = 21
        Width = 121
        Height = 21
        TabOrder = 0
        Text = '13'
      end
      object Edit2: TEdit
        Left = 61
        Top = 62
        Width = 121
        Height = 21
        TabOrder = 1
        Text = '13'
      end
    end
    object Button3: TButton
      Left = 58
      Top = 244
      Width = 76
      Height = 29
      Caption = 'Save Map'
      TabOrder = 2
      OnClick = Button3Click
    end
    object Button4: TButton
      Left = 45
      Top = 366
      Width = 116
      Height = 35
      Caption = 'Find The Tour'
      TabOrder = 3
      OnClick = Button4Click
    end
    object Button5: TButton
      Left = 27
      Top = 205
      Width = 129
      Height = 33
      Caption = 'load map'
      TabOrder = 4
      OnClick = Button5Click
    end
    object Button6: TButton
      Left = 27
      Top = 335
      Width = 138
      Height = 25
      Caption = 'show map in stringgrids'
      TabOrder = 5
      OnClick = Button6Click
    end
    object Edit3: TEdit
      Left = 58
      Top = 24
      Width = 121
      Height = 21
      TabOrder = 6
      Text = '40'
    end
    object Button7: TButton
      Left = 70
      Top = 563
      Width = 75
      Height = 25
      Caption = 'clear'
      TabOrder = 7
      OnClick = Button7Click
    end
    object CheckBox1: TCheckBox
      Left = 64
      Top = 448
      Width = 97
      Height = 17
      Caption = 'double buffer'
      TabOrder = 8
    end
  end
  object TrackBar1: TTrackBar
    Left = 15
    Top = 480
    Width = 150
    Height = 45
    Max = 30
    TabOrder = 1
  end
  object PageControl1: TPageControl
    Left = 185
    Top = 0
    Width = 498
    Height = 617
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 2
    object TabSheet1: TTabSheet
      Caption = 'Memo'
      object Memo1: TMemo
        Left = 0
        Top = 0
        Width = 490
        Height = 589
        Align = alClient
        Lines.Strings = (
          'Memo1')
        ScrollBars = ssVertical
        TabOrder = 0
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'stringGrid'
      ImageIndex = 1
      object StringGrid1: TStringGrid
        Left = 0
        Top = 0
        Width = 490
        Height = 589
        Align = alClient
        TabOrder = 0
        OnDrawCell = StringGrid1DrawCell
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'square'
      ImageIndex = 2
      object StringGrid2: TStringGrid
        Left = 0
        Top = 0
        Width = 490
        Height = 589
        Align = alClient
        TabOrder = 0
        OnClick = StringGrid2Click
        OnDrawCell = StringGrid2DrawCell
      end
    end
    object TabSheet4: TTabSheet
      Caption = 'color square'
      ImageIndex = 3
      object StringGrid3: TStringGrid
        Left = 0
        Top = 0
        Width = 490
        Height = 589
        Align = alClient
        TabOrder = 0
        OnDrawCell = StringGrid3DrawCell
      end
    end
    object TabSheet5: TTabSheet
      Caption = 'no text'
      ImageIndex = 4
      object StringGrid4: TStringGrid
        Left = 0
        Top = 0
        Width = 490
        Height = 589
        Align = alClient
        TabOrder = 0
        OnDrawCell = StringGrid4DrawCell
      end
    end
    object TabSheet6: TTabSheet
      Caption = 'picture'
      ImageIndex = 5
      object StringGrid5: TStringGrid
        Left = 0
        Top = 0
        Width = 490
        Height = 589
        Align = alClient
        DefaultDrawing = False
        DoubleBuffered = True
        ParentDoubleBuffered = False
        TabOrder = 0
        OnDrawCell = StringGrid5DrawCell
      end
    end
  end
  object OpenDialog1: TOpenDialog
    Left = 304
    Top = 384
  end
  object SaveDialog1: TSaveDialog
    Left = 400
    Top = 336
  end
end
