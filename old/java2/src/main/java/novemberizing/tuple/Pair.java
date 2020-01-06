package novemberizing.tuple;

public class Pair<A, B> extends Single<A> {
    protected B second;

    public B second(){ return second; }
    public void second(B v){ second = v; }

    @Override
    public boolean empty(){ return first == null && second == null; }

    @Override
    public boolean exist(){ return first != null && second != null; }

    public void set(A first, B second){
        this.first = first;
        this.second = second;
    }

    public Pair(){
        super();
        second = null;
    }

    public Pair(A first, B second) {
        super(first);
        this.second = second;
    }
}
