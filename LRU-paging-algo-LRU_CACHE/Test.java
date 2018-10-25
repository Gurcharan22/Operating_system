import java.util.*;
class LRU_Cache
{  
    class Node //double linklist node
    {
        int key;
        int value;
        Node left,right;
        Node(int k,int v)
        {
            key=k;
            value=v;
            left=null;
            right=null;
        }
    }
  
    private HashMap<Integer,Node> map; // map key->double linklist node
    private Node head;
    private int leastrecentkey; //point to key which is leastrecently used
    private int size;                 //currentsize;
    private int capacity;        //given size
    private int pagefault;     //no of times required page not find in virtual memory
   
    public LRU_Cache(int capacity) 
    {
      map=new HashMap<Integer,Node>();
      head=null;
      size=0;
      this.capacity=capacity;
      leastrecentkey=-1;
      pagefault=0;
    }
  
    void pushtofront_in_dlinklist(Node topush) //pick topush node and put it to first of double linklist
    {
      pullnodeout(topush);//pull topush node out
    
      topush.left=null;  
      topush.right=head;
      head.left=topush;  
      head=topush;//new head
      return ;
    }
 
    void pullnodeout(Node toremove)//remove node from doubly linklist 
    {
      Node leftnode=toremove.left;
      Node rightnode=toremove.right;
      if(leftnode!=null)
      {
        leftnode.right=rightnode;
      }
       else
      {
        return;
      }
      
      if(rightnode!=null)
      {
        rightnode.left=leftnode;
      }
      
    }
    public int get(int key) 
    {
       
        if(map.containsKey(key)==false) //if not contain return -1
        return -1;     
        
        Node tomove=map.get(key);
        int r=tomove.value;
        if(leastrecentkey == key) //if node is last one
        {
          if(tomove.left!=null) //and there is node on left side of last node
          leastrecentkey=tomove.left.key;//mark leftnode of leastrecent node as leastrecent node
        
        }
        pushtofront_in_dlinklist(tomove); //pick that node and add it to front
        
        System.out.print("Value of key "+key+" is = ");
        return r;
    }
  
   
    
    public void set(int key, int value) 
    {  
       
      
        if(map.containsKey(key)==true)//if key is present 
        {
          Node keynode=map.get(key);
          keynode.value=value;//change its node value
        
        
          if(keynode.right==null & keynode.left!=null) //if left side of last node exists then change leastrecentkey
          leastrecentkey=keynode.left.key;
      
            
          pushtofront_in_dlinklist(keynode);//push node to front
          return;
        }
       
        Node toadd=new Node(key,value);
        
     
        if(size<capacity)//key not present
        {
           size++;
           if(size==1)
           {
               leastrecentkey=key;//intial value
           }
        }
        else //remove least recent used
        {   
           pagefault++;
           Node toremove=map.get(leastrecentkey);
       
           pullnodeout(toremove);
           map.remove(toremove.key);
    
          if(toremove.right ==null && toremove.left==null)//if size=1 
          {
            head=toremove.right; //mark head as null
            leastrecentkey=key;   //mark the new toadd node key as leastrecentkey now 
       
          }
          else if(toremove.right==null & toremove.left!=null)
          leastrecentkey=toremove.left.key;
    
        }
      
        map.put(key,toadd);//put added node in map
        toadd.right=head;//make it firstnode
        if(head!=null)
        {
           head.left=toadd; //changing leftnode of head
        }
        head=toadd; //new head
   }
   
   public int getpagefault()
   {
     return pagefault;
   }

}
public class Test
{
 public static void main(String args[])
 {
    LRU_Cache cache=new LRU_Cache(2);
    cache.set(2,1);
    cache.set(2,3);
    System.out.println(cache.get(2));
    cache.set(1,5);
    cache.set(5,6);
    System.out.println("Number of Pagefaults in Cache = " +cache.getpagefault());
 }
}
