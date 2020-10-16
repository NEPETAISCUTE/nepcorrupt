# nepcorrupt

if you want to compile it, just do
gcc nepcorrupt.c -o nepcorrupt

or if you're on windows
gcc nepcorrupt.c -o nepcorrupt.exe
(if i remember well)

if you want to know how to use the program

well basically -i is the flag to put before the input file name

-o is the same but for the output file name

-op is for the operator you want to use to corrupt

-r is for the range, the "corrupt every" and the number you want to use with your op, in that order, so for exemple if you want to corrupt a file named "test.txt" and put the output in "whatever.txt", use the operator add, and corrupt in a range from byte 0 to byte FA, corrupt every 3 bytes, and do all that by adding 26 you will have to do

windows:
nepcorrupt.exe -i test.txt -o whatever.txt -op add -r 0 FA 3 26

linux:
nepcorrupt -i test.txt -o whatever.txt -op add -r 0 FA 3 26

for the linux command, it works only if you put the binary into /bin/

thanks for downloading, testing, and modifying my program ^^
