public class AVLTest {

    public static void main(String[] args) {
        AVLTree<Integer> myTree = new AVLTree<>();
        for (int i=0; i<15; i++) {
            myTree.insertNoRotate(i);
        }
        System.out.println("Original (Insert no rotate):");
        printTree(myTree.root, 0);

        AVLTree<Integer> myTree2 = new AVLTree<>();
        for (int i=0; i<15; i++) {
             myTree2.insert(i);
        }
        System.out.println("Original (Insert with self-balance):");
        printTree(myTree2.root, 0);


        // I create an AVL tree and insert given integers without balancing
        AVLTree<Integer> testTree = new AVLTree<>();

        // Manually creating TreeCells
        TreeCell<Integer> node120 = new TreeCell<>(120);
        TreeCell<Integer> node42 = new TreeCell<>(42);
        TreeCell<Integer> node40 = new TreeCell<>(40);
        TreeCell<Integer> node7 = new TreeCell<>(7);
        TreeCell<Integer> node2 = new TreeCell<>(2);
        TreeCell<Integer> node32 = new TreeCell<>(32);
        TreeCell<Integer> node24 = new TreeCell<>(24);
        TreeCell<Integer> node37 = new TreeCell<>(37);
        TreeCell<Integer> node130 = new TreeCell<>(130);
        TreeCell<Integer> node125 = new TreeCell<>(125);
        TreeCell<Integer> node127 = new TreeCell<>(127);
        TreeCell<Integer> node126 = new TreeCell<>(126);
        TreeCell<Integer> node129 = new TreeCell<>(129);

        // Manually connecting TreeCells
        testTree.root = node120;

        node120.setLeft(node42);
        node42.setLeft(node40);
        node40.setLeft(node7);
        node7.setLeft(node2);
        node7.setRight(node32);
        node32.setLeft(node24);
        node32.setRight(node37);

        node120.setRight(node130);
        node130.setLeft(node125);
        node125.setRight(node127);
        node127.setLeft(node126);
        node127.setRight(node129);

        // Print the unbalanced tree
        System.out.println("Unbalanced tree:");
        printTree(testTree.root, 0);

       // Balance the tree using balanceTree method
        AVLTree<Integer> balancedNewTree = AVLTree.balanceTree(testTree);
        System.out.println("\nBalanced tree (Using balanceTree method):");
        printTree(balancedNewTree.root, 0);

        // Balance the tree in place (this method needs to be implemented in AVLTree.java)
        AVLTree.balanceTreeInPlace(testTree);
        System.out.println("\nBalanced tree (Using balanceTreeInPlace method):");
        printTree(testTree.root, 0);

    }

    
    public static <T> void printTree(TreeCell<T> node, int level) {
        if (node == null) return;
        printTree(node.right, level+1);
        for (int i=0; i<level; i++) {
            System.out.print("  ");
        }
        System.out.println(node.datum);
        printTree(node.left, level+1);
    }

}