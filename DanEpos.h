//---------------------------------------------------------------------------

#ifndef DanEPOSH
#define DanEPOSH
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
#endif
#define BIT16   0x10000
#define BIT15   0x8000
#define BIT14   0x4000
#define BIT13   0x2000
#define BIT12   0x1000
#define BIT11   0x0800
#define BIT10   0x0400
#define BIT9    0x0200
#define BIT8    0x0100
#define BIT7    0x0080
#define BIT6    0x0040
#define BIT5    0x0020
#define BIT4    0x0010
#define BIT3    0x0008
#define BIT2    0x0004
#define BIT1    0x0002
#define BIT0    0x0001
//-----------------------------------------------------------------------------
// ��������� ��� �����-������ ����������
//-----------------------------------------------------------------------------
struct DvMexUp {
           int    Nom;         // ����� �������
           int    CanCom;      // ��� ����������� CAN-COM            //@@@@
           WORD    COMport;     // ����� ���/CAN ����� ��� StepNet
           int    Baudrate;    // �������� ������ �� ���/CAN ����� ��� StepNet
           int    NumContr;    // ����� ����������� �� StepNet
           HANDLE    Handle;      // ����� ������
	       double Ft;          // ������� �������
	       double Kof;         // ���������� ��������� (������� �� ������)
	       double Step;        // ��� �������
	       double Mkm;         // �����.�������� ������� 1 mkm = N dis
	       double Cherv;       // ������������ ����� ���������� ���������
	       double Ekc;         // �������������� (������)
           double SlegZon;     // ���� �������� ��� StepNet
	       double Vbaz1;       // �������� �������� �� ������ ����
	       double Vbaz2;       // �������� �������� � ������� ����
	       double Kbaz;        // ���������� ����
           double SmBase;      // �������� ���� ��� StepNet
	       double Kini;        // ��������� ����������
           double ZoneSleg;    // ���� �������� ��� StepNet
	       double EkcC;        // ���������� ������ �����������
	       double Vmax;        // ������������ �������� � �\�
           double Vmin;        // �������� ����������
	       double Amax;        // ������������ ��������� � �\�*�
	       double Rmax;        // ������������ ����� � �\�*�*�
	       double Vizm;        // ������������� �������� � �\�
	       double Kmin;        // min ���������� ����������
	       double Kmax;        // max ���������� ����������
	       double Stan;        // ����������� ����������� (��� �������)
           double TimeOtr;     // ����� �������� ��������� ��� StepNet
	       int    Sens;        // ������� ������������ ������� ����
	       char   TipDv[20];   // ��� ���������
               } ;

extern struct ParCommon DefParamEpos[];
extern struct DvMexUp DvigMex[];
extern int KolDvMexUp ;
extern    DWORD Result;
extern double ZdnPos;
///////////////////////////////////////////////////////////////////////////////////////////

extern AnsiString Dgn;



extern int MotorEposNumInit(int) ;
extern int MotorEposComInit(int,int,int,int );
extern int MotorEposNumEnable(int);
extern int MotorEposNumDisable(int);
extern int MotorEposNumReadZdnCoord(int,double *);
extern int MotorEposNumReadTekCoord(int,double *);
extern int MotorEposRaschMoveCoordPar(int , double ,double *, char , int );
extern int MotorEposRaschMoveCoordPar(int , double ,double *, char , int );
extern int MotorEposCheckResult(int , int );
extern int MotorEposDiagnController(char *);
extern int MotorEposDgnPerMex(int, double, double, double, int *);
extern int MotorEposCheckStateController(int );
extern int MotorEposComDeInit(int ,int );
extern int MotorEposCheckStruct(int , int*);
extern int MotorEposNumBase(int,__int8 );
extern int MotorEposNumClearFaults(int );
extern int MotorEposNumReadParBase(int , double*, double*,double *, double*, double*);
extern int MotorEposNumWriteParBase(int , double , double ,double, double , double );
extern int MotorEposRaschMoveCoordPar(int , double ,double *, char, int );
extern int MotorEposNumWriteParMove(int , double , double , double , double );
extern int MotorEposNumReadParMove(int , double *, double *, double *, double *);
extern int MotorEposNumRelMove(int , double , int );
extern int MotorEposNumStop(int );
extern int MotorEposNumAbsMove(int , double , int );
extern int MotorEposNumStatBase( int);
extern int MotorEposNumReadMaxMin(int , double *, double *);
extern int MotorEposNumSkanMove(int , double );
extern int MotorEposNumWaitEndMove(int );
extern int MotorEposNumReadState(int , int *);
extern int MotorEposNumReadSensor(int , int *);
extern int Proba(HANDLE ,int);
extern int MotorEposNalDvig(int );

extern int MotorEposNumReadPos(int, double *);
