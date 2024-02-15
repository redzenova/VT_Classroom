public class ListCell<T> {
    private T datum;
    private ListCell<T> next;

    public ListCell(T datum, ListCell<T> next){
        this.datum = datum;
        this.next = next;
    }

    public T getDatum() {return datum;}
    public ListCell<T> getNext() {return next;}
    public void setDatum(T obj) {datum = obj;}
    public void setNext(ListCell<T> c) {next = c;}
}
