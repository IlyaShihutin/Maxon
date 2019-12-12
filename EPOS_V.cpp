
#pragma hdrstop
#include "FrmKom.h"
#include "Definitions.h"
#include "DanEpos.h"
#include "Diagn.h"
#include "stdio.h"

char TxtDgnContr01[] = "Инициализация соединения не выполнена";
char TxtDgnContr02[] = "Контроллер не включен !";
char TxtDgnContr03[] = "Отсутствует подключение с контроллером !";
char TxtDgnContr04[] = "Ошибка остановки привода !";
char TxtDgnContr05[] = "Ошибка при базировании привода.";
char TxtDgnContr06[] = "Базирование привода не закончено.";
char TxtDgnContr07[] = "При базировании привода\r\n контроллер подал команду на отмену движения.";
char TxtDgnContr08[] = "Не закончено перемещение привода.";
char TxtDgnContr09[] = "Контроллер включен !";
char TxtDgnContr10[] = "Ошибка выключения !";
char TxtDgnContr11[] = "Ошибка имени устройства !";
char TxtDgnContr12[] = "Ошибка имени протокола !";
char TxtDgnContr13[] = "Ошибка имени интерфейса !";
char TxtDgnContr14[] = "Ошибка имени порта !";
char TxtDgnContr15[] = "Базирование не законченно";


//----------------------------------------------------------------------------
int MotorEposDiagnController(char *Dgn)
{ sprintf(strng1," %s",Dgn);  swDiagn(0,otw_any,0);  return(0); }
//----------------------------------------------------------------------------
int MotorEposDgnPerMex(int MotorNum,double Min,double Max,double Koord,int *KeyErr)
{
    sprintf(strng1+strlen(strng1),
        " Недопустимая координата для привода %d.\r\n"
        " Min: %.2lf, Max: %.2lf, Задана координата: %.2lf. ",MotorNum,Min,Max,Koord);
    swDiagn(0,otw_any,0);
    *KeyErr = *KeyErr +1;
    return 0;
}
//----------------------------------------------------------------------------
//Проверка на инициализацию и включения
//----------------------------------------------------------------------------
int MotorEposCheckStateController(  int n)
{
    BOOL pIsEnabled=true;
    if (DvigMex[n].Handle!=0)
        {
            if(!VCS_GetEnableState(DvigMex[n].Handle, (WORD)DvigMex[n].NumContr, &pIsEnabled, &Result))
                {
                    MotorEposCheckResult(DvigMex[n].Nom,  Result);
                    return (-1);
                }
            if (pIsEnabled!=1)
                {
                    MotorEposDiagnController(TxtDgnContr02);
                    return(-1);
                }
            else if(MotorEposNalDvig(n)!=0)
                {
                    MotorEposDiagnController(TxtDgnContr03);
                    return (-1);
                }
        }
    else
        {
            MotorEposDiagnController(TxtDgnContr01);
            return(-1);
        }
    return (MotorEposCheckResult(DvigMex[n].Nom,Result));
}
//----------------------------------------------------------------------------
//Проверка данных в структуре
//----------------------------------------------------------------------------
int MotorEposCheckStruct(int MotorNum, int *index)
{
    for (int n=0; n<KolDvMexUp; n++)
      {
            if (DvigMex[n].Nom == MotorNum)
            {
                *index = n;
                return(0);
            }
      }
    sprintf(strng1," Для привода № %d данные отсутствуют ! ",MotorNum);
    return(-1);
}
//----------------------------------------------------------------------------
//Инициализация по порту
//----------------------------------------------------------------------------
int MotorEposComInit(int KeyCanCom, int COMNumber,int Baudrate,int MotorNum)
{
    int n=0;
    if (MotorEposCheckStruct(MotorNum,&n)==-1) return(-1);

    const WORD maxstr=100;
    BOOL pEndOfSelection=FALSE;
    char pDeviceNameSel[maxstr] ;
    char pProtocolStackNameSel[maxstr];
    char pInterfaceNameSel[maxstr];
    char pPortSel[maxstr];

    AnsiString strDeviceName;
    AnsiString strProtocolStackName;
    AnsiString strInterfaceName;
    AnsiString strPortName;
    AnsiString ProtocolStackName="CANopen";
    HANDLE m_KeyHandle1;
    if (KeyCanCom==2)
    {
        strInterfaceName="USB";
        strPortName=strInterfaceName+AnsiString(COMNumber);
        strDeviceName="EPOS2";
        strProtocolStackName="MAXON SERIAL V2";
    }
    else if(KeyCanCom==0)
            {
                strInterfaceName="RS232" ;
                strPortName="COM"+AnsiString(COMNumber);
                strDeviceName="EPOS2";
                strProtocolStackName="MAXON_RS232";
            }
    if(VCS_GetDeviceNameSelection(TRUE, pDeviceNameSel,maxstr, &pEndOfSelection, &Result))
        {
            do
            {
                if(AnsiString(pDeviceNameSel)==strDeviceName) break;
                if(!pEndOfSelection)
                        {
                            if(!VCS_GetDeviceNameSelection(FALSE, pDeviceNameSel,maxstr, &pEndOfSelection, &Result)) break;
                        }
                else {MotorEposDiagnController(TxtDgnContr11); return (-1);}
            } while(1);
        }
    if(MotorEposCheckResult(MotorNum,Result)==(-1)) return (-1);

    if(VCS_GetProtocolStackNameSelection(strDeviceName.c_str(), TRUE,pProtocolStackNameSel, maxstr, &pEndOfSelection, &Result))
        {
            do
            {
                if(AnsiString(pProtocolStackNameSel)==strProtocolStackName) break;
                if(!pEndOfSelection)
                        {
                            if(!VCS_GetProtocolStackNameSelection(strDeviceName.c_str(), FALSE,pProtocolStackNameSel, maxstr, &pEndOfSelection, &Result)) break;
                        }
                else {MotorEposDiagnController(TxtDgnContr12); return (-1);}
            } while(1);
        }
    if(MotorEposCheckResult(MotorNum,Result)==(-1)) return (-1);


    if(VCS_GetInterfaceNameSelection(strDeviceName.c_str(), strProtocolStackName.c_str(), TRUE, pInterfaceNameSel, maxstr, &pEndOfSelection, &Result))
        {
            do
            {
                if(AnsiString(pInterfaceNameSel)==strInterfaceName) break;
                if(!pEndOfSelection)
                        {
                            if(!VCS_GetInterfaceNameSelection(strDeviceName.c_str(), strProtocolStackName.c_str(), FALSE, pInterfaceNameSel,maxstr, &pEndOfSelection, &Result)) break;
                        }
                else {MotorEposDiagnController(TxtDgnContr13); return (-1);}
            } while(1);
        }
    if(MotorEposCheckResult(MotorNum,Result)==(-1)) return (-1);




    if(VCS_GetPortNameSelection(strDeviceName.c_str(), strProtocolStackName.c_str(), strInterfaceName.c_str(), TRUE, pPortSel,
    maxstr, &pEndOfSelection,&Result))
        {
            do
            {
                if(AnsiString(pPortSel)==strPortName) break;
                if(!pEndOfSelection)
                        {
                            if(!VCS_GetPortNameSelection(strDeviceName.c_str(), strProtocolStackName.c_str(), strInterfaceName.c_str(),FALSE, pPortSel, maxstr, &pEndOfSelection,&Result)) break;
                        }
                else {MotorEposDiagnController(TxtDgnContr14); return (-1);}
            } while(1);
        }
    if(MotorEposCheckResult(MotorNum,Result)==(-1)) return (-1);

    DvigMex[n].Handle=VCS_OpenDevice(strDeviceName.c_str(), strProtocolStackName.c_str(),strInterfaceName.c_str(), strPortName.c_str(), &Result);
    if(DvigMex[n].Handle!=0)
        {
            m_KeyHandle1=VCS_OpenSubDevice(DvigMex[n].Handle, strDeviceName.c_str(), ProtocolStackName.c_str(), &Result);
            if (m_KeyHandle1==0)
                {
                    MotorEposCheckResult(MotorNum,  Result);
                    return (-1);
                }
        }
    return (MotorEposCheckResult(MotorNum,Result));
}
//----------------------------------------------------------------------------
//Деинициализация
//----------------------------------------------------------------------------
int MotorEposComDeInit(int KeyCanCom,int MotorNum)
{
    int n=0;
    if (MotorEposCheckStruct(MotorNum,&n)==-1) return(-1);
    if(DvigMex[n].Handle!=0)
        {
            VCS_CloseDevice(DvigMex[n].Handle, &Result);
            DvigMex[n].Handle=0;
            return (MotorEposCheckResult(MotorNum,Result));
        }
    return 0 ;
}
//----------------------------------------------------------------------------
// Инициализация по номеру привода
//----------------------------------------------------------------------------
int MotorEposNumInit(int MotorNum)
{
    const WORD maxstr=100;
    BOOL pEndOfSelection=FALSE;
    char pDeviceNameSel[maxstr] ;
    char pProtocolStackNameSel[maxstr];
    char pInterfaceNameSel[maxstr];
    char pPortSel[maxstr];
    AnsiString ProtocolStackName="CANopen";
    AnsiString strDeviceName;
    AnsiString strProtocolStackName;
    AnsiString strInterfaceName;
    AnsiString strPortName;
    HANDLE m_KeyHandle1;
    int n=0;
    if (MotorEposCheckStruct(MotorNum,&n)==-1) return(-1);
    int COMNumber=DvigMex[n].COMport;

    if (DvigMex[n].CanCom==2)
        {
            strInterfaceName="USB";
            strPortName=strInterfaceName+AnsiString(COMNumber);
            strDeviceName="EPOS2";
            strProtocolStackName="MAXON SERIAL V2";
        }
    else if(DvigMex[n].CanCom==0)
            {
                strInterfaceName="RS232" ;
                strPortName="COM"+AnsiString(COMNumber);
                strDeviceName="EPOS2";
                strProtocolStackName="MAXON_RS232";
            }
    if(VCS_GetDeviceNameSelection(TRUE, pDeviceNameSel,maxstr, &pEndOfSelection, &Result))
        {
            do
            {
                if(AnsiString(pDeviceNameSel)==strDeviceName) break;
                if(!pEndOfSelection)
                        {
                            if(!VCS_GetDeviceNameSelection(FALSE, pDeviceNameSel,maxstr, &pEndOfSelection, &Result)) break;
                        }
                else {MotorEposDiagnController(TxtDgnContr11); return (-1);}
            } while(1);
        }
    if(MotorEposCheckResult(MotorNum,Result)==(-1)) return (-1);

    if(VCS_GetProtocolStackNameSelection(strDeviceName.c_str(), TRUE,pProtocolStackNameSel, maxstr, &pEndOfSelection, &Result))
        {
            do
            {
                if(AnsiString(pProtocolStackNameSel)==strProtocolStackName) break;
                if(!pEndOfSelection)
                        {
                            if(!VCS_GetProtocolStackNameSelection(strDeviceName.c_str(), FALSE,pProtocolStackNameSel, maxstr, &pEndOfSelection, &Result)) break;
                        }
                else {MotorEposDiagnController(TxtDgnContr12); return (-1);}
            } while(1);
        }
    if(MotorEposCheckResult(MotorNum,Result)==(-1)) return (-1);


    if(VCS_GetInterfaceNameSelection(strDeviceName.c_str(), strProtocolStackName.c_str(), TRUE, pInterfaceNameSel, maxstr, &pEndOfSelection, &Result))
        {
            do
            {
                if(AnsiString(pInterfaceNameSel)==strInterfaceName) break;
                if(!pEndOfSelection)
                        {
                            if(!VCS_GetInterfaceNameSelection(strDeviceName.c_str(), strProtocolStackName.c_str(), FALSE, pInterfaceNameSel,maxstr, &pEndOfSelection, &Result)) break;
                        }
                else {MotorEposDiagnController(TxtDgnContr13); return (-1);}
            } while(1);
        }
    if(MotorEposCheckResult(MotorNum,Result)==(-1)) return (-1);




    if(VCS_GetPortNameSelection(strDeviceName.c_str(), strProtocolStackName.c_str(), strInterfaceName.c_str(), TRUE, pPortSel,
    maxstr, &pEndOfSelection,&Result))
        {
            do
            {
                if(AnsiString(pPortSel)==strPortName) break;
                if(!pEndOfSelection)
                        {
                            if(!VCS_GetPortNameSelection(strDeviceName.c_str(), strProtocolStackName.c_str(), strInterfaceName.c_str(),FALSE, pPortSel, maxstr, &pEndOfSelection,&Result)) break;
                        }
                else {MotorEposDiagnController(TxtDgnContr14); return (-1);}
            } while(1);
        }
    if(MotorEposCheckResult(MotorNum,Result)==(-1)) return (-1);

    DvigMex[n].Handle=VCS_OpenDevice(strDeviceName.c_str(), strProtocolStackName.c_str(),strInterfaceName.c_str(), strPortName.c_str(), &Result);
    if(DvigMex[n].Handle!=0)
        {
            m_KeyHandle1=VCS_OpenSubDevice(DvigMex[n].Handle, strDeviceName.c_str(), ProtocolStackName.c_str(), &Result);
            if (m_KeyHandle1==0)
                {
                    MotorEposCheckResult(MotorNum,  Result);
                    return (-1);
                }

        }

    return (MotorEposCheckResult(MotorNum,Result));
}
//----------------------------------------------------------------------------
// Выключение привода
//----------------------------------------------------------------------------
int MotorEposNumDisable(int MotorNum)
{
    int n=0;
    if (MotorEposCheckStruct(MotorNum,&n)==-1) return(-1);
    BOOL pIsEnabled=false;
    if (DvigMex[n].Handle!=0)
        {

            if(!VCS_GetEnableState(DvigMex[n].Handle, (WORD)DvigMex[n].NumContr, &pIsEnabled, &Result))
                {
                    MotorEposCheckResult(MotorNum,  Result);
                    return (-1);
                }
            if (pIsEnabled==1)
                {
                    VCS_SetDisableState(DvigMex[n].Handle,(WORD)DvigMex[n].NumContr,&Result);
                }
        }
    else
        {
            MotorEposDiagnController(TxtDgnContr01);
            return (-1);
        }
    return 0;
}
//----------------------------------------------------------------------------
//Проверка на наличие контроллера
//----------------------------------------------------------------------------
int MotorEposNalDvig(int n)
{
    WORD pSoftwareVersion;
    WORD pApplicationNumber;
    WORD pApplicationVersion;
    WORD pHardwareVersion;

    if(!VCS_GetVersion(DvigMex[n].Handle, (WORD)DvigMex[n].NumContr, &pHardwareVersion,&pSoftwareVersion, &pApplicationNumber, &pApplicationVersion, &Result))
        return (-1);
    return 0;
}
//----------------------------------------------------------------------------
//Включение привода
//----------------------------------------------------------------------------
int MotorEposNumEnable(int MotorNum)
{
    int n=0;
    if (MotorEposCheckStruct(MotorNum,&n)==-1) return(-1);
    BOOL pIsEnabled =false;
    if (DvigMex[n].Handle!=0)
        {
            if(!VCS_GetEnableState(DvigMex[n].Handle,(WORD)DvigMex[n].NumContr,&pIsEnabled, &Result))
                {
    	                MotorEposCheckResult(MotorNum,  Result);
                        return (-1);
                }
            if(!pIsEnabled)
            {
                if(!VCS_SetEnableState(DvigMex[n].Handle,(WORD)DvigMex[n].NumContr,&Result))
                    {
                        MotorEposCheckResult(MotorNum, Result);
                        return (-1);
                    }
            }
        }
    else{MotorEposDiagnController(TxtDgnContr01); return (-1);}
    return 0;
}
//----------------------------------------------------------------------------
//Чтение текущих координат привода
//----------------------------------------------------------------------------
int MotorEposNumReadTekCoord(int MotorNum, double *TekPos)
{
    int n=0;
    if (MotorEposCheckStruct(MotorNum,&n)==-1) return(-1);
    if(MotorEposCheckStateController(n)!=0) return (-1);
    long pPositionIs;
    DWORD pNbOfBytesRead;

        if(!VCS_GetObject(DvigMex[n].Handle, (WORD)DvigMex[n].NumContr, 0x6062, 0x00, &pPositionIs, 4,&pNbOfBytesRead, &Result))
        {
            MotorEposCheckResult(MotorNum, Result);
            return (-1);
        }
    MotorEposRaschMoveCoordPar(MotorNum, (double)pPositionIs, TekPos,  'K',  1);
    return (MotorEposCheckResult(MotorNum,Result));
}
//----------------------------------------------------------------------------
//Чтение заданных координат привода
//----------------------------------------------------------------------------
int MotorEposNumReadZdnCoord(int MotorNum, double *ZdnPos)
{
    int n=0;
    if (MotorEposCheckStruct(MotorNum,&n)==-1) return(-1);
    if(MotorEposCheckStateController(n)!=0) return (-1);
    long pPositionIs ;

    if(!VCS_GetPositionIs(DvigMex[n].Handle, (WORD)DvigMex[n].NumContr, &pPositionIs, &Result))
        {
            MotorEposCheckResult(MotorNum, Result);
            return (-1);
        }

    MotorEposRaschMoveCoordPar(MotorNum, (double)pPositionIs, ZdnPos,  'K',  1);
    return (MotorEposCheckResult(MotorNum,Result));
}
//----------------------------------------------------------------------------
// Сброс ошибок привода (номер привода)
//---------------------------------------------------------------------------
int MotorEposNumClearFaults(int MotorNum)
{
    int n=0;
    if (MotorEposCheckStruct(MotorNum,&n)==-1) return(-1);
    if(!VCS_ClearFault(DvigMex[n].Handle, (WORD)DvigMex[n].NumContr, &Result))
        {
            MotorEposCheckResult(MotorNum, Result);
            return (-1);
        }
    return (MotorEposCheckResult(MotorNum,Result));
}
//---------------------------------------------------------------------------
// Базирование привода (номер привода)
//---------------------------------------------------------------------------
int MotorEposNumBase(int MotorNum,__int8 m_uMode)
{
    int n=0;
    if (MotorEposCheckStruct(MotorNum,&n)==-1) return(-1);
    if(MotorEposCheckStateController(n)!=0) return (-1);
    double TimeOtr = DvigMex[n].TimeOtr;
    BOOL pHomingAttained;
    BOOL pHomingError;
    if(!VCS_ActivateHomingMode(DvigMex[n].Handle, (WORD)DvigMex[n].NumContr,&Result))
        {
            MotorEposCheckResult(MotorNum, Result);
            return (-1);
        }
    if(!VCS_FindHome(DvigMex[n].Handle, (WORD)DvigMex[n].NumContr, m_uMode, &Result))
        {
            MotorEposCheckResult(MotorNum,Result);
            return(-1);
        }
    if(!VCS_WaitForHomingAttained(DvigMex[n].Handle, (WORD)DvigMex[n].NumContr, TimeOtr,&Result))
        {
            MotorEposCheckResult(MotorNum,Result);
            return(-1);
        }
    if(!VCS_GetHomingState(DvigMex[n].Handle, (WORD)DvigMex[n].NumContr, &pHomingAttained, &pHomingError, &Result))
        {
            MotorEposCheckResult(MotorNum,Result);
            return(-1);
        }
    if(!pHomingAttained)
        {
            MotorEposDiagnController(TxtDgnContr06);
            return (-1);
        }
    if(pHomingError)
        {
            MotorEposDiagnController(TxtDgnContr05);
            return (-1);
        }
    return MotorEposCheckResult(MotorNum,Result);
}
//---------------------------------------------------------------------------
// Проверка сбазирован или нет привод
//---------------------------------------------------------------------------
int MotorEposNumStatBase(int MotorNum)
{
    int n=0;
    if (MotorEposCheckStruct(MotorNum,&n)==-1) return(-1);
    if(MotorEposCheckStateController(n)!=0) return (-1);
    BOOL pHomingAttained=false;
    BOOL pHomingError=false;

    if(!VCS_GetHomingState(DvigMex[n].Handle, (WORD)DvigMex[n].NumContr, &pHomingAttained,&pHomingError, &Result))
        {
            MotorEposCheckResult(MotorNum, Result);
            return (-1);
        }
    if(!pHomingAttained) return (-1);

    return 0;
}
//---------------------------------------------------------------------------
// Чтение параметров базирования
//---------------------------------------------------------------------------
int MotorEposNumReadParBase(int MotorNum, double *SpeedSwitch, double *SpeedIndex, double *Uskor,double *HPosition, double *Offset)
{
    int n=0;
    if (MotorEposCheckStruct(MotorNum,&n)==-1) return(-1);
    if(MotorEposCheckStateController(n)!=0) return (-1);
    long HomePosition;
    DWORD pHomingAcceleration;
    DWORD pSpeedSwitch;
    DWORD pSpeedIndex;
    long pHomeOffset;
    unsigned short CurrentThreshold=0;

    if(!VCS_GetHomingParameter(DvigMex[n].Handle,(WORD)DvigMex[n].NumContr,&pHomingAcceleration,
    &pSpeedSwitch,&pSpeedIndex,&pHomeOffset,&CurrentThreshold,&HomePosition,&Result))
        {
            MotorEposCheckResult(MotorNum,Result); return(-1);
        }
    MotorEposRaschMoveCoordPar(MotorNum, (double)pHomingAcceleration, Uskor,  'U',  1);

    MotorEposRaschMoveCoordPar(MotorNum, (double)pSpeedSwitch, SpeedSwitch,  'V',  1);

    MotorEposRaschMoveCoordPar(MotorNum, (double)pSpeedIndex, SpeedIndex,  'V',  1);

    MotorEposRaschMoveCoordPar(MotorNum, (double)pHomeOffset, Offset,  'S',  1);

    MotorEposRaschMoveCoordPar(MotorNum, (double)HomePosition, HPosition,  'S',  1);

    return (MotorEposCheckResult(MotorNum,Result));
}
//---------------------------------------------------------------------------
// Запись параметров базирования
//---------------------------------------------------------------------------
int MotorEposNumWriteParBase(int MotorNum, double SpeedSwitch, double SpeedIndex, double Uskor,double HPosition, double Offset)
{
    int n=0;
    if (MotorEposCheckStruct(MotorNum,&n)==-1) return(-1);
    if(MotorEposCheckStateController(n)!=0) return (-1);
    long HomePosition;
    DWORD pHomingAcceleration;
    DWORD pSpeedSwitch;
    DWORD pSpeedIndex;
    long pHomeOffset;
    double Par2;
    unsigned short CurrentThreshold=0;

    MotorEposRaschMoveCoordPar(MotorNum, Uskor, &Par2,  'U',  0);
    pHomingAcceleration=(DWORD)(Par2+0.5);

    MotorEposRaschMoveCoordPar(MotorNum, SpeedSwitch, &Par2,  'V',  0);
    pSpeedSwitch=(DWORD)(Par2+0.5);

    MotorEposRaschMoveCoordPar(MotorNum, SpeedIndex, &Par2,  'V',  0);
    pSpeedIndex=(DWORD)(Par2+0.5);


    MotorEposRaschMoveCoordPar(MotorNum, Offset, &Par2,  'S',  0);
    pHomeOffset=(long)(Par2+0.5);

    MotorEposRaschMoveCoordPar(MotorNum, HPosition, &Par2,  'S',  0);
    if (Par2>=0)HomePosition=(long)(Par2+0.5);
    else HomePosition=(long)(Par2-0.5);

    if(!VCS_SetHomingParameter(DvigMex[n].Handle, (WORD)DvigMex[n].NumContr, pHomingAcceleration,  pSpeedSwitch, pSpeedIndex,
                                pHomeOffset,  CurrentThreshold,  HomePosition, &Result))
        {
            MotorEposCheckResult(MotorNum,Result);
            return(-1);
        }
    DvigMex[n].Vbaz1=SpeedSwitch;
    DvigMex[n].Vbaz2=SpeedIndex;
    DvigMex[n].Amax=Uskor;
    DvigMex[n].SmBase=Offset;
    DvigMex[n].Kbaz=HPosition;
   return (MotorEposCheckResult(MotorNum,Result));
}
 //---------------------------------------------------------------------------
// Запись параметров движения
//---------------------------------------------------------------------------
int MotorEposNumWriteParMove(int MotorNum, double Speed,double Uskor, double Torm, double Rivok)
{
    int n=0;
    if (MotorEposCheckStruct(MotorNum,&n)==-1) return(-1);
    if(MotorEposCheckStateController(n)!=0) return (-1);
    DWORD ProfileAcceleration;
    DWORD ProfileDeceleration;
    DWORD ProfileVelocity;
    double Par2;

    MotorEposRaschMoveCoordPar(MotorNum, Uskor, &Par2,  'U',  0);
    ProfileAcceleration=(DWORD)(Par2+0.5);

    MotorEposRaschMoveCoordPar(MotorNum, Torm, &Par2, 'U',  0);
    ProfileDeceleration=(DWORD)(Par2+0.5);

    MotorEposRaschMoveCoordPar(MotorNum, Speed, &Par2,  'V',  0);
    ProfileVelocity=(DWORD)(Par2+0.5);

    if(!VCS_SetPositionProfile(DvigMex[n].Handle, (WORD)DvigMex[n].NumContr,ProfileVelocity,ProfileAcceleration,ProfileDeceleration, &Result))
        {
            MotorEposCheckResult(MotorNum,Result); return(-1);
        }
    DvigMex[n].Vmax=Speed;
    DvigMex[n].Amax=Uskor;
    DvigMex[n].Vmin=Torm;
    return MotorEposCheckResult(MotorNum,Result);
}
//---------------------------------------------------------------------------
// Чтение параметров движения
//---------------------------------------------------------------------------
int MotorEposNumReadParMove(int MotorNum, double *Speed, double *Uskor, double *Torm, double *Rivok)
{
    int n=0;
    if (MotorEposCheckStruct(MotorNum,&n)==-1) return(-1);
    if(MotorEposCheckStateController(n)!=0) return (-1);
    DWORD ProfileAcceleration;
    DWORD ProfileDeceleration;
    DWORD ProfileVelocity;

    if(!VCS_GetPositionProfile(DvigMex[n].Handle, (WORD)DvigMex[n].NumContr,&ProfileVelocity,&ProfileAcceleration,&ProfileDeceleration, &Result))
        {
            MotorEposCheckResult(MotorNum,Result); return(-1);
        }
    MotorEposRaschMoveCoordPar(MotorNum, (double)ProfileAcceleration, Uskor,  'U',  1);

    MotorEposRaschMoveCoordPar(MotorNum, (double)ProfileDeceleration, Torm,  'U',  1);

    MotorEposRaschMoveCoordPar(MotorNum, (double)ProfileVelocity, Speed,  'V',  1);

    return MotorEposCheckResult(MotorNum,Result);
}
//----------------------------------------------------------------------------
//Относительное перемещение
//----------------------------------------------------------------------------
int MotorEposNumRelMove(int MotorNum, double DistMove, int Key)
{
    int n=0;
    if (MotorEposCheckStruct(MotorNum,&n)==-1) return(-1);
    if(MotorEposCheckStateController(n)!=0) return (-1);
    double NewPos;
    bool m_oImmediately=TRUE;
    long TargetPosition;
    double Par2;
    double ZdnPos;
    if (Key==1) m_oImmediately=FALSE;

    if (MotorEposNumWaitEndMove(MotorNum)==(-1)) return (-1);

    if(!VCS_ActivateProfilePositionMode(DvigMex[n].Handle, (WORD)DvigMex[n].NumContr,&Result))
        {
            MotorEposCheckResult(MotorNum, Result);
            return (-1);
        }
    double Max=DvigMex[n].Kmax;
    double Min=DvigMex[n].Kmin;
    int KeyErr=0;
    if(MotorEposNumReadZdnCoord( MotorNum, &ZdnPos)==(-1))
        {
            return (-1);
        }
    NewPos=DistMove + ZdnPos;
    if ((NewPos<Min) || (NewPos>Max))
        MotorEposDgnPerMex(MotorNum,Min, Max, NewPos, &KeyErr);
    if(KeyErr!=0) return (-1);
    MotorEposRaschMoveCoordPar(MotorNum, NewPos, &Par2,  'O',  0);
    if (Par2>=0)TargetPosition=(long)(Par2+0.5);
    else TargetPosition=(long)(Par2-0.5);
    if(!VCS_MoveToPosition(DvigMex[n].Handle, (WORD)DvigMex[n].NumContr,TargetPosition,TRUE,m_oImmediately,&Result))
        {
            MotorEposCheckResult(MotorNum, Result);
            return (-1);
        }
    if (MotorEposNumWaitEndMove(MotorNum)==(-1)) return (-1);

    return MotorEposCheckResult(MotorNum, Result);
}
//----------------------------------------------------------------------------
//Абсолютное  перемещение
//----------------------------------------------------------------------------
int MotorEposNumAbsMove(int MotorNum, double DistMove, int Key)
{
    int n=0;
    if (MotorEposCheckStruct(MotorNum,&n)==-1) return(-1);
    if(MotorEposCheckStateController(n)!=0) return (-1);
    int KeyErr=0;
    bool m_oImmediately=TRUE;
    long TargetPosition;
    double Par2;

    if (Key==1) m_oImmediately=FALSE;

    if (MotorEposNumWaitEndMove(MotorNum)==(-1)) return (-1);

    if(!VCS_ActivateProfilePositionMode(DvigMex[n].Handle, (WORD)DvigMex[n].NumContr,&Result))
        {
            MotorEposCheckResult(MotorNum, Result);
            return (-1);
        }
    double Max=DvigMex[n].Kmax;
    double Min=DvigMex[n].Kmin;

    if ((DistMove<Min) || (DistMove>Max))
        MotorEposDgnPerMex(MotorNum,Min, Max, DistMove, &KeyErr);
    if(KeyErr!=0) return (-1);

    MotorEposRaschMoveCoordPar(MotorNum, DistMove, &Par2,  'O',  0);
    if (Par2>=0)TargetPosition=(long)(Par2+0.5);
    else TargetPosition=(long)(Par2-0.5);

    if(!VCS_MoveToPosition(DvigMex[n].Handle, (WORD)DvigMex[n].NumContr,TargetPosition,TRUE,m_oImmediately,&Result))
        {
            MotorEposCheckResult(MotorNum, Result);
            return (-1);
        }

    if (MotorEposNumWaitEndMove(MotorNum)==(-1)) return (-1);

    return MotorEposCheckResult(MotorNum, Result);
}
//----------------------------------------------------------------------------
//Экстренная остановка движения привода
//----------------------------------------------------------------------------
int MotorEposNumStop(int MotorNum)
{
    int n=0;
    if (MotorEposCheckStruct(MotorNum,&n)==-1) return(-1);
    if(MotorEposCheckStateController(n)!=0) return (-1);
    if(!VCS_HaltPositionMovement(DvigMex[n].Handle, (WORD)DvigMex[n].NumContr,&Result))
        {
            MotorEposCheckResult(MotorNum, Result);
            return (-1);
        }
    return MotorEposCheckResult(MotorNum, Result);
}
//----------------------------------------------------------------------------
//Чтение макс. и мин. координат привода
//----------------------------------------------------------------------------
int MotorEposNumReadMaxMin(int MotorNum, double *Max, double *Min)
{
    int n=0;
    if (MotorEposCheckStruct(MotorNum,&n)==-1) return(-1);
    *Max=DvigMex[n].Kmax;
    *Min=DvigMex[n].Kmin;
    return 0;

}
//----------------------------------------------------------------------------
//Сканирование привода
//----------------------------------------------------------------------------
int MotorEposNumSkanMove(int MotorNum, double DistMove)
{
    int n=0;
    if (MotorEposCheckStruct(MotorNum,&n)==-1) return(-1);
    if(MotorEposCheckStateController(n)!=0) return (-1);
    bool m_oImmediately=FALSE;
    long TargetPosition;
    double Par2;
    if (MotorEposNumWaitEndMove(MotorNum)==(-1)) return (-1);
    if(!VCS_ActivateProfilePositionMode(DvigMex[n].Handle, (WORD)DvigMex[n].NumContr,&Result))
        {
            MotorEposCheckResult(MotorNum, Result);
            return (-1);
        }
    double Max=DvigMex[n].Kmax;
    double Min=DvigMex[n].Kmin;
    int KeyErr=0;
    if(MotorEposNumReadZdnCoord( MotorNum, &ZdnPos)==(-1))
        {
            return (-1);
        }
    double NewPos=DistMove + ZdnPos;
    if ((NewPos<Min) || (NewPos>Max))
        MotorEposDgnPerMex(MotorNum,Min, Max, NewPos, &KeyErr);
    if(KeyErr!=0) return (-1);

    MotorEposRaschMoveCoordPar(MotorNum, NewPos, &Par2,  'O',  0);
    if (Par2>=0)TargetPosition=(long)(Par2+0.5);
    else TargetPosition=(long)(Par2-0.5);

    if(!VCS_MoveToPosition(DvigMex[n].Handle, (WORD)DvigMex[n].NumContr,TargetPosition,TRUE,m_oImmediately,&Result))
        {
            MotorEposCheckResult(MotorNum, Result);
            return (-1);
        }
    if (MotorEposNumWaitEndMove(MotorNum)==(-1)) return (-1);

    MotorEposRaschMoveCoordPar(MotorNum, ZdnPos, &Par2,  'O',  0);
    if (Par2>=0)TargetPosition=(long)(Par2+0.5);
    else TargetPosition=(long)(Par2-0.5);

    if(!VCS_MoveToPosition(DvigMex[n].Handle, (WORD)DvigMex[n].NumContr,TargetPosition,TRUE,m_oImmediately,&Result))
        {
            MotorEposCheckResult(MotorNum, Result);
            return (-1);
        }
    if (MotorEposNumWaitEndMove(MotorNum)==(-1)) return (-1);
    return MotorEposCheckResult(MotorNum, Result);
}
//----------------------------------------------------------------------------
//Ожидание окончания движения
//----------------------------------------------------------------------------
int MotorEposNumWaitEndMove(int MotorNum)
{
    int n=0;
    if (MotorEposCheckStruct(MotorNum,&n)==-1) return(-1);
    if(MotorEposCheckStateController(n)!=0) return (-1);
    double TimeOtr = DvigMex[n].TimeOtr; // в сек
    BOOL pTargetReached=0;
    int KolCikl = (int)(TimeOtr*1000./5.);    // кол-во циклов по 5 млсек
    for (int i=0; i<KolCikl; i++)
        {
            if(!VCS_GetMovementState(DvigMex[n].Handle, (WORD)DvigMex[n].NumContr, &pTargetReached,&Result))
                {
                    MotorEposCheckResult(MotorNum, Result);
                    return (-1);
                }
            if (pTargetReached) return 0;               // перемещение закончено
            Sleep(5);
        }
    if (!pTargetReached)
        {
            MotorEposDiagnController(TxtDgnContr08);// "Перемещение не закончено"
            return(-1);
        }  
   return  MotorEposCheckResult(MotorNum, Result);
}
//----------------------------------------------------------------------------
//Чтение состояния привода
//----------------------------------------------------------------------------
int MotorEposNumReadState(int MotorNum, int *State)
{
    int n=0;
    if (MotorEposCheckStruct(MotorNum,&n)==-1) return(-1);
    __int8 pMode=1;
    int statusword_;
    DWORD pNbOfBytesRead;

    if(!VCS_GetObject(DvigMex[n].Handle, (WORD)DvigMex[n].NumContr, 0x6041, 0x00, &statusword_, 2,&pNbOfBytesRead, &Result))
        {
            MotorEposCheckResult(MotorNum, Result);
            return (-1);
        }
    VCS_GetOperationMode(DvigMex[n].Handle, (WORD)DvigMex[n].NumContr,  &pMode, &Result);

    *State=statusword_;
    if (pMode==6)  *State | BIT16 ;
    else if (pMode==1) *State & (~BIT16);



    return MotorEposCheckResult(MotorNum, Result);
}
//----------------------------------------------------------------------------
//Чтение датчиков, заведенных на контроллер привода.
//----------------------------------------------------------------------------
int MotorEposNumReadSensor(int MotorNum, int *Sens)
{
    int n=0;
    if (MotorEposCheckStruct(MotorNum,&n)==-1) return(-1);
    WORD pInputs=0;

    if(!VCS_GetAllDigitalInputs(DvigMex[n].Handle,(WORD)DvigMex[n].NumContr,&pInputs,&Result))
        {
            MotorEposCheckResult(MotorNum, Result);
            return (-1);
        }

    *Sens=pInputs;
    return MotorEposCheckResult(MotorNum, Result);
}
//----------------------------------------------------------------------------
//Проверка результата выполнения команд
//----------------------------------------------------------------------------
int MotorEposCheckResult(int MotorNum, int Result)
{
    switch(Result)
    {
    case 0x00000000:
        strng1[0]='\0';
        break;
    case 0x06020000:
        sprintf(strng1,"Для привода № %d обьекта не существует,неверный индекс или субиндекс\n",MotorNum);
        break;
    case 0x06090011:
        sprintf(strng1,"Для привода № %d субиндекса не существует \n",MotorNum);
        break;
    case 0x05040005:
        sprintf(strng1,"Для привода № %d недостаточно памяти \n",MotorNum);
        break;
    case 0x06010000:
        sprintf(strng1,"Для привода № %d ошибка доступа \n",MotorNum);
        break;
    case 0x06010001:
        sprintf(strng1,"Для привода № %d команда чтения обьекта только для записи \n",MotorNum);
        break;
    case 0x06010002:
        sprintf(strng1,"Для привода № %d записи объекта только для чтения \n",MotorNum);
        break;
    case 0x06040043:
        sprintf(strng1,"Для привода № %d несовместимость общих параметров \n",MotorNum);
        break;
    case 0x06040047:
        sprintf(strng1,"Для привода № %d внутренняя несовместимость в устройстве \n",MotorNum);
        break;
    case 0x06060000:
        sprintf(strng1,"Для привода № %d доступ не выполнен из-за аппаратной ошибки \n",MotorNum);
        break;
    case 0x06090030:
        sprintf(strng1,"Для привода № %d превышен диапазон значений параметра \n",MotorNum);
        break;
    case 0x06090031:
        sprintf(strng1,"Для привода № %d значение записанного параметра слишком велико \n",MotorNum);
        break;
    case 0x06090032:
        sprintf(strng1,"Для привода № %d значение записанного параметра слишком низкое \n",MotorNum);
        break;
    case 0x06090036:
        sprintf(strng1,"Для привода № %d максимальное значение меньше минимального значения \n",MotorNum);
        break;
    case 0x0f00ffc0:
        sprintf(strng1,"Для привода № %d неправильно состояние NMT! \n",MotorNum);
        break;
    case 0x0f00ffbe:
        sprintf(strng1,"Для привода № %d некорректный пароль!\n",MotorNum);
        break;
    case 0x0f00ffbc:
        sprintf(strng1,"Для привода № %d устройство не в сервисном режиме! \n",MotorNum);
        break;
    case 0x0f00ffb9:
        sprintf(strng1,"Для привода № %d ошибка в Node-ID \n",MotorNum);
        break;
    case 0x10000003:
        sprintf(strng1,"Для привода № %d ошибка ключа порта\n",MotorNum);
        break;
    case 0x10000005:
        sprintf(strng1,"Для привода № %d некорректное имя устройства \n",MotorNum);
        break;
    case 0x10000006:
        sprintf(strng1,"Для привода № %d некорректное имя стека протоколов \n",MotorNum);
        break;
    case 0x10000008:
        sprintf(strng1,"Для привода № %d некорректное имя порта\n",MotorNum);
        break;
    case 0x10000007:
        sprintf(strng1,"Для привода № %d некорректное имя интерфейса\n",MotorNum);
        break;
    case 0x05030000:
        sprintf(strng1,"Для привода № %d переключаемый бит не чередуется\n",MotorNum);
        break;
    case 0x05040000:
        sprintf(strng1,"Для привода № %d тайм-аут SDO\n",MotorNum);
        break;
    case 0x05040001:
        sprintf(strng1,"Для привода № %d спецификатор команды сервера/клиента недопустим или неизвестен\n",MotorNum);
        break;
    case 0x05040002:
        sprintf(strng1,"Для привода № %d неверный размер блока\n",MotorNum);
        break;
    case 0x05040003:
        sprintf(strng1,"Для привода № %d неверная последовательность\n",MotorNum);
        break;
    case 0x05040004:
        sprintf(strng1,"Для привода № %d ошибка CRC\n",MotorNum);
        break;
    case 0x06040041:
        sprintf(strng1,"Для привода № %d обьект не может быть сопоставлен с PDO\n",MotorNum);
        break;
    case 0x06040042:
        sprintf(strng1,"Для привода № %d ошибка длины PDO\n",MotorNum);
        break;
    case 0x06070012:
        sprintf(strng1,"Для привода № %d слишком высокий служебный параметр(тип данных или длина)\n",MotorNum);
        break;
    case 0x06070010:
        sprintf(strng1,"Для привода № %d ошибка служебного параметра(тип данных или длина)\n",MotorNum);
        break;
    case 0x06070013:
        sprintf(strng1,"Для привода № %d сервисный параметр слишком низкий\n",MotorNum);
        break;
    case 0x08000000:
        sprintf(strng1,"Для привода № %d общая ошибка\n",MotorNum);
        break;
    case 0x08000020:
        sprintf(strng1,"Для привода № %d ошибка передачи или сохранения данных\n",MotorNum);
        break;
    case 0x08000021:
        sprintf(strng1,"Для привода № %d ошибка локального управления\n",MotorNum);
        break;
    case 0x08000022:
        sprintf(strng1,"Для привода № %d неправильное состояние устройства\n",MotorNum);
        break;
    case 0x0f00ffbf:
        sprintf(strng1,"Для привода № %d недопустимая команда RS232\n",MotorNum);
        break;
    case 0x10000001:
        sprintf(strng1,"Для привода № %d внутренняя ошибка\n",MotorNum);
        break;
    case 0x10000002:
        sprintf(strng1,"Для привода № %d нулевой указатель передан в функцию\n",MotorNum);
        break;
    case 0x10000009:
        sprintf(strng1,"Для привода № %d библиотека не загружена\n",MotorNum);
        break;
    case 0x1000000a:
        sprintf(strng1,"Для привода № %d ошибка команды\n",MotorNum);
        break;
    case 0x1000000b:
        sprintf(strng1,"Для привода № %d Время ожидания истекло\n",MotorNum);
        break;
    case 0x1000000c:
        sprintf(strng1,"Для привода № %d неправильный параметр передан в функцию\n",MotorNum);
        break;
    case 0x1000000d:
        sprintf(strng1,"Для привода № %d команда прервана пользователем\n",MotorNum);
        break;
    case 0x1000000e:
        sprintf(strng1,"Для привода № %d слишком маленький буфер\n",MotorNum);
        break;
    case 0x1000000f:
        sprintf(strng1,"Для привода № %d связь не найдена\n",MotorNum);
        break;
    case 0x10000010:
        sprintf(strng1,"Для привода № %d функция не поддерживается\n",MotorNum);
        break;
    case 0x10000011:
        sprintf(strng1,"Для привода № %d параметр уже используется\n",MotorNum);
        break;
    case 0x10000013:
        sprintf(strng1,"Для привода № %d плохой ключ порта\n",MotorNum);
        break;
    case 0x10000014:
        sprintf(strng1,"Для привода № %d плохой ключ протокола\n",MotorNum);
        break;
    case 0x10000015:
        sprintf(strng1,"Для привода № %d плохой ключ интерфейса\n",MotorNum);
        break;
    case 0x10000016:
        sprintf(strng1,"Для привода № %d плохой ключ порта\n",MotorNum);
        break;
    case 0x10000017:
        sprintf(strng1,"Для привода № %d параметры адреса неверны\n",MotorNum);
        break;
    case 0x10000020:
        sprintf(strng1,"Для привода № %d плохое состояние устройства\n",MotorNum);
        break;
    case 0x10000021:
        sprintf(strng1,"Для привода № %d плохое содержимое файла\n",MotorNum);
        break;
    case 0x10000022:
        sprintf(strng1,"Для привода № %d система не может найти указанный путь\n",MotorNum);
        break;
    case 0x10000024:
        sprintf(strng1,"Для привода № %d ошибка многопоточности\n",MotorNum);
        break;
    case 0x10000026:
        sprintf(strng1,"Для привода № %d ошибка поддержки шлюза\n",MotorNum);
        break;
    case 0x10000027:
        sprintf(strng1,"Для привода № %d ошибка обновленния серийного номера\n",MotorNum);
        break;
    case 0x10000028:
        sprintf(strng1,"Для привода № %d ошибка интерфейса связи\n",MotorNum);
        break;
    case 0x10000029:
        sprintf(strng1,"Для привода № %d ошибка поддержки прошивки\n",MotorNum);
        break;
    case 0x1000002a:
        sprintf(strng1,"Для привода № %d ошибка аппаратного обеспечения файла прошивки\n",MotorNum);
        break;
    case 0x1000002b:
        sprintf(strng1,"Для привода № %d файл прошивки не совпадает или поврежден\n",MotorNum);
        break;
    case 0x20000001:
        sprintf(strng1,"Для привода № %d ошибка открытия интерфейса\n",MotorNum);
        break;
    case 0x20000002:
        sprintf(strng1,"Для привода № %d ошибка закрытия интерфейса\n",MotorNum);
        break;
    case 0x20000003:
        sprintf(strng1,"Для привода № %d интерфейс не открыт\n",MotorNum);
        break;
    case 0x20000004:
        sprintf(strng1,"Для привода № %d ошибка при открытии порта\n",MotorNum);
        break;
    case 0x20000005:
        sprintf(strng1,"Для привода № %d ошибка закрытия порта\n",MotorNum);
        break;
    case 0x20000006:
        sprintf(strng1,"Для привода № %d порт не открыт\n",MotorNum);
        break;
    case 0x20000007:
        sprintf(strng1,"Для привода № %d ошибка сброса порта\n",MotorNum);
        break;
    case 0x20000008:
        sprintf(strng1,"Для привода № %d ошибка настройки параметров порта\n",MotorNum);
        break;
    case 0x20000009:
        sprintf(strng1,"Для привода № %d ошибка настройки режима порта\n",MotorNum);
        break;
    case 0x21000001:
        sprintf(strng1,"Для привода № %d ошибка записи данных порта RS232\n",MotorNum);
        break;
    case 0x21000002:
        sprintf(strng1,"Для привода № %d ошибка чтения данных порта RS232\n",MotorNum);
        break;
    case 0x22000001:
        sprintf(strng1,"Для привода № %d ощибка получения кадра CAN\n",MotorNum);
        break;
    case 0x22000002:
        sprintf(strng1,"Для привода № %d ошибка передачи кадра CAN\n",MotorNum);
        break;
    case 0x23000001:
        sprintf(strng1,"Для привода № %d ошибка записи данных на USB\n",MotorNum);
        break;
    case 0x23000002:
        sprintf(strng1,"Для привода № %d ошибка чтения данных с USB\n",MotorNum);
        break;
    case 0x31000002:
        sprintf(strng1,"Для привода № %d получен плохой CRC \n",MotorNum);
        break;
    case 0x31000003:
        sprintf(strng1,"Для привода № %d получены неверные данные\n",MotorNum);
        break;
    case 0x24000001:
        sprintf(strng1,"Для привода № %d ошибка записи данных HID\n",MotorNum);
        break;
    case 0x24000002:
        sprintf(strng1,"Для привода № %d ошибка чтения данных HID\n",MotorNum);
        break;
    case 0x31000001:
        sprintf(strng1,"Для привода № %d получено отрицательно подтверждение\n",MotorNum);
        break;
    case 0x32000001:
        sprintf(strng1,"Для привода № %d кадр CAN протокола SDO не получен\n",MotorNum);
        break;
    case 0x32000002:
        sprintf(strng1,"Для привода № %d запрошенный кард CAN не получен\n",MotorNum);
        break;
    case 0x32000003:
        sprintf(strng1,"Для привода № %d кадр CAN не получен\n",MotorNum);
        break;
    case 0x34000001:
        sprintf(strng1,"Для привода № %d ошибка заполнения данных\n",MotorNum);
        break;
    case 0x34000002:
        sprintf(strng1,"Для привода № %d ошибка удаления данных\n",MotorNum);
        break;
    case 0x34000003:
        sprintf(strng1,"Для привода № %d получен плохой CRC\n",MotorNum);
        break;
    case 0x34000004:
        sprintf(strng1,"Для привода № %d получен неверный размер данных\n",MotorNum);
        break;
    case 0x34000005:
        sprintf(strng1,"Для привода № %d неверный размер записанных данных\n",MotorNum);
        break;
    case 0x34000006:
        sprintf(strng1,"Для привода № %d серийный фрейм данных не записан\n",MotorNum);
        break;
    case 0x34000007:
        sprintf(strng1,"Для привода № %d серийный фрейм данных не получен\n",MotorNum);
        break;
    case 0x51000001:
        sprintf(strng1,"Для привода № %d получен неверный размер данных\n",MotorNum);
        break;
    case 0x51000007:
        sprintf(strng1,"Для привода № %d конфигурация датчика не поддерживается\n",MotorNum);
        break;
    case 0x51000008:
        sprintf(strng1,"Для привода № %d конфигурация датчиков неизвестна\n",MotorNum);
        break;
    case 0x51000009:
        sprintf(strng1,"Для привода № %d конфигурация не поддерживается\n",MotorNum);
        break;
    case 0x5100000A:
        sprintf(strng1,"Для привода № %d маска цифрового ввода не поддерживается\n",MotorNum);
        break;
    default: sprintf(strng1," Неизвестная ошибка!\r\n Код ошибки = %d",Result); break;
    }
    if (strng1[0]!='\0')
        {
            swDiagn(0,otw_any,0);
            return(-1);
        }
    return(0);
}

int MotorEposRaschMoveCoordPar(int MotorNum, double Par1,double *Par2, char Key , int Type)
{
    int n=0;
    if (MotorEposCheckStruct(MotorNum,&n)==-1) return(-1);
    double koff=1.;
    const double red=84.;//коэффициент редуктора
    const double inc=2048.;//коэффициент двигателя 512 и коэффициент энкодера 4
    const double min=60.;//коэффициент для перевода из минут в секунды;
    const double grad=360.;//360 градусов
    if (Type==0)
       {
       switch(Key)
          {
          case 'O':
          case 'A':
          case 'S':
          case 'K': koff=(inc*red)/grad; break;
          case 'V':
          case 'U':
          case 'R': koff=red*min; break;
          }
       }
    else {
       switch(Key)
          {
          case 'O':
          case 'A':
          case 'S':
          case 'K': koff=grad/(inc*red); break;
          case 'V':
          case 'U':
          case 'R': koff=1./(red*min); break;
          }
       }
    *Par2 =koff*Par1;
    return 0;
}



























