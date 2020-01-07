package novemberizing.ds.tuple;

import com.google.gson.annotations.Expose;
import novemberizing.util.Log;

/**
 * @author novemberizing, me@novemberizing.net
 * @since 2017. 1. 20.
 */
@SuppressWarnings("WeakerAccess")
public class Triple<A, B, C> extends Pair<A, B> {
    private static final String Tag = "novemberizing.ds.tuple.tuple";
    @Expose public C third;

    public Triple(){
        super();
        Log.f(Tag, "");
        this.third = null;
    }

    public Triple(A first, B second, C third){
        super(first, second);
        Log.f(Tag, "");
        this.third = third;
    }
}
