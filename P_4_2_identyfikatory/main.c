#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define IN_LINE_COMMENT 1
#define IN_BLOCK_COMMENT 2
#define IN_STRING 4
#define IN_ID 8

#define MAX_ID_LEN 64
#define MAX_IDS 1024

#define TEST 0  // 1 - dla testowania,  0 - dla automatycznej oceny

int index_cmp(const void*, const void*);
int cmp(const void*, const void*);

char tab[MAX_IDS][MAX_ID_LEN];

#define MAX_KEYWORDS 32

char *keywords[MAX_KEYWORDS] = {
	"auto", "break", "case", "char",
	"const", "continue", "default", "do",
	"double", "else", "enum", "extern",
	"float", "for", "goto", "if",
	"int", "long", "register", "return",
	"short", "signed", "sizeof", "static",
	"struct", "switch", "typedef", "union",
	"unsigned", "void", "volatile", "while"
};

#define FIRST_NUMBER (int)'0'
#define LAST_NUMBER (int)'9'

#define FIRST_BIG_LETTER (int)'A'
#define LAST_BIG_LETTER (int)'Z'

#define FIRST_SMALL_LETTER (int)'a'
#define LAST_SMALL_LETTER (int)'z'

int find_idents(FILE *stream)
{
    char c = (char)fgetc(stream);
    char current_string[MAX_ID_LEN] = {0};
    int flag = 0;
    int id_counter = 0;
    int total_ids = 0;
    while(!feof(stream)){
        if(flag == 0 && c == '/'){
            c = (char)fgetc(stream);
            if(c == '/'){
                flag = IN_LINE_COMMENT;
            }
            else if(c == '*'){
                flag = IN_BLOCK_COMMENT;
            }
        } else if(flag == IN_LINE_COMMENT && ( c == '\n' || c == '\r')) {
            flag = 0;
        } else if(flag == IN_BLOCK_COMMENT && c == '*'){
            c = (char)fgetc(stream);
            if(c == '/')
                flag = 0;
        }
        if(c == '"' || c == '\''){
            if (flag == 0)
                flag = IN_STRING;
            else if(flag == IN_STRING) {
                flag = 0;
            }
        }

        if (flag != IN_LINE_COMMENT && flag != IN_BLOCK_COMMENT && flag != IN_STRING){
            if( (c >= FIRST_BIG_LETTER && c <= LAST_BIG_LETTER) ||
                (c >= FIRST_SMALL_LETTER && c <= LAST_SMALL_LETTER) ||
                (c >= FIRST_NUMBER && c <= LAST_NUMBER) || c == '_') {
                current_string[id_counter++] = c;
            } else {
                if(id_counter != 0){
                    int ok = 1;

                    for (int i = 0; i < MAX_KEYWORDS; i++){
                        if(strcmp(keywords[i], current_string) == 0) {
                            ok = 0;
                            break;
                        }
                    }

                    for(int i = 0; i < total_ids; i++){
                        if(strcmp(tab[i], current_string) == 0) {
                            ok = 0;
                            break;
                        }
                    }

                    if(current_string[0] <= LAST_NUMBER)
                        ok = 0;

                    if(ok == 1)
                        strcpy(tab[total_ids++], current_string);

                    memset(current_string, 0, MAX_ID_LEN*sizeof(char));
                    id_counter = 0;
                }
            }
        }

        c = (char)fgetc(stream);
    }

    return total_ids;
}

int main(void) {
	char file_name[40];
	FILE *stream;

  if(TEST)  stream = stdin;
  else {
      scanf("%s",file_name);
      stream = fopen(file_name,"r");
      if(stream == NULL) {
          printf("fopen failed\n");
          return -1;
      }
  }
	printf("%d\n", find_idents(stream));
	return 0;
}

