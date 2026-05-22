#include <iostream>

enum class tolkentype {
    INT, FLOAT, STRING, KEYWORD, IDENTIFIER, PLUS, MINUS, L_PAREN, R_PAREN, L_BRACE, R_BRACE, L_BRACKET, R_BRACKET, SEMICOLON, COMMA, DOT, COLON, NEWLINE, UNKNOWN, EOF_TOKEN
}

struct Token{
tolkentype type;
std::string value;
int line;
}

Class Lexer{
public:
    Lexer(const std::string&source):Source_(source),pos(0),line(1){
    keywords_ = {"int", "float", "string", "bool", "if", "else", "for","return", "true", "false", "print"}}
    
private:
 std::string source
 size_t pos
 int line
 std::unordered_set<std::string> keywords
 char c
 
 void skipwhitespace(){
    while(pos<source.size()){
        c = source[pos];
        if(c == ' ' || c == '\t')
          pos++;
        else
            break;}}
            
void skipblankline()

    while(pos<source.size()){
    c = source[pos];
    if (c == '\n')
        line++
    else 
        break;}}

void skipcomment(){
    if(c == '/' && pos + 1 < source.size() && source[pos + 1] == '/'){
        pos += 2;
        while(pos < source.size() && source[pos] != '\n')
            pos++;
    }
}
void checknext(){
    if(pos < source.size())
        c = source[pos++];
    else
        c = '\0';
}
