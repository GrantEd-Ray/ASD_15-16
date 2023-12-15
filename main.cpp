#include <iostream>
#include <string>
#include <windows.h>
#include <stack>

const std::string nums = {"1234567890"};

struct Node
{
    int value;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(std::string& s)
    {
        value = getValue(s);
        s.erase(0, cut(value));
        if (s[0] == '(')
            s = unbracket(s);
        else
            return;

        if (isDigit(s[0]))
            left = new Node(s);
        if (s[0] == ',' && isDigit(s[1]))
        {
            s.erase(0, 1);
            right = new Node(s);
        }
    }

private:
    bool isDigit(char c)
    {
        return nums.find(c) != std::string::npos;
    }
    int cut(int n)
    {
        int i = 0;
        if (n == 0)
            return 1;
        while (n > 0)
        {
            n /= 10;
            i++;
        }
        return i;
    }

    int getValue(std::string& s)
    {
        int temp = 0;
        for (int i = 0; i < s.size(); i++)
            if (isDigit(s[i]))
            {
                temp = temp * 10 + int(s[i] - 48);
                if (!isDigit(s[i + 1]))
                    return temp;
            }
    }

    std::string unbracket(std::string s)
    {
        int brackets = 0;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '(')
                brackets++;

            if (s[i] == ')')
                brackets--;

            if (!brackets)
            {
                s.erase(0, 1);
                s.erase(i - 1, 1);
                return s;
            }
        }
        return s;
    }
};

class BinaryTree
{
    Node* root = nullptr;

public:
    BinaryTree(std::string s)
    {
        root = new Node(s);
    }
    void preOrder()
    {
        preOrderTreeWalk(root);
        std::cout << std::endl;
    }
    void inOrder()
    {
        inOrderTreeWalk(root);
        std::cout << std::endl;
    }
    void postOrder()
    {
        postOrderTreeWalk(root);
        std::cout << std::endl;
    }

    void preOrderTreeWalk(Node* n)
    {
        if (!n)
        {
            return;
        }
        std::cout << n->value << " ";
        preOrderTreeWalk(n->left);
        preOrderTreeWalk(n->right);
    }

    void inOrderTreeWalk(Node* n)
    {
        if (!n)
        {
            return;
        }
        inOrderTreeWalk(n->left);
        std::cout << n->value << " ";
        inOrderTreeWalk(n->right);
    }

    void postOrderTreeWalk(Node* n)
    {
        if (!n)
        {
            return;
        }
        postOrderTreeWalk(n->left);
        postOrderTreeWalk(n->right);
        std::cout << n->value << " ";
    }

    void nonRecursivePreOrder()
    {
        std::stack<Node*> stack;
        Node* temp;
        stack.push(root);
        while (!stack.empty())
        {
            temp = stack.top();
            stack.pop();
            std::cout << temp->value << ' ';
            if (temp->right != nullptr)
                stack.push(temp->right);
            if (temp->left != nullptr)
                stack.push(temp->left);
        }
    }
};

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    std::string s = "8(3(1,6(4,7)),10(,14(13,)))";
    BinaryTree tree(s);

    std::cout << "Рекурсивный прямой обход: ";
    tree.preOrder();

    std::cout << "Рекурсивный центральный обход: ";
    tree.inOrder();

    std::cout << "Рекурсивный обратный обход: ";
    tree.postOrder();

    std::cout << "Нерекурсивный прямой обход: ";
    tree.nonRecursivePreOrder();

    return 0;
}
