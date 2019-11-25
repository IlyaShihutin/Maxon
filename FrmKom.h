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
//---------------------------------------------------------------------------
class TFormFrmKom : public TForm
{
__published:	// IDE-managed Components
    TButton *Button2;
    TLabel *Label1;
    TLabel *Label2;
    TButton *Button3;
    TButton *Button4;
    TButton *Button5;
    TButton *Button6;
    TGroupBox *GroupBox1;
    TCheckBox *CheckBox1;
    TCheckBox *CheckBox2;
    TCheckBox *CheckBox3;
    TCheckBox *CheckBox4;
    TGroupBox *GroupBox2;
    TRadioButton *RadioButton1;
    TRadioButton *RadioButton2;
    TLabel *Label7;
    TButton *Button7;
    TTiSpinEdit *MotorNumEdit;
    TTiSpinEdit *NodeId;
    TButton *Button1;
    TComboBox *ComboBox1;
    TButton *Button8;
    TButton *Button9;
    TGroupBox *GroupParBaz;
    TLabel *Label5;
    TLabel *Label11;
    TLabel *Label12;
    TLabel *Label6;
    TLabel *Label8;
    TTiSpinEdit *TiSpEdBU;
    TTiSpinEdit *TiSpEdBS1;
    TTiSpinEdit *TiSpEdBS2;
    TTiSpinEdit *TiSpEdBSm;
    TCheckBox *CheckBox5;
    TButton *Button10;
    TButton *Button11;
    TButton *Button12;
    TButton *Button13;
    TGroupBox *GroupParDv;
    TLabel *Label16;
    TLabel *Label17;
    TLabel *Label23;
    TLabel *Label3;
    TTiSpinEdit *TiSpEdU;
    TTiSpinEdit *TiSpEdT;
    TTiSpinEdit *TiSpEdMaxS;
    TTiSpinEdit *TiSpEdMaxU;
    TComboBox *ComboBox2;
    TButton *Button14;
    TGroupBox *GroupPer;
    TLabel *LabelOrientM;
    TLabel *LabelSch1;
    TTiSpinEdit *TTiSpEdPosition;
    TTiSpinEdit *TTiSpEdTek;
    TButton *Button15;
    TButton *Button16;
    TButton *Button17;
    TCheckBox *CheckBox6;
    TLabel *Label4;
    TTiSpinEdit *TiSpinEdit1;
    TButton *Button18;
    TRadioButton *RadioButton3;
    TRadioButton *RadioButton4;
    TGroupBox *GroupBox3;
    TButton *Button19;
    TLabel *Label9;
    TLabel *Label10;
    TTiSpinEdit *TiSpinEdit2;
    TTiSpinEdit *TiSpinEdit3;
    TButton *Button20;
    TButton *Button21;
    TCheckListBox *CheckListBox1;
    TButton *Button22;
    TCheckListBox *CheckListBox2;
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall Button4Click(TObject *Sender);
    void __fastcall Button5Click(TObject *Sender);
    void __fastcall GroupBox2Click(TObject *Sender);
    void __fastcall Button3Click(TObject *Sender);
    void __fastcall Button6Click(TObject *Sender);
    void __fastcall Button7Click(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall ComboBox1Change(TObject *Sender);
    void __fastcall Button8Click(TObject *Sender);
    void __fastcall Button9Click(TObject *Sender);
    void __fastcall Button10Click(TObject *Sender);
    void __fastcall Button12Click(TObject *Sender);
    void __fastcall Button11Click(TObject *Sender);
    void __fastcall Button13Click(TObject *Sender);
    void __fastcall ComboBox2Change(TObject *Sender);
    void __fastcall Button14Click(TObject *Sender);
    void __fastcall Button15Click(TObject *Sender);
    void __fastcall Button16Click(TObject *Sender);
    void __fastcall Button17Click(TObject *Sender);
    void __fastcall GroupParDvClick(TObject *Sender);
    void __fastcall Button18Click(TObject *Sender);
    void __fastcall Button19Click(TObject *Sender);
    void __fastcall Button20Click(TObject *Sender);
    void __fastcall Button21Click(TObject *Sender);
    void __fastcall Button22Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFormFrmKom(TComponent* Owner);


};
//---------------------------------------------------------------------------
extern PACKAGE TFormFrmKom *FormFrmKom;
//---------------------------------------------------------------------------
#endif
