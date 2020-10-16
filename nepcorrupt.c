#include "nepcorrupt.h"


int main(int argc, char** argv) {
  int status=0; //status will basically contain the error value
  int * informationBool = malloc(7 * sizeof(int)); //just an array of booleans, but since it's pure C, well it's ints instead

  for(int i=0;i<sizeof(informationBool);i++) {
    informationBool[i] = 0; //initialize the boolean array to False
  }

  srand(time(NULL)); //this is useless for now.

  int help = 0; //just an additional boolean for not having any reaction on the inputs if help is shown

  char* ifilename; //a string (char pointer) to the input file name
  char* ofilename; //same for the output file name
  char* op; // op is kept as a string for now and will be converted on the go
  char* rangeStart; // rangeStart will be in hexadecimal, so string too
  char* rangeEnd; // same with rangeEnd obviously
  uint64_t nb; // basically the rom corruptor will corrupt every nb bytes
  uint8_t opNum; // this will be what the op will apply to the bytes concerned
  if(informationBool != NULL) { //just checking if the memory allocation went alright
    if(argc<2) { //just checking if the user put any arguments
      printhelp(); // if they don't put any argument, they must've either forgot the options, or doesn't know yet, so print help
    }
    else {
      for(int i=1;i<argc;i++) { // setting up a loop for each argument
        if(strcmp(argv[i],"-h")==0){ //if there's -h at argv[i], it prints help as well
          printhelp();
          help=1;
          break; //yeah a break would be more efficient, and would save up cycles, at least a little
        } else {
          if(strcmp(argv[i],"-i")==0) { //if there's -i as an option thingy (even if it's needed ik)
            if(!(informationBool[0])) {
              if(argc>i+1) { //check if there's one more argv after
                ifilename=argv[i+1]; //set ifilename (char pointer) to the next argv
                informationBool[0]=1; //and put a boolean to be sure that we don't assign it 2 times
              } else {
                status = 1;
                printf("no input file name, quitting\n");
                break;
              }} else {
                status = 3;
                printf("two occurences of inputs, quitting\n");
                break;
              }
            }
          }
          if(strcmp(argv[i],"-o")==0) { // same as before but with -o
            if(!(informationBool[1])) {
              if(argc>i+1) {
                ofilename=argv[i+1];
                informationBool[1]=1;
              } else {
                status = 1;
                printf("no output file name, quitting\n");
                break;
              }
            } else {
              status = 3;
              printf("two occurences of inputs, quitting\n");
              break;
            }
          }
          if(strcmp(argv[i],"-op")==0) { //same with -op
            if(!(informationBool[2])) {
              if(argc>=i+1) {
                op=argv[i+1];
                informationBool[2]=1;
              } else {
                status = 1;
                printf("no actual operator, quitting\n");
                break;
              }
            } else {
              status = 3;
              printf("two occurences of inputs, quitting\n");
              break;
            }
          }
          if(strcmp(argv[i],"-r")==0) { //this one is kinda different
            if(!(informationBool[3])) { //it checks first for the 4 last bool thingies
              if(argc>i+1) {
                rangeStart = argv[i+1]; //it puts rangeStart to the argv right after -r
                informationBool[3]=1;
              } else {
                status = 1;
                printf("no actual range start value, quitting\n");
                break;
              }
            } else {
              status = 3;
              printf("two occurences of inputs, quitting\n");
              break;
            }
            if(!(informationBool[4])) {
              if(argc>i+2) {
                rangeEnd = argv[i+2];
                informationBool[4]=1;
              } else {
                status = 1;
                printf("no actual range end value, quitting\n");
                break;
              }
            } else {
              status = 3;
              printf("two occurences of inputs, quitting\n");
              break;
            }
            if(!(informationBool[5])) {
              if(argc>i+3) {
                nb = atoi(argv[i+3]); //atoi converts multiple char* into an int, since the type of nb is uint64 it just converts it to uint automatically because numerical formats are both made to be automatically converted from binary, so if i happened to put -1, it would automatically become the max value of a 64 bit value.
                informationBool[5]=1;
              } else {
                status = 1;
                printf("no nb value, quitting\n");
                break;
              }
            } else {
              status = 3;
              printf("two occurences of inputs, quitting\n");
              break;
            }
            if(!(informationBool[6])) {
              if(argc>i+4) {
                opNum = atoi(argv[i+4]);
                informationBool[6]=1;
              } else {
                status = 1;
                printf("no opNum value, quitting\n");
                break;
              }
            } else {
              status = 3;
              printf("two occurences of inputs, quitting\n");
              break;
            }
          }
        }

      if(status||help) { //if there is an error or if the help message was shown, do not do anything under

      } else if(!informationBool[0]) { //if there's some bool not triggered just put error 2 and print a message to tell the user what they forgot
        status = 2;
        printf("no input\n");
      } else if(!informationBool[1]) {
        status = 2;
        printf("no output\n");
      } else if(!informationBool[2]) {
        status = 2;
        printf("no operator\n");
      } else { //else, just do the editing
        status=editfile(ifilename,ofilename,op,hextodec(rangeStart),hextodec(rangeEnd),nb,opNum); // uses my function editfile (prototype: "int editfile(char*,char*,char*,uint64_t,uint64_t,uint8_t,uint8_t);")
        if(status==0) { // if there's no error from editfile, print the message:
          printf("no errors. outputted %s from corrupting %s\n", ofilename, ifilename);
        }
      }
    }
    free(informationBool); //just disallocate informationBool
    informationBool=NULL; //sets the pointer to NULL, just in case.
  } else {
    perror("memory allocation failed."); //just tell the user the allocation of memory failed

  }
  return status; // returns the error value
}

void printhelp() { //it just prints the help message, nothing that important
  printf("here's the help\n");
  printf("\nflags:\n");
  printf("-i: input file name\n");
  printf("-o: output file name\n");
  printf("-op: set operator\n");
  printf("-r: set rangeStart (in hexadecimal, put letters in all caps), rangeStop (in hexadecimal, put letters in all caps), nb (corrupt each nb byte) and opNum (the amount to add/substract/multiply etc.)\n");
  printf("different possible operators:\n\n");
  printf("add: Add\n");
  printf("sub: Substract\n");
  printf("mul: Multiply\n");
  printf("div: Divides\n");
  printf("and: bitwise AND logical operator\n");
  printf("or: bitwise OR logical operator\n");
  printf("xor: bitwise XOR logical operator\n");
  printf("(still not ready) ran: randomized addings\n");
  printf("\n\nyes you do need to put all the flags, they are just here so that you can put your infos in whatever order you want, i know it's not efficient, but it works, i'll work on updates.\n");
  printf("\n\n\nprogram by Nepeta.\n");
}

int editfile(char* ifilename, char* ofilename,char* op,uint64_t rangeStart ,uint64_t rangeEnd , uint8_t nb, uint8_t opNum) {

  printf("ifilename: %s, ofilename: %s, op: %s, rangeStart: %u, rangeEnd: %u, nb: %u, opNum: %u\n", ifilename, ofilename, op, rangeStart, rangeEnd, nb, opNum);

  int opint = getStringHash(op); //it executes another one of my functions, int getStringHash(char*), and then puts the op identificator into a variable.
  int status = 0; //the status must be kepts inside editfile, just in case an error with file handling happens.
  if(opint>0) { //if op was identified, do the whole file handling routine
    FILE* inpfile = fopen(ifilename,"rb");
    FILE* outfile = fopen(ofilename,"wb");
    if(inpfile!=NULL) {
      if(outfile!=NULL) {  
        fseek(inpfile, 0L, SEEK_END); //it goes to the end of the size
        uint64_t size = ftell(inpfile); //then puts the value of size in a variable
        rewind(inpfile); //and then gets back to the start of the file
        if(rangeStart<=rangeEnd) {
          if(rangeEnd<size) {
            int charRead = 0;
            uint8_t nbcnt = 0;

            char character = 0;

            while(fread(&character, 1, 1, inpfile)!=NULL) {
              charRead+=1;
              if(charRead<=rangeEnd && charRead>=rangeStart) {
                nbcnt+=1;
                if(nbcnt==nb) {
                  character = doOp(opint,character,opNum);
                  nbcnt=0;
                }
              } else {
                nbcnt=0;
              }
              fwrite(&character, 1, 1, outfile);
            }
            fclose(inpfile);
            fclose(outfile);
          } else {
            printf("rangeEnd is bigger than the total size of the input file.");
            status = 5;
          }
        } else { //if the range isn't making sense, error
          printf("rangeStart cannot be greater than rangeEnd.\n");
          status = 5;
        }
      } else { //if the input file cannot be opened in rb mode, error
        perror("unable to open output file\n");
        status = 6;
      }
    } else { //if the output file cannot be opened in wb mode, error
      perror("unable to open input file\n");
      status = 7;
    }
  } else { //if the operator is not recognized by getStringHash(char*), error
    printf("the operator is not a handled or existing operator.");
    status = 8;
  }
  return status; //return the error value to the main function
}

int getStringHash(char* op) { //the function getStringHash just converts a char pointer containing the info for op into an identifier. it supports:
  if(strcmp(op,"add")==0) { //add
    return 1;
  } else if (strcmp(op,"sub")==0) {//sub
    return 2;
  } else if (strcmp(op,"mul")==0) {//mul
    return 3;
  } else if (strcmp(op,"div")==0) {//div
    return 4;
  } else if (strcmp(op,"and")==0) {//and
    return 5;
  } else if (strcmp(op,"or")==0) {//or
    return 6;
  } else if (strcmp(op,"xor")==0) {// and xor
    return 7;
  } else if (strcmp(op,"ran")==0) {// ran is still WIP
    return 8;
  } else { //anything else is leading to an error.
    return 0;
  }
}

int doOp(int op,char character, uint8_t opNum) {//doOp executes the operator of opId

  switch(op) {
    case 1:
      return character+opNum;
    case 2:
      return character-opNum;
    case 3:
      return character*opNum;
    case 4:
      return character/opNum;
    case 5:
      return character&&opNum;
    case 6:
      return character||opNum;
    case 7:
      return character^opNum;
    case 8:
      return 0;
  }
}

char* dectohex(uint64_t value) {//dectohex is barely used in the program, to show the size of the file in hexadecimal.
  uint64_t temptest = value;//it just sets a temporary testing value to the value put in dectohex
  int index = 0; //it sets up an index too
  if(value==0) {
    return "0";
  }
  while(temptest!=0) {
    temptest-=temptest%16;//just checks the size of the base 16 hex value to set up the array after
    temptest/=16;//using the modulo method because ln would be way too hard to implement

    index++;
  }
  int* binarray = malloc(index*sizeof(int)); //i'm allocating it now, using index as an indicator of the size
  int sizebinarray = index; //and i set up the size in another variable to use it as a loopsize thingy

  temptest = value; //then i set up temptest to the value again

  index=0;
  while(temptest!=0) {//this is the modulo method again, but this time i just put the values inside my array

    binarray[index] = temptest%16;
    temptest-=binarray[index];
    temptest/=16;
    index++;
  }



  char* returnstr = malloc(sizebinarray/4*sizeof(char)); //i set up the return string, that will basically contain the hex version with the letters
  for(int i=0;i<sizebinarray;i++) {// i do a loop of size sizebinarray
    if(binarray[sizebinarray-i-1] <= 9) { //it takes the last value of binarray first, and goes up to the first one, it checks if each value is strictly lower than 10
      returnstr[i] = binarray[sizebinarray-i-1]+48;//if it is i just convert it to a string number.
    } else {//else i convert it to a letter.
      returnstr[i] = binarray[sizebinarray-i-1]+48+7;
    }
  }
  return returnstr;//and i return the string thingy
}

uint64_t hextodec(char* hexvalue) {//that function does the opposite of the last one
  uint64_t decvalue = 0;
  int* tvalue = malloc(strlen(hexvalue)); //tvalue is just the int version of each hex part of the hex string
  for(int i=0;i<strlen(hexvalue); i++) {
    if(hexvalue[strlen(hexvalue)-i-1]>57) {//it checks if the char is a letter
      tvalue[strlen(hexvalue)-i-1] = hexvalue[strlen(hexvalue)-i-1]-48-7; // it then converts the letter to its numerical value and multiplies it by pow(16,i), which is basically 16^i
      decvalue+=tvalue[strlen(hexvalue)-i-1]*power(16,i); // it adds to decvalue the math thingy i just wrote before
    } else { //else it is a number
      tvalue[strlen(hexvalue)-i-1] = hexvalue[strlen(hexvalue)-i-1]-48; // same as with a letter, but the numerical values are from number chars instead
      decvalue+=tvalue[strlen(hexvalue)-i-1]*power(16,i); //and it adds it to decvalue too.
    }
  }
  return decvalue; //and then i just return the hex value from my maths
}

uint64_t power(int n, int p) {//yeah i won't import math.h just for the pow function, that'd be a waste of memory and disk space
  int total=1; //no need to explain that function, it's kinda obvious tbh
  for(int i = 0;i<p;i++) {
    total*=n;
  }
  if(p==0) {
    total=1;
  }
  return total;
}