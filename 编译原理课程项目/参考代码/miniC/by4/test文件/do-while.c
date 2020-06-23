
int main() {
	int i = 10;
int a = 1, b = a + 2, c = a * b, d = b * c, e = 10;
	do {
		c = a * b;
		d = b * c;
		e = c * d;
	} while(i--);
	return 0;
}
