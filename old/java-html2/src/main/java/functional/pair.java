package functional;

import novemberizing.tuple.Pair;

public class pair {
    public static <A, B> Pair<A, B> create(A first, B second){ return new Pair<>(first, second); }
    public static boolean exist(Pair<?, ?> pair){ return pair != null && !pair.empty(); }
}
