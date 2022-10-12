// Author: Amasha Rajaguru, COP3402 Fall 2022 HW1
#include <stdio.h>
#include <string.h>

typedef struct instruction
{
  int op;
  int l;
  int m;
} instruction;

// bars array used to help print divider at correct locations in stack to show new AR
int PAS[500] = {0};
int bars[500] = {0};
int bp = 0;
int sp;
int pc;
int halt = 1;
int stackStart = 0;
instruction ir;

// base function to help in calculations
int base(int *pas, int BP, int L)
{
  int arb = BP; // arb = activation record base
  while (L > 0) // find base L levels down
  {
    arb = pas[arb];
    L--;
  }
  return arb;
}

int main(int argc, char const *argv[])
{
  FILE *fp = fopen(argv[1], "r");

  // read input and save in PAS
  while (!feof(fp))
  {
    fscanf(fp, "%d %d %d", &PAS[bp], &(PAS[bp + 1]), &(PAS[bp + 2]));
    bp += 3;
  }

  // set stack pointer to last element from text, bp = 0, start of stack
  sp = bp - 1;
  stackStart = bp;
  pc = 0;

  // print header and start values
  printf("VM Exectution:\n");
  printf("\t\t\t\tPC\tBP\tSP\tstack\n");
  printf("Initial Values:\t\t\t%d\t%d\t%d\n", pc, bp, sp);

  int currPc;
  char opName[4];
  while (halt == 1)
  {
    // fetch cycle, store values in ir
    ir.op = PAS[pc];
    ir.l = PAS[pc + 1];
    ir.m = PAS[pc + 2];

    // set currPc so can print out correct pc lower down
    currPc = pc / 3;
    pc += 3;

    // execute cycle
    switch (ir.op)
    {
    case 1: // LIT	0, M	Pushes a constant value (literal) M onto the stack
      sp = sp + 1;
      PAS[sp] = ir.m;
      strcpy(opName, "LIT");
      break;
    case 2: // Operation to be performed on the data at the top of the stack.
      switch (ir.m)
      {
      case 0:
        strcpy(opName, "RTN");
        sp = bp - 1;
        bp = PAS[sp + 2];
        pc = PAS[sp + 3];
        bars[sp + 1] = 0;
        break;
      case 1:
        strcpy(opName, "ADD");
        PAS[sp - 1] = PAS[sp - 1] + PAS[sp];
        sp = sp - 1;
        break;
      case 2:
        strcpy(opName, "SUB");
        PAS[sp - 1] = PAS[sp - 1] - PAS[sp];
        sp = sp - 1;
        break;
      case 3:
        strcpy(opName, "MUL");
        PAS[sp - 1] = PAS[sp - 1] * PAS[sp];
        sp = sp - 1;
        break;
      case 4:
        strcpy(opName, "DIV");
        PAS[sp - 1] = PAS[sp - 1] / PAS[sp];
        sp = sp - 1;
        break;
      case 5:
        strcpy(opName, "EQL");
        PAS[sp - 1] = PAS[sp - 1] == PAS[sp];
        sp = sp - 1;
        break;
      case 6:
        strcpy(opName, "NEQ");
        PAS[sp - 1] = PAS[sp - 1] != PAS[sp];
        sp = sp - 1;
        break;
      case 7:
        strcpy(opName, "LSS");
        PAS[sp - 1] = PAS[sp - 1] < PAS[sp];
        sp = sp - 1;
        break;
      case 8:
        strcpy(opName, "LEQ");
        PAS[sp - 1] = PAS[sp - 1] <= PAS[sp];
        sp = sp - 1;
        break;
      case 9:
        strcpy(opName, "GTR");
        PAS[sp - 1] = PAS[sp - 1] > PAS[sp];
        sp = sp - 1;
        break;
      case 10:
        strcpy(opName, "GEQ");
        PAS[sp - 1] = PAS[sp - 1] >= PAS[sp];
        sp = sp - 1;
        break;
      }
      break;
    case 3: // Load value to top of stack from stack location at offset M from L levels down
      strcpy(opName, "LOD");
      sp = sp + 1;
      PAS[sp] = PAS[base(PAS, bp, ir.l) + ir.m];
      break;
    case 4: // Store value at top of stack in stack location at offset M from L levels down
      strcpy(opName, "STO");
      PAS[base(PAS, bp, ir.l) + ir.m] = PAS[sp];
      sp = sp - 1;
      break;
    case 5: // Call procedure at code index M (generates new Activation Record and PC = M)
      strcpy(opName, "CAL");
      PAS[sp + 1] = base(PAS, bp, ir.l); // static link (SL)
      PAS[sp + 2] = bp;                  // dynamic link (DL)
      PAS[sp + 3] = pc;                  // return address (RA)
      bars[sp + 1] = 1;
      bp = sp + 1;
      pc = ir.m;
      break;
    case 6: // Allocate M memory words. First four are reserved to SL, DL and RA
      strcpy(opName, "INC");
      sp = sp + ir.m;
      break;
    case 7: // Jump to instruction M (PC = M)
      strcpy(opName, "JMP");
      pc = ir.m;
      break;
    case 8: // Jump to instruction M if top stack element is 0
      strcpy(opName, "JPC");
      if (PAS[sp] == 0)
      {
        pc = ir.m;
      }
      sp = sp - 1;
      break;
    case 9:
      switch (ir.m)
      {
      case 1: // Write the top stack element to the screen
        strcpy(opName, "WRT");
        printf("Output : %d\n", PAS[sp]);
        sp = sp - 1;
        break;
      case 2: // Read in input from the user and store it on top of the stack
        strcpy(opName, "RED");
        sp = sp + 1;
        printf("Input :\n");
        scanf("%d", &PAS[sp]);
        break;
      case 3: // End of program (Set Halt flag to zero)
        strcpy(opName, "HLT");
        halt = 0;
        break;
      }
    }

    // print instruction wrt the given guidelines
    printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\t", currPc, opName, ir.l, ir.m, pc, bp, sp);
    for (int i = stackStart; i <= sp; i++)
    {
      // if new AR, print a divider
      if (bars[i] == 1)
      {
        printf("| ");
      }
      printf("%d", PAS[i]);
      printf(" ");
    }
    printf("\n");
  }
}
