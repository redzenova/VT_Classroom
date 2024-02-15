class TreeNode {
    char data;
    TreeNode firstChild;
    TreeNode nextSibling;

    TreeNode(char data) {
        this.data = data;
        this.firstChild = null;
        this.nextSibling = null;
    }
}


public void printTree(TreeNode root) {
    printTree(root, 0);
}

private void printTree(TreeNode root, int level) {
    if (root == null) {
        return;
    }
    for (int i = 0; i < level; i++) {
        System.out.print("  ");
    }
    System.out.println(root.data);
    printTree(root.firstChild, level + 1);
    printTree(root.nextSibling, level);
}

public void printPreOrder(TreeNode root) {
    printPreOrder(root, 0);
}

private void printPreOrder(TreeNode root, int level) {
    if (root == null) {
        return;
    }
    for (int i = 0; i < level; i++) {
        System.out.print("  ");
    }
    System.out.println(root.data);
    printPreOrder(root.firstChild, level + 1);
    printPreOrder(root.nextSibling, level);
}

public void printPostOrder(TreeNode root) {
    printPostOrder(root, 0);
}

private void printPostOrder(TreeNode root, int level) {
    if (root == null) {
        return;
    }
    printPostOrder(root.firstChild, level + 1);
    printPostOrder(root.nextSibling, level);
    for (int i = 0; i < level; i++) {
        System.out.print("  ");
    }
    System.out.println(root.data);
}

// Tree add A to Q
public static void main(String[] args){
    GeneralTreeCell<Character> tree = new GeneralTreeCell<Character>('A');
}