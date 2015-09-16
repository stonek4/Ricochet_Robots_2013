HOMEWORK 6: RICOCHET ROBOT RECURSION


NAME:  < Kevin Stoner >



COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< TA Rebecca... Prof... but neither really reflect in my code... cplusplus >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 20 >



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

i & j = dimensions of the board
    r = number of robots on the board
    w = number of interior walls
    m = maximum total number of moves allowed

O(r^(m)*i*j*w)

Well... it's a guess anyways.  The exponent I figure is the number of moves a robot can make because
the more moves you allow, the program grows exponentially.  Then that times the number of possible spaces it can cover,
times the directions it can move (4) which gets dropped and I guess times the number of walls because you have to check them...  and you get my equation.


SUMMARY OF PERFORMANCE OF YOUR PROGRAM ON THE PROVIDED PUZZLES:
Puzzle 1 is fast no matter what I specify
Puzzle 2 is maybe a little faster
Puzzle 3 is fast because there is only one solution
Puzzle 4 is slower... my program takes a while to figure its not valid
Puzzle 5 same with 5
Puzzle 6 is mean but after a lot of time it works
Puzzle 7 is mean too but it works as well (as far as I can tell)


MISC. COMMENTS TO GRADER:  
What opens when it closes, and closes when it opens? (scroll down for answer)












**Answer**
A drawbridge!


