#include<iostream>
#include<queue>
using namespace std;
class node{
    public:
        int data;
        node* right;
        node* left;

    node(int data){
        this->data = data;
        this->right = NULL;
        this->left = NULL;
    }
};
node* BuildTree(node* root){
    cout<<"Enter the data: "<<endl;
    int data;
    cin>>data;
    if(data == -1){
        return NULL;
    }
    root = new node(data);
    cout<<"Enter data for inserting in left of data: "<<data<<endl;
    root->left = BuildTree(root->left);

    cout<<"Enter data for inserting in right of data: "<<data<<endl;
    root->right = BuildTree(root->right);

    return root;
}
void levelOrderTraversal(node* root){
    queue<node*>q;
    q.push(root);
    while(!q.empty()){
        node* temp = q.front();
        cout<<temp->data<<" ";
        q.pop();
        if(temp->left){
            q.push(temp->left);
        }
        if(temp->right){
            q.push(temp->right);
        }
    }

}
void inorder(node* root){
    //LNR
    //base case
    if(root == NULL){
        return;
    }
    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right);
}
void preorder(node* root){
    //NLR
    //base case
    if(root == NULL){
        return;
    }
    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
}
void postorder(node* root){
    //LRN
    //base case
    if(root == NULL){
        return;
    }
    postorder(root->left);
    postorder(root->right);
    cout<<root->data<<" ";
}
//height of binary tree
int height(node* root){
    if(root == NULL){
        return 0;
    }
    int left = height(root->left);
    int right = height(root->right);

    int ans = max(left,right)+1;
    return ans;
}

// int diameter(node* root){
//     if(root == NULL){
//         return 0;
//     }
//     int op1 = diameter(root->left);
//     int op2 = diameter(root->right);
//     int op3 = height(root->left) + 1 + height(root->right);

//     int ans = max(op1, max(op2, op3));
//     return ans;
// }


//Diameter of binary tree
pair<int, int> diameterFast(node* root){
    if(root == NULL){
        pair<int, int> p = make_pair(0,0);
        return p;
    }
    pair<int, int> left = diameterFast(root->left);
    pair<int, int> right = diameterFast(root->right);

    pair<int, int> ans;
    ans.first = max(left.first, max(right.first, left.second + right.second+ 1));
    ans.second = max(left.second, right.second)+1;

    return ans;
}
int diameter(node* root){
    pair<int, int> ans = diameterFast(root);
    return ans.first;
}
//check for balanced tree

bool isBalanced(node* root){
    if(root == NULL){
        return true;
    }
    bool left = isBalanced(root->left);
    bool right = isBalanced(root->right);

    bool diff = height(root->left) - height(root->right) <=1;

    if(left && right && diff){
        return true;
    }else{
        return false;
    }
}

//Zig Zag traversal: 

void zigzagTraversal(node* root){
    queue<node*>q;
    q.push(root);
    vector<int>res;
    bool leftToRight = true;
    while(!q.empty()){
        int size = q.size();    
        vector<int>ans(size);
        for(int i=0;i<size;i++){
            node* temp = q.front();
            q.pop();
            // ans.push_back(temp->data);
            int pos = size-i-1;
            int index = leftToRight?i:pos;
            ans[index] = temp->data;

            if(temp->left != NULL){
                q.push(temp->left);
            }
            if(temp->right != NULL){
                q.push(temp->right);
            }
        }
        leftToRight = !leftToRight;
        for(auto i: ans){
            res.push_back(i);
        }
    }

    for(auto i: res){
        cout<<i<<" ";
    }

}

//boundry traversal: 


//Traverse in left part of tree: 
void leftTraverse(node* root, vector<int> &ans){
    if(root == NULL){
        return;
    }
    if(root->left == NULL && root->right == NULL){
        return;
    }
    ans.push_back(root->data);
    if(root->left){
        leftTraverse(root->left, ans);
    }else{
        leftTraverse(root->right, ans);
    }

}
//traverse in leaf node:
void leafTraverse(node* root, vector<int> &ans){
    if(root == NULL){
        return;
    }
    if(root->left == NULL && root->right == NULL){
        ans.push_back(root->data);
        return;
    }
    leafTraverse(root->left, ans);
    leafTraverse(root->right, ans);
}
//traverse in right of tree: 
void rightTraverse(node* root, vector<int> &ans){
    if(root == NULL){
        return;
    }
    if(root->left == NULL && root->right == NULL){
        return;
    }
    if(root->right){
        rightTraverse(root->right, ans);
    }else{
        rightTraverse(root->left, ans);
    }

    ans.push_back(root->data);
}
void boundryTraversal(node* root){
    //1 2 3 -1 -1 5 6 -1 -1 8 -1 -1 4 -1 7 -1 9 10 -1 -1 11 -1 -1
    vector<int>ans;
    if(root == NULL){
        return;
    }
    ans.push_back(root->data);
    //left boundry
    leftTraverse(root->left, ans);
    //leaf nodes traverse
    //traverse in left subtree
    leafTraverse(root->left, ans);
    //traverse in right subtree
    leafTraverse(root->right, ans);

    //right boundry
    rightTraverse(root->right ,ans);


    for(auto i: ans){
        cout<<i<<" ";
    }



}

int main(){
    node* root = NULL;
    root = BuildTree(root);
    // 3 5 7 -1 -1 9 -1 -1 8 6 -1 -1 5 -1 -1
    cout<<"\n\nprinting level order traversal: "<<endl;
    levelOrderTraversal(root);
    cout<<"\n\nprinting inorder traversal: "<<endl;
    inorder(root);
    cout<<"\n\nprinting postorder traversal: "<<endl;
    postorder(root);
    cout<<"\n\nprinting preorder traversal: "<<endl;
    preorder(root);

    cout<<endl<<endl;
    cout<<"Height of tree is: "<<endl;
    cout<<height(root)<<endl<<endl;

    cout<<"Diameter of Tree is: "<<endl;
    cout<<diameter(root)<<endl;

    cout<<"is balanced or not: "<<endl;
    cout<<isBalanced(root)<<endl;

    cout<<"Printing ZigZag Traversal: "<<endl;
    zigzagTraversal(root);

    cout<<endl<<endl;

    cout<<"Boundry traversal: "<<endl;
    boundryTraversal(root);
 



    return 0;
}
