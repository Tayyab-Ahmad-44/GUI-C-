﻿//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>

#include "myHeader.cpp"
#include <Vcl.Imaging.jpeg.hpp>
//---------------------------------------------------------------------------
class TmainForm : public TForm
{
__published:	// IDE-managed Components
	TImage *homeImage;
	TLabel *garageLabel;
	TLabel *mainDoorLabel;
	TLabel *roomsLabel1;
	TLabel *roomsLabel3;
	TLabel *roomsLabel2;
	TLabel *kitchenLabel;
	TLabel *terrisLabel;
	TLabel *guestRoomLabel;
	TButton *newUserButton;
	TButton *userDetailsButton;
	TButton *userLocationButton;
	void __fastcall garageLabelClick(TObject *Sender);
	void __fastcall mainDoorLabelClick(TObject *Sender);
	void __fastcall newUserButtonClick(TObject *Sender);
	void __fastcall userDetailsButtonClick(TObject *Sender);
	void __fastcall userLocationButtonClick(TObject *Sender);
private:	// User declarations
	Home* h1;
public:		// User declarations
	__fastcall TmainForm(TComponent* Owner);
	Home* getHomeObj()
	{
		return h1;
	}

};
//---------------------------------------------------------------------------
extern PACKAGE TmainForm *mainForm;
//---------------------------------------------------------------------------
#endif
