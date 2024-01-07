﻿//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <fstream>
#include "UserDetails.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TuserDetailsForm *userDetailsForm;
//---------------------------------------------------------------------------
__fastcall TuserDetailsForm::TuserDetailsForm(TComponent* Owner)
	: TForm(Owner)
{
//	Home* home = mainForm->getHomeObj();

//    h1->users[]

	fstream myFile;

	myFile.open("userData.txt", std::ios::in);

	std::string fn, ln, pn, cnic, car, loc, locks, lights, speakers, curtains, heaters, cameras;

	myFile >> fn;
	myFile >> ln;
	myFile >> pn;
	myFile >> cnic;
	myFile >> car;
	myFile >> loc;
	myFile >> locks;
	myFile >> lights;
	myFile >> speakers;
	myFile >> curtains;
	myFile >> heaters;
	myFile >> cameras;

	myFile.close();

	fn += ln;

	nameLabel->Caption = fn.c_str();
	pnLabel->Caption = pn.c_str();
	cnicLabel->Caption = cnic.c_str();
	carLabel->Caption = car.c_str();
	locLabel->Caption = loc.c_str();
	lockLabel->Caption = locks.c_str();
	lightLabel->Caption = lights.c_str();
	speakerLabel->Caption = speakers.c_str();
	curtainLabel->Caption = curtains.c_str();
	heaterLabel->Caption = heaters.c_str();
	cameraLabel->Caption = cameras.c_str();


}
//---------------------------------------------------------------------------
