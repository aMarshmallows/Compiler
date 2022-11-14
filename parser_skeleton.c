#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ARRAY_SIZE 500

typedef enum
{
	identifier = 1,
	number = 2,
	keyword_const = 3,
	keyword_var = 4,
	keyword_procedure = 5,
	keyword_call = 6,
	keyword_begin = 7,
	keyword_end = 8,
	keyword_if = 9,
	keyword_then = 10,
	keyword_else = 11,
	keyword_while = 12,
	keyword_do = 13,
	keyword_read = 14,
	keyword_write = 15,
	keyword_def = 16,
	period = 17,
	assignment_symbol = 18,
	minus = 19,
	semicolon = 20,
	left_curly_brace = 21,
	right_curly_brace = 22,
	equal_to = 23,
	not_equal_to = 24,
	less_than = 25,
	less_than_or_equal_to = 26,
	greater_than = 27,
	greater_than_or_equal_to = 28,
	plus = 29,
	times = 30,
	division = 31,
	left_parenthesis = 32,
	right_parenthesis = 33
} token_type;

typedef enum opcode_name
{
	LIT = 1,
	OPR = 2,
	LOD = 3,
	STO = 4,
	CAL = 5,
	INC = 6,
	JMP = 7,
	JPC = 8,
	SYS = 9,
	WRT = 1,
	RED = 2,
	HLT = 3,
	RTN = 0,
	ADD = 1,
	SUB = 2,
	MUL = 3,
	DIV = 4,
	EQL = 5,
	NEQ = 6,
	LSS = 7,
	LEQ = 8,
	GTR = 9,
	GEQ = 10
} opcode_name;

typedef struct lexeme
{
	token_type type;
	char identifier_name[12];
	int number_value;
	int error_type;
} lexeme;

typedef struct instruction
{
	int op;
	int l;
	int m;
} instruction;

typedef struct symbol
{
	int kind;
	char name[12];
	int value;
	int level;
	int address;
	int mark;
} symbol;

lexeme *tokens;
int token_index = 0;
symbol *table;
int table_index = 0;
instruction *code;
int code_index = 0;

int error = 0;
int level;

void emit(int op, int l, int m);
void add_symbol(int kind, char name[], int value, int level, int address);
void mark();
int multiple_declaration_check(char name[]);
int find_symbol(char name[], int kind);

void print_parser_error(int error_code, int case_code);
void print_assembly_code();
void print_symbol_table();

int program()
{
	add_symbol(3, "main", 0, 0, 0);
	level = -1;
	emit(7, -1, 0);
}

int block(token_index)
{
	int where_our_procedure_is = table[]
}

void constFunct()
{
	char symbol_name[12];
	int number_value;
	bool minus_flag = false;
	token_index++;

	if (tokens[token_index].type != identifier)
	{
		print_parser_error(2, 1);
		return;
	}

	if (multiple_declaration_check(tokens[token_index].identifier_name) != -1)
	{
		print_parser_error(3, 0);
		return;
	}

	strcpy(symbol_name, tokens[token_index].identifier_name);
	token_index++;

	if (tokens[token_index].type != assignment_symbol)
	{
		print_parser_error(4, 1);
		return;
	}

	token_index++;
	if (tokens[token_index].type == minus)
	{
		minus_flag = true;
		token_index++;
	}
	if (tokens[token_index].type != number)
	{
		print_parser_error(5, 0);
		return;
	}

	number_value = tokens[token_type].number_value;
	token_index++;

	if (minus_flag)
	{
		number_value *= -1;
	}

	add_symbol(1, symbol_name, number_value, 0, 0);

	if (tokens[token_index].type != semicolon)
	{
		print_parser_error(6, 1);
	}

	token_index++;
}

int main(int argc, char *argv[])
{
	// variable setup
	int i;
	tokens = calloc(ARRAY_SIZE, sizeof(lexeme));
	table = calloc(ARRAY_SIZE, sizeof(symbol));
	code = calloc(ARRAY_SIZE, sizeof(instruction));
	FILE *ifp;
	int buffer;

	// read in input
	if (argc < 2)
	{
		printf("Error : please include the file name\n");
		return 0;
	}

	ifp = fopen(argv[1], "r");
	while (fscanf(ifp, "%d", &buffer) != EOF)
	{
		tokens[token_index].type = buffer;
		if (buffer == identifier)
			fscanf(ifp, "%s", tokens[token_index].identifier_name);
		else if (buffer == number)
			fscanf(ifp, "%d", &(tokens[token_index].number_value));
		token_index++;
	}
	fclose(ifp);
	token_index = 0;

	// YOUR CODE HERE

	free(tokens);
	free(table);
	free(code);
	return 0;
}

// adds a new instruction to the end of the code
void emit(int op, int l, int m)
{
	code[code_index].op = op;
	code[code_index].l = l;
	code[code_index].m = m;
	code_index++;
}

// adds a new symbol to the end of the table
void add_symbol(int kind, char name[], int value, int level, int address)
{
	table[table_index].kind = kind;
	strcpy(table[table_index].name, name);
	table[table_index].value = value;
	table[table_index].level = level;
	table[table_index].address = address;
	table[table_index].mark = 0;
	table_index++;
}

// marks all of the current procedure's symbols
void mark()
{
	int i;
	for (i = table_index - 1; i >= 0; i--)
	{
		if (table[i].mark == 1)
			continue;
		if (table[i].level < level)
			return;
		table[i].mark = 1;
	}
}

// returns -1 if there are no other symbols with the same name within this procedure
int multiple_declaration_check(char name[])
{
	int i;
	for (i = 0; i < table_index; i++)
		if (table[i].mark == 0 && table[i].level == level && strcmp(name, table[i].name) == 0)
			return i;
	return -1;
}

// returns the index of the symbol with the desired name and kind, prioritizing
// 		symbols with level closer to the current level
int find_symbol(char name[], int kind)
{
	int i;
	int max_idx = -1;
	int max_lvl = -1;
	for (i = 0; i < table_index; i++)
	{
		if (table[i].mark == 0 && table[i].kind == kind && strcmp(name, table[i].name) == 0)
		{
			if (max_idx == -1 || table[i].level > max_lvl)
			{
				max_idx = i;
				max_lvl = table[i].level;
			}
		}
	}
	return max_idx;
}

void print_parser_error(int error_code, int case_code)
{
	switch (error_code)
	{
	case 1:
		printf("Parser Error 1: missing . \n");
		break;
	case 2:
		switch (case_code)
		{
		case 1:
			printf("Parser Error 2: missing identifier after keyword const\n");
			break;
		case 2:
			printf("Parser Error 2: missing identifier after keyword var\n");
			break;
		case 3:
			printf("Parser Error 2: missing identifier after keyword procedure\n");
			break;
		case 4:
			printf("Parser Error 2: missing identifier after keyword call\n");
			break;
		case 5:
			printf("Parser Error 2: missing identifier after keyword read\n");
			break;
		case 6:
			printf("Parser Error 2: missing identifier after keyword def\n");
			break;
		default:
			printf("Implementation Error: unrecognized error code\n");
		}
		break;
	case 3:
		printf("Parser Error 3: identifier is declared multiple times by a procedure\n");
		break;
	case 4:
		switch (case_code)
		{
		case 1:
			printf("Parser Error 4: missing := in constant declaration\n");
			break;
		case 2:
			printf("Parser Error 4: missing := in assignment statement\n");
			break;
		default:
			printf("Implementation Error: unrecognized error code\n");
		}
		break;
	case 5:
		printf("Parser Error 5: missing number in constant declaration\n");
		break;
	case 6:
		switch (case_code)
		{
		case 1:
			printf("Parser Error 6: missing ; after constant declaration\n");
			break;
		case 2:
			printf("Parser Error 6: missing ; after variable declaration\n");
			break;
		case 3:
			printf("Parser Error 6: missing ; after statement in begin-end\n");
			break;
		default:
			printf("Implementation Error: unrecognized error code\n");
		}
		break;
	case 7:
		printf("Parser Error 7: procedures and constants cannot be assigned to\n");
		break;
	case 8:
		switch (case_code)
		{
		case 1:
			printf("Parser Error 8: undeclared identifier used in assignment statement\n");
			break;
		case 2:
			printf("Parser Error 8: undeclared identifier used in call statement\n");
			break;
		case 3:
			printf("Parser Error 8: undeclared identifier used in read statement\n");
			break;
		case 4:
			printf("Parser Error 8: undeclared identifier used in arithmetic expression\n");
			break;
		default:
			printf("Implementation Error: unrecognized error code\n");
		}
		break;
	case 9:
		printf("Parser Error 9: variables and constants cannot be called\n");
		break;
	case 10:
		printf("Parser Error 10: begin must be followed by end\n");
		break;
	case 11:
		printf("Parser Error 11: if must be followed by then\n");
		break;
	case 12:
		printf("Parser Error 12: while must be followed by do\n");
		break;
	case 13:
		printf("Parser Error 13: procedures and constants cannot be read\n");
		break;
	case 14:
		printf("Parser Error 14: missing {\n");
		break;
	case 15:
		printf("Parser Error 15: { must be followed by }\n");
		break;
	case 16:
		printf("Parser Error 16: missing relational operator\n");
		break;
	case 17:
		printf("Parser Error 17: procedures cannot be used in arithmetic\n");
		break;
	case 18:
		printf("Parser Error 18: ( must be followed by )\n");
		break;
	case 19:
		printf("Parser Error 19: invalid expression\n");
		break;
	default:
		printf("Implementation Error: unrecognized error code\n");
	}
}

void print_assembly_code()
{
	int i;
	printf("Assembly Code:\n");
	printf("Line\tOP Code\tOP Name\tL\tM\n");
	for (i = 0; i < code_index; i++)
	{
		printf("%d\t%d\t", i, code[i].op);
		switch (code[i].op)
		{
		case LIT:
			printf("LIT\t");
			break;
		case OPR:
			switch (code[i].m)
			{
			case RTN:
				printf("RTN\t");
				break;
			case ADD: // DO NOT ATTEMPT TO IMPLEMENT THIS, YOU WILL GET A ZERO IF YOU DO
				printf("ADD\t");
				break;
			case SUB: // DO NOT ATTEMPT TO IMPLEMENT THIS, YOU WILL GET A ZERO IF YOU DO
				printf("SUB\t");
				break;
			case MUL: // DO NOT ATTEMPT TO IMPLEMENT THIS, YOU WILL GET A ZERO IF YOU DO
				printf("MUL\t");
				break;
			case DIV: // DO NOT ATTEMPT TO IMPLEMENT THIS, YOU WILL GET A ZERO IF YOU DO
				printf("DIV\t");
				break;
			case EQL: // DO NOT ATTEMPT TO IMPLEMENT THIS, YOU WILL GET A ZERO IF YOU DO
				printf("EQL\t");
				break;
			case NEQ: // DO NOT ATTEMPT TO IMPLEMENT THIS, YOU WILL GET A ZERO IF YOU DO
				printf("NEQ\t");
				break;
			case LSS: // DO NOT ATTEMPT TO IMPLEMENT THIS, YOU WILL GET A ZERO IF YOU DO
				printf("LSS\t");
				break;
			case LEQ: // DO NOT ATTEMPT TO IMPLEMENT THIS, YOU WILL GET A ZERO IF YOU DO
				printf("LEQ\t");
				break;
			case GTR: // DO NOT ATTEMPT TO IMPLEMENT THIS, YOU WILL GET A ZERO IF YOU DO
				printf("GTR\t");
				break;
			case GEQ: // DO NOT ATTEMPT TO IMPLEMENT THIS, YOU WILL GET A ZERO IF YOU DO
				printf("GEQ\t");
				break;
			default:
				printf("err\t");
				break;
			}
			break;
		case LOD:
			printf("LOD\t");
			break;
		case STO:
			printf("STO\t");
			break;
		case CAL:
			printf("CAL\t");
			break;
		case INC:
			printf("INC\t");
			break;
		case JMP:
			printf("JMP\t");
			break;
		case JPC: // DO NOT ATTEMPT TO IMPLEMENT THIS, YOU WILL GET A ZERO IF YOU DO
			printf("JPC\t");
			break;
		case SYS:
			switch (code[i].m)
			{
			case WRT: // DO NOT ATTEMPT TO IMPLEMENT THIS, YOU WILL GET A ZERO IF YOU DO
				printf("WRT\t");
				break;
			case RED:
				printf("RED\t");
				break;
			case HLT:
				printf("HLT\t");
				break;
			default:
				printf("err\t");
				break;
			}
			break;
		default:
			printf("err\t");
			break;
		}
		printf("%d\t%d\n", code[i].l, code[i].m);
	}
	printf("\n");
}

void print_symbol_table()
{
	int i;
	printf("Symbol Table:\n");
	printf("Kind | Name        | Value | Level | Address | Mark\n");
	printf("---------------------------------------------------\n");
	for (i = 0; i < table_index; i++)
		printf("%4d | %11s | %5d | %5d | %5d | %5d\n", table[i].kind, table[i].name, table[i].value, table[i].level, table[i].address, table[i].mark);
	printf("\n");
}
