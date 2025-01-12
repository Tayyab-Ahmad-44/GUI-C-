//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.jpeg.hpp>
//---------------------------------------------------------------------------
class TenteranceForm : public TForm
{
__published:	// IDE-managed Components
	TImage *Image;
	TButton *guestRoomButton;
	TButton *usersRoomButton;
	void __fastcall usersRoomButtonClick(TObject *Sender);
	void __fastcall guestRoomButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TenteranceForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TenteranceForm *enteranceForm;
//---------------------------------------------------------------------------
#endif
