#if 0
Note that sizeof is an operator, not a function. If you apply it to a type, it must be used with the parenthesized form shown above, but if you apply it to a variable you can use it without parentheses:
#endif

int main() {
        int x;
        int i = sizeof x;

        sizeof (int); // Ok
      //  sizeof int; // Not Okay, expected parentheses around type name in sizeof expression
      // parentheses are mandatory around type name.

        sizeof (x); // Ok
        sizeof x; // ok

        /*
           That's the way the language is specified, type names must be parenthesized here.
           the grammar looked like this:
           sizeof unary-expression
           sizeof type-name

           Now, e.g. the following expression would be ambiguous:
           sizeof int * + 0

           It could be either sizeof(int *) + 0 or sizeof(int) * +0. This ambiguity doesn't arise for unary expressions,
           as an asterisk appended to an expression isn't an expression (but for some type names, appending one, is again a type name).
           Something had to be specified here and requiring type-names to be parenthesized is a way to solve the ambiguity.
         */
}
