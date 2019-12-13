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
// Структура для ввода-вывода параметров
//-----------------------------------------------------------------------------
struct DvMexUp {
           int    Nom;         // номер привода
           int    CanCom;      // тип подключения CAN-COM            //@@@@
           WORD    COMport;     // номер СОМ/CAN порта для StepNet
           int    Baudrate;    // скорость обмена по СОМ/CAN порту для StepNet
           int    NumContr;    // номер контроллера на StepNet
           HANDLE    Handle;      // номер хендла
	       double Ft;          // частота таймера
	       double Kof;         // Разрешение двигателя (дискрет на оборот)
	       double Step;        // Шаг нарезки
	       double Mkm;         // коэфф.передачи привода 1 mkm = N dis
	       double Cherv;       // передаточное число червячного редуктора
	       double Ekc;         // эксцентриситет (микрон)
           double SlegZon;     // зона слежения для StepNet
	       double Vbaz1;       // скорость движения на датчик базы
	       double Vbaz2;       // скорость движения с датчика базы
	       double Kbaz;        // координата базы
           double SmBase;      // смещение базы для StepNet
	       double Kini;        // Начальная координата
           double ZoneSleg;    // зона слежения для StepNet
	       double EkcC;        // координата центра эксцентрика
	       double Vmax;        // Максимальная скорость в м\с
           double Vmin;        // скорость торможения
	       double Amax;        // Максимальное ускорение в м\с*с
	       double Rmax;        // Максимальный рывок в м\с*с*с
	       double Vizm;        // Измерительная скорость в м\с
	       double Kmin;        // min допустимая координата
	       double Kmax;        // max допустимая координата
	       double Stan;        // Стандартное перемещение (для затвора)
           double TimeOtr;     // время ожидания отработки для StepNet
	       int    Sens;        // уровень срабатывания датчика базы
	       char   TipDv[20];   // Тип двигателя
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
