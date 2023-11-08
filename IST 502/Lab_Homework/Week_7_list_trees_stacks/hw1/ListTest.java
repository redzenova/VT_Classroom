public class ListTest {

    /**
     * @param args
     */
    public static void main(String[] args) {
 
       LinkedListIterative<Integer> lli = new LinkedListIterative<Integer>();
       for (int i = 0; i < 20; i++) {
          lli.insert(i + 100);
       }
       lli.delete(107);
       lli.insert(42);
       System.out.println(lli);
       
       LinkedListRecursive<Integer> llr = new LinkedListRecursive<Integer>();
       for (int i = 0; i < 20; i++) {
          llr.insert(i + 100);
       }
       llr.delete(107);
       llr.insert(42);
       System.out.println(llr);
       
       lli.head = iterativeReverse(lli.head);
       llr.head = iterativeReverse(llr.head);
       System.out.println(lli);
       System.out.println(llr);
       lli.head = recursiveReverse(lli.head);
       llr.head = recursiveReverse(llr.head);
       System.out.println(lli);
       System.out.println(llr);
       System.out.println();
       System.out.println();

       // Homework: implement a recursive version of iterativeReverse
       System.out.println("Homework: implement a recursive version of iterativeReverse");       
       System.out.println();
       System.out.print("Sample data: ");
       System.out.println(llr);
       System.out.print("[TEST]- count(111): ");
       System.out.println(llr.count(111));
       System.out.print("[TEST]- insertNth(111, 3): ");
       llr.insertNth(111, 3);
       System.out.println(llr);
       System.out.print("[TEST]- count(111): ");
       System.out.println(llr.count(111));
       System.out.print("[TEST]- sort(): ");
       llr.sort();
       System.out.println(llr);
       System.out.print("[TEST]- sortedInsert(99): ");
       llr.sortedInsert(99);
       System.out.println(llr);
       System.out.print("[TEST]- sortedInsert(107): ");
       llr.sortedInsert(107);
       System.out.println(llr);
       System.out.print("[TEST]- removeDuplicates(): ");
       llr.removeDuplicates();
       System.out.println(llr);
       System.out.println();
    }
    
    public static <T> ListCell<T> iterativeReverse(ListCell<T> c) {
       ListCell<T> rev = null;
       for (; c != null; c = c.getNext()) {
          rev = new ListCell<T>(c.getDatum(), rev);
       }
       return rev;
    }
 
    public static <T> ListCell<T> recursiveReverse(ListCell<T> c) {
       return recursiveReverse(c, null);
    }
    private static <T> ListCell<T> recursiveReverse(ListCell<T> c, ListCell<T> r) {
       if (c == null) return r;
       return recursiveReverse(c.getNext(), new ListCell<T>(c.getDatum(), r));
    }
 
 }