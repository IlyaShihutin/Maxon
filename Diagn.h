//"Diagn.h"

#ifndef _DiagnDll_H
#define _DiagnDll_H

#  define DLL_EXP __declspec(dllimport)
#  define otw_CRA  0
#  define otw_CR   1
#  define otw_CA   2
#  define otw_C    3
#  define otw_any  4
#  define otw_YN   5
#  define otw_CRSA 6
#  define otw_CRTA 7
#  define otw_UR   8
#  define otw_CBA  9
#  define otw_RA   10
#  define otw_A    11
#  define otw_SAI  12
#  define otw_AI   13
#  define otw_ESA  14
#  define otw_YNA  15
#  define otw_OUA  16

extern "C" void DLL_EXP DiagnOn(char *Path);
extern "C" void DLL_EXP DiagnOff(void);
extern "C" char DLL_EXP swDiagn(int dia, int otw, int psw);
extern "C" char DLL_EXP swDiagnA(int dia, int otw, int psw);
extern "C" char DLL_EXP swDiagnI(int dia, int otw, int psw);
extern "C" char DLL_EXP swDiagnV(int dia, int otw, int psw);
extern "C" void DLL_EXP DiagnStr(int dia, char *dia_str);
extern "C" void DLL_EXP SetDiagnSound(int i);
extern "C" void DLL_EXP SetNameDbDiag(char *Name);
extern "C" void DLL_EXP SetNameDbStat(char *Name);
extern "C" void DLL_EXP SetPasswordForDiagn(char *us);
extern char DLL_EXP strng1[3000];
extern  int DLL_EXP KeyLangDgn;
extern  int DLL_EXP KeyCodDgn;
extern  int DLL_EXP DiagnPsw;
extern  int DLL_EXP DgnModalResult;
extern char DLL_EXP StatTxtDiagn[200];

#endif

extern char Diagn(int,int),DiagnA(int,int),DiagnI(int,int),DiagnV(int,int);
