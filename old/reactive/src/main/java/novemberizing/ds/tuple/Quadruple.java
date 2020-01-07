package novemberizing.ds.tuple;

import novemberizing.util.Log;

/**
 * @author novemberizing, me@novemberizing.net
 * @since 2017. 1. 20.
 */
@SuppressWarnings("WeakerAccess")
public class Quadruple<A, B, C, D> extends Triple<A, B, C> {
    private static final String Tag = "novemberizing.ds.tuple.quadruple";
    public D fourth;

    public Quadruple(){
        super();
        Log.f(Tag, "");
        this.fourth = null;
    }

    public Quadruple(A first, B second, C third, D fourth){
        super(first, second, third);
        Log.f(Tag, "");
        this.fourth = fourth;
    }
}
