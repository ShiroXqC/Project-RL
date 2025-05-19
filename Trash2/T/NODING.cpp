struct ListNode
{
    int data;
    Listnode *next
}

void
addNode(ListNode *Thelist, int data)
{
    newnode = new ListNode;
    newnode->data = data;
    newnode->next = Null;
    // Travel to the end of the list
    ListNode *iter = Thelist;
    while (iter->next)
        iter = iter->next;
    // Point the next pointer of the end to the new Node
    iter->next = newnode;
}

void pushFrontNode(ListNode *theList, int data)
{

    if(theList->Next==Null)
    {
        theList->next=newNode;
    }
    else:
    {
 
        newNode->next=theList->Next
        theList->Next=newNode
    
        
    }
}

RemoveNode

struct DoubleLink{
    int data;
    DoubleLink* next;
    DoubleLink* before;
}
DoubleLink*Header
pushback(DoubleLink*Header, int data)
{
    newnode= new DoubleLink;
    newnode->data=data;
    newnode->next=NULL;
    //Travel to the end of the list
    DoubleLink*iter= Header;
    while(iter->next)
    {
        if (newmode->before=Null)
        iter=iter->next
        iter->next=newnode
    }
   

}