typedef char * Item;
typedef char * Key;
typedef char * Value;

#define NULLitem NULL

#define key(A) A
#define value(A) A

#define eq(A,B) (strcmp(A,B) == 0)
#define less(A,B) (strcmp(A,B) < 0)
#define greater(A,B) (strcmp(A,B) > 0)

#define showItem(A) printf("%s ",A)
