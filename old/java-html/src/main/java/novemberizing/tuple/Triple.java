package novemberizing.tuple;

public class Triple<A, B, C> extends Pair<A, B> {
    protected C third;

    @Override
    public boolean empty(){ return first == null && second == null && third == null; }

    public void set(A first, B second, C third){
        this.first = first;
        this.second = second;
        this.third = third;
    }

    public C third(){ return third; }
    public void third(C v){ third = v; }

    public Triple(){
        super();
        this.third = null;
    }

    public Triple(A first, B second, C third) {
        super(first, second);
        this.third = third;
    }
}
