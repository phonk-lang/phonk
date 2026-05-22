std::vector<Token> Lexer::Tokenize(){ 

    std::vector<Token> tokens;

    tokens.reserve(source.size() / 4); 

    while (true){

    Token t = nextToken();

        if (t.type == TokenType::EOF_TOKEN){

            tokens.push_back(std::move(t)); 

            break;}

        if (t.type == TokenType::UNKNOWN){

            throw LexerError(

                "Unexpected error at line: " + std::to_string(t.line) + ", column: " + std::to_string(t.column));}
                
        tokens.push_back(std::move(t));}

    return tokens;}