#include <stdio.h>
#include <stdlib.h>

struct node {
    int info;
    struct node *left;
    struct node *right;
};

struct node *minValueNode(struct node *node);

void Binsearch(struct node *root, int key) {
    if (root == NULL) {
        printf("The number does not exist");
        exit(1);
    } else if (key == root->info) {
        printf("The searched item is found");
    } else if (key < root->info) {
        Binsearch(root->left, key);
    } else {
        Binsearch(root->right, key);
    }
}

struct node *insert(struct node *root, int item) {
    if (root == NULL) {
        root = (struct node *)malloc(sizeof(struct node));
        root->left = root->right = NULL;
        root->info = item;
    } else if (item < root->info) {
        root->left = insert(root->left, item);
    } else {
        root->right = insert(root->right, item);
    }
    return root;
}

struct node *delete(struct node *root, int key) {
    if (root == NULL) {
        printf("The number does not exist");
        exit(1);
    } else if (key < root->info) {
        root->left = delete(root->left, key);
    } else if (key > root->info) {
        root->right = delete(root->right, key);
    } else {
        if (root->left == NULL) {
            struct node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct node *temp = root->left;
            free(root);
            return temp;
        }
        struct node *temp = minValueNode(root->right);
        root->info = temp->info;
        root->right = delete(root->right, temp->info);
    }
    return root;
}

struct node *minValueNode(struct node *node) {
    struct node *current = node;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

void preorder(struct node *root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->info);
    preorder(root->left);
    preorder(root->right);
}

void postorder(struct node *root) {
    if (root == NULL) {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->info);
}

void inorder(struct node *root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf("%d ", root->info);
    inorder(root->right);
}
void display(struct node *root,int level)
{
	int i;
	if ( root!=NULL )
	{
		display(root->right, level+1);
		printf("\n");
		for (i = 0; i < level; i++)
			printf("    ");
		printf("%d", root->info);
		display(root->left, level+1);
	}
}


int main() {
    struct node *root = NULL;
    int choice, item;

    do {
        printf("1. Search 2. Insert 3. Delete\n");
        printf("4. Preorder 5. Postorder 6. Inorder 7.display 8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter element to search: ");
                scanf("%d", &item);
                Binsearch(root, item);
                break;
            case 2:
                printf("Enter element to insert: ");
                scanf("%d", &item);
                root = insert(root, item);
                break;
            case 3:
                printf("Enter element to delete: ");
                scanf("%d", &item);
                root = delete(root, item);
                break;
                case 4:
                 display(root,0);
                break;
            case 5:
                preorder(root);
                break;
            case 6:
                postorder(root);
                break;
            case 7:
                inorder(root);
                break;
            case 8:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 7);

    return 0;
}
