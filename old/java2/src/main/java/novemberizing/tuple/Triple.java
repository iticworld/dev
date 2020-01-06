package novemberizing.tuple;

public class Triple<A, B, C> extends Pair<A, B> {
    protected C third;

    public C third(){ return third; }
    public void third(C v){ third = v; }

    @Override
    public boolean empty(){ return first == null && second == null && third == null; }

    @Override
    public boolean exist(){ return first != null && second != null && third != null; }

    public void set(A first, B second, C third){
        this.first = first;
        this.second = second;
        this.third = third;
    }

    public Triple(){
        super();
        third = null;
    }

    public Triple(A first, B second, C third) {
        super(first, second);
        this.third = third;
    }
}
