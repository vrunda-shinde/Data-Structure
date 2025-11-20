#include <iostream>
using namespace std;
class BST
{
  public:
    string name;
    int salary;
    BST* left;
    BST* right;
    BST(string n ,int s)
    {
        name=n;
        salary=s;
        right=left=nullptr;
    }
    
    BST* insert(BST* root,string n,int s)
    {
    if(root==nullptr)
    {
    return new BST(n,s);
    }
    else if(s<root->salary)
    {
       root->left=insert(root->left,n,s);
    }
    else if(s>root->salary)
    {
            root->right=insert(root->right,n,s);
    }
        return root;
    }
    
    void inorder(BST* root)
    {
        if(root==nullptr) return;
        inorder(root->left);
        cout<<root->name<<" "<<root->salary<<endl;
        inorder(root->right);
    }
    BST* search(BST* root,int s)
    {
        if(root==nullptr) return nullptr;
        if(s<root->salary)
        {
            return search(root->left,s);
        }
        else if(s>root->salary)
        {
            return search(root->right,s);
        }
        return root;
    }
    
    BST* findmax(BST* root)
    {
        if(root==nullptr) return nullptr;
            while(root->right!=nullptr)
            {
                root=root->right;
            }
        return root;
    }
    BST* Delete(BST* root, int s)
    {
    if (root == nullptr)
    {
        cout << "Element not present to delete!" << endl;
        return root;
    }
    else if (s < root->salary)
    {
        root->left = Delete(root->left, s);
    }
    else if (s > root->salary)
    {
        root->right = Delete(root->right, s);
    }
    else // Found the node to be deleted
    {
        if (root->left == nullptr && root->right == nullptr) // Case 1: No children
        {
            delete root;
            return nullptr;
        }
        else if (root->left == nullptr) // Case 2: Only right child
        {
            BST* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) // Case 3: Only left child
        {
            BST* temp = root->left;
            delete root;
            return temp;
        }
        else // Case 4: Two children
        {
            BST* temp = findmax(root->left); // Get max value from left subtree
            root->salary = temp->salary;
            root->name = temp->name;
            root->left = Delete(root->left, temp->salary);
        }
    }
    return root;
}

};
int main() {
    BST* root=nullptr;
    BST b(" ",0);
    BST* key;
    BST* de;
    int ch,s,ss,ds;
    string n;
    do
    {
    cout<<"1.insert\n2.display\n3.search\n4.delete\n";
    cin>>ch;
    switch(ch)
    {
        case 1:
                cout<<"enter name:";
                cin>>n;
                cout<<"enter salary:";
                cin>>s;
                root=b.insert(root,n,s);
                break;
        case 2:b.inorder(root);
                break;
        case 3:
              cout<<"search slary:";
              cin>>ss;
              key=b.search(root,ss);
              if(key==nullptr)
              {
                  cout<<"not found!!!\n";
              }
              else
              {
              cout<<"elemnet found \n";
              }
              break;
        case 4:cout<<"delete salry:";
              cin>>ds;
              de=b.Delete(root,ds);
               break;
              
    }
    }while(ch!=5);

    return 0;
}