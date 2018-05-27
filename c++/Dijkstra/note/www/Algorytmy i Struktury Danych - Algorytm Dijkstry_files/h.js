// Kolorowanie sk�adni w C++, Pascalu, Basicu, Javascript i Asemblerze
// (C)2011 mgr Jerzy Wa�aszek
//--------------------------------------------
// Wywo�anie z ustawionymi znacznikami:
// <pre id="pas_n"|"cpp_n"|"bas_n"|"jsc_n"|"asm_n">
// pcba()
//--------------------------------------------


function isAlpha(x,lng)
{
  switch(lng)
  {
    case "p" : return (x >= "0" && x <= "9") || (x >= "A" && x <= "Z") ||
                      (x >= "a" && x <= "z") || ("_#$".indexOf(x) >= 0)
    case "c" :
    case "j" : return (x >= "0" && x <= "9") || (x >= "A" && x <= "Z") ||
                      (x >= "a" && x <= "z") || (x == "_")
    case "b" : return (x >= "0" && x <= "9") || (x >= "A" && x <= "Z") ||
                      (x >= "a" && x <= "z") || ("_$".indexOf(x) >= 0)
    case "a" : return (x >= "0" && x <= "9") || (x >= "A" && x <= "Z") ||
                      (x >= "a" && x <= "z") || ("_$?%.@".indexOf(x) >= 0)
  }
}

function isDigit(x,lng)
{
  switch(lng)
  {
    case "p" : return x == '#' || x == '$' || (x >= '0' && x <= '9')
    case "c" :
    case "j" :
    case "a" : 
    case "b" : return x >= '0' && x <= '9'
  }
}

function highlight(obj,lng)
{
  var t = obj.innerHTML + " "
  var keys

  switch(lng)
  {
    case "p" : keys = "and array as begin case class const constructor destructor div do " +
                      "downto else end end. except file finally for function goto if " +
                      "implementation in inherited interface is mod not object of on or " +
                      "packed procedure program property raise record repeat set shl " +
                      "shr then threadvar to try type unit until uses var while with xor"
               break

    case "c" : keys = "asm auto bool break case catch char class const const_cast " +
                      "continue default delete do double dynamic_cast else enum " +
                      "explicit extern false float for friend goto if inline int " +
                      "long mutable namespace new operator private protected " +
                      "public register reinterpret_cast return short signed " +
                      "sizeof static static_cast struct switch template this throw " +
                      "true try typedef typeid typename union unsigned using " +
                      "virtual void volatile wchar_t while"
               break
    case "b" : keys = "$DYNAMIC $INCLUDE $LANG $STATIC ABS ACCESS ACOS ADD ALIAS ALLOCATE " +
                      "ALPHA AND ANDALSO ANY APPEND AS ASC ASIN ASM ASSERT ASSERTWARN " +
                      "ATAN2 ATN BASE BEEP BIN BINARY BIT BITRESET BITSET BLOAD BSAVE " +
                      "BYREF BYTE BYVAL CALL CALLOCATE CASE CAST CBYTE CDBL CDECL CHAIN " +
                      "CHDIR CHR CINT CIRCLE CLEAR CLNG CLNGINT CLOSE CLS COLOR COM " +
                      "COMMAND COMMON CONDBROADCAST CONDCREATE CONDDESTROY CONDSIGNAL " +
                      "CONDWAIT CONS CONST CONSTRUCTOR CONTINUE COS CPTR CSHORT CSIGN " +
                      "CSNG CSRLIN CUBYTE CUINT CULNG CULNGINT CUNSG CURDIR CUSHORT " +
                      "CUSTOM CVD CVI CVL CVLONGINT CVS CVSHORT DATA DATE DATEADD DATEDIFF " +
                      "DATEPART DATESERIAL DATEVALUE DAY DEALLOCATE DECLARE DEFBYTE " +
                      "DEFDBL DEFINT DEFLNG DEFLONGINT DEFSHORT DEFSNG DEFSTR DEFUBYTE " +
                      "DEFUINT DEFULONGINT DEFUSHORT DELETE DESTRUCTOR DIM DIR DO DOUBLE DRAW " +
                      "DYLIBFREE DYLIBLOAD DYLIBSYMBOL DYNAMIC ELSE ELSEIF ENCODING END " +
                      "ENUM ENVIRON EOF EQV ERASE ERFN ERL ERMN ERR ERROR ESCAPE EXEC " +
                      "EXEPATH EXIT EXP EXPLICIT EXPORT EXTERN FIELD FILEATTR FILECOPY " +
                      "FILEDATETIME FILEEXISTS FILELEN FIX FLIP FOR FORMAT FRAC FRE " +
                      "FREEFILE FUNCTION GET GETJOYSTICK GETKEY GETMOUSE GOSUB GOTO HEX " +
                      "HIBYTE HIWORD HOUR IF IIF IMAGECONVERTROW IMAGECREATE IMAGEDESTROY " +
                      "IMAGEINFO IMP IMPORT INKEY INP INPUT INSTR INSTRREV INT INTEGER IS " +
                      "ISDATE KILL LBOUND LCASE LEFT LEN LET LIB LINE LOBYTE LOC LOCAL " +
                      "LOCATE LOCK LOF LOG LONG LONGINT LOOP LOWORD LPOS LPRINT LPT LSET " +
                      "LTRIM MID MINUTE MKD MKDIR MKI MKL MKLONGINT MKS MKSHORT MOD MONTH " +
                      "MONTHNAME MULTIKEY MUTEXCREATE MUTEXDESTROY MUTEXLOCK MUTEXUNLOCK " +
                      "NAKED NAME NAMESPACE NEW NEXT NOGOSUB NOKEYWORD NOT NOW OCT OFFSETOF ON " +
                      "ERROR OPEN OPERATOR OPTION OR ORELSE OUT OUTPUT OVERLOAD PAINT " +
                      "PALETTE PASCAL PCOPY PEEK PIPE PMAP POINT POINTER POKE POS PRESERVE " +
                      "PRESET PRINT PRIVATE PROCPTR PROPERTY PROTECTED PSET PTR PUBLIC PUT " +
                      "RANDOM RANDOMIZE READ REALLOCATE REDIM REM RESET RESTORE RESUME " +
                      "RETURN RGB RGBA RIGHT RMDIR RND RSET RTRIM RUN SADD SCOPE SCREEN " +
                      "SCREENCONTROL SCREENCOPY SCREENEVENT SCREENGLPROC SCREENINFO " +
                      "SCREENLIST SCREENLOCK SCREENPTR SCREENRES SCREENSET SCREENSYNC " +
                      "SCREENUNLOCK SCRN SECOND SEEK SELECT SETDATE SETENVIRON SETMOUSE " +
                      "SETTIME SGN SHARED SHELL SHL SHORT SHR SIN SINGLE SIZEOF SLEEP " +
                      "SPACE SPC SQR STATIC STDCALL STEP STICK STOP STR STRIG STRING STRPTR " +
                      "SUB SWAP SYSTEM TAB TAN THEN THIS THREADCREATE THREADWAIT TIME TIMER " +
                      "TIMESERIAL TIMEVALUE TO TRANS TRIM TYPE TYPEOF UBOUND UBYTE UCASE " +
                      "UINTEGER ULONG ULONGINT UNION UNLOCK UNSIGNED UNTIL USHORT USING VAL " +
                      "VALINT VALLNG VALUINT VALULNG VAR VARPTR VA_ARG VA_FIRST VA_NEXT VIEW " +
                      "WAIT WBIN WCHR WEEKDAY WEEKDAYNAME WEND WHEX WHILE WIDTH WINDOW " +
                      "WINDOWTITLE WINPUT WITH WOCT WRITE WSPACE WSTR WSTRING XOR YEAR " +
                      "ZSTRING DEFINE ENDIF ENDMACRO IFDEF IFNDEF INCLIB INCLUDE LIBPATH " +
                      "LANG MACRO PRAGMA UNDEF"
               break
    case "j" : keys = "abstract boolean break byte case catch char class const continue " +
                      "debugger default delete do double else enum export extends false " +
                      "final finally float for function goto if implements import in  " +
                      "instanceof int interface long native new null package private " +
                      "protected public return short static super switch synchronized this " +
                      "throw throws transient true try typeof var void volatile while with"
               break
    case "a" : keys = "EAX AX AH AL EBX BX BH BL ECX CX CH CL EDX DX DH DL SI ESI DI EDI BP EBD " +
                      "SP ESP IP EIP CS DS SS ES FS GS AAA AAD AAM AAS ADC ADD AND " +
                      "ARPL BOUND BSF BSR BSWAP BT BTC BTR BTS CALL CBW CDQ CLC CLD CLI CLTS CMC " +
                      "CMP CMPS CMPXCHNG CWD CWDE DAA DAS DEC DIV ENTER ESC HLT IDIV IMUL IN INC " +
                      "INS INT INTO INVD INVLPG IRET IRETD JA JAE JB JBE JC JCXZ JE JG JGE JL " +
                      "JLE JMP JNA JNAE JNB JNBE JNC JNE JNG JNGE JNL JNLE JNO JNP JNS JNZ JO " +
                      "JP JPE JPO JS JZ JCXZ JECXZ LAHF LAR LDS LEA LEAVE LES LFS LGDT LIDT LGS " +
                      "LLDT LMSW LOCK LODS LOOP LOOPE LOOPZ LOOPNZ LOOPNE LSL LSS LTR MOV MOVS " +
                      "MOVSX MOVZX MUL NEG NOP NOT OR OUT OUTS POP POPA POPAD POPF POPFD " +
                      "PUSH PUSHA PUSHAD PUSHF PUSHFD RCL RCR " +
                      "REP REPE REPZ REPNE REPNZ RET RETF ROL ROR SAHF SAL SHL SAR SBB SCAS SETAE " +
                      "SETNB SETB SETNAE SETBE SETNA SETE SETZ SETNE SETNZ SETL SETNGE SETGE SETNL " +
                      "SETLE SETNG SETG SETNLE SETS SETNS SETC SETNC SETO SETNO SETP SETPE SETNP " +
                      "SETPO SGDT SIDT SHL SHR SHLD SHRD SLDT SMSW STC STD STOS STR SUN TEST VERR " +
                      "VERW WAIT FWAIT WBINVD XCHG XLAT XLATB XOR " +

                      "%OUT .186 .286 .286P .287 .386 .386P .387 .486 .486P .8086 .8087 .ALPHA "+
                      ".BREAK .CODE .CONST .CREF .DATA .DATA? .DOSSEG .ELSE .ELSEIF .ENDIF .ENDW " +
                      ".ERR .ERR1 .ERR2 .ERRB .ERRDEF .ERRDIF .ERRDIFI .ERRE .ERRIDN .ERRIDNI " +
                      ".ERRNB .ERRNDEF .ERRNZ .EXIT .FARDATA .FARDATA? .IF .LALL .LFCOND .LIST " +
                      ".LISTALL .LISTIF .LISTMACRO .LISTMACROALL .MODEL .MSFLOAT .NO87 .NOCREF " +
                      ".NOLIST .NOLISTIF .NOLISTMACRO .RADIX .REPEAT .UNTIL .SALL .SEQ .SFCOND " +
                      ".STACK .STARTUP .TFCOND .UNTIL .UNTILCXZ .WHILE .XALL .XCREF .XLIST " +

                      "ALIGN ASSUME BYTE CATSTR COMM COMMENT DB DD DF DOSSEG DQ DT DUP DW DWORD " +
                      "ECHO ELSE ELSEIF ELSEIF1 ELSEIF2 ELSEIFB ELSEIFDEF ELSEIFDEF ELSEIFE " +
                      "ELSEIFIDN ELSEIFNB ELSEIFNDEF END ENDIF ENDM ENDP ENDS EQU EVEN EXITM " +
                      "EXTERN EXTRN EXTERNDEF FOR FORC FWORD GOTO GROUP IF IF1 IF2 IFB IFDEF " +
                      "IFDIF IFDIFI IFE IFIDN IFIDNI IFNB IFNDEF INCLUDE INCLUDELIB INSTR INVOKE " +
                      "IRP IRPC LABEL LOCAL MACRO NAME OPTION ORG PAGE POPCONTEXT PROC PROTO PTR " +
                      "PUBLIC PURGE PUSHCONTEXT QWORD REAL4 REAL8 REAL10 RECORD REPEAT REPT " +
                      "SBYTE SDWORD SEGMENT SIZESTR STRUC STRUCT SUBSTR SUBTITLE SUBTTL SWORD " +
                      "TBYTE TEXTEQU TITLE TYPEDEF UNION WHILE WORD"
                break
  }
  
  keys = keys.split(" ")

  var s = ""
  var w = ""
  var ww
  var c_m = 0 // komentarz blokowy
  var c_s = 0 // komentarz wierszowy 
  var k_w = 0 // litera�
  var p_p = 0 // preprocesor
  var t_q = 0 // tekst w cudzys�owie
  var t_a = 0 // tekst w apostrofie
  var h_e = 0 // kod HTML
  var h_m = 0 // znacznik HTML
  var t_i = 0 // ignorowanie tekstu do ko�ca wiersza
  var c,i
  
  
  for(i = 0; i < t.length; i++)
  {

    c = t.charAt(i)

    //
    // Specjalny kod HTML &nazwa;
    //

    if(h_e)
    {
       if(c == ";") h_e = 0
    }

    // 
    // Znacznik HTML
    //

    else if(h_m)
    {
       if(c == ">") h_m = 0
    }

    //
    // ignorowanie reszty tekstu do ko�ca wiersza
    //

    else if(t_i)
    {
      if(c == "\n") t_i = 0
    }

    //
    // Komentarz blokowy
    //

    else if(c_m)
    {
       if( (lng == "p" && c == "}") ||
         ( (lng == "c" || lng == "j") && c == "/" && t.charAt(i-1) == "*") || 
           (lng == "b" && c == "/" && t.charAt(i-1) == "'"))
       {
         c_m = 0
         s += c + "</span>"
         continue
       }
    }

    //
    // Komentarz jednowierszowy
    //

    else if(c_s) 
    {
       if(c == "\n")
       {
          c_s = 0
          s += "</span>"
       }
    }

    //
    // Preprocesor
    //

    else if(p_p)
    {
       if(c == "\n")
       {
          p_p = 0
          s += "</span>"
       }
    }

    //
    // Tekst w cudzys�owach
    //

    else if(t_q)
    {
       if(c == "\\" && lng != "a")
       {
         if(t.charAt(i+1) == "\\" || t.charAt(i+1) == '"' || t.charAt(i+1) == "'")
         {
            s += c + t.charAt(i+1)
            i++
            continue
         }
       }
       else if(c == '"')
       {
         t_q = 0
         s += '"</span>'
         continue
       }
    }

    //
    // Tekst w apostrofach
    //

    else if(t_a)
    {
      if(c == "\\" && lng != "a")
      {
        if(t.charAt(i+1) == "\\" || t.charAt(i+1) == '"' || t.charAt(i+1) == "'")
        {
           s += c + t.charAt(i+1)
           i++
           continue
        }
      }
      else if(c == "'")
      {
        t_a = 0
        s += "'</span>"
        continue
      }
    }

    //
    // Instrukcja, zmienna, liczba
    //

    else if(k_w) // s�owo - instrukcja, zmienna, liczba
    {
      if(isAlpha(c,lng))
      {
        w += c
        continue
      }
      else
      {
        k_w = 0

        if(lng=="b" || lng=="a") ww = w.toUpperCase()
        else if(lng == "p") ww = w.toLowerCase()
        else ww = w

        if(isDigit(w.charAt(0),lng))
        {
           s += '<span class="n">' + w + '</span>'
           i--
           continue
        }
        else if(lng == "b" && (s.substr(s.length-5) == "&amp;" && (ww.charAt(0) == "H" ||
                ww.charAt(0) == "O" || ww.charAt(0) == "B")))
        {
          s = s.substr(0,s.length-5)
          s += '<span class="n">&amp;' + ww + '</span>'
          i--
          continue
        }
        else if(lng == "b" && w == "_") s += w
        else
        {
           q = -1
           for(j = 0; j < keys.length; j++)
             if(ww == keys[j])
             {
               q = j
               break
             }
           if(q >= 0)
           {
             if(lng == "b")
             {
               if(s.charAt(s.length-1) == "#") // preprocesor
               {
                 p_p = 1
                 s = s.substr(0,s.length-1)
                 s += '<span class="pp">#' + ww
               }
               else  // zwyk�a instrukcja
               {
                 w = w.toLowerCase()
                 w = ww.charAt(0) + w.substr(1)
                 s += '<span class="i">' + w + '</span>'
                 if(w == "Rem")
                 {
                   c_s = 1
                   s += '<span class="c">'
                 }
               }
             }
             else if(lng == "a")
             {
                if(q < 224) s += '<span class="pp">' + ww.toLowerCase() + '</span>'
                else s += '<span class="i">' + ww + '</span>'
                if(ww == "INCLUDE" || ww == "INCLUDELIB") t_i = 1
                else if(ww == "OPTION" || ww == ".MODEL")
                {
                   p_p = 1
                   s += '<span class="pp">'
                }
             }
             else
             {
               s += '<span class="i">' + w + '</span>'
               i--
               continue
             }
           }
           else
           {
             s += '<span class="v">' + w + '</span>'
             i--
             continue
           }
        }        
      }
    }

    //
    // Rozpoznanie komentarza blokowego lub wierszowego
    //

    else if((lng == "c" || lng == "j") && c == "/")
    {
       if(t.charAt(i+1) == "*")
       {
         c_m = 1
         s += '<span class="c">'
       }
       else if(t.charAt(i+1) == "/")
       {
         c_s = 1
         s += '<span class="c">'
       }
    }
    
    else if((lng == "p" && c == "/" && t.charAt(i+1) == "/") ||
            (lng == "b" && c == "'") || (lng == "a" && c == ";"))
    {
      c_s = 1
      s += '<span class="c">'
    }
    else if((lng == "p" && c == "{") || (lng == "b" && c == "/" && t.charAt(i+1) == "'"))
    {
      c_m = 1
      s += '<span class="c">'
    }

    //
    // Rozpoznanie instrukcji preprocesora
    //

    else if(lng == "c" && c == "#")
    {
       p_p = 1
       s += '<span class="pp">'
    }

    //
    // Rozpoznanie tekstu w cudzys�owach - z wyjatkiem sekwencji \"
    //

    else if(c == '"')
    {
      if(lng == "a" || (lng != "p" && c == '"' && t.charAt(i-1) != "\\"))
      {
        t_q = 1
        s += '<span class="t">'
      }
    }
    //
    // Rozpoznanie tekstu w apostrofach
    //

    else if(c == "'")
    {
      t_a = 1
      s += '<span class="t">'
    }
    
    //
    // Rozpoznanie litera�u
    //
    
    else if(isAlpha(c,lng))
    {
      k_w = 1
      w = c
      continue
    }
    
    //
    // Rozpoznanie specjalnego kodu HTML &nazwa;
    //

    if(c == "&") h_e = 1

    //
    // Rozpoznanie znacznika HTML
    //
    
    if(c == "<") h_m = 1

    s += c
  }

  if(c_m) s += "</span>"
  if(c_s) s += "</span>"
  if(p_p) s += "</span>"
  if(t_q || t_a) s += "</span>"
  if(h_e) s += ";"
  if(h_m) s += ">"

  obj.innerHTML = "<pre>" + s + "</pre>"
}


// Funkcja rozsy�owa
//------------------

function pcba()
{
  var preElements = document.getElementsByTagName("pre")
  var i
  for(i = 0; i < preElements.length; i++)
  {
    var s_id = preElements[i].id
    var s = s_id.substr(0,3)
    if(s == "pas" || s == "cpp" || s == "bas" || s == "jsc" || s == "asm")
      highlight(preElements[i],s.charAt(0))
  }
}