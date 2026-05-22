#include <iostream>
#include<string>
#include<unordered_set>



enum class tolkentype {
    INT, FLOAT, STRING, KEYWORD, IDENTIFIER, PLUS, MINUS, L_PAREN, R_PAREN, L_BRACE, R_BRACE, L_BRACKET, R_BRACKET, SEMICOLON, COMMA, DOT, COLON, NEWLINE, UNKNOWN, EOF_TOKEN
};

struct Token{
tolkentype type;
std::string value;
int line;
};

class Lexer{
public:
    Lexer(const std::string&source_):source_(source_),pos_(0),line_(1){
    keywords_ = {"int", "float", "string", "bool", "if", "else", "for", "return", "true", "false", "print"};}
    
private:
 std::string source_;
 size_t pos_;
 int line_;
 std::unordered_set<std::string> keywords_;
 char c = '\0';
 
void skipwhitespace(){
    while(pos_<source_.size()){
        c = source_[pos_];
        if(c == ' ' || c == '\t'){
          pos_++;}
        else{
            break;}}}
            
void skipblankline(){

    while(pos_<source_.size()){
    c = source_[pos_];
    if (c == '\n'){
        line_++;
        pos_++;}
    else {
        break;}}

void skipcomment(){
    if(c == '/' && pos_ + 1 < source_.size() && source_[pos_ + 1] == '/'){
        pos_ += 2;
        while(pos_ < source_.size() && source_[pos_] != '\n')
            pos_++;}}

void checknext(){
    if(pos_ < source_.size()){
        c = source_[pos_++];}
    else{
        c = '\0';}}
};
