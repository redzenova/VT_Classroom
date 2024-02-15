public class TreeCell<T> {
    public T datum;
    public TreeCell<T> left, right;
    public int height;
    public TreeCell(T datum, TreeCell<T> left, TreeCell<T> right) {
        this.datum = datum;
        this.left = left;
        this.right = right;
        this.height = 0;
    }
    public TreeCell(T datum) {
        this(datum, null, null);
    }
    public TreeCell() {
        this(null, null, null);
    }
    public String toString() {
        return datum.toString();
    }

    public T getDatum() { return datum; }
    public TreeCell<T> getLeft() { return left; }
    public TreeCell<T> getRight() { return right; }
    public int getHeight() { return height; }
    public void setDatum(T datum) { this.datum = datum; }
    public void setLeft(TreeCell<T> left) { this.left = left; }
    public void setRight(TreeCell<T> right) { this.right = right; }
    public void setHeight(int height) { this.height = height; }
}