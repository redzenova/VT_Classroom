/**
 * A linked list implementation of List using lots of iteration instead of
 * recursion.
 * 
 */
public class LinkedListIterative<T> implements List<T> {

    ListCell<T> head; // Head (first cell) of the List
 
    /**
     * Constructor.
     */
    public LinkedListIterative() {
       head = null;
    }
 
    /**
     * Insert an element onto the list.
     * 
     * @param element
     *           the element to insert
     */
    public void insert(T element) {
       head = new ListCell<T>(element, head);
    }
    
    private boolean equal(T x, Object y) {
       return (x != null && x.equals(y)) || (x == null && y == null);
    }
 
    /**
     * Delete an element from the list.
     * 
     * @param element
     *           the element to delete
     */
    public void delete(T element) {
       if (head == null) return;
       if (equal(element, head.getDatum())) {
          head = head.getNext();
          return;
       }
       ListCell<T> current = head;
       ListCell<T> scout = head.getNext();
       while (scout != null) {
          if (equal(scout.getDatum(), element)) {
             current.setNext(scout.getNext()); // found--unlink cell
             return;
          }
          current = scout;
          scout = scout.getNext();
       }
    }
 
    /**
     * Report true if list contains element.
     * 
     * @param element
     *           the element to check for
     * @return true iff element is in the List
     */
    public boolean contains(T element) {
       for (ListCell<T> current = head; current != null; current = current.getNext())
          if (equal(current.getDatum(), element)) return true;
       return false;
    }
 
    /**
     * Report number of elements in List.
     * 
     * @return number of elements
     */
    public int size() {
       int count = 0;
       for (ListCell<T> current = head; current != null; current = current.getNext())
          count++;
       return count;
    }
 
    /**
     * String representation.
     * 
     * @return the String representation
     */
    public String toString() {
       String result = "[";
       for (ListCell<T> current = head; current != null; current = current.getNext())
          result += " " + current.getDatum();
       return result + " ]";
    }
 }