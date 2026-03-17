#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_camel_case(const char *word) {
    if (!word || !word[0] || isupper(word[0])) {
        return 0;
    }
    
    
    // Ищем хотя бы одну заглавную букву внутри слова
    int flag = 0;
    for (int i = 0; word[i]; i++) {
        if (isupper(word[i])) {
            flag =1;

        }
        if (word[i] == '_')return 0;
    }
    return flag; 
}
/*

int is_false(const char *word){
    if (!word || !word[0] || isupper(word[0])) {
        return 1; 
    }
    if (isdigit(word[0])) return 1;
    if (word[0] == '_') return 1;
    return 0;
}
*/

int is_normal(const char *word){
    
    if (!word || !word[0] || isdigit(word[0])) return 0;

    for (int i = 0; word[i]; i++ ){
        if (isupper(word[i])) {
            return 0;
        }
        if (word[i] == '_')return 0;
    }
    return 1;
    
}
// Функция проверки, является ли слово snake_case
int is_snake_case(const char *word) {
    // Проверяем базовые условия
    if (!word || !word[0] || word[0] == '_' || word[strlen(word)-1] == '_') {
        return 0; 
    }
    
    int has_underscore = 0; // Флаг наличия подчеркиваний
    for (int i = 0; word[i]; i++) {
        if (word[i] == '_') {
            // Проверяем на двойное подчеркивание
            if (i > 0 && word[i-1] == '_') {
                return 0; 
            }
            has_underscore = 1; 
        } else if (isupper(word[i])) {
            return 0; 
        }
    }
    return has_underscore; 
}

// Функция преобразования camelCase в snake_case
char *camel_to_snake(const char *camel, int len_word) {
    int j = 0; // Индекс для результирующей строки
    char *snake = (char*)malloc(len_word*2 + 1); 
    if (snake  == NULL) return NULL;
    for (int i = 0; camel[i]; i++) {
        if (isupper(camel[i])) {
            
            if (i > 0) {
                snake[j++] = '_';
            }
            snake[j++] = tolower(camel[i]);
        } else {
            snake[j++] = camel[i];
        }
    }
    snake[j] = '\0'; 
    return snake;
}

// Функция преобразования snake_case в camelCase
char *snake_to_camel(const char *snake, int len_word) {
    int j = 0; 
    int capitalize_next = 0;
    
    char *camel = (char*)malloc(len_word + 1);
    if (camel == NULL) return NULL;

    for (int i = 0; snake[i]; i++) {
        if (snake[i] == '_') {
            capitalize_next = 1; // Следующую букву нужно сделать заглавной
        } else {
            if (capitalize_next) {
                camel[j++] = toupper(snake[i]);
                capitalize_next = 0;
            } else {
                camel[j++] = snake[i];
            }
        }
    }
    camel[j] = '\0'; 
    return camel;

}

// определяем количество строк в файле
int len_file(char const *node){
    FILE *input = fopen(node, "r");
    if (input == NULL) return -1;

    int count_line = 0;
    int ch;
    int has_chars = 0; //для ситуации, когдда файл не заканчивается на пустую строку

    while ((ch = fgetc(input)) != EOF){
        if (ch == '\n') {
            count_line++;
            has_chars = 0;
        }
        has_chars = 1;
    }
    if (has_chars) {
        count_line++;
    }

    fclose(input);
    return count_line;
}



int main_f(const char *input_f, const char *output_f){
    int lenF =  len_file(input_f);
    
    FILE *input = fopen(input_f, "r");
    FILE *output = fopen(output_f, "w");
    if(input == NULL || output == NULL){
        printf("ОШИБКА ПРИ ОТКРЫТИИ ФАЙЛОВ");
        return -1;

    }

    for (int i = 0; i< lenF; i++){
        int len_word = 0;
        int ch;
        // определяем кличество символов в строке, для оптимизации памяти, каждый раз будем выделять место для конкретного слова
        long start_pos = ftell(input);

        while ((ch = fgetc(input)) != EOF && ch != '\n'){
            len_word++;
        }
        
        if (len_word == 0 && ch == EOF) break;
        
        fseek(input, start_pos, SEEK_SET);

        int j = 0;
        
        char *line = (char*)malloc(len_word + 5);
        if (line == NULL) {
            fclose(input);
            fclose(output);
            return -1;
        }
        
        while ((ch = fgetc(input)) != EOF && ch != '\n'){
            line[j++] = ch;
        }
        line[j] = '\0';
        char *result = NULL;
        
        if (is_camel_case(line)){
            result = camel_to_snake(line, len_word);
            if (result) {
                fprintf(output, "%s\n", result);
                free(result);
            }
            else fprintf(output, "**error**\n");
            
        }
        else if (is_snake_case(line)){
            result = snake_to_camel(line, len_word);
            if (result) {
                fprintf(output, "%s\n", result);
                free(result);
            }
            else fprintf(output, "**error**\n");
            
        }
        
        else if (is_normal(line)) fprintf(output, "%s\n", line);
        else fprintf(output ,"**error**\n");



        free(line);
    }
    fclose(input);
    fclose(output);
    return 1;

}

int main(){
    return main_f("node1.txt", "node2.txt");
}