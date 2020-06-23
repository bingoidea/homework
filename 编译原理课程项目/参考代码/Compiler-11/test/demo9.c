void change(int *a, int *b){
	int t = *a;
	write(t);
	printf("\n");
	*a = *b;
	write(*b);
	printf("\n");
	*b = t;
	write(*b);
	printf("\n");
}
int main() {
	int aqqqqqqqq = 2;
	int bqqqqqqqq = 3;
	write(aqqqqqqqq);
	printf("\n");
	write(bqqqqqqqq);
	printf("\n");
	change(&aqqqqqqqq,&bqqqqqqqq);
	write(aqqqqqqqq);
	printf("\n");
	write(bqqqqqqqq);
	printf("\n");
}
