#include <iostream>
#include <cmath>
using namespace std;


struct Vector {
	float x, y;
	Vector(float X, float Y) {
		x = X;
		y = Y;
	}
	
	void add( Vector A, Vector B) {
		Vector result(0, 0);
		result.x = A.x + B.x;
		result.y = A.y + B.y;
		cout << "result is: " << result.x <<' ' << result.y  <<'\n';
	}
	
	void substract(Vector A, Vector B) {
		Vector result(0, 0);
		result.x = A.x - B.x;
		result.y = A.y - B.y;
		cout << "result is: " << result.x <<' ' << result.y  <<'\n';
	}
	
	void scale(float x, Vector B) {
		Vector result(0, 0);
		result.x = x * B.x;
		result.y = x * B.y;
		cout << "result is: " << result.x <<' ' << result.y  <<'\n';
	}
	
	float len(Vector A) {
		Vector result(0, 0);
		result.x = pow(A.x, 2);
		result.y = pow(A.y, 2);
		return sqrt(result.x + result.y);
	}
	
	void normalize(Vector A) {
		Vector result(0, 0);
		result.x = A.x / len(A);
		result.y = A.y / len(A);
		cout << pow(result.x, 2) + pow(result.y, 2) + '\n';
	}

	
	bool Do(string operation) {
		if (operation == "add") {
			float a, b, c, d;
			cout << "Enter Vectors:\n";
			cin >> a >> b >> c >> d;
			add(Vector(a, b), Vector(c, d));
			return true;
		}
		if(operation == "substract") {
			substract(Vector(x, y), Vector(x, y));
			return true;
		}
		if(operation == "scale") {
			scale(x,  Vector(x, y));
			return true;
		}
		if(operation == "length") {
			len(Vector(x, y));
			cout << "\n";
			return true;
		}
		if(operation == "normalize") {
			normalize(Vector(x, y));
			return true;
		}
		if(operation == "exit"){
			cout << "Exiting...\n";
			return false;
		}
	}
	
};





int main() {
	int len;
	float x = 1.2, y = 2.3, x1 = 2.23, y1 = 3.4, a = 4, b = 3;
 	float aa = 3;
	Vector v1(x, y);
	Vector v2(x1, y1);
	Vector v3(a, b);
	Vector sum(0, 0);
//	cout <<"Len is " << sum.len(v3); cout <<'\n';
//	sum.scale(aa, v3);
//	cout << "Normalized ";
//	sum.normalize(v3);
//	sum.add(v1, v2); cout<<"\n";
	string operation;
	cout << "Enter command to operate with vectors (add, sustract, scale, length, normalize)\n";
	cin >> operation;
	if( sum.Do(operation) );
	
}
