//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AllUsersRoomsForm.h"
#include "Unit1.h"
#include "Rooms.h"
#include <fstream>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TallRoomsForm *allRoomsForm;
//---------------------------------------------------------------------------
__fastcall TallRoomsForm::TallRoomsForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TallRoomsForm::searchButtonClick(TObject *Sender)
{
	long long cnic = std::stoll(AnsiString(cnicEdit->Text).c_str());

	Home* home = mainForm->getHomeObj();

	if(home->users.find(cnic) == home->users.end())
		ShowMessage("User with Cnic: " + cnicEdit->Text + " not found");
	else
	{
		fstream myFile;

		myFile.open("userData.txt", std::ios::out | std::ios::trunc);

		myFile << cnic;

		myFile.close();

		rooomsForm->ShowModal();
	}

}
//---------------------------------------------------------------------------
