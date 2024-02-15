package List;
// Purpose: Demonstrate the use of a linked list.
public class ListCell<T> {
    private T data;
    private ListCell<T> next;

    public ListCell(T data, ListCell<T> next) {
        this.data = data;
        this.next = next;
    }

    public T getData() { return data; }
    public ListCell<T> getNext() { return next; }
    public void setData(T data) { this.data = data; }
    public void setNext(ListCell<T> next) { this.next = next; }

}
