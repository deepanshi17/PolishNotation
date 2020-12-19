# PolishNotation
Toy programming language "Blip" that reads inputs in polish notation with internal symbol table

## Blip Language
The basic structure includes four language statements. Two of these (var and set) are for creating and assignment values to variables, and two of these (output and text) are for producing output (i.e., printing to the screen). A Blip program consists of zero or more statements. Each statement begins with a keyword (var, set, output or text).
* text statements result in a text message being displayed on the screen. The text message can be either a single word, or a quoted string. The following are examples of legal text statements
text Hello
text “Hello World”
* output statements result in a number being displayed on the screen. The number displayed is the result of evaluating any legal Blip expression. For now, Blip only supports integer variables, and so only integer values can be displayed. The following are examples of output statements. For more information on Blip expressions, see below
output 42
output + 1 1
output * x x
output + * x x * y y
* var statements initialize a new variable. If a var statement specifies a variable that already exists, then Blip must generate a warning (not an error), with the text, “variable <varName> incorrectly re-initialized”, where <VarName> is the variable’s name. Regardless of whether the warning message is created, the result of a var statement is to ensure that there is a variable in the Blip internal memory with the specified value. The variable must be set to the value of a legal Blip expression. The syntax is: “var <varName> <expr>”. The following are examples of legal var expressions
var x 42 
var y + x 1
* set statements are just like var statements, except a set statement should be used to re-assign a new value to an existing variable. As such, if a set statement specifies a variable that does not already exist, then Blip must generate a warning (not an error) with the text, “variable <varName> not declared”. Regardless of whether the warning message is created, the result of a set statement is to ensure that there is a variable in the Blip internal memory with the specified value. The following are examples of legal set expressions
set x 42 
set x + x 1
Blip programs do not have to have only a single statement on a line, in fact, line breaks don’t really matter to Blip (nor do tabs or spaces). Additionally, Blip programs can have comments between statements (but not in the middle of a statement). For example, the following is correct Blip
text “Hello, and welcome to Blip” // first line var x 0
// set x to (5 + 3) * (x – 1)
set x
*
+53
-x1

A comment is marked by // and continues to the end of the current line. Note that the following statement is illegal in Blip, since we can’t have comments in the middle of a statement
output + // two terms in this expression * 5 3 // 5 * 3 is the first term
- 10 7 // 10 – 7 is the second term

## Symbol Table
To implement variables, the language relies on a symbol table that is structured like a binary search tree. It has the potential to scale to a large number of variables.

## Blip Expressions
Blip has a fairly rich set of C-like integer operators, but has a distinctly non-C expression syntax. The reason for the odd syntax is so that Blip is easy to parse. Perhaps the easiest-to-parse languages are those that use prefix expression syntax, so that’s what Blip uses. For example, instead of writing 2 + 2 (infix expressions), we write “+ 2 2” in Blip. The order for the arguments is important for non-commutative operations, so, for example, the Blip expression / 10 5 will evaluate to 2 (10 / 5 is 2). The complete list of operators that you must support are:
Binary math operators: +, -, *, /, %
Binary logic operators: &&, ||
Comparison Operators: <, >, ==, !=, <=, >= Unary Operators: !, ~
Note that for logic operations, we use the C conventions for integer values. Any value other than zero is “true”, and zero is false. When evaluating an expression that produces a logical value (e.g., && or <=), you must evaluate true expressions to 1 and false expressions to zero. So...
&& 5 42 evaluates to 1
+ && 6 12 10 evaluates to 11
Note that we are not implementing the bit-wise logic at this time. Please implement ~ as arithmetic negation (i.e., ~ 5 is really -5).
