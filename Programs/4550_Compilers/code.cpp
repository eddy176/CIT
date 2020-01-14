//void main()
//{
//	int i;
//	int j;
//	int t;
//	i = 2;
//	int a;
//	a = 1;
//	j = 10;
//	t = 0;
//	repeat(3)
//		cout << i;
//	cout << 2 ** 3;
//	j+=10;
//	cout << j;
//
//	cout << 1 and 0 and 1;
//	cout << 0 and 0;
//	cout << 1 or 0;
//	cout << 0 or 0;
//	cout << 0 or 1;
//	cout << 0 or 0 or 1;
//	if (1 and j > t or a < i) {
//		cout << a;
//	}
//	else if (a < t)
//		cout << t;
//	else {
//		cout << i;
//	}
//
//	while (t < 10) {
//		t = t + 1;
//		cout << t;
//	}
//	cout << j;
//}

// testing while, if, and cout
//void main() {
//	int t;
//	int i;
//	int j;
//	i = 2;
//	while (i <= 10) {
//		t = 0;
//		j = 0;
//		while (j <= i) {
//			if (j / i + j == i) {
//				t = 1;
//				j = j + 1;
//			}
//			j = j + 4;
//			if (t == 0) {
//				//cout << i;
//				i = i + 1;
//			}
//		}
//	}
//}

// testing multi cout, endl, +=, and -=
void main() {
	cout << true;
	cout << false;
	int a;
	int b;
	int c;
	a = 0;
	b = 1;
	c = 2;
	int v;
	v = 9;
	do {
		a += 1;
	}
	while (a < v);
	if (a % 3 == 0) {
		cout << 2319 << endl;
	}
	else {
		cout << 666 << endl;
	}
	while (v < 15) {
		v += 2;
		cout << v << endl;
	}
	repeat(2) {
		cout << 0 << 0;
		cout << 7 << endl;
	}
	int girl = 999;

	if (true) {
		girl = 666;
	}
	else {
		girl = 333;
	}
	a += 1;
	c -= 1;
	b *= 2;
	cout << b << endl;
	b /= 2;
	cout << b << endl;
	cout << a << endl << b << endl << c << endl;
	cout << girl << endl;
	cout << 10 >> 2 - 1;
	cout << 10 >> 1 == 1;
}

//void main() {
//	int x;
//	x = 24;
//	int y;
//	y = 2;
//	cout << (x >> y);
//	cout << (x >> y - 1);
//	cout << (x >> y == 2);
//}



//void main() {
//	int sum;
//	sum = 30 + 100;
//	cout << sum << endl;
//}