#include <stdio.h>
#include <stdlib.h>

// self-referential structure                       
struct listNode {                                      
   char data; // each listNode contains a character 
   struct listNode *nextPtr; // pointer to next node
}; 

typedef struct listNode ListNode; // synonym for struct listNode
typedef ListNode *ListNodePtr; // synonym for ListNode*

// prototypes
void insert(ListNodePtr *sPtr, char value);
char delete(ListNodePtr *sPtr, char value);
int isEmpty(ListNodePtr sPtr);
void printList(ListNodePtr currentPtr);
void instructions(void);

int main(void)
{ 
   ListNodePtr startPtr = NULL; // initially there are no nodes
   char item; // char entered by user

   instructions(); // display the menu
   printf("%s", "? ");
   unsigned int choice; // user's choice
   scanf("%u", &choice);

   // loop while user does not choose 3
   while (choice != 3) { 

      switch (choice) { 
         case 1:
            printf("%s", "Enter a character: ");
            scanf("\n%c", &item);
            insert(&startPtr, item); // insert item in list
            printList(startPtr);
            break;
         case 2: // delete an element
            // if list is not empty
            if (!isEmpty(startPtr)) { 
               printf("%s", "Enter character to be deleted: ");
               scanf("\n%c", &item);

               // if character is found, remove it
               if (delete(&startPtr, item)) { // remove item
                  printf("%c deleted.\n", item);
                  printList(startPtr);
               } 
               else {
                  printf("%c not found.\n\n", item);
               } 
            } 
            else {
               puts("List is empty.\n");
            } 

            break;
         default:
            puts("Invalid choice.\n");
            instructions();
            break;
      } // end switch

      printf("%s", "? ");
      scanf("%u", &choice);
   } 

   puts("End of run.");
} 

// display program instructions to user
void instructions(void)
{ 
   puts("Enter your choice:\n"
      "   1 to insert an element into the list.\n"
      "   2 to delete an element from the list.\n"
      "   3 to end.");
} 

// insert a new value into the list in sorted order
void insert(ListNodePtr *sPtr, char value)
{ 
   ListNodePtr newPtr = malloc(sizeof(ListNode)); // create node
   if (newPtr != NULL) {
   		newPtr->data=value;
		newPtr->nextPtr=NULL;
   		ListNodePtr currentPtr=*sPtr;
   		ListNodePtr previousPtr=NULL;
   		if(currentPtr==NULL) *sPtr=newPtr;
   		else
   		{
   			while((currentPtr!=NULL)&&(value>currentPtr->data))//两个判断条件的位置不能对调，否则当currentPtr为空指针时，会对其进行非法的解引用。 
   			{
   				previousPtr=currentPtr;
   				currentPtr=currentPtr->nextPtr;
			   }
			   if(previousPtr==NULL)
			   {
			   		newPtr->nextPtr=currentPtr;
			   		*sPtr=newPtr;
			   }
			   else if(currentPtr!=NULL)
			   {
			   		previousPtr->nextPtr=newPtr;
			   		newPtr->nextPtr=currentPtr;
			   }
			   else if(currentPtr==NULL)
			   {
			   		previousPtr->nextPtr=newPtr;
			   }
		   }
   		
      
   } 
   else {
      printf("%c not inserted. No memory available.\n", value);
   } 
} 

// delete a list element
char delete(ListNodePtr *sPtr, char value)
{ 
   //如果第一个节点匹配，则将其删除 
   if (value == (*sPtr)->data) { 
      ListNodePtr tempPtr = *sPtr; // hold onto node being removed
      *sPtr = (*sPtr)->nextPtr; // de-thread the node
      free(tempPtr); // 释放内存 
      return value;
   } 
   else { 
      ListNodePtr previousPtr = *sPtr;
      ListNodePtr currentPtr = (*sPtr)->nextPtr;

      // loop to find the correct location in the list
      while (currentPtr != NULL && currentPtr->data != value) { 
         previousPtr = currentPtr; // walk to ...  
         currentPtr = currentPtr->nextPtr; // ... next node  
      } 

      // delete node at currentPtr
      if (currentPtr != NULL) { //currentPtr非空，则代表找到了这个节点。 
         ListNodePtr tempPtr = currentPtr;
         previousPtr->nextPtr = currentPtr->nextPtr;
         free(currentPtr);//free（currentPtr）也能起到一样的效果 
         return value;
      } 
   } 

   return '\0';//等效于return 0;
} 

// return 1 if the list is empty, 0 otherwise
int isEmpty(ListNodePtr sPtr)
{ 
   return sPtr == NULL;//若sPtr为空指针，则返回1，否则返回0； 
} 

// print the list
void printList(ListNodePtr currentPtr)
{ 
   // if list is empty
   if (isEmpty(currentPtr)) {
      puts("List is empty.\n");
   } 
   else { 
      puts("The list is:");

      // while not the end of the list
      while (currentPtr != NULL) { 
         printf("%c --> ", currentPtr->data);
         currentPtr = currentPtr->nextPtr;   
      } 

      puts("NULL\n");
   } 
} 
