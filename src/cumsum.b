declblock
{
int data[100];
int cum[100];
int n;
int i;
}
codeblock
{
read n;
for i=0,n-1,1 
{
read data[i];
cum[i]=data[i];
if(i!=0)
{
cum[i]=cum[i]+cum[i-1];
}
}
for i=0,n-1,1
{
  println cum[i];
}

}
