#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
int d, t;
class Node
{
private:
    /* data */
public:
    vector<int> A;
    vector<Node *> B;
    bool isDataNode;
    Node *Parent;
    Node()
    {
        isDataNode = true;
        Parent = nullptr;
    }
    bool aboveMaxSize()
    {
        if (isDataNode)
        {
            if (A.size() > 2 * d)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            if (A.size() > 2 * t + 1)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
};
// REASON TO MAINTAIN SINGLE NODE
// IN INDEX NODE LAST NODES POINTS TO DATA NODE WHEREAS OTHER POINTS INDEX NODE ONLY

class BplusTree
{
private:
    /* data */
public:
    Node *root;
    BplusTree()
    {
        root = nullptr;
    }
    void insert(int v)
    {
        // CREATION OF TREE AND INSERT OF 1ST VALUE
        if (root == nullptr)
        {
            Node *x = new Node();
            x->isDataNode = true;
            x->A.push_back(v);
            x->Parent = nullptr;
            root = x;
            return;
        }

        // TREE WITH ONLY ROOT NODE
        if (root->B.size() == 0)
        {
            root->A.push_back(v);
            sort(root->A.begin(), root->A.end());
            if (root->aboveMaxSize())
            {
                // cout<<"CORRECT"<<endl;
                Node *L = new Node();
                Node *M = new Node();
                Node *R = new Node();
                L->isDataNode = true;
                M->isDataNode = false;
                R->isDataNode = true;
                L->Parent = M;
                R->Parent = M;
                for (int i = 0; i < d; i++)
                {
                    L->A.push_back(root->A[i]);
                }
                M->A.push_back(root->A[d]);
                for (int i = d; i < 2 * d + 1; i++)
                {
                    R->A.push_back(root->A[i]);
                }
                M->B.push_back(L);
                M->B.push_back(R);
                root = M;
            }
            return;
        }

        // TREE WITH INDEX NODES

        // REACHING TILL DATA NODE
        Node *ptr = root;
        while (!ptr->isDataNode)
        {
            if (v > ptr->A[ptr->A.size() - 1])
            {
                ptr = ptr->B[ptr->B.size() - 1];
                continue;
            }
            else
            {
                for (int i = 0; i < ptr->A.size(); i++)
                {
                    if (v < ptr->A[i])
                    {
                        ptr = ptr->B[i];
                        break;
                    }
                }
                continue;
            }
        }

        // REACHED DATA NODE
        // ptr

        ptr->A.push_back(v);
        sort(ptr->A.begin(), ptr->A.end());

        if (!ptr->aboveMaxSize())
        {
            return;
        }
        else
        {
            // PASSING FROM DATA NODE TO INDEX NODE
            Node *L = new Node();
            Node *R = new Node();
            L->isDataNode = true;
            R->isDataNode = true;
            for (int i = 0; i < d; i++)
            {
                L->A.push_back(ptr->A[i]);
            }
            for (int i = d; i < 2 * d + 1; i++)
            {
                R->A.push_back(ptr->A[i]);
            }
            Node *ptr2 = ptr->Parent;
            L->Parent = ptr2;
            R->Parent = ptr2;
            //  if (v == 253)
            // {
            //     cout << "HERE" << endl;
            //     return;
            // }
            // if(ptr2==nullptr)
            // {
            //     cout<<" NULL";
            //     return;
            // }
            if (ptr2->A[ptr2->A.size() - 1] < ptr->A[d])
            {
                ptr2->B.erase(ptr2->B.end() - 1);
                ptr2->B.push_back(L);
                ptr2->B.push_back(R);
                ptr2->A.push_back(ptr->A[d]);
            }
            else
            {

                for (int i = 0; i < ptr2->A.size(); i++)
                {
                    if (ptr->A[d] < ptr2->A[i])
                    {
                        ptr2->A.insert(ptr2->A.begin() + i, ptr->A[d]);
                        ptr2->B.erase(ptr2->B.begin() + i);
                        ptr2->B.insert(ptr2->B.begin() + i, R);
                        ptr2->B.insert(ptr2->B.begin() + i, L);
                        break;
                    }
                }
            }

            // NOW WE HAVE SHIFTED THE NODE UP AND SEEING IS IT FULLED
            while (ptr2->aboveMaxSize())
            {
                if (ptr2->Parent == nullptr)
                {
                    Node *X = new Node();
                    Node *Y = new Node();
                    Node *Z = new Node();
                    X->isDataNode = false;
                    Y->isDataNode = false;
                    Z->isDataNode = false;
                    X->Parent = Y;
                    Z->Parent = Y;
                    for (int i = 0; i < t; i++)
                    {
                        X->A.push_back(ptr2->A[i]);
                        X->B.push_back(ptr2->B[i]);
                    }
                    X->B.push_back(ptr2->B[t]);
                    // UPDATING PARENT
                    for (int i = 0; i < X->B.size(); i++)
                    {
                        X->B[i]->Parent = X;
                    }
                    for (int i = t + 1; i < 2 * t + 2; i++)
                    {
                        Z->A.push_back(ptr2->A[i]);
                        Z->B.push_back(ptr2->B[i]);
                    }
                    Z->B.push_back(ptr2->B[2 * t + 2]);
                    // UPDATING PARENT
                    for (int i = 0; i < Z->B.size(); i++)
                    {
                        Z->B[i]->Parent = Z;
                    }
                    Y->A.push_back(ptr2->A[t]);
                    Y->B.push_back(X);
                    Y->B.push_back(Z);
                    root = Y;
                    return;
                }
                else
                {
                    Node *X = new Node();
                    Node *Z = new Node();
                    Node *ptr3 = ptr2->Parent;
                    X->isDataNode = false;
                    Z->isDataNode = false;
                    X->Parent = ptr3;
                    Z->Parent = ptr3;
                    for (int i = 0; i < t; i++)
                    {
                        X->A.push_back(ptr2->A[i]);
                        X->B.push_back(ptr2->B[i]);
                    }
                    X->B.push_back(ptr2->B[t]);
                    // UPDATING PARENT
                    for (int i = 0; i < X->B.size(); i++)
                    {
                        X->B[i]->Parent = X;
                    }

                    for (int i = t + 1; i < 2 * t + 2; i++)
                    {
                        Z->A.push_back(ptr2->A[i]);
                        Z->B.push_back(ptr2->B[i]);
                    }
                    Z->B.push_back(ptr2->B[2 * t + 2]);
                    // UPDATING PARENT
                    for (int i = 0; i < Z->B.size(); i++)
                    {
                        Z->B[i]->Parent = Z;
                    }

                    if (ptr3->A[ptr3->A.size() - 1] < ptr2->A[t])
                    {
                        ptr3->B.erase(ptr3->B.end() - 1);
                        ptr3->B.push_back(X);
                        ptr3->B.push_back(Z);
                        ptr3->A.push_back(ptr2->A[t]);
                    }
                    else
                    {
                        for (int i = 0; i < ptr3->A.size(); i++)
                        {
                            if (ptr2->A[t] < ptr3->A[i])
                            {
                                ptr3->B.erase(ptr3->B.begin() + i);
                                ptr3->B.insert(ptr3->B.begin() + i, Z);
                                ptr3->B.insert(ptr3->B.begin() + i, X);
                                ptr3->A.insert(ptr3->A.begin() + i, ptr2->A[t]);
                                break;
                            }
                        }
                    }
                    ptr2 = ptr3;
                }
            }
        }
        return;
    }
    void displayTree(Node *ptr, int &x, int &y)
    {

        if (ptr == nullptr)
        {
            return;
        }
        if (ptr->isDataNode)
        {
            x = x + 1;
            return;
        }
        else
        {
            y = y + 1;
            for (int i = 0; i < ptr->B.size(); i++)
            {
                displayTree(ptr->B[i], x, y);
            }
            return;
        }
        return;
    }
    void display(Node *ptr)
    {
        if (ptr == nullptr)
        {
            return;
        }
        cout << "IS DATA NODE : " << ptr->isDataNode << " Parent Size : ";
        if (ptr->Parent == nullptr)
        {
            cout << " NULL ";
        }
        else
        {
            cout << ptr->Parent->A.size() << " "
                 << " Parent Elements: ";
            for (int i = 0; i < ptr->Parent->A.size(); i++)
            {
                cout << ptr->Parent->A[i] << " ";
            }
        }
        cout << endl;
        cout << "No of elements in That Node : " << ptr->A.size() << " No of Children in That Node : " << ptr->B.size() << endl;
        for (int i = 0; i < ptr->A.size(); i++)
        {
            cout << ptr->A[i] << " ";
        }
        cout << " DISPLAYED NODE " << endl
             << endl;
        for (int i = 0; i < ptr->B.size(); i++)
        {
            display(ptr->B[i]);
        }
        return;
    }
};

int main()
{
    cin >> d >> t;
    BplusTree T;
    int x;
    while (cin >> x)
    {
        if (x == 1)
        {
            int y;
            cin >> y;
            T.insert(y);
        }
        else if (x == 2)
        {

            int a = 0, b = 0;
            T.displayTree(T.root, a, b);
            // a -> no of data nodes
            cout << b << " " << a << " ";
            if (T.root != nullptr)
            {
                for (int i = 0; i < T.root->A.size(); i++)
                {
                    cout << T.root->A[i] << " ";
                }
            }
            cout << endl;
            // T.display(T.root);
        }
        else if (x == 3)
        {
            return 0;
        }
    }
    return 0;
}