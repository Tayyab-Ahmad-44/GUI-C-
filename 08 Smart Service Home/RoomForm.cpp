//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RoomForm.h"
#include "Unit1.h"
#include <fstream>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TroomsForm *roomsForm;
//---------------------------------------------------------------------------
__fastcall TroomsForm::TroomsForm(TComponent* Owner)
	: TForm(Owner)
{
//	fstream myFile;
//	myFile.open("userData.txt", std::ios::in);
//
//	long long cnic;
//
//	myFile >> cnic;
//
//	Home *home = mainForm->getHomeObj();
////
////	User *user = home->users[cnic];
//
//	bool a =  home->users[cnic]->lights;
//
//	if(home->users[cnic]->lights)
//	{
//		int i = 0;
//	}
//		lightImage->Visible = true;
//	else
//		lightImage->Visible = false;
//
//	if(!user->thermostat)
//		thermostatImage->Visible = true;
//	else
//		thermostatImage->Visible = false;
//
//	if(!user->security)
//		securityImage->Visible = true;
//	else
//		securityImage->Visible = false;
//
//	if(!user->cameras)
//		camerasImage->Visible = true;
//	else
//		camerasImage->Visible = false;
//
//	if(!user->assistant)
//		assistantImage->Visible = true;
//	else
//		assistantImage->Visible = false;
//
//	if(!user->speakers)
//		speakersImage->Visible = true;
//	else
//		speakersImage->Visible = false;
}
//---------------------------------------------------------------------------
