package novemberizing.ds.tuple;

import com.google.gson.annotations.Expose;
import novemberizing.util.Log;

/**
 *
 * @author novemberizing, me@novemberizing.net
 * @since 2017. 2. 12.
 */
@SuppressWarnings("unused")
public class Quintuple<A, B, C, D, E> extends Quadruple<A, B, C, D> {
    private static final String Tag = "novemberizing.ds.tuple.quintuple";
    @Expose public E fifth;

    public Quintuple(){
        super();
        Log.f(Tag, "");
        this.fifth = null;
    }

    public Quintuple(A first, B second, C third, D fourth, E fifth){
        super(first, second, third, fourth);
        Log.f(Tag, "");
        this.fifth = fifth;
    }
}
