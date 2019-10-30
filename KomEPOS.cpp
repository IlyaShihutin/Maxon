#include <vcl.h>
#pragma hdrstop

#include "stdio.h"
#include "FrmKom.h"
#include "DanEpos.h"
#include "Definitions.h"
#include "TiSpin.h"


/*
int ReadDanPodkl(void)
{
const WORD maxStrSize = 100;
strDeviceName = new char[maxStrSize];
strProtocolStackName= new char[maxStrSize];
strInterfaceName= new char[maxStrSize];
strPortName= new char[maxStrSize];
BOOL endOfSel;


 if(!VCS_GetInterfaceName(m_KeyHandle, strInterfaceName, maxStrSize, &m_dErrorCode))
    {
  	ShowErrorInformation(m_dErrorCode);
        return false;
    //Timer->Enabled = false;
    }
 if(!VCS_GetDeviceName(m_KeyHandle, strDeviceName, maxStrSize, &m_dErrorCode))
    {
  	ShowErrorInformation(m_dErrorCode);
        return false;
    //    Timer->Enabled = false;
    }



 if(!VCS_GetPortName(m_KeyHandle, strPortName, maxStrSize, &m_dErrorCode))
    {
  	ShowErrorInformation(m_dErrorCode);
        return false;
      //  Timer->Enabled = false;
    }




FormFrmKom->Label3->Caption= strProtocolStackName;


FormFrmKom->Label4->Caption= strInterfaceName;


FormFrmKom->Label5->Caption= strDeviceName;


FormFrmKom->Label6->Caption= strPortName;
//free(strProtocolStackName);
//free(strInterfaceName);
//free(strDeviceName);
//free(strPortName);
return 0;
//----------------------------------------------------------------------------
//proba
//----------------------------------------------------------------------------
int Proba(HANDLE m_KeyHandle1,int MotorNum)
{
int n=0;
    if (MotorEposCheckStruct(MotorNum,&n)==-1) return(-1);
    int MHandle=DvigMex[n].Handle;
int DialogMode=1;
   const WORD maxstr=100;
   char strDeviceName[maxstr];
   char pProtocolStackName[maxstr];
   DWORD Baudrate1=1000000;
   WORD pNodeId=3;
VCS_FindSubDeviceCommunicationSettings(m_KeyHandle[MHandle], &m_KeyHandle1,strDeviceName, pProtocolStackName, maxstr, &Baudrate1, &pNodeId,DialogMode, &Result);
return 0;
}

}  */
/*
//---------------------------------------------------------------------------
int MotorEposNumBase(int MotorNum)
{
int n=0;
  if (MotorEposCheckStruct(MotorNum,&n)==-1) return(-1);
  int COMNumber = DvigMex[n].COMport;
  int NumID = (WORD)DvigMex[n].NumContr;
  double TimeOtr = DvigMex[n].TimeOtr;      // в сек
  int KolCikl = (int)(TimeOtr*1000./5.);    // кол-во циклов по 5 млсек
  if (MotorEposCheckStateController(COMNumber,NumID)==-1) return(-1);
///  result = Motor.TGStartHoming(MotorCOMNumID);
  if (MotorEposCheckResult(MotorNum,Result)==-1) return(-1);
  for (int i=0; i<KolCikl; i++)
      {
      Sleep(5);
      Application->ProcessMessages();
 ///     result = Motor.TGGetCurrentState(MotorCOMNumID,&n);
      if (MotorEposCheckResult(MotorNum,Result)==-1) return(-1);
      if ((n&0x5800)!=0) break;                  // если ошибка, останов или базирование закончено
      }
  if ((n&0x1000)!=0) {  return(0); }
  else if ((n&0x800)!=0)            MotorEposDiagnController(TxtDgnContr05);  // "Ошибка при базировании"
       else if ((n&0x2000)!=0)      MotorEposDiagnController(TxtDgnContr06);  // "Базирование не закончено"
            else if ((n&0x4000)!=0) MotorEposDiagnController(TxtDgnContr07);  // "При базировании произошла остановка привода"
  return(-1);
}

/************************************************************************
Shows a message box with error description of the input error code
************************************************************************/
/* bool ShowErrorInformation(DWORD dErrorCode)
{
 	char* pStrErrorInfo;
        pStrErrorInfo= new char[100];

	if(VCS_GetErrorInfo(Result,pStrErrorInfo,100))
	{
		Application->MessageBoxA(pStrErrorInfo,"Error Information",MB_ICONINFORMATION);

		free(pStrErrorInfo);

		return 0;
	}
	else
	{
		free(pStrErrorInfo);
		Application->MessageBoxA("Error information can't be read!","Error Information",MB_ICONINFORMATION);

		return (-1);
	}
}
*/
//  VCS_OpenDeviceDlg(&Result);
//  VCS_OpenSubDeviceDlg(m_KeyHandle[COMNumber], &Result);
//  VCS_SetGatewaySettings(m_KeyHandle[COMNumber], Baudrate1, &Result);
//  VCS_GetGatewaySettings(m_KeyHandle[COMNumber], &Baudrate1, &Result);
//  VCS_FindDeviceCommunicationSettings(&m_KeyHandle1, strDeviceName.c_str(),  STRPROT.c_str(),strInterfaceName.c_str(), strPortName.c_str(), maxstr,&Baudrate1, &pTimeout, &NumID, DialogMode, &Result);
//  VCS_GetGatewaySettings(m_KeyHandle[COMNumber], &Baudrate1, &Result);
//  m_KeyHandle1=VCS_OpenSubDevice(m_KeyHandle[COMNumber], strDeviceName.c_str(), STRPROT.c_str(), &Result);
//  VCS_SetGatewaySettings(m_KeyHandle[COMNumber], Baudrate1, &Result);
/*
WORD pHardwareVersion, pSoftwareVersion ,  pApplicationNumber,pApplicationVersion;
for(WORD i=0;i<8;i++)
{
if(VCS_GetVersion(m_KeyHandle[COMNumber], i, &pHardwareVersion,&pSoftwareVersion, &pApplicationNumber, &pApplicationVersion, &Result))
{sprintf(strng1,"есть версия для  %d \n",i);
     swDiagn(0,otw_any,0);}

}
*/
//  VCS_Restore(m_KeyHandle[COMNumber], NumID, &Result);
//  DWORD Baudrate1;
//       int DialogMode=1;
//        unsigned short Node=3;
//        VCS_FindSubDeviceCommunicationSettings(m_KeyHandle[COMNumber], &m_KeyHandle1,strDeviceName.c_str(), strProtocolStackName.c_str(), maxstr, &Baudrate1, &Node,DialogMode, &Result);
//  Result=0;

//  VCS_ReadCANFrame(m_KeyHandle1, CobID, Length,  pData,pTimeout , &Result);
//  VCS_GetDeviceName(m_KeyHandle1, strDeviceName.c_str(), maxstr,&Result);   268435459
//  VCS_GetProtocolStackName(m_KeyHandle[COMNumber], strProtocolStackName.c_str(), maxstr, &Result);
//  VCS_GetInterfaceName(m_KeyHandle[COMNumber], strInterfaceName.c_str(), maxstr,&Result);
//  VCS_GetPortName(m_KeyHandle[COMNumber], strPortName.c_str(), maxstr, &Result);
//WriteObj();

 /*

void __fastcall TFormFrmKom::ComboBox2Change(TObject *Sender)
{

    ComboBox2->ItemIndex == 0 ;

    switch (ComboBox2->ItemIndex)
    {
        case 0:
            m_uMode=35;
            break;
        case 1:
            m_uMode=34;
            break;
        case 2:
            m_uMode=33;
            break;
        case 3:
            m_uMode=27;
            break;
        case 4:
            m_uMode=23;
            break;
        case 5:
            m_uMode=18;
            break;
        case 6:
            m_uMode=17;
            break;
        case 7:
            m_uMode=11;
            break;
        case 8:
            m_uMode=7;
            break;
        case 9:
            m_uMode=2;
            break;
        case 10:
            m_uMode=1;
            break;
        case 11:
            m_uMode=0;
            break;
        case 12:
            m_uMode=(-1);
            break;
        case 13:
            m_uMode=(-2);
            break;
        case 14:
            m_uMode=(-3);
            break;
        case 15:
            m_uMode=(-4);
            break;


        default: Baudrate=9600; break;
  }
}

 int WriteObj(void)
{
int n=0;
    if (MotorEposCheckStruct(MotorNum,&n)==-1) return(-1);
    COMNumber=(WORD)DvigMex[n].COMport;
    NumID=(WORD)DvigMex[n].NumContr;
 char   Fname[80];
 DWORD    pNbOfBytesRead;
 FILE *F;
 DWORD w= 0;
 strcpy(Fname, "Object.par");
  if ((F=fopen(Fname,"wt"))==NULL)
       {
       sprintf(strng1," %s - Object.par ",sys_errlist[errno]); swDiagn(0,otw_any,0);
       }
  else {
        if(VCS_GetObject(m_KeyHandle[COMNumber], NumID, 0x1005, 0x00, &w, 2,&pNbOfBytesRead, &Result))
          { sprintf(strng1,"SYNC1 %d \n",w);
     swDiagn(0,otw_any,0);     }
          if(VCS_GetObject(m_KeyHandle[COMNumber], NumID, 0x1012, 0x00, &w, 2,&pNbOfBytesRead, &Result))
          { sprintf(strng1,"Time stamp 2 %d \n",w);
     swDiagn(0,otw_any,0);}
     if(VCS_GetObject(m_KeyHandle[COMNumber], NumID, 0x1001, 0x00, &w, 2,&pNbOfBytesRead, &Result))
          { sprintf(strng1,"Erro register %d \n",w);
     swDiagn(0,otw_any,0);}
     if(VCS_GetObject(m_KeyHandle[COMNumber], NumID, 0x1003, 0x00, &w, 2,&pNbOfBytesRead, &Result))
          { sprintf(strng1,"number of errors %d \n",w);
     swDiagn(0,otw_any,0);}
     if(VCS_GetObject(m_KeyHandle[COMNumber], NumID, 0x1003, 0x01, &w, 2,&pNbOfBytesRead, &Result))
          { sprintf(strng1,"error history 1 %d \n",w);
     swDiagn(0,otw_any,0);}
     if(VCS_GetObject(m_KeyHandle[COMNumber], NumID, 0x1003, 0x02, &w, 2,&pNbOfBytesRead, &Result))
          { sprintf(strng1,"error history  2 %d \n",w);
     swDiagn(0,otw_any,0);}
     if(VCS_GetObject(m_KeyHandle[COMNumber], NumID, 0x1003, 0x03, &w, 2,&pNbOfBytesRead, &Result))
          { sprintf(strng1,"error history 3 %d \n",w);
     swDiagn(0,otw_any,0);}
     if(VCS_GetObject(m_KeyHandle[COMNumber], NumID, 0x1003, 0x04, &w, 2,&pNbOfBytesRead, &Result))
          { sprintf(strng1,"error history 4 %d \n",w);
     swDiagn(0,otw_any,0);}
     if(VCS_GetObject(m_KeyHandle[COMNumber], NumID, 0x1003, 0x05, &w, 2,&pNbOfBytesRead, &Result))
          { sprintf(strng1,"error history 5 %d \n",w);
     swDiagn(0,otw_any,0);}



     else { sprintf(strng1,"ничего нет %d \n",0x200a);
     swDiagn(0,otw_any,0);}

  fclose(F);
  }
  return true;
  }


*/
