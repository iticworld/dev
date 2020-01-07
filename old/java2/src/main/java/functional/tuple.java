package functional;

import novemberizing.tuple.Single;
import novemberizing.tuple.Pair;
import novemberizing.tuple.Triple;

public class tuple {
    public static boolean exist(Single<?> o){ return o != null && o.exist(); }
    public static boolean exist(Pair<?, ?> o){ return o != null && o.exist(); }
    public static boolean exist(Triple<?, ?, ?> o){ return o != null && o.exist(); }

    public static boolean empty(Single<?> o){ return o == null || o.empty(); }
    public static boolean empty(Pair<?, ?> o){ return o == null || o.empty(); }
    public static boolean empty(Triple<?, ?, ?> o){ return o == null || o.empty(); }
}
