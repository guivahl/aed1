#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node
{
    int value;
    struct Node *left, *right;
};
typedef struct Node Node;

void show (Node *root){ 
    if(root != NULL){
        printf("%d\n", root->value);
        show(root->left);
        show(root->right);
    }
}

int height(Node *root)
{
    int leftHeight, rightHeight;

    if (root == NULL)
        return 0;

    leftHeight = height(root->left);
    rightHeight = height(root->right);

    if (leftHeight > rightHeight)
        return leftHeight + 1;

    return rightHeight + 1;
}

int balanceFactory(Node *root)
{
    if (root == NULL)
        return 0;

    return height(root->left) - height(root->right);
}

void rotateSimpleLeft(Node **root)
{
    Node *aux = NULL;

    aux = (*root)->right;
    (*root)->right = aux->left;
    aux->left = (*root);
    (*root) = aux;
}

void rotateSimpleRight(Node **root)
{
    Node *aux = NULL;

    aux = (*root)->left;
    (*root)->left = aux->right;
    aux->right = (*root);
    (*root) = aux;
}

int rotateDoubleLeft(Node **root)
{
    int balance = balanceFactory((*root)->left);

    if (balance > 0)
    {
        rotateSimpleRight(root);
        return 1;
    }

    if (balance < 0)
    {
        rotateSimpleLeft(&((*root)->left));
        rotateSimpleRight(root);
        return 1;
    }

    return 0;
}

int rotateDoubleRight(Node **root)
{
    int balance = balanceFactory((*root)->right);

    if (balance < 0)
    {
        rotateSimpleLeft(root);

        return 1;
    }

    if (balance > 0)
    {
        rotateSimpleRight(&((*root)->right));
        rotateSimpleLeft(root);

        return 1;
    }

    return 0;
}

int balanceTree(Node **root)
{
    int fb = balanceFactory(*root);

    if (fb > 1)
        return rotateDoubleLeft(root);
    if (fb < -1)
        return rotateDoubleRight(root);

    return 0;
}

int insert(Node **root, int value)
{
    if (*root == NULL)
    {
        *root = (Node *) malloc(sizeof(Node));
        (*root)->value = value;
        (*root)->left = NULL;
        (*root)->right = NULL;

        return 1;
    }

    if ((*root)->value > value)
    {
        if (insert(&(*root)->left, value))
        {
            if (balanceTree(root))
                return 0;
            else
                return 1;
        }
    }

    else if ((*root)->value < value)
    {
        if (insert(&(*root)->right, value))
        {
            if (balanceTree(root))
                return 0;
            else
                return 1;
        }
        else
            return 0;
    }
    
    return 0;
}

void freeTree (Node *root) { 
    if(root != NULL){
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

void createUserTree (Node *root)  {
    int quantity = 0, value = 0, iterator;

    srand(time(0));  

    printf("Quantos nodos deseja inserir?\n");
    scanf("%d", &quantity);
    
    for (int iterator = 0; iterator < quantity; iterator++) {
        value = rand() % 1000;

        printf("Inserindo na posição %d o valor %d\n", value, quantity);

        insert(&root, value);
    }

    if (root == NULL) {
        printf("Árvore vazia!\n");
    }
    else {
        if (balanceFactory(root) >= -1 && balanceFactory(root) <= 1) {
            printf("\nÁrvore AVL\n");
        }
        else {
            printf("\nNão é árvore AVL\n");
        }
    }

    freeTree(root);
}

void testTree (Node *root)  {
    int values[] = {30,5,15,7,9,27,25,35,33}, valuesSize = 9;

    srand(time(0));  
    
    for (int iterator = 0; iterator < valuesSize; iterator++) {
        printf("Inserindo na posição %d o valor %d\n", iterator, values[iterator]);
        insert(&root, values[iterator]);
    }

    if (root == NULL) {
        printf("Árvore vazia!\n");
    }
    else {
        if (balanceFactory(root) >= -1 && balanceFactory(root) <= 1) {
            printf("\nÁrvore AVL\n");
        }
        else {
            printf("\nNão é árvore AVL\n");
        }
    }
    
    printf("Inserindo o valor %d\n", root->value);

    show(root);
    freeTree(root);
    // free(root);
}

int main()
{
    int options = 0;
    Node *root = NULL;

    printf("Deseja definir quantos nós? Digite 1.\nDeseja rodar os testes? Digite 2.\nSair? Digite 3.\n");
    scanf("%d", &options);
        
    switch (options){
        case 1:
            createUserTree(root);
            break;
        case 2:
            testTree(root);
            break;
        case 3:
        default:
            break;
    }

    return 0;
}
