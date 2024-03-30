This calculator performs operations on sets of integer numbers within the range [0,127].
The user has 6 sets on which he can perform operations. Those sets are SETA through SETF.
Operations that can be performed:

print_set SETN ==> prints the contents of SETN. If the set is empty then it will print so.

read_set SETN, a1, a2, ..., an, -1  ==> stores the values of a1 through an in setn
whereas, (an) is a series of integer numbers within the range [0,127].

union_set SETN1, SETN2, SETN3 ==> combines the values of setn2 and setn3 and stores them in setn1.
You can use the same set more than once.

intersect_set SETN1, SETN2, SETN3 ==> combines the shared values of setn2 and setn3 and stores them in setn1.

sub_set SETN1, SETN2, SETN3 ==> stores the values implicit to just setn2 in setn1.

symdiff_set SETN1, SETN2, SETN3 ==> stores the values implicit to setn2 or setn3, that are not present in both, in setn1.
