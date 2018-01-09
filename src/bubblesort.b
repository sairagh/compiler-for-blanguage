declblock
{
	int n, temp;
	int A[100];
	int j;
	int i;
}

codeblock
{
	read n;
	for i = 0, n-1
	{
		read A[i];
	}
	for i = 0, n-2
	{
		for j = 0, n-i-2
		{
			if A[j] > A[j+1]
			{
				temp = A[j];
				A[j] = A[j+1];
				A[j+1] = temp;
			}
		}
	}
	for j = 0, n-1
	{
		println A[j];
	}
	println " ";
}
