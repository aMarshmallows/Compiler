// Author: Amasha Rajaguru
// Class: COP 3403
// Date: Friday Oct 14th, 2022

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "compiler.h"
int flag_invalid = 0;

lexeme *tokens;
int token_index = 0;

// return 1 if is a keyword, else return 0
int isKeyword(char buffer[], int list_flag)
{
  if (strcmp(buffer, "const") == 0)
  {
    if (list_flag)
      printf("%s\t3\n", buffer);

    tokens[token_index].type = 3;
    token_index++;
  }
  else if (strcmp(buffer, "var") == 0)
  {
    if (list_flag)
      printf("%s\t4\n", buffer);

    tokens[token_index].type = 4;
    token_index++;
  }
  else if (strcmp(buffer, "procedure") == 0)
  {
    if (list_flag)
      printf("%s\t5\n", buffer);

    tokens[token_index].type = 5;
    token_index++;
  }
  else if (strcmp(buffer, "call") == 0)
  {
    if (list_flag)
      printf("%s\t6\n", buffer);

    tokens[token_index].type = 6;
    token_index++;
  }
  else if (strcmp(buffer, "begin") == 0)
  {
    if (list_flag)
      printf("%s\t7\n", buffer);

    tokens[token_index].type = 7;
    token_index++;
  }
  else if (strcmp(buffer, "end") == 0)
  {
    if (list_flag)
      printf("%s\t8\n", buffer);

    tokens[token_index].type = 8;
    token_index++;
  }
  else if (strcmp(buffer, "if") == 0)
  {
    if (list_flag)
      printf("%s\t9\n", buffer);

    tokens[token_index].type = 9;
    token_index++;
  }
  else if (strcmp(buffer, "then") == 0)
  {
    if (list_flag)
      printf("%s\t10\n", buffer);

    tokens[token_index].type = 10;
    token_index++;
  }
  else if (strcmp(buffer, "else") == 0)
  {
    if (list_flag)
      printf("%s\t11\n", buffer);

    tokens[token_index].type = 11;
    token_index++;
  }
  else if (strcmp(buffer, "while") == 0)
  {
    if (list_flag)
      printf("%s\t12\n", buffer);

    tokens[token_index].type = 12;
    token_index++;
  }
  else if (strcmp(buffer, "do") == 0)
  {
    if (list_flag)
      printf("%s\t13\n", buffer);

    tokens[token_index].type = 13;
    token_index++;
  }
  else if (strcmp(buffer, "read") == 0)
  {
    if (list_flag)
      printf("%s\t14\n", buffer);

    tokens[token_index].type = 14;
    token_index++;
  }
  else if (strcmp(buffer, "write") == 0)
  {
    if (list_flag)
      printf("%s\t15\n", buffer);

    tokens[token_index].type = 15;
    token_index++;
  }
  else if (strcmp(buffer, "def") == 0)
  {
    if (list_flag)
      printf("%s\t16\n", buffer);

    tokens[token_index].type = 16;
    token_index++;
  }
  else if (strcmp(buffer, "null") == 0 || strcmp(buffer, "main") == 0)
  {
    printf("Lexical Analyzer Error: identifiers cannot be named 'null' or 'main'\n");
    flag_invalid = 1;
  }
  else
  {
    return 0;
  }
  return 1;
}

// check if special character
int isSpecialCharacter(char buffer[], int list_flag)
{
  if (buffer[0] == '.')
  {
    if (list_flag)
      printf(".\t17\n");

    tokens[token_index].type = 17;
    token_index++;
  }
  else if (buffer[0] == ':')
  {
    if (buffer[1] == '=')
    {
      if (list_flag)
        printf(":=\t18\n");

      tokens[token_index].type = 18;
      token_index++;
    }
    else
    {
      return 0;
    }
  }
  else if (buffer[0] == '-')
  {
    if (list_flag)
      printf("-\t19\n");

    tokens[token_index].type = 19;
    token_index++;
  }
  else if (buffer[0] == ';')
  {
    if (list_flag)
      printf(";\t20\n");

    tokens[token_index].type = 20;
    token_index++;
  }
  else if (buffer[0] == '{')
  {
    if (list_flag)
      printf("{\t21\n");

    tokens[token_index].type = 21;
    token_index++;
  }
  else if (buffer[0] == '}')
  {
    if (list_flag)
      printf("}\t22\n");

    tokens[token_index].type = 22;
    token_index++;
  }
  else if (buffer[0] == '=')
  {
    if (buffer[1] == '=')
    {
      if (list_flag)
        printf("==\t23\n");

      tokens[token_index].type = 23;
      token_index++;
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
      if (list_flag)
        printf("<>\t24\n");

      tokens[token_index].type = 24;
      token_index++;
    }
    else if (buffer[1] == '\0')
    {
      if (list_flag)
        printf("<\t25\n");

      tokens[token_index].type = 25;
      token_index++;
    }
    else if (buffer[1] == '=')
    {
      if (list_flag)
        printf("<=\t26\n");

      tokens[token_index].type = 26;
      token_index++;
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
      if (list_flag)
        printf(">\t27\n");

      tokens[token_index].type = 27;
      token_index++;
    }
    else if (buffer[1] == '=')
    {
      if (list_flag)
        printf(">=\t28\n");

      tokens[token_index].type = 28;
      token_index++;
    }
    else
    {
      return 0;
    }
  }
  else if (buffer[0] == '+')
  {
    if (list_flag)
      printf("+\t29\n");

    tokens[token_index].type = 29;
    token_index++;
  }
  else if (buffer[0] == '*')
  {
    if (list_flag)
      printf("*\t30\n");

    tokens[token_index].type = 30;
    token_index++;
  }
  else if (buffer[0] == '/')
  {
    if (list_flag)
      printf("/\t31\n");

    tokens[token_index].type = 31;
    token_index++;
  }
  else if (buffer[0] == '(')
  {
    if (list_flag)
      printf("(\t32\n");

    tokens[token_index].type = 32;
    token_index++;
  }
  else if (buffer[0] == ')')
  {
    if (list_flag)
      printf(")\t33\n");

    tokens[token_index].type = 33;
    token_index++;
  }
  else
  {
    return 0;
  }
  return 1;
}

// int main(int argc, char *argv[])
lexeme *lex_analyze(int list_flag, char *ch)
{

  tokens = calloc(500, sizeof(lexeme));
  char buffer[12];
  int i = 0;
  int j = 0;

  // // read input into ch array
  // while (!feof(fp))
  // {
  //   fscanf(fp, "%c", &ch[i]);
  //   i++;
  // }
  // int max = i;

  if (list_flag)
    printf("Lexeme List:\nlexeme\ttoken type\n");

  // go through input and analyse
  i = 0;
  while (ch[i] != '\0')
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
        flag_invalid = 1;

        while (isalpha(ch[i]) || isdigit(ch[i]))
        {
          i++;
        }
      }

      buffer[j] = '\0';

      // check if keyword, else it is an identifier
      if (j != 11 && !isKeyword(buffer, list_flag))
      {
        if (list_flag)
          printf("%s\t1\n", buffer);

        tokens[token_index].type = identifier;
        strcpy(tokens[token_index].identifier_name, buffer);
        token_index++;
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
        flag_invalid = 1;
        while (isdigit(ch[i]) || isalpha(ch[i]))
          i++;
      }

      // otherwise it is a digit that is longer than 5
      else if (isdigit(ch[i]))
      {
        printf("Lexical Analyzer Error: maximum number length is 5\n");
        flag_invalid = 1;
        while (isdigit(ch[i]) || isalpha(ch[i]))
          i++;
      }
      else
      {
        buffer[j] = '\0';
        if (list_flag)
          printf("%s\t2\n", buffer);

        tokens[token_index].type = number;
        strcpy(tokens[token_index].number_value, buffer);
        token_index++;
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
          i += 1;
          j += 1;
          buffer[j] = ch[i];
        }
        i++;
        j++;
      }

      buffer[j] = '\0';

      // check if it is a keyword, otherwise it is an error
      if (!isComment && !isSpecialCharacter(buffer, list_flag))
      {
        printf("Lexical Analyzer Error: invalid symbol\n");
        flag_invalid = 1;
      }
    }

    // reset j to 0
    j = 0;
  }

  // return lexeme array if valid
  if (flag_invalid)
  {
    return;
  }
  else
    return tokens;
}
