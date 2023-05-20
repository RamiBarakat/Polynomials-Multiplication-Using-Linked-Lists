#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <stdbool.h>
#include <math.h>
#define max 100
///////////////////////////////////////////////////////
struct node;

typedef struct node* ptr;
typedef ptr list;
typedef ptr position;

struct node{double cof;int power; ptr next; ptr previous;};
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
void print(position temp){//function to print the lists of equations

    while (temp->next != NULL) {//as long as next pointer temp isnt NULL
        temp = temp->next;

         if(temp->power == 0 && temp->cof !=0){//if power is zero then only print the temp->cof
            printf("%0.1lf",temp->cof);


         }
        else if(temp->power ==0 && temp->cof < 0){

            printf("%0.1f",temp->cof);
        }
       else if(temp->power > 1 && temp->cof !=0){//if temp->power is larger than 1 and the cof isnt zero

            printf("%0.1fx^%d",temp->cof,temp->power);

       }
       else if(temp->power == 1&& temp->cof !=0){//if power is one then dont print the p->power
            printf("%0.1fx",temp->cof);

       }

       else if(temp->cof == 0){//neglect if temp->cof is zero
        continue;

       }
        if(temp->next != NULL){// to know if either print "+" or not
       if(temp->next->cof <= 0){// if the next cof is minus neglect
      continue;
       }
       else if(temp->next->cof >= 0){//if not then print "+"
            if (temp->next != NULL)
        printf("+");
       }
        }
    }

}
////////////////////////////////////////////////////////
void insert(list l,position p,double x,int y){//insert function for linked list

    position temp;
    temp=(struct node*)malloc(sizeof(struct node));//reserve space for temp
    temp->cof = x;
    temp->power = y;//enter the data to temp
    temp->previous = p;//let the previous for temp be p
    temp->next=p->next;// and the next is the node after p originally
    p->next=temp;//and change p-> next to point to temp

}

////////////////////////////////////////////////////////
list MakeEmpty(list L){  //Create a linked list
    if (L!=NULL)  //If the linked list is not empty then delete it
        DeleteList(L);
    L=(list)malloc(sizeof(struct node));
    if(L==NULL)
        printf("out of memory\n");
    L->next=NULL;
    return L;
}
////////////////////////////////////////////////////////
void DeleteList(list l){// a function to delete the whole list
position p, temp;
p = l->next;
l->next = NULL;

while(p != NULL){
temp = p->next;
free(p);
p=temp;

}
}
////////////////////////////////////////////////////////
int IsLast(list p,list l){//Check if the node is last in the linked list

    return p->next==NULL;
}
////////////////////////////////////////////////////////
int IsEmpty(list l)//Check if linked list is empty
{
    return l->next==NULL;
}
////////////////////////////////////////////////////////
bool Power(char line[max]){//function to help reading from file

int i;
for(i=0;line[i] != '\0';i++){

    if(line[i] == 'x' && (line[i+1] != '^')){
    return true;

    }

}
}
////////////////////////////////////////////////////////
int ReadFile(list l[max],FILE *in){

char arr[40][40];// two-dim array to save the token
for (int i=0; i<max+1; i++) {l[i] = MakeEmpty(NULL);}//we reserve space for all nodes of the array of the linked list

char a[100];
int index =0;

  in = fopen("equations.txt","r");

   if(in == NULL){//if file is empty then error
   printf("there is an error with the file\n");
   exit(0);
   }

while(fgets(a,100,in) != NULL) {

int strlength = 1;

 for( int i=0 ;a[i] != '\0' ;i++){strlength = i+1;}

int minus[max];// to save the sign before every cof.
int x =0;
  if(isdigit(a[0]) || a[0] == 'x'){
    minus[x] = 1;
    x++;
  }

  for(int i=0;i<strlength;i++){

    if(a[i] == '-'){
        minus[x] = -1;
        x++;
    }

    else if (a[i] == '+'){

        minus[x] = 1;
        x++;
    }
    else{
        continue;
    }
  }

int size =0;

    char *token = strtok(a,"[+-]");//split each line in the string for the + or -

    while (token != NULL){
       // printf("%s\n",token);
        strcpy(arr[size],token);//store them in an array
        size++;
        token = strtok(NULL,"[+-]");

    }
   double cof;
   int power;
   char linee[max];
   bool ok = true;
   int p =0;

   position pi = l[index];// a pointer to the head in each list in the the array of lists.
   l[index]->next = NULL;

   for(int i=0;i<size;i++){

   if(arr[i][0] == 'x'){//if the first element of each string is x then cof = 1*its sign
    cof = minus[i]*1;
    char *tok= strtok(arr[i],"[x^]");
    power = atoi(tok);

   }

    else{
    strcpy(linee,arr[i]);
   char* token2 = strtok(linee,"[x^]");//here we split by x or ^ and use atoi that changes from strings to integers
    cof = minus[i]*(strtod(token2,&token2));

    if(cof == 0){
      cof = minus[i]*1;
    }

    if(Power(arr[i]) == true){//if power func return true set power to 1
        power = 1;
    }
    else if (Power(arr[i]) == false){
     token2 = strtok(NULL,"[x^]");//else we continue splitting and use atoi to change to integer
     power = atoi(token2);
    }
    }

    //printf("%d %d",cof,power);
   insert(l[index],pi,cof,power);// insert the cof and power to array of linked list using position pi that will point only to the next node
    pi = pi->next;

   }

   index++;// increment so it can store the second equation


}

return index;//return the number of equations
}
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
list addPoly(list l1,list l2){// this function adds two polynomials and returns the answer

list p1,p2;
// create 2 lists to put l1 and l2 in
 p1 = MakeEmpty(NULL);
 p2 = MakeEmpty(NULL);
 p1 = l1;
 p2 = l2;
list add = MakeEmpty(NULL);//to store the results
position pi = add;

   while(p1 && p2){//while p1 and p2 != null

       if( p1->power > p2->power){//if the node of p1 has a power greater that p2's power

        insert(add,pi,p1-> cof,p1->power);//we insert the p1 node to add and move it to the next node
        pi = pi->next;
        p1 = p1->next;
     }


   else if(p1->power < p2->power){//if the node of p2 has a power greater that p1's power
        insert(add,pi,p2->cof,p2->power);//insert the p2 node to add and move p2 to the next node
        pi = pi->next;
        p2 = p2->next;
       }
    else{//if both powers is equal save the power and add the cof's to each other
       insert(add,pi,p1-> cof + p2->cof,p1->power);
        pi = pi->next;
        p1 = p1->next;//move p1 and p2 to their next nodes
        p2= p2->next;
    }
    }


 while(p1 || p2){//if either p1 or p2 hasn't got to the end of their lists we insert the remaining nodes in add

        if(p1){
        insert(add,pi,p1-> cof,p1->power);
        pi = pi->next;
        p1 = p1->next;


        }
       if(p2){
        insert(add,pi,p2-> cof,p2->power);
        pi = pi->next;
        p2 = p2->next;

       }
    }

    add = add->next;

    return add;
}


////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
list minuspoly(l1,l2){//this function subtracts two lists
list p1,p2;

 p1 = MakeEmpty(NULL);
 p2 = MakeEmpty(NULL);
 p1 = l1;
 p2 = l2;
list minus = MakeEmpty(NULL);
position pi = minus;

   while(p1 && p2){

       if( p1->power > p2->power){//we insert the p1 node to add and move it to the next node

        insert(minus,pi,p1-> cof,p1->power);//we insert the p1 node to add and move it to the next node
        pi = pi->next;
        p1 = p1->next;
     }


   else if(p1->power < p2->power){//if the node of p2 has a power greater that p1's power
        insert(minus,pi,-1*p2->cof,p2->power);//insert the p2 node to add to the list and move p2 to the next node
        pi = pi->next;
        p2 = p2->next;
       }
    else{//if both powers is equal save the power and add the cof's to each other
       insert(minus,pi,p1-> cof - p2->cof,p1->power);
        pi = pi->next;
        p1 = p1->next;
        p2= p2->next;
    }
    }
    while(p1 || p2){//if either p1 or p2 hasn't got to the end of their nodes we insert them in add

        if(p1){
        insert(minus,pi,p1-> cof,p1->power);
        pi = pi->next;
        p1 = p1->next;


        }
       if(p2){
        insert(minus,pi,-1*p2->cof,p2->power);
        pi = pi->next;
        p2 = p2->next;

       }
    }


    minus = minus->next;
return minus;
}


////////////////////////////////////////////////////////////////////
list multiply(list l1, list l2){
//we create nodes to point to the linked two linked lists that we passed
list p1,p2;
//here we initlize these nodes by the make empty function
 p1 = MakeEmpty(NULL);
 p2 = MakeEmpty(NULL);
 p1 = l1;
 p2 = l2;
 // after pointing to the two linked list we modify the pointers to not point to the head node because we dont usually save anything in it.
 p1 = p1->next;
 p2 = p2->next;
 // we reserve a place in memory for multi in the memory
list multi = MakeEmpty(NULL);
//position node to insert into the mutlti linked list sequentialy
position p = multi;
list mult = MakeEmpty(NULL);
//to multiply the polynomials we take two at a time
while(p1){//we continue as long as p1 is not NULL

position p = multi;//new node to point to the header of the multi equation(here because we delete the eqaution if each loop)
    while(p2){//as long as p2 is not NULL
      insert(multi,p,(p1->cof * p2->cof),(p1->power+p2->power));//we take the first node of p1 and move of each node in p2 as you would multiply when using a pen a paper
      p = p ->next;// move the position to save to the next node
      p2 = p2->next;//move the second equation
    }

   mult = addPoly(multi,mult);//we add the result of every node in p1 multiplied with the whole of p2 to avoid multiple occurence
   DeleteList(multi);//delete multi so it is ready for the new node in p1
   p2 = l2->next;//let p2 point to start of l2 again
   p1 = p1->next;//let p1 move to the next node
}


return mult;

}
////////////////////////////////////////////////////////////////////
void fprintlist(list temp,FILE *in) {//same function as print but this is specifically to print to files

    while (temp->next != NULL) {
        temp = temp->next;

         if(temp->power == 0 && temp->cof !=0){
            fprintf(in,"%0.1f",temp->cof);


         }
        else if(temp->power ==0 && temp->cof <= 0){

            fprintf(in,"%0.1f",temp->cof);
        }
       else if(temp->power >0 && temp->cof !=0){

            fprintf(in,"%0.1fx^%d",temp->cof,temp->power);

       }
       else if(temp->power == 1){
             fprintf(in,"%0.1fx",temp->cof);

       }
       else if(temp->cof == 0){
        continue;

       }
        if(temp->next != NULL){
       if(temp->next->cof <= 0){

        continue;
       }
       else if(temp->next->cof >= 0){
            if (temp->next != NULL)
        fprintf(in,"+");
       }
        }
    }


}
////////////////////////////////////////////////////////////////////
void AddAll(list l[],int index,FILE *in,bool ok){//in this function we add all the functions using addpoly that adds two polynomials

  list d = addPoly(l[0],l[1]);//first we add the first two linked lists

for(int i = 2; i <index ; i++){//the answer to the first two equations we add to the third and so on till the last equation

  d = addPoly(d,l[i]);

}
double x;
double sum = 0;
if(ok == true){//save to file
  fprintf(in,"the result of adding polynomial is\t");
    fprintlist(d,in);
}

else if( ok ==false){//show on console
    printf("the result of adding polynomial is\t");
    print(d);

}
printf("\nplease enter the value of x\n");
scanf("%lf",&x);// enter a double value for x

while(d->next != NULL){// we pass through the add equation to each node till the last points to null and put a value in place of x
    d = d->next;

 sum += (d->cof*pow(x,d->power));//adding sum of each node

}
if(ok == false){//show to console
    print(d);
    printf("%0.1f\n",sum);
}

else{//save to file
    fprintf(in,"\nthe value for x = %f for addition = %0.1f\n",x,sum);

}

}
///////////////////////////////////////////////////////////////////
void minusall(list l[],int index,FILE *in,bool ok){//this function is to subract the equations from each other

list d = minuspoly(l[0],l[1]);//same procedure as the AddAll() function


for(int i = 2; i <index ; i++){

  d = minuspoly(d,l[i]);//here to subtract two equations at a time

}
double x;
double sum = 0;
if(ok == true){//save to file
  fprintf(in,"the result of subtraction polynomial is\t");
    fprintlist(d,in);
}
else if(ok == false){//save to console
    printf("the result of subtraction polynomial is\t");
    print(d);
}

printf("\nplease enter the value of x\n");
scanf("%lf",&x);//enter value for x

while(d->next != NULL){
    d = d->next;

 sum += (d->cof*pow(x,d->power));//sum of each node in the final subtraction equation

}
if(ok == false){//to console

    printf("%0.1f\n",sum);
}

else{//to screen
    fprintf(in,"\nthe value for x = %f for subtraction = %0.1f\n",x,sum);
   fprintlist(d,in);
}

}
//////////////////////////////////////////////////////////////////
void multiplyall(list l[],int index,FILE *in,bool ok){//this function is to multiply all equations

    list d = multiply(l[0],l[1]);//multiply the first two and save their answer to mult. it with the next equation

for(int i = 2; i <index ; i++){

  d = multiply(d,l[i]);//keep multiplying the equations until there is no more of them

}
double x;
double sum = 0;
if(ok == true){//when printing to file
    fprintf(in,"the result of multiplication polynomial is\t");
    fprintlist(d,in);
}
else if(ok == false){//when printing to console
    printf("the result of multiplication polynomial is\t");
    print(d);
}


printf("\nplease enter the value of x\n");
scanf("%lf",&x);// enter a value to x

while(d->next != NULL){
    d = d->next;

 sum += (d->cof*pow(x,d->power));// add all the nodes to each other with value x

}
if(ok == false){//show on console

    printf("%0.1f\n",sum);
}

else{//save to file
    fprintf(in,"\nthe value for x = %f for multiplication = %0.1f\n",x,sum);

}

}

//////////////////////////////////////////////////////////////////
void SaveToFile(FILE *in, list l[max],int index){//function to save all the mathematical calculations

in = fopen("results.txt","w");
     if(in == NULL){
        printf("there is an error with the file\n");
        exit(0);
     }

AddAll(l,index,in,true);//add and save to file
minusall(l,index,in,true);//subtract and add to file
multiplyall(l,index,in,true);//multiply and save to file

fclose(in);
}
///////////////////////////////////////////////////////////////////////
int main()
{
list l[max];//array of linked list
FILE *in;//file pointer to read from it
int choice = 0;
int index = 0;

printf("\t\t\t\t\t\tPROJECT 1\n");
printf("\t\t------------------------------------------------------------------------\n");
printf("\t\t\t\t\t\twelcome!\n");



while(1){//while loop to execute the switch statement repeatedly

printf("\nPlease select an option to perform\n");
printf ("1- Read File and store the equations in the linked list\n2- Perform addition operation on all equations\n3- Perform subtraction operation on all equations\n4- Perform multiplication operation on all equations\n5- Save the results of all operations back to the file\n6- Exit\n\n");

 scanf("%d",&choice);

 switch(choice){

 case 1://read from file
     printf("the equations are :\n");
    index = ReadFile(l,in);

   for(int i=0;i<index;i++){
    print(l[i]);
    printf("\n\n");
 }
 break;

 case 2:// add all equations
    AddAll(l,index,in,false);
    break;

 case 3:// subtract all equations
     minusall(l,index,in,false);
    break;


 case 4://multiply all equations
     multiplyall(l,index,in,false);
   break;

 case 5:// do all the operations and save to file
     SaveToFile(in,l,index);
    break;

 case 6://quit the program
     printf("good bye!");
    exit(0);
break;

 }
 }

  return 0;

}
