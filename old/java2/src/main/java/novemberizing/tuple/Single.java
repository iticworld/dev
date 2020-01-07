package novemberizing.tuple;

/**
 *
 * @param <A> object
 * @author sean <sean@collab.ee>
 * @since 0.0.1
 */
public class Single<A> {
    protected A first;

    public A first(){ return first; }
    public void first(A v){ first = v; }

    public boolean empty(){ return first == null; }
    public boolean exist(){ return first != null; }
    public void set(A first){ this.first = first; }

    public Single(){ first = null; }
    public Single(A first){ this.first = first; }
}
