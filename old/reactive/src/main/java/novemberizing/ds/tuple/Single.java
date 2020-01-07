package novemberizing.ds.tuple;

import com.google.gson.annotations.Expose;
import novemberizing.util.Log;

/**
 *
 * @author novemberizing, me@novemberizing.net
 * @since 2017. 1. 18.
 */
public class Single<A> extends Empty {
    private static final String Tag = "novemberizing.ds.tuple.single";
    @Expose public A first;
    public Single(){
        Log.f(Tag, "");
        this.first = null;
    }
    public Single(A first){
        Log.f(Tag, "");
        this.first = first;
    }
}
