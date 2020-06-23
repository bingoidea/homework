/* test */
int s;
int gcd (int u, int v)
{
	int x; int y;
	u=v+1; x=v*u;
	if (v == 0) return u ;
	else return gcd(v,u-u/v*v);
}
void main(void)
{
	int x; int y; int b[10];
	void p;
	p = 1;
	x = input(); y = input();

	output(gcd(x,y));

	return ;
}
