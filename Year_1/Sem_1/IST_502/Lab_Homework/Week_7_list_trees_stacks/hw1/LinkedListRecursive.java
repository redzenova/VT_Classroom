/**
 * A linked list implementation of List using lots of recursion.
 * 
 */
public class LinkedListRecursive<T> implements List<T> {

    ListCell<T> head; // head (first cell) of the List
 
    /**
     * Constructor.
     */
    public LinkedListRecursive() {
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
 
    /**
     * Delete an element from the list.
     * 
     * @param element
     *           the element to delete
     */
    public void delete(T element) {
       delete(element, head);
    }
 
    private ListCell<T> delete(T element, ListCell<T> cell) {
       if (cell == null) return null;
       if (cell.getDatum().equals(element)) return cell.getNext();
       cell.setNext(delete(element, cell.getNext()));
       return cell;
    }
 
    /**
     * Report true if list contains element.
     * 
     * @param element
     *           the element to check for
     * @return true iff element is in the List
     */
    public boolean contains(T element) {
       return contains(element, head);
    }
 
    private boolean contains(T element, ListCell<T> cell) {
       if (cell == null) return false;
       return cell.getDatum().equals(element) || contains(element, cell.getNext());
    }
 
    /**
     * Report number of elements in List.
     * 
     * @return number of elements
     */
    public int size() {
       return size(head);
    }
 
    private int size(ListCell<T> cell) {
       if (cell == null) return 0;
       return size(cell.getNext()) + 1;
    }
 
    /**
     * String representation.
     * 
     * @return the String representation
     */
    public String toString() {
       return "[" + toString(head) + " ]";
    }
 
    private String toString(ListCell<T> cell) {
       if (cell == null) return "";
       return " " + cell.getDatum().toString() + toString(cell.getNext());
    }

    //===================================| HOMEWORK 4 |=========================================
    /**
     * Given a list and a searchFor value, return the number of times that value occurs in the list. in recursive way
     */
    
    public int count(T searchFor) {
        return count(searchFor, head);
    }

    private int count(T searchFor, ListCell<T> cell) {
        if (cell == null) return 0; // base case
        if (cell.getDatum().equals(searchFor)) return count(searchFor, cell.getNext()) + 1;
        return count(searchFor, cell.getNext());
    }

    /**
     * Given a list, an index 'n' in the range 0..length, and a data element,
     *  add a new node to the list so that it has the given index.
     */
    public void insertNth(T data,int index) {
        head = insertNth(data, index, head);
    }

    private ListCell<T> insertNth(T data, int index, ListCell<T> cell) {
        if (index == 0) return new ListCell<T>(data, cell);
        if (cell == null) return null;
        cell.setNext(insertNth(data, index - 1, cell.getNext()));
        return cell;
    }


    /**
     * Sort the list in ascending order 
     */
    public void sort(){
        head = sort(head);
        return;
    }

    private ListCell<T> sort(ListCell<T> cell) {
        if (cell.getNext() == null) return cell;

        // This selection sort algorithm is not efficient, but it is easy to implement
        T min = cell.getDatum();
        ListCell<T> current = cell.getNext();

        // find min traversing the list
        while (current != null) {
            if ((int) min > (int) current.getDatum()) {
                min = current.getDatum();
            }
            current = current.getNext();
        }

        // delete the min from the list
        cell = delete(min, cell);
        // insert the min at the beginning of the list
        cell = insertNth(min, 0, cell);

        // recursively sort the rest of the list
        cell.setNext(sort(cell.getNext()));
        
        // return the sorted list
        return cell;
    }
   
    /**
     * Given a list that is sorted in increasing order, 
     * inserts the data node into the correct sorted position in the list.
     */
    public void sortedInsert(T data){
        head = sortedInsert(data, head);
    }

    private ListCell<T> sortedInsert(T data, ListCell<T> cell) {
        if (cell == null) return new ListCell<T>(data, null);
        if ((int) data < (int) cell.getDatum()) return new ListCell<T>(data, cell); // traverse the list until the right position is found
        cell.setNext(sortedInsert(data, cell.getNext()));
        return cell;
    }

    /**
     * Given a list that is sorted in increasing order, remove any duplicates from a sorted list.
     */
    public void removeDuplicates(){
        if (head == null) return;
        removeDuplicates(head);
    }

    private void removeDuplicates(ListCell<T> cell) {
        if (cell.getNext() == null) return;
        if (cell.getDatum().equals(cell.getNext().getDatum())) {
            cell.setNext(cell.getNext().getNext());
            removeDuplicates(cell);
        } else {
            removeDuplicates(cell.getNext());
        }
    }

 }