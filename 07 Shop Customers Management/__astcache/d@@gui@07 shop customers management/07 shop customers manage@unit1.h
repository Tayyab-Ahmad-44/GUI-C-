﻿//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Grid.hpp>
#include <FMX.Grid.Style.hpp>
#include <FMX.ScrollBox.hpp>
#include <System.Rtti.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *AddCustomerButton;
	TLabel *addCustomerLabel;
	TButton *checkOutButton;
	TStringGrid *Line1StringGrid;
	TStringColumn *StringColumn4;
	TStringColumn *StringColumn5;
	TStringGrid *Line2StringGrid;
	TStringColumn *StringColumn1;
	TStringColumn *StringColumn2;
	TStringGrid *Line3StringGrid;
	TStringColumn *StringColumn3;
	TStringColumn *StringColumn6;
	TLabel *Label2;
	TLabel *Label10;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label9;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label11;
	TLabel *Label1;
	TLabel *Label3;
	TLabel *Label13;
	TLabel *Label12;
	TLabel *Label15;
	TLabel *Label16;
	TLabel *Label14;
	void __fastcall AddCustomerButtonClick(TObject *Sender);
	void __fastcall checkOutButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
