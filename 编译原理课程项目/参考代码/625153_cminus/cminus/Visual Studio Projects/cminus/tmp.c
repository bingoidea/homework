main()
{
	int a, b, i, t, n;

	a = 0;
	b = 1;
	i = 1;
	input(n);
	print(a);
	print(b);
	while (i < n)
	{
		t = b;
		b = a + b;
		print(b);
		a = t;
		i = i + 1;
	}
}
