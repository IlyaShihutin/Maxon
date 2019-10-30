//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "zadacha1.h"
#include "FrmKom.h"
#include "TiSpin.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
FormKom->Show();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
Close();    
}
//---------------------------------------------------------------------------

