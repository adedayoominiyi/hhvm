<?php
/* Prototype  : proto string mb_ereg_replace(string pattern, string replacement, string string [, string option])
 * Description: Replace regular expression for multibyte string
 * Source code: ext/mbstring/php_mbregex.c
 * Alias to functions:
 */

// get a class
class classA
{
  public function __toString() {
    return "UTF-8";
  }
}
<<__EntryPoint>> function main() {
echo "*** Testing mb_ereg_replace() : usage variations ***\n";

// Initialise function arguments not being substituted (if any)
$replacement = 'string_val';
$string = 'string_val';
$option = '';

//get an unset variable
$unset_var = 10;
unset ($unset_var);

// heredoc string
$heredoc = <<<EOT
UTF-8
EOT;

// unexpected values to be passed to $encoding argument
$inputs = array(

       // int data
/*1*/  0,
       1,
       12345,
       -2345,

       // float data
/*5*/  10.5,
       -10.5,
       12.3456789000e10,
       12.3456789000E-10,
       .5,

       // null data
/*10*/ NULL,
       null,

       // boolean data
/*12*/ true,
       false,
       TRUE,
       FALSE,

       // empty data
/*16*/ "",
       '',

       // string data
/*18*/ "UTF-8",
       'UTF-8',
       $heredoc,

       // object data
/*21*/ new classA(),

       // undefined data
/*22*/ @$undefined_var,

       // unset data
/*23*/ @$unset_var,

);

// loop through each element of the array for pattern

$iterator = 1;
foreach($inputs as $input) {
      echo "\n-- Iteration $iterator --\n";
      var_dump( mb_ereg_replace($input, $replacement, $string, $option) );
      $iterator++;
};

echo "Done";
}
