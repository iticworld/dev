package novemberizing.ds.tuple;

import com.google.gson.annotations.Expose;
import novemberizing.util.Log;

/**
 *
 * @author novemberizing, me@novemberizing.net
 * @since 2017. 1. 18.
 */
public class Pair<A, B> extends Single<A> {
    private static final String Tag = "novemberizing.ds.tuple.pair";
    @Expose public B second;
    public Pair(){
        super();
        Log.f(Tag, "");
        this.second = null;
    }
    public Pair(A first, B second){
        super(first);
        Log.f(Tag, "");
        this.second = second;
    }
}
