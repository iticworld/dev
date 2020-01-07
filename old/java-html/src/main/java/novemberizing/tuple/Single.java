package novemberizing.tuple;

public class Single<A> {
    protected A first;

    public boolean empty(){ return first == null; }
    public boolean exist(){ return !empty(); }

    public void set(A first){ this.first = first; }

    public A first(){ return first; }
    public void first(A v){ first = v; }

    public Single(){ this.first = null; }
    public Single(A first){ this.first = first; }
}
