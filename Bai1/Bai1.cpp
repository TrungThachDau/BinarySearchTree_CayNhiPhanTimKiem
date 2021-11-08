#include <iostream>
#include <fstream>
using namespace std;
struct Node
{
	int data;
	Node* left;
	Node* right;
};
typedef Node* Tree;
Tree root;
void createTree(Tree& root)
{
	{
		root = NULL;
	}
}
Node* createNode(int x)
{
	Node* p = new Node;
	p->data = x;
	p->right = NULL;
	p->left = NULL;
	return p;
}
void addNode(Tree& root, Node* p)
{
	if (root != NULL)
	{
		if (root->data == p->data)
			return;
		else if (root->data < p->data)
			addNode(root->right, p);
		else
			addNode(root->left, p);
	}
	else
		root = p;
}
void createTreeFromFile(Tree& root, string filename)
{
	ifstream f;
	f.open(filename);
	if (f.eof()) cout << "Không tìm thấy file";
	else
	{
		int n;
		int x;
		f >> n;
		createTree(root);
		for (int i = 1; i <= n; i++)
		{
			f >> x;
			Node* p = createNode(x);
			addNode(root, p);
		}
	}
	f.close();
}
void NLR(Tree root)
{
	if (root != NULL)
	{
		cout << root->data << " ";
		NLR(root->left);
		NLR(root->right);
	}
}
Node* findNode(Tree root, int x)
{
	if (root == NULL) return NULL;
	else
	{
		if (root->data > x)
			findNode(root->left, x);
		else if (root->data < x)
			findNode(root->right, x);
		else
			return root;
	}
}
void findNodeReplace(Tree &root,Tree q)
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
void deleteNode(Tree& root, int x)
{
	if (root == NULL)
		return;
	else
	{
		if (root->data > x)
			deleteNode(root->left, x);
		else if (root->data < x)
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
void maxNode(Tree root)
{
	Node* p = root;
	while (p->right != NULL)
	{
		p = p->right;
	}
	cout << p->data;
}
void minNode(Tree root)
{
	Node* p = root;
	while (p->left != NULL)
	{
		p = p->left;
	}
	cout << p->data;
}
void showNodeOfLevelK(Tree root, int k)
{
	if (root == NULL)
		return;
	else if (k == 0)
		cout << root->data;
	else
	{
		k--;
		cout << root->data << " ";
		showNodeOfLevelK(root->left, k);
		showNodeOfLevelK(root->right, k);
	}
}
void showNodeIsLeafOfLevelK(Tree root, int k)
{
	if (root == NULL)
		return;
	else
	{
		
		if (k == 0 && root->left == NULL && root->right == NULL)
				cout << root->data;
		else
		{
			k--;
			cout << root->data << " ";
			showNodeIsLeafOfLevelK(root->left, k);
			showNodeIsLeafOfLevelK(root->right, k);
		}
	}
}
void NodeLeaf(Tree root)
{
	if (root != NULL)
	{
		if (root->left == NULL && root->right == NULL)
			cout << root->data << " ";
		NodeLeaf(root->left);
		NodeLeaf(root->right);
	}
}
void deleteTree(Tree& root)
{
	if (root == NULL) return;
	deleteTree(root->left);
	deleteTree(root->right);
	delete root;
}
int maxDistance(Tree root, int x)
{
	if (root == NULL) return -1;
	else
	{
		Node* minLeft = root;
		while (minLeft->left != NULL)
			minLeft = minLeft->left;
		Node* maxRight = root;
		while (maxRight->right != NULL)
			maxRight = maxRight->right;
		int dis1 = abs(x - minLeft->data);
		int dis2 = abs(x - maxRight->data);
		if (dis1 > dis2)
			return minLeft->data;
		else
			return maxRight->data;
	}
}
int sumofNode(Tree root)
{
	if (root == NULL) return 0;
	
	else
	{
		return root->data + sumofNode(root->left) + sumofNode(root->right);
	}
}
void menu()
{
	//system("pause");
	//system("cls");
	cout << "\n1. Nhập cây từ file";
	cout << "\n2. Duyệt NLR";
	cout << "\n3. Tìm kiếm nút";
	cout << "\n4. Xóa nút";
	cout << "\n5. Tìm nút lớn nhất và lớn nhất";
	cout << "\n6. Xuất nút ở mức k";
	cout << "\7. Xuất nút lá ở mức k";
	cout << "\n8. Xuất nút lá";
	cout << "\n9. Tổng các nút";
	cout << "\n10.Xuat cac so hoan thien";
	cout << "\nChọn chức năng: ";
}
int main()
{
	Tree root;
	createTree(root);
	int cn;
	do
	{
		menu();
		cin >> cn;
		switch (cn)
		{
		case 1:
		{
			string filename="file.txt";
			//cout << "Nhập tên file: ";
			//cin >> filename;
			createTreeFromFile(root, filename); break;
		}
		case 2:
		{
			NLR(root); break;
		}
		case 3:
		{
			int x;
			cout << "Nhập x tìm kiếm: ";
			cin >> x;
			Node* p = findNode(root,x);
			if (p == NULL)
				cout << "Không tìm thấy nút";
			else 
				cout << "Tìm thấy nút";
			break;
		}
		case 4:
		{
			int x;
			cout << "Nhập nút cần xóa: ";
			cin >> x;
			deleteNode(root,x);
			NLR(root);
			break;
		}
		case 5:
		{
			cout << "MAX=";
			maxNode(root);
			cout << "\nMIN= ";
			minNode(root); break;
		}
		case 6:
		{
			int k;
			cout << "Nhập mức của cây(NLR): ";
			cin >> k;
			showNodeOfLevelK(root, k); break;
		}
		case 7:
		{
			int k;
			cout << "Nhập mức của cây(NLR): ";
			cin >> k;
			showNodeIsLeafOfLevelK(root, k); break;
		}
		case 8:
		{
			NodeLeaf(root);
		}
		case 9:
		{
			cout << "Tong la: " << sumofNode(root);
		}
		default:
			break;
		}
	} while (cn!=0);
}