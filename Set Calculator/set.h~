/* Realloc factor for input string. */
#define realloc_Factor 5

/* Error and success constants for Error Examiner. */
#define FAIL -1

#define SUCCESS 1

#define TOTAL_SETS 6

/* Min command length when it comes to print_set. */
#define MIN_COMMAND_LEN 4

/* Max command length when it comes to union/sub/intersect/symdiff_set. */
#define MAX_COMMAND_LEN 14

/* The declarations pointer for set and the struct of set. */
typedef struct ListNode * setptr;

typedef struct ListNode 
{
	int group[4];
}set;

/* Declarations of the available operations. As per this assignment's requirement. */
void read_set(setptr *s, char *nums);
void print_set(setptr s);
void union_set(setptr s1, setptr s2, setptr *s3);
void sub_set(setptr s1, setptr s2, setptr *s3);
void intersect_set(setptr s1, setptr s2, setptr *s3);
void symdiff_set(setptr s1, setptr s2, setptr *s3);

/* Declaration for a helper function that resets a given set's bits. */
void reset(setptr *s);

/* Declarations for Error examining functions. */
int examine_Errors_For_Read(char *in, int len);
int examine_Errors_For_Print(char *in, int len);
int examine_Errors_For_Others(char *in, int len);
