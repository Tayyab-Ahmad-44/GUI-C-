﻿//---------------------------------------------------------------------------

#ifndef InputCnicH
#define InputCnicH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TinputCnicForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TEdit *cnicEdit;
	TButton *doneButton;
	void __fastcall doneButtonClick(TObject *Sender);
private:	// User declarations
	long long cnic;
public:		// User declarations
	__fastcall TinputCnicForm(TComponent* Owner);
	long long getCnic()
	{
        return cnic;
    }
};
//---------------------------------------------------------------------------
extern PACKAGE TinputCnicForm *inputCnicForm;
//---------------------------------------------------------------------------
#endif
