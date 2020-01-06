package functional;

import novemberizing.tuple.Single;
import novemberizing.tuple.Pair;
import novemberizing.tuple.Triple;

@SuppressWarnings("unused")
public class tuple {
    public static <A> boolean exist(Single<A> o){ return o != null && o.exist(); }
    public static <A, B> boolean exist(Pair<A, B> o){ return o != null && o.exist(); }
    public static <A, B, C> boolean exist(Triple<A, B, C> o){ return o != null && o.exist(); }
}
