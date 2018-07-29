#include<iostream>
#include<string.h>
using namespace std;

int memory[10]={0,0,0,0,0,0,0,0,0,0};

struct node       
{int size;   		 // size=no of blocks occupied in memory
 int *mmyptr;            //mmyptr= pointer to point memory address
 struct node *nptr;      //nptr=next node pointer
};

class list
{protected: node* start;
 public:
 list()
 {start=NULL;}
 
 list(int *m,int s,int *ptr) //intialiser for free list
 {
   start=createnode(); 
   start->size=s;
   start->mmyptr=m;        
   start->nptr=NULL;
 }
 
 node* createnode()
 {return new node;}
 
 int *raddress;// used to return memory address of freeslot of required size

 int *search(int rsize) //function to search a required size slot in memory
 { node *temp=start;
   node *prev=NULL; //this pointer bcz if we find a empty slot in memory we can modify freelist
   while(temp && !(temp->size >= rsize)) 
   { prev=temp;
   temp=temp->nptr;
   }
   if(temp==NULL) //we doesnot find a required size empty slot  in memory
   {return NULL;}  //return null
   else
   {

     raddress=temp->mmyptr;  //return this free block address
     temp->mmyptr = temp->mmyptr + rsize; //inc the pointer to next free addresses
     temp->size=temp->size-rsize;   //dec. size of free blocks in node
     //
     if(temp->nptr==NULL && temp->size==0)//  starting node and its size =0
     {start=NULL;}
     else if(temp->size==0)  // in between node and its size =0 
     {prev->nptr=temp->nptr; //deleting temp node form freelist
      delete(temp);
     }
     
    return raddress; //returning address of req. free slot
    }
 
 }
 void add(int *foundadd,int size) //function to add a node in allocated list with foundadd and assigned size
 {
    node *temp=new node();
    temp->size=size;
    temp->nptr=NULL;
    temp->mmyptr=foundadd;
    
    if(start == NULL)
    { start=temp;}
    else
    { node *newtemp=start;
      while(newtemp->nptr!=NULL) //reach end of allocated list
      {newtemp=newtemp->nptr;}
      
      newtemp->nptr=temp;//adding new node at end
   }   
 }
 
 void attach(node *t) //function to attach a node t containing the freeaddress and its size 
 {  t->nptr=NULL; 
  if(start==NULL) //if freelist was empty
   {start=t;}
   else
   {node* prev=NULL;
   node *temp=start;
   while(temp)  /////working to join free memory
   { prev=temp;
    if((temp->mmyptr + temp->size )==t->mmyptr) //then we have to join old free memory and new free memory as they are adjacent to each other
    {temp->size=temp->size + t->size;  //inc. size of free block in that node
    cout<<"join"<<endl;
    delete(t);        
    return;
    }
    
   temp=temp->nptr;
    
   }
   
   prev->nptr=t; // if no adjacent node than add node t to end

   }
 
 }
 
 node* pick(int *searchmmy)  // function for alloclist to find mmyadd in list
 { node *returnnode,*prevnode=NULL;
   node *temp=start;
   while(temp->mmyptr!=searchmmy)  //until we find a node containing mmyadd required
   {prevnode=temp;
    temp=temp->nptr;}
   if(temp==start)    //first node in allocated list
   {returnnode=start;   
    start=start->nptr;
   }
   else
   { returnnode=temp;
     prevnode->nptr=temp->nptr; //changing link to delete node from allocated list    ////////working here
   }
   
   return returnnode; //returning that node that contain reqmmyaddr 
 }
 
 
  void show()       
 { node *temp=start;
   if(temp==NULL)
   {cout<<"empty"<<endl;
   return;
   }
   while(temp)
   {//cout<<temp->size<<"s "<<temp->mmyptr<<"m "<<temp->nptr<<"nptr ";
    cout<<*temp->mmyptr<<" ";
   temp=temp->nptr;
   }
   cout<<endl;
 
 }
 
};

////////////////////
list freelist(memory,10,NULL); //intialising freelist - 1st arg =memory starting index , 2nd arg= total memory ,3rd arg= next node
list alloclist;   //intialising allocated list

////////////////////////

int *mymalloc(int size)
{
  int *foundadd=freelist.search(size);//return a memory address of required size if available
  if(!foundadd)
  {cout<<"memory not available"<<endl;}
  else
  {  alloclist.add(foundadd,size);  } // add that memory address with its size to allocated list
  return foundadd;    //return that found address
}

void myfree(int *t)
{ 
  node *attachnode =alloclist.pick(t);// return a node containing the memory address t

  node* temp=attachnode;       //
  int *mptr=temp->mmyptr;      //
  int count=0;                 //to free memory
  while(count!=temp->size)     //
  { mptr[count]=0;             //
  count++;                     // 
  }
  
  freelist.attach(attachnode); // attachnode to freelist 
 
}

void printmmy()
{ int i;
 for(i=0;i<10;i++)
 {cout<<memory[i]<<" ";}
 cout<<endl;
}

int main()
{  
   int *a=mymalloc(2); //  11--------   one represents allocated '-' represents free
    a[0]=1;
    a[1]=2;
    printmmy();  
   int *b=mymalloc(4); //  111111----
    b[0]=3;
    b[1]=4;
    b[2]=5;
    b[3]=6;
    printmmy();  
   int *c=mymalloc(4);//   1111111111
   c[0]=7;
   c[1]=8;
   c[2]=9;
   c[3]=10;
   printmmy();  
 
     myfree(b);       //11----1111
    printmmy();  
     int *d=mymalloc(2);   // 1111--1111 
    d[0]=11;
    d[1]=12;
   printmmy();  
     myfree(a);
                 //--11--1111       
      printmmy();  
     myfree(c);            //--11------
     printmmy();  
   
     int *e=mymalloc(10);  //not enough memory
   //cout<<memory<<" "<<a<<endl;
   //freelist.show();
   //alloclist.show();
   return 0; 
}
