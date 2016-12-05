I made programs for following problems. Please note that this is work in progres.

1) Write a program that takes a name of a text file as a parameter and produces 
   an output file containing the list of words from the input file and number of ocuurencs for each word. 
   For example, for the following input file:
   
   ABC,cba.CBA.IOT;LTE...PRR prr iot some text.
   
   The output file should contain:
   abc 1
   cba 2
   iot 2
   lte 1
   prr 2
   some 1
   text 1

2) Write a program that takes a text file with a list of words and a file with a text in which the words will be checked for correctness, based on the list from the first file. 
   The output file should contain list of words from the second file (including line number) that are not correctly spelled or not found in the list from the first file.

   For example, for the follwing input files:

   This, is, a, text, some, to, be, check

and

   This is a simple text to be checked.

   The output file should contain:
   1 simple
   1 checked

3) Write a program that takes an input file with a set of numbers and generates all subsets of this set.
   For example, for the input file:
   {1,2}
   The output file should contain:
   {},{1},{2},{1,2}

4) Implement a mastermind game (text based). The program generates a sequence of colours (four are possible : Blue, Green, Red, Yellow) 
   on a maximum of four positions, for example RGGB. 
   Player's task is to guess the sequence. 
   If the player guesses the colour on a correct position, the player gets a hit. 
   If the player guesses a colour on a wrong position, the player gets a partial hit.
   For example, if the sequence to guess is RGBY and the player provides a guess : GGRR, the player gets one hit and one partial hit.

5) Write a program that receives a string of letters and compresses it based on letter repetition. 
   For example, for a string aabcccccaaa the output should be a2b1c5a3. 
   Try to come up with a solution that runs is O(n).

6) Dsign the necessary data structures and develop a program that receives a grid of points in two dementional space 
   (assume the grid starts at (0,0) and ends at (X,Y)) and finds a path from point (0,0) to (X,Y).
   Assume that some of the points are forbidden to step on. 
   The program should return a list of points that can be followed to reach (X,Y).
