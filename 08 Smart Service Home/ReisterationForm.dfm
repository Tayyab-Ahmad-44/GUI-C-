object registerationForm: TregisterationForm
  Left = 523
  Top = 177
  Caption = 'Registeration Form'
  ClientHeight = 350
  ClientWidth = 283
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poDesigned
  TextHeight = 15
  object Label1: TLabel
    Left = 40
    Top = 32
    Width = 63
    Height = 15
    Caption = 'First Name: '
  end
  object Label2: TLabel
    Left = 40
    Top = 80
    Width = 62
    Height = 15
    Caption = 'Last Name: '
  end
  object Label3: TLabel
    Left = 40
    Top = 128
    Width = 59
    Height = 15
    Caption = 'Phone No: '
  end
  object Label4: TLabel
    Left = 40
    Top = 173
    Width = 30
    Height = 15
    Caption = 'Cnic: '
  end
  object Label7: TLabel
    Left = 8
    Top = 224
    Width = 102
    Height = 15
    Caption = 'Do you have a car? '
  end
  object Label5: TLabel
    Left = 40
    Top = 242
    Width = 40
    Height = 15
    Caption = '(1 or 0):'
  end
  object fN_Edit: TEdit
    Left = 118
    Top = 29
    Width = 121
    Height = 23
    ImeName = 'US'
    TabOrder = 0
  end
  object lN_Edit: TEdit
    Left = 118
    Top = 77
    Width = 121
    Height = 23
    TabOrder = 1
  end
  object pN_Edit: TEdit
    Left = 118
    Top = 125
    Width = 121
    Height = 23
    TabOrder = 2
  end
  object cnic_Edit: TEdit
    Left = 118
    Top = 170
    Width = 121
    Height = 23
    TabOrder = 3
  end
  object doneButton: TButton
    Left = 118
    Top = 272
    Width = 89
    Height = 33
    Caption = 'Done'
    TabOrder = 5
    OnClick = doneButtonClick
  end
  object hasCar_Edit: TEdit
    Left = 118
    Top = 221
    Width = 121
    Height = 23
    TabOrder = 4
  end
end