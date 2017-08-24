Assembler()
char * getNToken (char ** tokBegin, char ** tokEnd);
	// Moves tokBegin and tokEnd to point to beginning and end of token
        // Returns the beginning of the token if a token was found (the
        // same address as tokBegin points to), or null if no token was
        // found.

   void getOpType (char * opcode, char * opType, int * code, int line);
	// Takes opcode (mnemonic name, e.g., "add") and returns
        // opType ('R', 'I', 'J') and code (opcode or funct number).
	// Takes line number as input for printing error messages.

   int  getRegNbr (char * regName, int line);
	// Takes register name (e.g., $t0) and returns register number.
	// Takes line number as input for printing error messages.

   void assembleR (int opcode, char * restOfStmt, int line);
	// Takes opcode (actually funct number in most cases),
	// pointer to the rest of the statement, and line number for
	// printing error messages.
	// Prints I-format instruction to standard output.

   void assembleI (int opcode, char * restOfStmt, int line, LabelTable table);
	// Takes opcode, pointer to the rest of the statement,
	// line number (for printing error messages), and label table.
	// Prints I-format instruction to standard output.
        // (Alternative: label table could be global instead of a param.)

   void assembleJ (int opcode, char * restOfStmt, int line, LabelTable table);
	// Takes opcode, pointer to the rest of the statement,
	// line number (for printing error messages), and label table.
	// Prints J-format instruction to standard output.
        // (Alternative: label table could be global instead of a param.)

   void printBin (int value, int length);
	// Takes a numeric value and prints the binary format to
	// standard output as characters.  The length specifies how
	// many binary digits to print.
	// E.g., printBin (3, 5) would print 00011 to stdout (the binary
        // representation for the number 3, expressed using 5 characters).
