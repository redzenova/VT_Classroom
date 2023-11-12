public class AVLTree<T extends Comparable<T>> {
    public TreeCell<T> root;

    public AVLTree() {
        root = null;
    }

    public AVLTree(TreeCell<T> root) {
        this.root = root;
    }

    // =============== Insert ======================
    // insert no rotate 
    public void insertNoRotate(T datum) {
        root = insertNoRotate(root, datum);
    }
    private static <T extends Comparable<T>> TreeCell<T> insertNoRotate(TreeCell<T> root, T datum) {
        if (root == null) {
            return new TreeCell<T>(datum);
        }
        if (datum.compareTo(root.getDatum()) < 0) {
            root.setLeft(insertNoRotate(root.getLeft(), datum));
        } else {
            root.setRight(insertNoRotate(root.getRight(), datum));
        }
        root.setHeight(Math.max(getHeight(root.getLeft()), getHeight(root.getRight())) + 1);
        return root;
    }

    // insert with self-balance
    public void insert(T datum) {
        root = insert(root, datum);
    }
    private static <T extends Comparable<T>> TreeCell<T> insert(TreeCell<T> root, T datum) {
        if (root == null) {
            return new TreeCell<T>(datum);
        }
        if (datum.compareTo(root.getDatum()) < 0) {
            root.setLeft(insert(root.getLeft(), datum));
        } else {
            root.setRight(insert(root.getRight(), datum));
        }
        root.setHeight(Math.max(getHeight(root.getLeft()), getHeight(root.getRight())) + 1);
        return makeBalance(root);
    }


    // About balance of tree
    // ========== Make tree balance ==========
    public void makeBalance() {
        root = makeBalance(root);
    }
    private static <T extends Comparable<T>> TreeCell<T> makeBalance(TreeCell<T> root) {
        if (root == null) {
            return null;
        }
        int balance = getBalance(root);
        // If this node becomes unbalanced, then there are 4 cases
        // Left Left Case
        if (balance > 1) {
            if (getBalance(root.getLeft()) < 0) {
                root.setLeft(leftRotate(root.getLeft()));
            }
            return rightRotate(root);
        }
        // Right Right Case
        if (balance < -1) {
            if (getBalance(root.getRight()) > 0) {
                root.setRight(rightRotate(root.getRight()));
            }
            return leftRotate(root);
        }
        // Left Right Case
        if (balance > 1) {
            root.setLeft(leftRotate(root.getLeft()));
            return rightRotate(root);
        }
        // Right Left Case
        if (balance < -1) {
            root.setRight(rightRotate(root.getRight()));
            return leftRotate(root);
        }

        // 
        return root;
    }

    // ========== Rotate ==========
    // Left rotate
    private static <T extends Comparable<T>> TreeCell<T> leftRotate(TreeCell<T> root) {
        TreeCell<T> newRoot = root.getRight();
        root.setRight(newRoot.getLeft());
        newRoot.setLeft(root);
        root.setHeight(Math.max(getHeight(root.getLeft()), getHeight(root.getRight())) + 1);
        newRoot.setHeight(Math.max(getHeight(newRoot.getLeft()), getHeight(newRoot.getRight())) + 1);
        return newRoot;
    }

    // Right rotate
    private static <T extends Comparable<T>> TreeCell<T> rightRotate(TreeCell<T> root) {
        TreeCell<T> newRoot = root.getLeft();
        root.setLeft(newRoot.getRight());
        newRoot.setRight(root);
        root.setHeight(Math.max(getHeight(root.getLeft()), getHeight(root.getRight())) + 1);
        newRoot.setHeight(Math.max(getHeight(newRoot.getLeft()), getHeight(newRoot.getRight())) + 1);
        return newRoot;
    }

    // public static <T> AVLTree<T> balanceTree(AVLTree<T> node)
    // that takes in an unbalanced BST and return a new more balanced tree
    // Using in-order traversal to get the sorted list of the tree
    public static <T extends Comparable<T>> AVLTree<T> balanceTree(AVLTree<T> tree) {
        AVLTree<T> newTree = new AVLTree<>();
        balanceTreeHelper(tree.root, newTree);
        return newTree;
    }
    private static <T extends Comparable<T>> void balanceTreeHelper(TreeCell<T> node, AVLTree<T> newTree) {
        if (node == null) {
            return;
        }
        balanceTreeHelper(node.getLeft(), newTree);
        newTree.insert(node.getDatum());
        balanceTreeHelper(node.getRight(), newTree);
    }


    // public static <T> void balanceTreeInPlace(AVLTree<T> node)
    // that takes in an unbalanced BST and balance it in-place (without creating a new tree but modify the existing one in-place)
    public static <T extends Comparable<T>> void balanceTreeInPlace(AVLTree<T> tree) {
        tree.root = balanceTreeInPlaceHelper(tree.root);
    }

    private static <T extends Comparable<T>> TreeCell<T> balanceTreeInPlaceHelper(TreeCell<T> node) {
        if (node == null) {
            return null;
        }
        node.setLeft(balanceTreeInPlaceHelper(node.getLeft()));
        node.setRight(balanceTreeInPlaceHelper(node.getRight()));
        return makeBalance(node);
    }



    // =============== Delete ======================
    public void delete(T datum) {
        root = delete(root, datum);
    }
    private static <T extends Comparable<T>> TreeCell<T> delete(TreeCell<T> root, T datum) {
        if (root == null) {
            return null;
        }
        if (datum.compareTo(root.getDatum()) < 0) {
            root.setLeft(delete(root.getLeft(), datum));
        } else if (datum.compareTo(root.getDatum()) > 0) {
            root.setRight(delete(root.getRight(), datum));
        } else {
            if (root.getLeft() == null || root.getRight() == null) {
                root = (root.getLeft() == null) ? root.getRight() : root.getLeft();
            } else {
                TreeCell<T> temp = findMin(root.getRight());
                root.setDatum(temp.getDatum());
                root.setRight(delete(root.getRight(), temp.getDatum()));
            }
        }
        if (root == null) {
            return null;
        }
        root.setHeight(Math.max(getHeight(root.getLeft()), getHeight(root.getRight())) + 1);
        return makeBalance(root);
    }



    // =============== Traverse ======================
    // in-order traversal
    public void inOrder() {
        inOrder(root);
    }
    private static <T extends Comparable<T>> void inOrder(TreeCell<T> root) {
        if (root == null) {
            return;
        }
        inOrder(root.getLeft());
        System.out.print(root.getDatum() + " ");
        inOrder(root.getRight());
    }

    // pre-order traversal
    public void preOrder() {
        preOrder(root);
    }
    private static <T extends Comparable<T>> void preOrder(TreeCell<T> root) {
        if (root == null) {
            return;
        }
        System.out.print(root.getDatum() + " ");
        preOrder(root.getLeft());
        preOrder(root.getRight());
    }

    // post-order traversal
    public void postOrder() {
        postOrder(root);
    }
    private static <T extends Comparable<T>> void postOrder(TreeCell<T> root) {
        if (root == null) {
            return;
        }
        postOrder(root.getLeft());
        postOrder(root.getRight());
        System.out.print(root.getDatum() + " ");
    }

    // =============== Utility ======================
    public boolean isEmpty() {
        return root == null;
    }

    private static <T extends Comparable<T>> int getHeight(TreeCell<T> left) {
        if (left == null) {
            return -1;
        }
        return left.getHeight();
    }

    private static <T extends Comparable<T>> int getBalance(TreeCell<T> root) {
        if (root == null) {
            return 0;
        }
        return getHeight(root.getLeft()) - getHeight(root.getRight());
    }

    public T findMin() {
        return findMin(root).getDatum();
    }
    private static <T extends Comparable<T>> TreeCell<T> findMin(TreeCell<T> root) {
        if (root == null) {
            return null;
        }
        if (root.getLeft() == null) {
            return root;
        }
        return findMin(root.getLeft());
    }

    public T findMax() {
        return findMax(root).getDatum();
    }
    private static <T extends Comparable<T>> TreeCell<T> findMax(TreeCell<T> root) {
        if (root == null) {
            return null;
        }
        if (root.getRight() == null) {
            return root;
        }
        return findMax(root.getRight());
    }

    public int size() {
        return size(root);
    }
    private static <T extends Comparable<T>> int size(TreeCell<T> root) {
        if (root == null) {
            return 0;
        }
        return 1 + size(root.getLeft()) + size(root.getRight());
    }

    public String toString() {
        return toString(root);
    }
    private static <T extends Comparable<T>> String toString(TreeCell<T> root) {
        if (root == null) {
            return "";
        }
        return toString(root.getLeft()) + root.getDatum() + " " + toString(root.getRight());
    }

    public boolean contains(T datum) {
        return contains(root, datum);
    }
    private static <T extends Comparable<T>> boolean contains(TreeCell<T> root, T datum) {
        if (root == null) {
            return false;
        }
        if (datum.compareTo(root.getDatum()) == 0) {
            return true;
        }
        if (datum.compareTo(root.getDatum()) < 0) {
            return contains(root.getLeft(), datum);
        }
        return contains(root.getRight(), datum);
    }

    // =============== Print ======================
    // print tree
    public void printTree() {
        printTree(root, 0);
    }
    private static <T extends Comparable<T>> void printTree(TreeCell<T> root, int level) {
        if (root == null) {
            return;
        }
        printTree(root.getRight(), level + 1);
        for (int i = 0; i < level; i++) {
            System.out.print("  ");
        }
        System.out.println(root.getDatum());
        printTree(root.getLeft(), level + 1);
    }

}
   