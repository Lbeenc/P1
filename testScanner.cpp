#include "scanner.h"
#include <iostream>
#include <iomanip>


static void printToken(const Token& t) {
std::cout << std::setw(5) << t.line << " "
<< std::setw(20) << tokenName[static_cast<int>(t.id)] << " "
<< t.instance << '\n';
}


int testScanner() {
Token tk = scanner();
while (true) {
printToken(tk);
if (tk.id == TokenID::EOFTk) break;
tk = scanner();
}
return 0;
}
