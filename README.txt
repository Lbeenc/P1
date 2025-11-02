Implementation notes
--------------------
This submission uses Option 2 (assisted by generative AI). I designed the token set and scanning logic, then used AI to help draft boilerplate and edge‑case checks which I reviewed and edited. The scanner is hand‑written and table‑guided for operators; comments `#...#` are skipped; multi‑char operators ("eq", "neq", "<=", ">=") are recognized without whitespace.


Invocation: P1 [file]
- If [file] is omitted, input is read from stdin (you may also use shell redirection).
- If [file] is provided, the program reads exactly that file.


Architecture:
- `main.cpp` parses arguments and calls `testScanner()`.
- `token.h` defines token enums and the token struct.
- `scanner.h/.cpp` implement `scanner()` and helpers; also expose `testScanner()`.
- `testScanner.cpp` prints one token per line: line, class, instance.
- `Makefile` builds an executable named `P1`.


Limits enforced by spec:
- Identifiers: must start with `id_`, then letters/digits, total length ≤ 8.
- Integers: digits only, length ≤ 8.
- Alphabet: English letters/digits/whitespace and these operators/delims: `eq`, `neq`, `<=`, `<`, `>`, `>=`, `~`, `:`, `;`, `+`, `-`, `*`, `%`, `(`, `)`, `{`, `}`, `[`, `]`. Any other non‑WS character triggers a lexical error.
- Keywords: `start trats while var exit read print if then set func program`.
- Comments: start with `#`, end with `#`, same line, no whitespace inside (per assignment simplification). Comments are skipped entirely and are **not** tokens.


Note on ownership: I understand the code and can explain every function, state, and error path.
