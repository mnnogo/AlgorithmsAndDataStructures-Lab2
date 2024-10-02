#include <iostream>
#include <Windows.h>
#include <iomanip>
using namespace std;

struct BinaryTree
{
    int data;
    BinaryTree* left;
    BinaryTree* right;
};

static BinaryTree* MakeBinaryTree(int n, int numbers[])
{
    BinaryTree* head = new BinaryTree();

    BinaryTree* current = head; // текущий узел

    while (n > 0)
    {
        current->data = numbers[--n];

        // при попадании в последний листовой узел, он никуда не должен указывать
        if (n <= 0)
        {
            current->left = current->right = nullptr;
            break;
        }

        // определение какой дочерний узел будет листовым, какой внутренним
        BinaryTree** leafNode;
        BinaryTree** internalNode;
        if ((double)rand() / RAND_MAX < 0.5)
        {
            leafNode = &current->left;
            internalNode = &current->right;
        }
        else
        {
            leafNode = &current->right;
            internalNode = &current->left;
        }

        // делаем этот узел листовым
        *leafNode = new BinaryTree();
        (*leafNode)->data = numbers[--n];
        (*leafNode)->left = nullptr;
        (*leafNode)->right = nullptr;

        // переходим к дочернему внутреннему узлу и повторяем алгоритм
        *internalNode = new BinaryTree();

        current = *internalNode;
    }

    return head;
}

static void PrintTree(BinaryTree* node)
{
    if (node != NULL)
    {
        cout << setw(3) << node->data;
        PrintTree(node->left);
        PrintTree(node->right);
    }
}

static bool isLeaf(BinaryTree* node)
{
    return node->left == nullptr && node->right == nullptr;
}

static BinaryTree* AddLeafValues(BinaryTree* node)
{
    if (node == nullptr)
        return nullptr;

    if (node->left == nullptr || node->right == nullptr)
        return nullptr;

    // проверка какой дочерний элемент лист, или оба если это конец дерева
    bool isLeftLeaf = isLeaf(node->left);
    bool isRightLeaf = isLeaf(node->right);

    if (isLeftLeaf && isRightLeaf)
        return nullptr;

    if (isLeftLeaf)
    {
        cout << "К листовой вершине со значением " << node->left->data << " было добавлено значение внутренней вершины " << node->right->data;
        node->left->data += node->right->data;
        cout << ". Новое значение = " << node->left->data << endl;
    }
    else if (isRightLeaf)
    {
        cout << "К листовой вершине со значением " << node->right->data << " было добавлено значение внутренней вершины " << node->left->data;
        node->right->data += node->left->data;
        cout << ". Новое значение = " << node->right->data << endl;
    }
    else
    {
        throw exception("Невозможная ситуация, ошибка в алгоритме.");
    }

    AddLeafValues(node->left);
    AddLeafValues(node->right);

    return node;
}

int main()
{
    setlocale(0, "");
    SetConsoleCP(1251);

    int N;
    do
    {
        cout << "Введите число вершин N (нечетное): ";
        cin >> N;
    } while (N < 1 || N % 2 == 0);

    int* numbers = new int[N];
    for (int i = 0; i < N; i++)
    {
        cout << "Введите число №" << i + 1 << ": ";
        cin >> numbers[i];
    }

    BinaryTree* bTree = MakeBinaryTree(N, numbers);

    system("cls");
    cout << "Вы ввели набор из " << N << " чисел: [";
    for (int i = 0; i < N - 1; i++)
    {
        cout << numbers[i] << " ";
    }
    cout << numbers[N - 1] << "]" << endl << endl;

    cout << "Указатель на корень созданного дерева: " << bTree << endl << endl;

    cout << "Элементы бинарного дерева при прямом обходе" << endl;
    PrintTree(bTree);

    cout << "\n\nДобавление к значению каждого листа дерева значение соседней дочерней вершины." << endl
        << "История сложений:" << endl;

    BinaryTree* newTree = AddLeafValues(bTree);

    cout << "\nЭлементы нового бинарного дерева при прямом обходе" << endl;
    PrintTree(bTree);
    cout << endl;
}