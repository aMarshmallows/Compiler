// Author: Amasha Rajaguru
// Class: COP 3403
// Date: Friday Oct 14th, 2022

#include <stdio.h>
#include <string.h>
#include <ctype.h>

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

// return 1 if is a keyword, else return 0
int isKeyword(char buffer[])
{
  if (strcmp(buffer, "const") == 0)
  {
    printf("%s\t3\n", buffer);
  }
  else if (strcmp(buffer, "var") == 0)
  {
    printf("%s\t4\n", buffer);
  }
  else if (strcmp(buffer, "procedure") == 0)
  {
    printf("%s\t5\n", buffer);
  }
  else if (strcmp(buffer, "call") == 0)
  {
    printf("%s\t6\n", buffer);
  }
  else if (strcmp(buffer, "begin") == 0)
  {
    printf("%s\t7\n", buffer);
  }
  else if (strcmp(buffer, "end") == 0)
  {
    printf("%s\t8\n", buffer);
  }
  else if (strcmp(buffer, "if") == 0)
  {
    printf("%s\t9\n", buffer);
  }
  else if (strcmp(buffer, "then") == 0)
  {
    printf("%s\t10\n", buffer);
  }
  else if (strcmp(buffer, "else") == 0)
  {
    printf("%s\t11\n", buffer);
  }
  else if (strcmp(buffer, "while") == 0)
  {
    printf("%s\t12\n", buffer);
  }
  else if (strcmp(buffer, "do") == 0)
  {
    printf("%s\t13\n", buffer);
  }
  else if (strcmp(buffer, "read") == 0)
  {
    printf("%s\t14\n", buffer);
  }
  else if (strcmp(buffer, "write") == 0)
  {
    printf("%s\t15\n", buffer);
  }
  else if (strcmp(buffer, "def") == 0)
  {
    printf("%s\t16\n", buffer);
  }
  else if (strcmp(buffer, "null") == 0 || strcmp(buffer, "main") == 0)
  {
    printf("Lexical Analyzer Error: identifiers cannot be named 'null' or 'main'\n");
  }
  else
  {
    return 0;
  }
  return 1;
}

// check if special character
int isSpecialCharacter(char buffer[])
{
  if (buffer[0] == '.')
  {
    printf(".\t17\n");
  }
  else if (buffer[0] == ':')
  {
    if (buffer[1] == '=')
    {
      printf(":=\t18\n");
    }
    else
    {
      return 0;
    }
  }
  else if (buffer[0] == '-')
  {
    printf("-\t19\n");
  }
  else if (buffer[0] == ';')
  {
    printf(";\t20\n");
  }
  else if (buffer[0] == '{')
  {
    printf("{\t21\n");
  }
  else if (buffer[0] ==  '}')
  {
    printf("}\t22\n");
  }
  else if (buffer[0] == '=')
  {
    if (buffer[1] == '=')
    {
      printf("==\t23\n");
    }
    else
    {
      return 0;
    }
  }
  else if (buffer[0] == '<')
  {
    if (buffer[1] == '>')
    {
      printf("<>\t24\n");
    }
    else if (buffer[1] == '\0')
    {
      printf("<\t25\n");
    }
    else if (buffer[1] == '=')
    {
      printf("<=\t26\n");
    }
    else
    {
      return 0;
    }
  }
  else if (buffer[0] == '>')
  {
    if (buffer[1] == '\0')
    {
      printf(">\t27\n");
    }
    else if (buffer[1] == '=')
    {
      printf(">=\t28\n");
    }
    else
    {
      return 0;
    }
  }
  else if (buffer[0] == '+')
  {
    printf("+\t29\n");
  }
  else if (buffer[0] == '*')
  {
    printf("*\t30\n");
  }
  else if (buffer[0] == '/')
  {
    printf("/\t31\n");
  }
  else if (buffer[0] == '(')
  {
    printf("(\t32\n");
  }
  else if (buffer[0] == ')')
  {
    printf(")\t33\n");
  }
  else
  {
    return 0;
  }
  return 1;
}

int main(int argc, char *argv[])
{
  FILE *fp = fopen(argv[1], "r");

  char ch[500] = {'\0'};
  char buffer[12];
  int i = 0;
  int j = 0;

  // read input into ch array
  while (!feof(fp))
  {
    fscanf(fp, "%c", &ch[i]);
    i++;
  }
  int max = i;

  printf("Lexeme List:\nlexeme\ttoken type\n");

  // go through input and analyse
  i = 0;
  while (i < max && ch[i] != '\0')
  {
    if (ch[i] == ' ' || iscntrl(ch[i]))
    {
      i++;
      continue;
    }
    // if first character of new part of a letter
    else if (isalpha(ch[i]))
    {
      // add to buffer while valid
      while (isdigit(ch[i]) || isalpha(ch[i]))
      {
        buffer[j] = ch[i];
        i++;
        j++;
    		if (j == 11)
    			break;
      }

      // if too long for an identifier, write error
      if (j == 11 && (isalpha(ch[i]) || isdigit(ch[i])))
      {
        printf("Lexical Analyzer Error: maximum identifier length is 11\n");
        while (isalpha(ch[i]) || isdigit(ch[i]))
        {
          i++;
        }
      }

      buffer[j] = '\0';

      // check if keyword, else it is an identifier
      if (j != 11 && !isKeyword(buffer))
      {
        printf("%s\t1\n", buffer);
      }
    }
    // check if starts with digit
    else if (isdigit(ch[i]))
    {
      while (isdigit(ch[i]))
      {
        buffer[j] = ch[i];
        i++;
        j++;
    		if (j == 5)
    			break;
      }

      // if has a letter, it is invalid
      if (isalpha(ch[i]))
      {
        printf("Lexical Analyzer Error: identifiers cannot begin with digits\n");
    		while (isdigit(ch[i]) || isalpha(ch[i]))
    			i++;
      }

      // otherwise it is a digit that is longer than 5
      else if (isdigit(ch[i]))
      {
        printf("Lexical Analyzer Error: maximum number length is 5\n");
    		while (isdigit(ch[i]) || isalpha(ch[i]))
    			i++;
      }
      else
      {
		    buffer[j] = '\0';
        printf("%s\t2\n", buffer);
      }
    }
    else
    {
      int isComment = 0;

      if (ispunct(ch[i]))
      {
        // if it is a comment ignore input until the end of the comment
        if (ch[i] == '#' && j == 0)
        {
          isComment = 1;
          while (!iscntrl(ch[i]))
          	i++;
        }

        buffer[j] = ch[i];

        // take next character if there is a possibility of it being 2 characters long
        if (ch[i] == ':' || ch[i] == '<' || ch[i] == '>')
        {
          i+= 1;
          j+= 1;
          buffer[j] = ch[i];
        }
        i++;
        j++;
      }

      buffer[j] = '\0';

      // check if it is a keyword, otherwise it is an error
      if (!isComment && !isSpecialCharacter(buffer))
      {
        printf("Lexical Analyzer Error: invalid symbol\n");
      }
    }

    // reset j to 0
    j = 0;
  }
}
