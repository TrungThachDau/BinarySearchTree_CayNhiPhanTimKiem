#include <iostream>
using namespace std;
struct PhanSo
{
	int tu, mau;
};
struct Node
{
	PhanSo data;
	Node* left;
	Node* right;
};
typedef Node* Tree;
Tree root;
PhanSo x;
int n;
void createTree(Tree& root)
{
	root = NULL;
}
Node* createNode(PhanSo x)
{
	Node* p = new Node;
	p->data.tu = x.tu;
	p->data.mau = x.mau;
	p->left = NULL;
	p->right = NULL;
	return p;
}
void addNode(Tree& root, Node* p)
{
	if (root != NULL)
	{
		if (root->data.tu == p->data.tu&& root->data.mau == p->data.mau)
			return;
		else if (root->data.tu < p->data.tu&& root->data.mau < p->data.mau)
			addNode(root->right, p);
		else
			addNode(root->left, p);
	}
	else
		root = p;
}
void createTreeFromArray(Tree& root,PhanSo a[], int n)
{
	for (int i = 1; i <= n; i++)
	{
		a[i].tu=rand()%49;
		a[i].mau = rand() & 49;
		Node*p=createNode(a[i]);
		addNode(root, p);
	}
}
void NLR(Tree root)
{
	if (root != NULL)
	{
		cout << root->data.tu<<"/"<<root->data.mau<<" ";
		NLR(root->left);
		NLR(root->right);
	}
}
void addOneNode(Tree& root)
{
	cout << "Nhap tu: ";
	cin >>x.tu;
	cout << "Nhap mau: ";
	cin >> x.mau;
	Node* p = createNode(x);
	addNode(root, p);
}
Node* findNode(Tree root,PhanSo x)
{
	if (root == NULL)
		return 0;
	else
	{
		if (root->data.tu > x.tu && root->data.mau > x.mau)
			findNode(root->left, x);
		else if (root->data.tu < x.tu && root->data.mau < x.mau)
			findNode(root->right, x);
		else
			return root;
	}
}
void findNodeReplace(Tree& root, Tree q)
{//Node q là node thế mạng
	if (q->left != NULL)//duyệt bên trái nhất
		findNodeReplace(root, q->left);//tìm node trái nhất
	else
	{
		root->data = q->data;//cập nhật data node cần xóa chính là node thế mạng
		root = q;//trỏ root đến node thế mạng
		q = q->right;//cập nhật mối liên kết
	}
}
void deleteNode(Tree& root, PhanSo x)
{
	if (root == NULL)
		return;
	else
	{
		if (root->data.tu > x.tu && root->data.mau > x.mau)
			deleteNode(root->left, x);
		else if (root->data.tu < x.tu && root->data.mau < x.mau)
			deleteNode(root->right, x);
		else
		{
			Node* p = root;
			if (root->left == NULL)
				root = root->right;
			else if (root->right == NULL)
				root = root->left;
			else
				findNodeReplace(root, p);
			delete p;
		}
	}
}
int UCLN(int a, int b) {
	if (a == b) return a;
	if (a > b)
		UCLN(a - b, b);
	else
		UCLN(a, b - a);
}
int BCNN(int a, int b) {
	return (a * b / UCLN(a, b));
}
float Tong(PhanSo a, PhanSo b)
{
	int tu, mau;
	tu = a.tu * b.mau + a.mau * b.tu;
	mau = a.mau * b.mau;
	return (float)tu / mau;
}
//PhanSo Cong(PhanSo a, PhanSo b, PhanSo c)
//{
//	PhanSo tong = (a.tu / a.mau) + (b.tu / b.mau) + (c.tu / c.mau);
//	return tong;
//}
float sumofNode(Tree root)
{
	if (root != NULL)
	{
		float a = sumofNode(root->left);
		float b = sumofNode(root->right);
		return (root->data.tu / root->data.mau) + a+b;
	}
}
PhanSo findMax(Tree root)
{
	if (root->left == NULL)
	{
		return root->data;
	}
	return findMax(root->left);
	//duyet den nut cuoi cung nhat ben cay con phai==max;
}
PhanSo findMin(Tree root)
{
	if (root->right == NULL)
	{
		return root->data;
	}
	return findMax(root->left);
}
void lietKePhanSoTuLonHonMau(Tree root)
{
	if (root != NULL)
	{
		if (root->data.tu > root->data.mau)
			cout << root->data.tu << "/" << root->data.mau << " ";
		lietKePhanSoTuLonHonMau(root->left);
		lietKePhanSoTuLonHonMau(root->right);
	}
}
bool kiemTraSNT(int n)
{
	if (n < 2) return false;
	int i = 2;
	while (i < n)
	{
		if (i % n == 0)
		{
			return false;
			break;
		}
		i++;
	}
	return true;
}
void lietKePhanSoTuMauLaSNT(Tree root)
{
	if (root != NULL)
	{
		if (kiemTraSNT(root->data.tu)==1&& kiemTraSNT(root->data.mau)==1)
			cout << root->data.tu << "/" << root->data.mau << " ";
		lietKePhanSoTuLonHonMau(root->left);
		lietKePhanSoTuLonHonMau(root->right);
	}
}
void menu()
{
	cout << "\n1. Tao cay tu mang";
	cout << "\n2. Duyet NLR";
	cout << "\n3.Them 1 nut";
	cout << "\n4. Tim kiem 1 phan so";
	cout << "\n5.";
	cout << "\n6. Tong phan so";
	cout << "\n7. Tim phan so lon nhat va nho nhat";
	cout << "\n8.Liet ke cac phan so co tu so lon hon mau so";
	cout << "\n9.Liet ke cac PS tu va mau la So Nguyen To";
	cout << "\n Chon chuc nang: ";
}
int main()
{
	Tree root;

	int cn;
	createTree(root);
	do
	{
		menu();
		cin >> cn;
		switch (cn)
		{
		case 1:
		{
			PhanSo a[20];
			n = 10;
			createTreeFromArray(root, a, n); break;
		}
		case 2:
		{
			NLR(root); break;
		}
		case 3:
		{
			addOneNode(root); break;
		}
		case 4:
		{
			cout << "Nhap tu so: ";
			cin >> x.tu;
			cout << "Nhap mau so: ";
			cin >> x.mau;
			Node* k = findNode(root,x);
			if (k == NULL)
				cout << "Khong tim thay phan so";
			else
				cout << "Tim thay phan so"; break;
		}
		case 5:
		{
			cout << "Nhap tu so: ";
			cin >> x.tu;
			cout << "nhap mau so: ";
			cin >> x.mau;
			deleteNode(root, x);
		}
		case 6:
		{
			
			cout << sumofNode(root);
		}
		case 7:
		{
			PhanSo a = findMax(root);
			cout << "Max la: " << a.tu << "/" << a.mau; break;
		}
		case 8:
		{
			lietKePhanSoTuLonHonMau(root); break;
		}
		case 9:
		{
			lietKePhanSoTuMauLaSNT(root); break;
		}
		default:
			break;
		}

	} while (cn!=0);
	return 0;
}