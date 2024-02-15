package List;
import java.util.Iterator;
import java.util.NoSuchElementException;

class List<T> implements Iterable<T>{
    // data
    private ListCell<T> head;
    private int size;

    // constructor
    public List() {
        this.head = null;
        this.size = 0;
    }
    
    // operations
    public void insert(T e) {
        this.head = insert(e, this.head);
    }

    private ListCell<T> insert(T e, ListCell<T> h) {
        if (h == null) {
            this.size += 1;
            return new ListCell<T>(e, null);
        }
        h.setNext(insert(e, h.getNext()));
        return h;
    }

    public void delete(T e) {
        this.head = delete(e, this.head);
    }

    private ListCell<T> delete(T e, ListCell<T> c) {
        if (c == null) return null;
        if (c.getData().equals(e)) {
            this.size -= 1;
            return c.getNext();
        }
        c.setNext(delete(e, c.getNext()));
        return c;
    }

    public boolean search(T e) {
        

        return search(e, this.head);

    }

    private boolean search(T e, ListCell<T> c) {
        if (c.getData().equals(e)) return true;
        if (c.getNext() == null) return false;
        return search(e, c.getNext());
    }

    public Iterator<T> iterator()  {
        return new ListIterator(head);  
    }

    // an iterator, doesn't implement remove() since it's optional
    private class ListIterator implements Iterator<T> {
        private ListCell<T> current;

        public ListIterator(ListCell<T> head) {
            current = head;
        }

        public boolean hasNext()  { return current != null;}
        public void remove()      { throw new UnsupportedOperationException();}

        public T next() {
            if (!hasNext()) throw new NoSuchElementException();
            T item = current.getData();
            current = current.getNext(); 
            return item;
        }
    }

    public int size() {
        // We will fill this in
        return this.size;
    }

    public static void main(String[] args) {
        List<Integer> intList = new List<Integer>();
        for (int i=10; i<=100; i += 10) {
            intList.insert(i);
        }
        for (Integer i : intList) {
            System.out.println(i);
        }
        System.out.println("intList size is " + intList.size());
        
        for (int i=1000; i<=4000; i += 1000) {
            intList.insert(i);
        }
        for (Integer i : intList) {
            System.out.println(i);
        }
        System.out.println("intList size is " + intList.size());
        
        intList.delete(50);
        for (Integer i : intList) {
            System.out.println(i);
        }
        System.out.println("intList size is " + intList.size());
        
        intList.delete(60);
        for (Integer i : intList) {
            System.out.println(i);
        }
        System.out.println("intList size is " + intList.size());
        
        intList.delete(200);
        for (Integer i : intList) {
            System.out.println(i);
        }        System.out.println("intList size is " + intList.size());
        
        intList.delete(10);
        for (Integer i : intList) {
            System.out.println(i);
        }
        System.out.println("intList size is " + intList.size());  
        
        intList.delete(400);
        for (Integer i : intList) {
            System.out.println(i);
        }
        System.out.println("intList size is " + intList.size());
        
        intList.delete(4000);
        for (Integer i : intList) {
            System.out.println(i);
        }
        System.out.println("intList size is " + intList.size());
    }
}
