Implement mini shell on Linux (then on Windows).
The shell should support command composition (with multiple operands) with the below operand precedence:  
  * | - pipe operator
  * conditional execution operator (&& and ||)
  * & - parallelism operator
  * ; - sequential operator
  
Firstly a parser will be implemented (expression tree will be created - bottom-up?).
The expression tree will be resolved. For each operand a new process should be created (fork + exec*)
The mini shell should also support redirection (see dup2)
