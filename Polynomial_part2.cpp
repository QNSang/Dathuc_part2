#include <iostream>
using namespace std;

typedef struct {
	int num;
	int data[100][2];
	//0 : heso
	// 1: so mu
}poly;

void input_poly(poly& A);//ham xuat
void output_poly(poly A);//ham nhap
poly sort_descending(poly& A);// ham sap xep
poly delete_elment(poly& A, int locate);//ham xoa ky tu
poly apply_poly(poly& A, poly& B);//ham nối 
poly add_poly(poly& A, poly& B);//ham cong
poly sub_poly(poly& A, poly& B);//ham tru
poly mult_poly(poly& A, poly& B);//ham nhan
poly divide_poly(poly& A, poly& B);//ham chia
poly derivate_poly(poly& A);// dao ham
poly derivate_oder_k(poly& A, int k);//dao ham bac k

int main() {
	poly A, B;
	input_poly(A);
	input_poly(B);
	output_poly(A);
	cout << '\n';
	output_poly(B);
	std::cout << "\ntong 2 da thuc: ";
	output_poly(add_poly(A, B));
	std::cout << "\ntru 2 da thuc: ";
	output_poly(sub_poly(A, B));
	std::cout << "\nnhan 2 da thuc: "<<std::endl;
	output_poly(mult_poly(A, B));
	std::cout << "\nchia 2 da thuc: "<<std::endl;
	output_poly(divide_poly(A, B));
	std::cout << "\ndao ham bac k: "<< std::endl;
	int k;
	std::cout << " \nnhap k"<<std::endl;
	cin >> k;
	output_poly(derivate_oder_k(A, k));

	return 0;
}
void input_poly(poly& A) {
	cout << "nhap so phan tu da thuc: ";
	cin >> A.num;
	for (int i = 0; i < A.num; i++) {
		cout << "nhap so he so _ va so mu _ ";
		for (int j = 0; j < 2;j++) {
			//cout << " nhap";
			cin >> A.data[i][j];
		}
	}
}
void output_poly(poly A) {
	A = sort_descending(A);// sort poly
	cout << A.data[0][0] << "*x^" << A.data[0][1];
	for (int i = 1; i < A.num; i++) {
		if (A.data[i][0] == 0) continue;
		else if (A.data[i][0] == 1)
			cout << " + "<<"x^" << A.data[i][1];
		else if (i == 0)
			cout << A.data[i][0] << "*x^" << A.data[i][1];
		else if (A.data[i][1] == 0)
			cout << " + " << A.data[i][0];
		else if (A.data[i][1] == 1)
			cout << " + " << A.data[i][0] << "*x";
		else 
			
			cout << " + " << A.data[i][0] << "*x^" << A.data[i][1];
		
	}
}
poly sort_descending(poly& A) {
	// bubble sort algorithm
	for (int i = 0; i < A.num; i++) {
		bool swapped = false;
		for (int j = 0; j < A.num - i - 1; j++) {
			if (A.data[j][1] < A.data[j + 1][1]) {
				// sort mu
				int temp1 = A.data[j + 1][1];
				A.data[j + 1][1] = A.data[j][1];
				A.data[j][1] = temp1;
				//sort he so
				int temp2 = A.data[j + 1][0];
				A.data[j + 1][0] = A.data[j][0];
				A.data[j][0] = temp2;
				swapped = true;
			}
		}
		if (!swapped) {
			break;
		}
	}
	return A;
}
poly delete_elment(poly& A, int locate) {
	for (int i = locate; i < A.num; i++) {
		A.data[i][0] = A.data[i + 1][0];
		A.data[i][1] = A.data[i + 1][1];
	}
	A.num--;
	return A;
}
//noi da thuc
poly apply_poly(poly& A, poly& B) {
	poly newpoly;
	newpoly.num = A.num + B.num;
	for (int i = 0; i < A.num; i++) {
		for (int j = 0; j < 2; j++) {
			newpoly.data[i][j] = A.data[i][j];
		}
	}
	for (int i = A.num; i < newpoly.num; i++) {
		for (int j = 0; j < 2; j++) {
			newpoly.data[i][j] = B.data[i - A.num][j];
		}
	}
	return newpoly;
}
// cong 2 da thuc
poly add_poly(poly& A, poly& B) {
	poly copy_A = A;
	poly copy_B = B;
	for (int i = 0; i < A.num; i++) {
		for (int j = 0; j < B.num; j++) {
			if (copy_A.data[i][1] == copy_B.data[j][1]) {
				copy_A.data[i][0] += copy_B.data[j][0];
				copy_B = delete_elment(copy_B, j);
			}
		}
	}
	return apply_poly(copy_A, copy_B);
}
// tru 2 da thuc
poly sub_poly(poly& A, poly& B) {
	poly copy_A = A;
	poly copy_B = B;
	for (int i = 0; i < A.num; i++) {
		for (int j = 0; j < B.num; j++) {
			if (copy_A.data[i][1] == copy_B.data[j][1]) {
				copy_A.data[i][0] -= copy_B.data[j][0];
				copy_B = delete_elment(copy_B, j);
			}
		}
	}
	for (int i = 0; i < copy_B.num; i++) {
		copy_B.data[i][0] *= -1;
	}
	return apply_poly(copy_A, copy_B);
}
// nhan 2 da thuc
poly mult_poly(poly& A, poly& B) {
	poly multpoly;
	multpoly.num = 0;
	// tao da thuc tich  = 0;
	poly copy_A = A;
	poly copy_B = B;
	for (int i = 0; i < A.num; i++) {
		for (int j = 0; j < B.num; j++) {
			copy_B.data[j][0] *= copy_A.data[i][0] ;
			copy_B.data[j][1] += copy_A.data[i][1] ;
		}
		multpoly = add_poly(multpoly, copy_B);
		copy_B = B;
	}
	return multpoly;
}
// chia 2 da thuc
poly divide_poly(poly& A, poly& B) {
	A = sort_descending(A);
	B = sort_descending(B);
	poly divpoly;
	if (A.data[0][1] < A.data[0][1]) {
		divpoly.num = -1;
		return divpoly;
	}
	poly polydivided = A;
	poly polydive = B;
	poly polyduw = A;
	poly loai = B;
	divpoly.num = 1;
	divpoly.data[0][0] = (double)polydivided.data[0][0] / polydive.data[0][0];
	divpoly.data[0][1] = polydivided.data[0][1] - polydive.data[0][1];
	while (polyduw.data[0][1] < polydive.data[0][1]) {
		// nhan thuong lai so chia ra loại
		for (int i = 0; i < loai.num; i++) {
			loai.data[i][0] *= divpoly.data[divpoly.num - 1][0];
			loai.data[i][1] += divpoly.data[divpoly.num - 1][1];
		}
		polyduw = sub_poly(polydivided, loai);
		divpoly.data[divpoly.num][0] = (double)polyduw.data[0][0] / polydive.data[0][0];
		divpoly.num++;
		loai = B;
	}
}
// dao ham
poly derivate_poly(poly& A) {
	for (int i = 0; i < A.num; i++) {
		if (A.data[i][1] == 0) A.data[i][0] = 0;
		A.data[i][0] *= A.data[i][1];
	}
	return A;
}
// dao ham bac k
poly derivate_oder_k(poly& A, int k) {
	A = derivate_poly(A);
	for (int i = 0; i < k; i++) {
		A = derivate_poly(A);
	}
	return A;
}
