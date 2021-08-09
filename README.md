# wxWidgetsExcel
A spreadsheet application made using wxWidgets and c++.

Allows the user to assign functions to cells that will be calculated dynamically:
 - Functions start with '=' symbol and may contain arithmetic operations as well as predefined functions (sum, avg, min, max, pow, sqrt);
 - Functions are entered as text and parsed into a calculable expression; 
 - If a cell's value is changed - function that uses this cell is updated;
 - If a function references its own cell it's marked as cyclic, and stays this way until the cycle is resolved.

The entire spreadsheet may be saved into a file and loaded from a file of .grd format.
