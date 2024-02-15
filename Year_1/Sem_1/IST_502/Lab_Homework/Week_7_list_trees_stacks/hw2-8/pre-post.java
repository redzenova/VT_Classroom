class TernaryTreeCell<T> {
    private T datum;
    private TernaryTreeCell<T> left, mid, right;

    public TernaryTreeCell(T x) { 
        datum = x; 
    }

    public TernaryTreeCell(T x, TernaryTreeCell<T> lft, TernaryTreeCell<T> md, TernaryTreeCell<T> rgt) {
        datum = x;
        left = lft;
        mid = md;
        right = rgt;
    }

    // Recursive pre-order traversal
    public void preOrderTraversal() {
        System.out.println(datum); // Visit the current node
        if (left != null) {
            left.preOrderTraversal();
        }
        if (mid != null) {
            mid.preOrderTraversal();
        }
        if (right != null) {
            right.preOrderTraversal();
        }
    }

    // Recursive post-order traversal
    public void postOrderTraversal() {
        if (left != null) {
            left.postOrderTraversal();
        }
        if (mid != null) {
            mid.postOrderTraversal();
        }
        if (right != null) {
            right.postOrderTraversal();
        }
        System.out.println(datum); // Visit the current node
    }

    // ... other methods ...

}
