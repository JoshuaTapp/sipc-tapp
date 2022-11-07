grammar TIP;
// Grammar for Moeller and Schwartzbach's Tiny Imperative Language (TIP)

////////////////////// TIP Programs //////////////////////////

program: (function)+;

function:
	nameDeclaration '(' (nameDeclaration (',' nameDeclaration)*)? ')' '{' (
		declaration*
	) (statement*) returnStmt '}';

////////////////////// TIP Declarations /////////////////////////

declaration: KVAR nameDeclaration (',' nameDeclaration)* ';';

nameDeclaration: IDENTIFIER;

////////////////////// TIP Expressions //////////////////////////

/*
 Expressions in TIP are ordered to capture precedence. We adopt the C convention that orders
 operators as: postfix, unary, multiplicative, additive, relational, and equality

 NB: # creates rule label that can be accessed in visitor

 ANTLR4 can automatically refactor direct left-recursion so we place all recursive rules as options
 in a single rule. This means that we have some complex rules here that might otherwise be separated
 out, e.g., funAppExpr, and that we can't factor out other useful concepts, e.g., defining a rule
 for the subset of expressions that can be used as an l-value. We prefer a clean grammar, which
 simplifies AST construction, and work around these issues elsewhere in the compiler, e.g.,
 introducing an assignable expr weeding pass.
 */

expr:
	// Precendence 1
	expr '(' (expr (',' expr)*)? ')'	# funAppExpr
	| expr '.' IDENTIFIER				# accessExpr
	| expr LSBR expr RSBR				# arraySubscriptExpr

	// Precendence 2: prefix unary expressions
	| LEN expr			# arrayLengthExpr
	| '*' expr			# deRefExpr
	| op = LNOT expr	# logicalNotExpr
	| '&' expr			# refExpr
	| SUB NUMBER		# negNumber
	| op = SUB expr 	# negExpr

	// Precendence 3
	| expr op = (MUL | DIV | MOD) expr # multiplicativeExpr

	// Precendence 4
	| expr op = (ADD | SUB) expr # additiveExpr

	// Precendence 6
	| expr op = (GT | LT | GTE | LTE) expr # relationalExpr

	// Precendence 7
	| expr op = (EQ | NE) expr # equalityExpr

	// Precendence 11
	| expr op = LAND expr # logicalAndExpr

	// Precendence 12
	| expr op = LOR expr # logicalOrExpr

	// Precendence 13
	| expr '?' expr ':' expr # ternaryExpr

	// ETC
	| IDENTIFIER	# varExpr
	| NUMBER		# numExpr
	| BOOLEAN		# booleanExpr
	| KINPUT		# inputExpr
	| KALLOC expr	# allocExpr
	| KNULL			# nullExpr
	| array			# arrayConstructorExpr
	| recordExpr	# recordRule
	| '(' expr ')'	# parenExpr;

recordExpr: '{' (fieldExpr (',' fieldExpr)*)? '}';

fieldExpr: IDENTIFIER ':' expr;

array: LSBR expr OF expr RSBR | LSBR (expr (',' expr)*)? RSBR;

////////////////////// TIP Statements //////////////////////////

statement:
	blockStmt
	| assignStmt
	| whileStmt
	| forStmt // * added for SIP
	| postfixStmt // * added for SIP
	| ifStmt
	| outputStmt
	| errorStmt;

assignStmt: expr '=' expr ';';

blockStmt: '{' (statement*) '}';

whileStmt: KWHILE '(' expr ')' statement;

ifStmt: KIF '(' expr ')' statement (KELSE statement)?;

outputStmt: KOUTPUT expr ';';

errorStmt: KERROR expr ';';

returnStmt: KRETURN expr ';';

postfixStmt: expr op = (DEC | INC) ';';

forStmt:
	KFOR '(' expr ':' expr (DDOT expr (BY expr)?)? ')' statement;

////////////////////// TIP Lexicon //////////////////////////

// By convention ANTLR4 lexical elements use all caps

MUL: '*';
DIV: '/';
ADD: '+';
SUB: '-';
GT: '>';
LT: '<';
GTE: '>=';
LTE: '<=';
EQ: '==';
NE: '!=';
MOD: '%';
LNOT: KNOT;
LAND: KAND;
LOR: KOR;
DEC: '--';
INC: '++';
LEN: '#';
LSBR: '[';
RSBR: ']';
BY: 'by';
OF: 'of';
DDOT: '..';

NUMBER: [0-9]+;
BOOLEAN: (KTRUE | KFALSE);

// Placing the keyword definitions first causes ANTLR4 to prioritize their matching relative to
// IDENTIFIER (which comes later).
KALLOC: 'alloc';
KINPUT: 'input';
KWHILE: 'while';
KIF: 'if';
KFOR: 'for';
KELSE: 'else';
KVAR: 'var';
KRETURN: 'return';
KNULL: 'null';
KOUTPUT: 'output';
KERROR: 'error';
KTRUE: 'true';
KFALSE: 'false';
KNOT: 'not';
KAND: 'and';
KOR: 'or';

IDENTIFIER: [a-zA-Z_][a-zA-Z0-9_]*;

// ANTLR4 has a nice mechanism for specifying the characters that should skipped during parsing. You
// write "-> skip" after the pattern and let ANTLR4s pattern matching do the rest.

// Ignore whitespace
WS: [ \t\n\r]+ -> skip;

// This does not handle nested block comments.
BLOCKCOMMENT: '/*' .*? '*/' -> skip;

COMMENT: '//' ~[\n\r]* -> skip;
