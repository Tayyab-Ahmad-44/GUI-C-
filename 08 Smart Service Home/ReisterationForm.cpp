//---------------------------------------------------------------------------

#include <vcl.h>
#include <fstream>

#pragma hdrstop

#include "ReisterationForm.h"
#include "ServicesProvider.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TregisterationForm *registerationForm;
//---------------------------------------------------------------------------
__fastcall TregisterationForm::TregisterationForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TregisterationForm::doneButtonClick(TObject *Sender)
{

		fN =  AnsiString(fN_Edit->Text).c_str();
		lN =  AnsiString(lN_Edit->Text).c_str();
		pN =  AnsiString(pN_Edit->Text).c_str();
		cnic =  AnsiString(cnic_Edit->Text).c_str();
		hasCar =  AnsiString(hasCar_Edit->Text).c_str();

		fN_Edit->Text = "";
		lN_Edit->Text = "";
		pN_Edit->Text = "";
		cnic_Edit->Text = "";
		hasCar_Edit->Text = "";

        this->Close();
}
//---------------------------------------------------------------------------
