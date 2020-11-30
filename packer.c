#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

//==============================================//
#define PROGNAME 0x02
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
#define SET_VALUE 0x14
#define GET_VALUE 0x15
#define GOTO 0x16
#define __IF 0x17
#define __FI 0x18
#define EQ 0x19 //Сравниваем последение два значения в стеке, если удовлетворяет условию, то ложит в стек 0, если нет, то -1
#define SM 0x1A
#define BG 0x1B
#define READ 0x1C
#define PUSH 0x1D
#define PS 0x1E
#define NS 0x1F
#define CAS 0x20 //clear all stack
#define CCR 0x21 //clear current
#define DUP 0x22
#define GET_PC 0x023
#define PRINT 0x24
#define SWAP 0x25
#define POP 0x26
#define IPI 0x27 //INIT PORT AS INPUT
#define OPI 0x28//INIT PORT AS OUTPUT
#define DWH 0x29//DigitalWrite High
#define DWL 0x2A//DigitalWrite Low
#define DRP 0x2B//DigitalRead Port
#define AWP 0x2C//Analog Write Port
#define ARP 0x2D//Analog Read Port

#define RUN_PROG 0x2E
#define GET_RAND 0x2F //RANDOM
#define GO_TO_LABEL 0x30 //Поиск и переход к LABEL по номеру в программе
#define LABEL_N 0xFA //LABEL

#define END_PROG 0xFF
#define END_WRITE 0xFE
//==============================================//

char SourceCode[2048*4]={};//Размер исходника(максимальный)
int tmpc=0;//Счетчики
char TMPCHAR=0;//

char OutputBinary[512]={};//Размер выходного файла
int OBC=0;//счетчик

void LoadFileToSC(char *Filename);//Загрузка исходника
void WriteBinFile(); //Запись bin файла

//=====debug=====//
int pname_c = 0;//ProgName counter
int cmd_c = 0;//CMD counter
int out_size = 0;//Size counter
//=====debug=====//

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Rus");
    if(argc==1)
    {
        printf("В командной строке напишите: SBC_Compiler.exe 'filename.txt' , чтобы скопилириовать.\nИли перетащите файл с исходным кодом на этот .exe\n");
        system("pause\n");
        exit(1);
    }
    else
    {
        LoadFileToSC(argv[1]);
    }
	//printf("%s",SourceCode);
    //char SourceCode[2048]={"PUSH '1';PRINT 'INPUT A:';READ;POP;END;@"};
    #define CLS_SC for(int i=0;i<2048;i++){SourceCode[i]=0xFF;}
    #define CLS_OB for(int i=0;i<512;i++){OutputBinary[i]=0xFF;}
    //CLS_SC;
    CLS_OB;
    char TempLine[64]={};
    char TLC=0;
    int CMD_COUNTER=0;
    #define CLS_TL for(int i=0;i<64;i++){TempLine[i]='\0';}
    for(int i=0;SourceCode[i]!='@';i++)
    {
        #define CLEAR_DATA TLC=0;CLS_TL;while(SourceCode[i]!=';'){i++;}
        #define CLEAR_DATA1 TLC=0;CLS_TL;for(int a=0;a!=64;a++){TempLine[a]='\0';}
        TempLine[TLC]=SourceCode[i];
        TLC++;
        if(strcmp(TempLine, "PUSH")==0)
        {
            cmd_c++;

            OutputBinary[OBC]=PUSH;
            OBC++;
            CLEAR_DATA1;
            while(SourceCode[i]!='\''){i++;}
            i++;
            while(SourceCode[i]!='\'')
            {
                OutputBinary[OBC]=SourceCode[i];
                OBC++;
                i++;

                out_size++;
            }
            OutputBinary[OBC]=0x00;
            OBC++;
            out_size++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "GO_LABEL")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=GO_TO_LABEL;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, ":LABEL")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=LABEL_N;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "ADD")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=ADD;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "SUB")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=SUB;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "MUL")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=MUL;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "DIV")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=DIV;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "LN")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=LN;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "LOG")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=LOG;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "SIN")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=SIN;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "COS")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=COS;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "TAN")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=TAN;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "ASIN")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=ASIN;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "ACOS")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=ACOS;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "ATAN")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=ATAN;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "L_SHIFT")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=L_SHIFT;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "R_SHIFT")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=R_SHIFT;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "SET_VALUE")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=SET_VALUE ;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "GET_VALUE")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=GET_VALUE;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "GOTO")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=GOTO;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "__IF")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=__IF;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "__FI")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=__FI;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "EQ")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=EQ;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "SM")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=SM;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "BG")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=BG;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "READ")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=READ;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "DUP")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=DUP;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "CAS")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=CAS;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "GET_PC")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=GET_PC;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "SWAP")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=SWAP;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "POP")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=POP;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "IPI")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=IPI;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "OPI")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=OPI;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "DWH")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=DWH;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "DWL")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=DWL;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "DRP")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=DRP;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "AWP")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=AWP;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "ARP")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=ARP;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "END")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=END_PROG;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "RAND")==0)
        {
            cmd_c++;out_size++;
            OutputBinary[OBC]=GET_RAND;
            OBC++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "PRINT")==0)
        {
            cmd_c++;
            OutputBinary[OBC]=PRINT;
            OBC++;
            CLEAR_DATA1;
            while(SourceCode[i]!='\''){i++;}
            i++;
            while(SourceCode[i]!='\'')
            {
                OutputBinary[OBC]=SourceCode[i];
                OBC++;
                i++;
                out_size++;
            }
            OutputBinary[OBC]=0x00;
            OBC++;
            out_size++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "RUN")==0)
        {
            cmd_c++;
            OutputBinary[OBC]=RUN_PROG;
            OBC++;
            CLEAR_DATA1;
            while(SourceCode[i]!='\''){i++;}
            i++;
            while(SourceCode[i]!='\'')
            {
                OutputBinary[OBC]=SourceCode[i];
                OBC++;
                i++;
                out_size++;
            }
            OutputBinary[OBC]=0x00;
            OBC++;
            out_size++;
            CLEAR_DATA;
        }
        else if(strcmp(TempLine, "PROGNAME")==0)
        {
            pname_c++;
            cmd_c++;
            OutputBinary[OBC]=PROGNAME;
            OBC++;
            CLEAR_DATA1;
            while(SourceCode[i]!='\''){i++;}
            i++;
            while(SourceCode[i]!='\'')
            {
                OutputBinary[OBC]=SourceCode[i];
                OBC++;
                i++;
                out_size++;
            }
            OutputBinary[OBC]=0x00;
            OBC++;
            out_size++;
            CLEAR_DATA;
        }

    }
    WriteBinFile();
    printf("Размер:%d\nКол-во команд:%d\nКол-во progname:%d\n",out_size,cmd_c,pname_c);
    system("pause\n");
    return 0;
}

void LoadFileToSC(char *Filename)//Загрузка исходника
{
    FILE *ptr_file;
    ptr_file =fopen(Filename,"r");
    while(1)
    {
        fscanf(ptr_file,"%c",&TMPCHAR);
        //SourceCode[tmpc]=TMPCHAR;
        if(TMPCHAR=='@')
        {
            SourceCode[tmpc]='@';
            break;
        }
        else if(TMPCHAR=='\n' || TMPCHAR=='\t')
        {
            continue;
            //pass
        }
        SourceCode[tmpc]=TMPCHAR;
        tmpc++;
    }
	fclose(ptr_file);
}

void WriteBinFile()
{
    FILE *ptr;
    ptr = fopen("ex.sbc","w+b");  // r for read, b for binary

    char TEMP=0;
    for(int i=0;i<OBC;i++)
    {
        TEMP=OutputBinary[i];
        fwrite(&TEMP,sizeof(char),1,ptr); // read 10 bytes to our buffer
    }
    fclose(ptr);
}
