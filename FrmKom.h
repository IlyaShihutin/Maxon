//---------------------------------------------------------------------------

#ifndef FrmKomH
#define FrmKomH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TiSpin.h"
#include <CheckLst.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormFrmKom : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel4;
    TPanel *Panel5;
    TButton *Button3;
    TButton *Button4;
    TButton *Button5;
    TButton *Button6;
    TButton *Button1;
    TButton *Button8;
    TButton *Button15;
    TPanel *Panel6;
    TButton *Button20;
    TButton *Button14;
    TButton *Button16;
    TButton *Button9;
    TPanel *Panel3;
    TButton *Button10;
    TButton *Button11;
    TButton *Button12;
    TButton *Button13;
    TPanel *Panel7;
    TGroupBox *GroupPer;
    TTiSpinEdit *TTiSpEdPosition;
    TTiSpinEdit *TTiSpEdTek;
    TTiSpinEdit *TiSpinEdit4;
    TButton *Button7;
    TButton *Button18;
    TButton *Button23;
    TGroupBox *GroupBox1;
    TCheckBox *CheckBox1;
    TCheckBox *CheckBox2;
    TCheckBox *CheckBox3;
    TCheckBox *CheckBox4;
    TCheckBox *CheckBox5;
    TCheckBox *CheckBox6;
    TGroupBox *GroupBox3;
    TLabel *Label9;
    TLabel *Label10;
    TButton *Button19;
    TTiSpinEdit *TiSpinEdit2;
    TTiSpinEdit *TiSpinEdit3;
    TGroupBox *GroupBox5;
    TGroupBox *GroupBox6;
    TCheckListBox *CheckListBox1;
    TCheckListBox *CheckListBox2;
    TGroupBox *GroupParBaz;
    TLabel *Label5;
    TLabel *Label11;
    TLabel *Label15;
    TLabel *Label6;
    TLabel *Label8;
    TLabel *Label4;
    TTiSpinEdit *TiSpEdBU;
    TTiSpinEdit *TiSpEdBS1;
    TTiSpinEdit *TiSpEdBS2;
    TTiSpinEdit *TiSpEdBSm;
    TComboBox *ComboBox2;
    TTiSpinEdit *TiSpinEdit1;
    TGroupBox *GroupParDv;
    TLabel *Label16;
    TLabel *Label17;
    TLabel *Label23;
    TLabel *Label3;
    TTiSpinEdit *TiSpEdU;
    TTiSpinEdit *TiSpEdT;
    TTiSpinEdit *TiSpEdMaxS;
    TTiSpinEdit *TiSpEdMaxU;
    TRadioButton *RadioButton3;
    TRadioButton *RadioButton4;
    TButton *Button17;
    TButton *Button21;
    TButton *Button22;
    TGroupBox *GroupBox2;
    TRadioButton *RadioButton1;
    TRadioButton *RadioButton2;
    TGroupBox *GroupBox4;
    TRadioButton *RadioButton5;
    TRadioButton *RadioButton6;
    TButton *Button2;
    TPanel *Panel1;
    TLabel *Label1;
    TTiSpinEdit *NodeId;
    TTiSpinEdit *MotorNumEdit;
    TLabel *Label2;
    TLabel *Label7;
    TComboBox *ComboBox1;
    void __fastcall Button2678Click(TObject *Sender);
    void __fastcall Button4213Click(TObject *Sender);
    void __fastcall Button514Click(TObject *Sender);
    void __fastcall gfdsgClick(TObject *Sender);
    void __fastcall Button323Click(TObject *Sender);
    void __fastcall Button6213Click(TObject *Sender);
    void __fastcall Button7123Click(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall Button123Click(TObject *Sender);
    void __fastcall fsdChange(TObject *Sender);
    void __fastcall Button8534Click(TObject *Sender);
    void __fastcall Button95435Click(TObject *Sender);
    void __fastcall Button10123Click(TObject *Sender);
    void __fastcall Button12123Click(TObject *Sender);
    void __fastcall Button11123Click(TObject *Sender);
    void __fastcall Button13123Click(TObject *Sender);
    void __fastcall sdfChange(TObject *Sender);
    void __fastcall Button147654Click(TObject *Sender);
    void __fastcall Button15321Click(TObject *Sender);
    void __fastcall Button1623Click(TObject *Sender);
    void __fastcall Button1712Click(TObject *Sender);
    void __fastcall fdsClick(TObject *Sender);
    void __fastcall Button18123Click(TObject *Sender);
    void __fastcall Button19Click(TObject *Sender);
    void __fastcall Button20123Click(TObject *Sender);
    void __fastcall gds2123Click(TObject *Sender);
    void __fastcall Button2212Click(TObject *Sender);
    void __fastcall Button23213Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFormFrmKom(TComponent* Owner);


};
//---------------------------------------------------------------------------
extern PACKAGE TFormFrmKom *FormFrmKom;
//---------------------------------------------------------------------------
#endif
