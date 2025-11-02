#include "scanner.h"
int c = peekc();
if (!std::isalpha(c)) {
lexError("unexpected non-letter where a word token was expected");
}
// Special handling for identifiers starting with id_
if (c == 'i') {
// Peek ahead 3 chars to see if "id_"
int save1 = getc_and_track(); // 'i'
int save2 = peekc();
ungetc(save1, SRC);
(void)save2;
// Safer: read a small buffer to test prefix without consuming
char buf[4] = {0};
int c1 = fgetc(SRC); int c2 = fgetc(SRC); int c3 = fgetc(SRC);
if (c1 != EOF) ungetc(c3, SRC);
if (c2 != EOF) ungetc(c2, SRC);
if (c1 != EOF) ungetc(c1, SRC);
if (c1=='i' && c2=='d' && c3=='_') {
return lexIdentifierOrKeyword();
}
}
// Otherwise collect contiguous letters (keyword candidate)
std::string w;
while (std::isalpha(peekc())) {
w.push_back(static_cast<char>(getc_and_track()));
if (w.size() > 16) break; // safety; keywords are short
}
if (KEYWORDS.count(w)) {
return Token{TokenID::KW_tk, w, LINE};
}
// Also allow alphabetic operator eq/neq here if multi-op missed
if (w == "eq" || w == "neq") {
return Token{TokenID::OP_tk, w, LINE};
}
lexError("invalid word token '" + w + "'");
}
}


void initScanner(FILE* in) {
SRC = in ? in : stdin;
LINE = 1;
}


Token scanner() {
skipWhitespace();
int c = peekc();
if (c == EOF) {
return Token{TokenID::EOFTk, "", LINE};
}


Token tk{TokenID::ERR_tk, "", LINE};


// Multi-char operators first: eq, neq, <=, >=
if (tryMultiOp(tk)) return tk;


c = peekc();
if (c == EOF) return Token{TokenID::EOFTk, "", LINE};


if (isDigit(c)) {
return lexNumber();
}
if (std::isalpha(c)) {
return lexWordOrError();
}


// Single-char operator/delimiter
if (SINGLE.count(static_cast<char>(c))) {
getc_and_track();
std::string s(1, static_cast<char>(c));
return Token{TokenID::OP_tk, s, LINE};
}


// Two-char look for "<>"? Not in spec. Only <=, >= handled above.


// Unknown character in alphabet
if (std::isspace(c)) {
// should have been skipped; but just in case
getc_and_track();
return scanner();
}


std::string bad(1, static_cast<char>(getc_and_track()));
lexError("unrecognized character '" + bad + "'");
}
