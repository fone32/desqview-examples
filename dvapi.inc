
;  DESQview 2.26 API interfaces
;  converted to FASM by ACP based on Quarterdeck DVAPI

;***************************************************************
;
;  Function numbers (AX values) for the @CALL interface
;
;***************************************************************

DVC_PAUSE       EQU     1000H
DVC_PRINTC      EQU     1003H
DVC_GETBIT      EQU     1013H
DVC_FREEBIT     EQU     1014H
DVC_SETBIT      EQU     1015H
DVC_ISOBJ       EQU     1016H
DVC_LOCATE      EQU     1018H
DVC_SOUND       EQU     1019H
DVC_OSTACK      EQU     101AH
DVC_BEGINC      EQU     101BH
DVC_ENDC        EQU     101CH
DVC_STOP        EQU     101DH
DVC_START       EQU     101EH
DVC_DISPEROR    EQU     101FH
DVC_PGMINT      EQU     1021H
DVC_POSWIN      EQU     1023H
DVC_GETBUF      EQU     1024H
DVC_USTACK      EQU     1025H
DVC_POSTTASK    EQU     102BH
DVC_NEWPROC     EQU     102CH
DVC_KMOUSE      EQU     102DH

DVC_COMMONMEM   EQU     1104H                   ; (2.0)
DVC_CONVENMEM   EQU     1105H                   ; (2.0)
DVC_EXPANDMEM   EQU     1106H                   ; (2.0)
DVC_APPNUM      EQU     1107H
DVC_DBGPOKE     EQU     110AH
DVC_APILEVEL    EQU     110BH
DVC_GETMEM      EQU     110CH
DVC_PUTMEM      EQU     110DH
DVC_FINDMAIL    EQU     110EH
DVC_PUSHKEY     EQU     1110H
DVC_JUSTIFY     EQU     1111H
DVC_CSTYLE      EQU     1112H

DVC_GETCRIT     EQU     1113H                   ; NEW (2.2)
DVC_OBJTYPE     EQU     1114H                   ; NEW (2.2)
DVC_SETERROR    EQU     1115H                   ; NEW (2.2)
DVC_GETERROR    EQU     1116H                   ; NEW (2.2)
DVC_ASSERTMAP   EQU     1117H                   ; NEW (2.2)
DVC_GETCOMMON   EQU     1119H                   ; NEW (2.23)
DVC_PUTCOMMON   EQU     111AH                   ; NEW (2.23)
DVC_ENTERC      EQU     111CH                   ; NEW (2.23)
DVC_PUTKEY      EQU     111DH                   ; NEW (2.23)
DVC_SCRNINFO    EQU     111EH                   ; NEW (2.23)
DVC_DOSUSER     EQU     111FH                   ; NEW (2.23)
DVC_DISPATCHINT EQU     1120H                   ; NEW (2.26)
DVC_ASSERTVIR   EQU     1121H                   ; NEW (2.26)
DVC_PROCESSMEM  EQU     1122H                   ; NEW (2.26)

DVC_DVPRESENT   EQU     0FFFFH
DVC_SHADOW      EQU     0FFFEH
DVC_UPDATE      EQU     0FFFDH

;***************************************************************
;
;  Message numbers (BH values) for the @SEND interface
;
;***************************************************************

DVM_HANDLE      EQU     00H
DVM_NEW         EQU     01H
DVM_FREE        EQU     02H
DVM_ADDR        EQU     03H
DVM_DIR         EQU     03H
DVM_CONNECT     EQU     03H                     ; NEW (2.26)
DVM_READ        EQU     04H
DVM_APPLY       EQU     04H
DVM_WRITE       EQU     05H

DVM_SETPRI      EQU     06H                     ; NEW (2.2)
DVM_GETPRI      EQU     07H                     ; NEW (2.2)

DVM_SIZEOF      EQU     08H
DVM_LEN         EQU     09H
DVM_ADDTO       EQU     0AH
DVM_SUBFROM     EQU     0BH
DVM_OPEN        EQU     0CH
DVM_CLOSE       EQU     0DH
DVM_ERASE       EQU     0EH
DVM_STATUS      EQU     0FH
DVM_EOF         EQU     10H
DVM_AT          EQU     11H
DVM_SETSCALE    EQU     11H
DVM_SETNAME     EQU     11H
DVM_READN       EQU     12H
DVM_GETSCALE    EQU     12H
DVM_REDRAW      EQU     13H
DVM_SETESC      EQU     14H
DVM_LOCK        EQU     14H

DVM_SETFLAGS    EQU     15H                     ; NEW (2.2)
DVM_GETFLAGS    EQU     16H                     ; NEW (2.2)

;***************************************************************
;
;  Alias numbers (BL values) for the @SEND interface
;
;***************************************************************

DVA_TOS         EQU     00H
DVA_ME          EQU     01H
DVA_MAILTOS     EQU     02H
DVA_MAILME      EQU     03H
DVA_KEYTOS      EQU     04H
DVA_KEYME       EQU     05H
DVA_OBJQTOS     EQU     06H
DVA_OBJQME      EQU     07H
DVA_WINDOW      EQU     08H
DVA_MAILBOX     EQU     09H
DVA_KEYBOARD    EQU     0AH
DVA_TIMER       EQU     0BH
DVA_OBJECTQ     EQU     0CH                     ; NEW (2.20)
DVA_OWNERTOS    EQU     0CH                     ; NEW (2.26)
DVA_OWNERME     EQU     0DH                     ; NEW (2.26)
DVA_POINTER     EQU     0FH
DVA_PANEL       EQU     10H


