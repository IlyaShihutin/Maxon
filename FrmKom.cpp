//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Definitions.h"
#include "stdio.h"
#include "FrmKom.h"
#include "DanEpos.h"
#include "Diagn.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormFrmKom *FormFrmKom;
int MotorNum=11;
int COMNumber=0;
int KeyCanCom=2;
int Baudrate=115200;
__int8  m_uMode=35;
int Key=1;
//---------------------------------------------------------------------------
__fastcall TFormFrmKom::TFormFrmKom(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormFrmKom::Button2Click(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormFrmKom::Button5Click(TObject *Sender)//��������� ���������
{
    MotorNum =MotorNumEdit->Value;

    if (MotorEposNumEnable(MotorNum )==0)
        {
            CheckBox3->Checked=true ;
            CheckBox4->Checked=false ;
        }
    else
        CheckBox3->Checked=false ;
}
//---------------------------------------------------------------------------
void __fastcall TFormFrmKom::Button4Click(TObject *Sender) //������������� �� ���������
{
    MotorNum =MotorNumEdit->Value;
    int n=0;
    if (MotorEposCheckStruct(MotorNum,&n)==0)
        {
            DvigMex[n].COMport=NodeId->Value;
            DvigMex[n].CanCom=KeyCanCom;

            if (MotorEposNumInit(MotorNum )==0)
                CheckBox2->Checked=true ;
            else
                CheckBox2->Checked=false ;
        }
    else ShowMessage("���������� �� ������� � ���������");
}
//---------------------------------------------------------------------------
void __fastcall TFormFrmKom::GroupBox2Click(TObject *Sender)
{
    if(RadioButton1->Checked)KeyCanCom=0;
    else if (RadioButton2->Checked) KeyCanCom=2;
   
}
//---------------------------------------------------------------------------
void __fastcall TFormFrmKom::Button3Click(TObject *Sender) //������������� �� �����
{
    COMNumber=NodeId->Value;
    MotorNum =MotorNumEdit->Value;
    if (MotorEposComInit( KeyCanCom,  COMNumber,Baudrate,MotorNum)==0)
        {
            CheckBox1->Checked=true ;
        }
    else    CheckBox1->Checked=false ;
}
//---------------------------------------------------------------------------
void __fastcall TFormFrmKom::Button6Click(TObject *Sender)//���������� ���������
{
    MotorNum =MotorNumEdit->Value;

    if (MotorEposNumDisable(MotorNum )==0)
        {
            CheckBox3->Checked=false ;
            CheckBox4->Checked=true ;
        }
}
//---------------------------------------------------------------------------
void __fastcall TFormFrmKom::Button7Click(TObject *Sender)//������ ������� �������
{
    MotorNum =MotorNumEdit->Value;
    double TekPos;
    if(MotorEposNumReadTekCoord(MotorNum, &TekPos)==0)
        TTiSpEdTek->Value=TekPos;
}
//---------------------------------------------------------------------------

void __fastcall TFormFrmKom::FormCreate(TObject *Sender)
{
    FormFrmKom->CheckBox4->Checked=true ;
    MotorNum=MotorNumEdit->Value;
    COMNumber=NodeId->Value;

    SetNameDbDiag("Diagn84.DB");
    SetNameDbStat("DgnStat.DB");
    DiagnOn("D:\\Tasks\\raz\\Task1");
    KeyLangDgn=0;
    KeyCodDgn = 0;

}
//---------------------------------------------------------------------------
void __fastcall TFormFrmKom::FormDestroy(TObject *Sender)
{
    DiagnOff();
    exit(0);
}
//---------------------------------------------------------------------------
void __fastcall TFormFrmKom::Button1Click(TObject *Sender)//���������������
{
    COMNumber=NodeId->Value;
    MotorNum=MotorNumEdit->Value;
    if(MotorEposComDeInit( COMNumber, MotorNum)==0)
        {
            CheckBox1->Checked=false ;
            CheckBox2->Checked=false ;
            CheckBox3->Checked=false ;
            CheckBox4->Checked=true ;
        }
}
//---------------------------------------------------------------------------
void __fastcall TFormFrmKom::ComboBox1Change(TObject *Sender)//��������� �������� ��������
{
    ComboBox1->ItemIndex == 5 ;

    switch (ComboBox1->ItemIndex)
    {
        case 0: Baudrate=9600;  break;
        case 1: Baudrate=14400; break;
        case 2: Baudrate=19200; break;
        case 3: Baudrate=38400; break;
        case 4: Baudrate=57600; break;
        case 5: Baudrate=115200;break;
        default: Baudrate=115200; break;
  }
}
//---------------------------------------------------------------------------


void __fastcall TFormFrmKom::Button8Click(TObject *Sender)//����� ������ �������
{
  MotorNum=MotorNumEdit->Value;
  MotorEposNumClearFaults(MotorNum);
}
//---------------------------------------------------------------------------

void __fastcall TFormFrmKom::Button9Click(TObject *Sender)//����������� 
{
    MotorNum=MotorNumEdit->Value;
    if(MotorEposNumBase(MotorNum, m_uMode)==0)
        CheckBox6->Checked=false ;
}
//---------------------------------------------------------------------------


void __fastcall TFormFrmKom::Button10Click(TObject *Sender)//������ ���������� �����������
{
    MotorNum=MotorNumEdit->Value;
    double Uskor;
    double SpeedSwitch;
    double SpeedIndex;
    double Offset;
    double HPosition;
    if(MotorEposNumReadParBase( MotorNum, &SpeedSwitch, &SpeedIndex, &Uskor,&HPosition, &Offset)==0)
        {
            TiSpEdBU->Value = Uskor;
            TiSpEdBS1->Value = SpeedSwitch;
            TiSpEdBS2->Value = SpeedIndex;
            TiSpEdBSm->Value = Offset;
            TiSpinEdit1->Value=HPosition;
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormFrmKom::Button12Click(TObject *Sender)//������ ���������� �����������
{
    MotorNum=MotorNumEdit->Value;
    double Uskor=TiSpEdBU->Value;
    double SpeedSwitch=TiSpEdBS1->Value;
    double SpeedIndex=TiSpEdBS2->Value;
    double Offset=TiSpEdBSm->Value;
    double HPosition=TiSpinEdit1->Value;
    MotorEposNumWriteParBase( MotorNum, SpeedSwitch, SpeedIndex, Uskor,HPosition, Offset);
}
//---------------------------------------------------------------------------

void __fastcall TFormFrmKom::Button11Click(TObject *Sender)//������ ���������� ��������
{
    MotorNum=MotorNumEdit->Value;
    double Uskor;
    double Torm;
    double Speed;
    double Rivok;
    if(MotorEposNumReadParMove(MotorNum, &Speed,&Uskor, &Torm,&Rivok)==0)
        {
            TiSpEdU->Value=Uskor;
            TiSpEdT->Value=Torm;
            TiSpEdMaxS->Value=Speed;
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormFrmKom::Button13Click(TObject *Sender)//������ ���������� ��������
{
    MotorNum=MotorNumEdit->Value;
    double Uskor=TiSpEdU->Value;
    double Torm=TiSpEdT->Value;
    double Speed=TiSpEdMaxS->Value;
    double Rivok=TiSpEdMaxU->Value;
    MotorEposNumWriteParMove(MotorNum, Speed, Uskor, Torm,Rivok);

}
//---------------------------------------------------------------------------

void __fastcall TFormFrmKom::ComboBox2Change(TObject *Sender)//��������� ������ �����������
{
    ComboBox2->ItemIndex == 0 ;

    switch (ComboBox2->ItemIndex)
    {
        case 0: m_uMode=35; break;
        case 1: m_uMode=34; break;
        case 2: m_uMode=33; break;
        case 3: m_uMode=27; break;
        case 4: m_uMode=23; break;
        case 5: m_uMode=18; break;
        case 6: m_uMode=17; break;
        case 7: m_uMode=11; break;
        case 8: m_uMode=7;  break;
        case 9: m_uMode=2;  break;
        case 10: m_uMode=1;  break;
        case 11: m_uMode=0;  break;
        case 12: m_uMode=(-1); break;
        case 13: m_uMode=(-2); break;
        case 14: m_uMode=(-3); break;
        case 15: m_uMode=(-4); break;
        default: m_uMode=35; break;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormFrmKom::Button14Click(TObject *Sender)//������������� �����������
{
    double DistMove=TTiSpEdPosition->Value;
    MotorNum=MotorNumEdit->Value;
    if(MotorEposNumRelMove(MotorNum, DistMove, Key)==0)
       CheckBox6->Checked=false ;
}
//---------------------------------------------------------------------------

void __fastcall TFormFrmKom::Button15Click(TObject *Sender)//��������� �������� �������
{
  MotorNum=MotorNumEdit->Value;
  if(MotorEposNumStop(MotorNum)==0)
    CheckBox6->Checked=false ;
}
//---------------------------------------------------------------------------

void __fastcall TFormFrmKom::Button16Click(TObject *Sender)//���������� ����������� 
{
    double DistMove=TTiSpEdPosition->Value;
    MotorNum=MotorNumEdit->Value;
    if(MotorEposNumAbsMove(MotorNum, DistMove, Key)==0)
        CheckBox6->Checked=false ;
}
//---------------------------------------------------------------------------

void __fastcall TFormFrmKom::Button17Click(TObject *Sender)//�������� ���������� �� ������
{
    MotorNum=MotorNumEdit->Value;
    if(MotorEposNumStatBase( MotorNum)==0)
        CheckBox6->Checked=true ;
    else
        CheckBox6->Checked=false ;
}
//---------------------------------------------------------------------------

void __fastcall TFormFrmKom::GroupParDvClick(TObject *Sender)
{
   if(RadioButton3->Checked)Key=0;
    else if (RadioButton4->Checked) Key=1;
}
//---------------------------------------------------------------------------

void __fastcall TFormFrmKom::Button18Click(TObject *Sender)//������ �������� ����������
{
    double  ZdnPos;
    MotorNum=MotorNumEdit->Value;
    if(MotorEposNumReadZdnCoord(MotorNum, &ZdnPos)==0)
        TTiSpEdPosition->Value=ZdnPos;
}
//---------------------------------------------------------------------------

void __fastcall TFormFrmKom::Button19Click(TObject *Sender)//������ ��� � ���� ����������
{
    MotorNum=MotorNumEdit->Value;
    double Max,Min;
    MotorEposNumReadMaxMin(MotorNum, &Max, &Min);
    TiSpinEdit2->Value=Max;
    TiSpinEdit3->Value=Min;

}
//---------------------------------------------------------------------------

void __fastcall TFormFrmKom::Button20Click(TObject *Sender)//������������ ������� 
{
    double DistMove=TTiSpEdPosition->Value;
    MotorNum=MotorNumEdit->Value;
    MotorEposNumSkanMove(MotorNum,DistMove);
}
//---------------------------------------------------------------------------

void __fastcall TFormFrmKom::Button21Click(TObject *Sender)//������ ��������� �������
{
    MotorNum=MotorNumEdit->Value;
    int State=0;
    if (MotorEposNumReadState( MotorNum,&State)==0)
        {

            if(State & BIT16)//�����������
                {
                    CheckListBox1->Items->Strings[13] = "������ ������ ��������� �����";
                    CheckListBox1->Items->Strings[12] = "���������� ��������� �����";
                }
            else //position mod
                {
                    CheckListBox1->Items->Strings[13] = "������ ����������";
                    CheckListBox1->Items->Strings[12] = "������������� ��������� ������������ �����";
                }

            for(int i = 0 ; i < 16; i++)
                {
                    int j = 1 << i;
                    CheckListBox1->Checked[i] = (State & j);
                }
        }
}
//---------------------------------------------------------------------------


void __fastcall TFormFrmKom::Button22Click(TObject *Sender) //������ ��������
{
    MotorNum=MotorNumEdit->Value;
    int Sens=0;
    if (MotorEposNumReadSensor(MotorNum, &Sens)==0)
        {
            for(int i = 0 ; i < 16; i++)
                {
                    int j = 1 << i;
                    CheckListBox2->Checked[i] = (Sens & j);
                }
        }
}
//---------------------------------------------------------------------------
