package functional.tuple;

import novemberizing.tuple.Triple;

public class triple {
    public static <A, B, C> Triple<A, B, C> create(A first, B second, C third) { return new Triple<>(first, second, third); }
}
