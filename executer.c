#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

float random(int max)
{
    int rnd = rand()%max;
    return rnd;
}
//=====œ≈–≈Ã≈ÕÕ€≈======//
#define MAX_V 32
float VARIABLES[MAX_V]={};
float GET_VARBLE(int POS);
void SET_VARBLE(unsigned char POS,float VALUE);
void DUMP_VARIABLES();
//=====œ≈–≈Ã≈ÕÕ€≈======//

//====—“≈ ===//
#define MAX_STACK 32
float VSTACK[MAX_STACK]={};
unsigned char STACK_POINTER=0;
void ADD_TO_STACK(float VALUE);
float GET_FROM_STACK();
void DUMP_STACK();
//====—“≈ ===//

#define PROGNAME 0x02

//======Ã¿“¿Õ=====//
#define ADD 0x05
#define SUB 0x06
#define MUL 0x07
#define DIV 0x08
#define SQRT 0x09
#define LN 0x0A
#define LOG 0x0B
#define SIN 0x0C
#define COS 0x0D
#define TAN 0x0E
#define ASIN 0x0F
#define ACOS 0x10
#define ATAN 0x11
#define L_SHIFT 0x12
#define R_SHIFT 0x13
//======Ã¿“¿Õ=====//

//====œ≈–≈Ã≈ÕÕ€≈===//
#define SET_VALUE 0x14
#define GET_VALUE 0x15
//====œ≈–≈Ã≈ÕÕ€≈===//

#define GOTO 0x16

//===Œœ≈–¿÷»» —–¿¬Õ≈Õ»ﬂ===//
#define __IF 0x17
#define __FI 0x18
#define EQ 0x19 
#define SM 0x1A
#define BG 0x1B
//===Œœ≈–¿÷»» —–¿¬Õ≈Õ»ﬂ===//

#define READ 0x1C
#define PUSH 0x1D
#define PS 0x1E 
#define NS 0x1F 
#define CAS 0x20 
#define CCR 0x21 
#define DUP 0x22
#define GET_PC 0x023
#define PRINT 0x24
#define SWAP 0x25
#define POP 0x26

//===œŒ–“€===//
#define IPI 0x27
#define OPI 0x28
#define DWH 0x29
#define DWL 0x2A
#define DRP 0x2B
#define AWP 0x2C
#define ARP 0x2D
//===œŒ–“€===//

#define RUN_PROG 0x2E 
#define GET_RAND 0x2F 
#define GO_TO_LABEL 0x30 

//=====◊¿—€=====//
#define LABEL_N 0xFA 
#define END_PROG 0xFF
#define END_WRITE 0xFE
//====œ¿Ãﬂ“‹====//

#define MAX_VRAM 512 
unsigned char VRAM[MAX_VRAM]={};
void CLEAR_VRAM(){for(int i=0;i<512;i++){VRAM[i]=0xFF;}} 
unsigned char GET_FROM_VRAM(short int POS); 
float VGET_VALUE();
//====œ¿Ãﬂ“‹====//

void VM();
float ReadValue();
short int PROG_COUNTER=0;

#define LOOP_EN 1
#define LOOP_DS -1
unsigned char STATUS=LOOP_EN;
void InputFilename();

//==========ƒÀﬂ ›Ã”Àﬂ÷»» œŒ–“Œ¬============//
#define INPUT 0
#define OUTPUT 1
#define LOW 0
#define HIGH 1
unsigned char PORTS_STATE[16];
unsigned char PORTS_SIG[16];
void pinMode(int p,float m)
{
    PORTS_STATE[p]=m;
}
void digitalWrite(int p,float m)
{
    PORTS_SIG[p]=m;
}
void analogWrite(int p,float m)
{
    PORTS_SIG[p]=m;
}
float analogRead(int p)
{
    return PORTS_SIG[p];
}
float digitalRead(int p)
{
    if(PORTS_SIG[p]>0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//==========ƒÀﬂ ›Ã”Àﬂ÷»» œŒ–“Œ¬============//

void init()
{
    CLEAR_VRAM();
    setlocale(LC_ALL, "Russian");
}

int main(int argv, char *args[])
{
    init();
    while(1)
    {
        InputFilename();
        CLEAR_VRAM();
        for(int i=0;i<512;i++)
        {
          VRAM[i]=0xFF;
        }
        PROG_COUNTER=0;
        STATUS=LOOP_EN;
        STACK_POINTER=0;
    }
    return 0;
}
void InputFilename()
{
    char TextToValue[16]={};
    printf("\n:");
    gets(TextToValue);
    LoadFromSDCard(TextToValue);
}
void LoadFromSDCard(char *Fname)
{
    int tmpc=0;
    unsigned char TMPCHAR=0;
    FILE *ptr_file;
    ptr_file =fopen(Fname,"rb");
    if(ptr_file)
    {
        fread(VRAM,sizeof(char),512,ptr_file);
        fclose(ptr_file);
        VM();
    }
    else
    {
        printf("“‡ÍÓ„Ó Ù‡ÈÎ‡ ÌÂ ÒÛ˘ÂÒÚ‚ÛÂÚ.\nFile not founded!");
    }
}

void VM()
{
    if(GET_FROM_VRAM(PROG_COUNTER)==PROGNAME)
    {
        PROG_COUNTER++;
        printf("Program Name:");
        while(GET_FROM_VRAM(PROG_COUNTER)!=0x00)
        {
            printf("%c",GET_FROM_VRAM(PROG_COUNTER));
            PROG_COUNTER++;
        }
        printf("\n");
    }
    float A=0;
    float B=0;
    int AI=0;
    int BI=0;
    char Filename[16]={};
    int FNC=0;
    while(STATUS==LOOP_EN)
    {
        A=0;
        B=0;
        if(STACK_POINTER<0||STACK_POINTER>32){STACK_POINTER=0;}
        switch(GET_FROM_VRAM(PROG_COUNTER))
        {
            case 0x00:
                //NOP
                PROG_COUNTER++;
                break;
            case ADD:
                ADD_TO_STACK(GET_FROM_STACK()+GET_FROM_STACK());
                PROG_COUNTER++;
                break;
            case SUB:
                ADD_TO_STACK(GET_FROM_STACK()-GET_FROM_STACK());
                PROG_COUNTER++;
                break;
            case DIV:
                ADD_TO_STACK(GET_FROM_STACK()/GET_FROM_STACK());
                PROG_COUNTER++;
                break;
            case MUL:
                ADD_TO_STACK(GET_FROM_STACK()*GET_FROM_STACK());
                PROG_COUNTER++;
                break;
            case SQRT:
                ADD_TO_STACK(sqrt(GET_FROM_STACK()));
                PROG_COUNTER++;
                break;
            case LN:
                ADD_TO_STACK(log(GET_FROM_STACK()));
                PROG_COUNTER++;
                break;
            case LOG:
                ADD_TO_STACK(log10(GET_FROM_STACK()));
                PROG_COUNTER++;
                break;
            case SIN:
                ADD_TO_STACK(sin(GET_FROM_STACK()));
                PROG_COUNTER++;
                break;
            case COS:
                ADD_TO_STACK(cos(GET_FROM_STACK()));
                PROG_COUNTER++;
                break;
            case TAN:
                ADD_TO_STACK(tan(GET_FROM_STACK()));
                PROG_COUNTER++;
                break;
            case ASIN:
                ADD_TO_STACK(asin(GET_FROM_STACK()));
                PROG_COUNTER++;
                break;
            case ACOS:
                ADD_TO_STACK(acos(GET_FROM_STACK()));
                PROG_COUNTER++;
                break;
            case ATAN:
                ADD_TO_STACK(atan(GET_FROM_STACK()));
                PROG_COUNTER++;
                break;
            case L_SHIFT:
                AI=abs(GET_FROM_STACK());
                BI=abs(GET_FROM_STACK());
                ADD_TO_STACK(AI<<BI);
                PROG_COUNTER++;
                break;
            case R_SHIFT:
                AI=abs(GET_FROM_STACK());
                BI=abs(GET_FROM_STACK());
                ADD_TO_STACK(AI>>BI);
                PROG_COUNTER++;
                break;
            case SET_VALUE:
                SET_VARBLE(GET_FROM_STACK(),GET_FROM_STACK());
                PROG_COUNTER++;
                break;
            case GET_VALUE:
                A=GET_FROM_STACK();
                B=GET_VARBLE(A);
                ADD_TO_STACK(B);
                PROG_COUNTER++;
                break;
            case CAS:
                for(int tsp=0;tsp<MAX_STACK;tsp++)
                {
                    VSTACK[tsp]=0;
                }
                STACK_POINTER=0;
                PROG_COUNTER++;
                break;
            case PUSH:
                PROG_COUNTER++;
                ADD_TO_STACK(VGET_VALUE());
                PROG_COUNTER++;
                break;
            case READ:
                ADD_TO_STACK(ReadValue());
                PROG_COUNTER++;
                break;
            case DUP:
                A=GET_FROM_STACK();
                ADD_TO_STACK(A);
                ADD_TO_STACK(A);
                PROG_COUNTER++;
                break;
            case PRINT:
                PROG_COUNTER++;
                while(GET_FROM_VRAM(PROG_COUNTER)!=0x00)
                {
                    printf("%c",GET_FROM_VRAM(PROG_COUNTER));
                    PROG_COUNTER++;
                }
                PROG_COUNTER++;
                break;
            case SWAP:
                A=GET_FROM_STACK();
                B=GET_FROM_STACK();
                ADD_TO_STACK(A);
                ADD_TO_STACK(B);
                PROG_COUNTER++;
                break;
            case POP:
                A=GET_FROM_STACK();
                printf("%f\n",A);
                PROG_COUNTER++;
                break;
            case EQ:
                A=GET_FROM_STACK();
                B=GET_FROM_STACK();
                if(A==B)
                {
                    ADD_TO_STACK(0);
                }
                else
                {
                    ADD_TO_STACK(-1);
                }
                PROG_COUNTER++;
                break;
            case SM:
                A=GET_FROM_STACK();
                B=GET_FROM_STACK();
                if(A<B)
                {
                    ADD_TO_STACK(0);
                }
                else
                {
                    ADD_TO_STACK(-1);
                }
                PROG_COUNTER++;
                break;
            case BG:
                A=GET_FROM_STACK();
                B=GET_FROM_STACK();
                if(A>B)
                {
                    ADD_TO_STACK(0);
                }
                else
                {
                    ADD_TO_STACK(-1);
                }
                PROG_COUNTER++;
                break;
            case __IF:
                if(GET_FROM_STACK()==-1)
                {
                    while(GET_FROM_VRAM(PROG_COUNTER)!=__FI)
                    {
                        PROG_COUNTER++;
                    }
                }
                PROG_COUNTER++;
                break;
            case __FI:
                //NOP
                PROG_COUNTER++;
                break;
            case GOTO:
                PROG_COUNTER=GET_FROM_STACK();
                continue;
                break;
            case GET_PC:
                ADD_TO_STACK(PROG_COUNTER);
                PROG_COUNTER++;
                break;
            case IPI:
                AI=GET_FROM_STACK();
                pinMode(AI,INPUT);
                PROG_COUNTER++;
                break;
            case OPI:
                AI=GET_FROM_STACK();
                pinMode(AI,OUTPUT);
                PROG_COUNTER++;
                break;
            case DWH:
                AI=GET_FROM_STACK();
                digitalWrite(AI,HIGH);
                PROG_COUNTER++;
                break;
            case DWL:
                AI=GET_FROM_STACK();
                digitalWrite(AI,LOW);
                PROG_COUNTER++;
                break;
            case DRP:
                AI=GET_FROM_STACK();
                ADD_TO_STACK(digitalRead(AI));
                PROG_COUNTER++;
                break;
            case ARP:
                AI=GET_FROM_STACK();
                ADD_TO_STACK(analogRead(AI));
                PROG_COUNTER++;
                break;
            case AWP:
                AI=GET_FROM_STACK();
                A=GET_FROM_STACK();
                analogWrite(AI,A);
                PROG_COUNTER++;
                break;
            case GET_RAND:
                A=GET_FROM_STACK();
                B=random(A);
                ADD_TO_STACK(B);
                PROG_COUNTER++;
                break;
            case RUN_PROG:
                PROG_COUNTER++;
                while(GET_FROM_VRAM(PROG_COUNTER)!=0x00)
                {
                  Filename[FNC]=GET_FROM_VRAM(PROG_COUNTER);
                  PROG_COUNTER++;
                  FNC++;
                }
                PROG_COUNTER=0;
                LoadFromSDCard(Filename);
                VM();
                break;
            case GO_TO_LABEL:
                AI=0;
                BI=GET_FROM_STACK();
                PROG_COUNTER=0;
                while(1)
                {
                  if(GET_FROM_VRAM(PROG_COUNTER)==LABEL_N)
                  {
                    if(AI==BI)
                    {
                      break;
                    }
                    else
                    {
                      AI++;
                      PROG_COUNTER++;
                    }
                  }
                  else
                  {
                    PROG_COUNTER++;
                  }
                }
                break;
            case LABEL_N:
                PROG_COUNTER++;
                break;
            case END_PROG:
                STATUS=LOOP_DS;
                break;
        }
    }
}

float ReadValue()
{
    char TextToValue[16]={};
    unsigned char Counter=0;
    return atof(gets(TextToValue));
}
float VGET_VALUE()
{
    char TEMP_FLOAT_CHAR[12]={};
    unsigned char TFC_COUNTER=0;
    while(VRAM[PROG_COUNTER]!=0x00)
    {
        TEMP_FLOAT_CHAR[TFC_COUNTER]=VRAM[PROG_COUNTER];
        PROG_COUNTER++;
        TFC_COUNTER++;
        if(VRAM[PROG_COUNTER]==0x00)break;
    }
    return atof(TEMP_FLOAT_CHAR);
}

void DUMP_STACK()
{
    for(unsigned char a=0;a<32;a++)
    {
        if(a==STACK_POINTER)
        {
            printf(">> [%d]=%f\n",a,VSTACK[a]);
        }
        else
        {
            printf("[%d]=%f\n",a,VSTACK[a]);
        }

    }
}

void DUMP_VARIABLES()
{
    for(unsigned char a=0;a<32;a++)
    {
        printf("[%d]=%f\n",a,VARIABLES[a]);
    }
}

unsigned char GET_FROM_VRAM(short int POS)
{
    return VRAM[POS];
}

void ADD_TO_STACK(float VALUE)
{
    if(STACK_POINTER>MAX_STACK)
    {
        STACK_POINTER=0;
    }
    VSTACK[STACK_POINTER]=VALUE;
    STACK_POINTER++;
}
float GET_FROM_STACK()
{
    STACK_POINTER--;
    if(STACK_POINTER<0)
    {
        STACK_POINTER=0;
    }
    return VSTACK[STACK_POINTER];
}


float GET_VARBLE(int POS)
{
    if(POS<0||POS>MAX_V)
    {
        return VARIABLES[0];
    }
    return VARIABLES[POS];
}
void SET_VARBLE(unsigned char POS,float VALUE)
{
    if(POS<0||POS>MAX_V)
    {
        VARIABLES[0]=VALUE;
    }
    VARIABLES[(int) POS]=VALUE;
}
