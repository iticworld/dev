package functional;

import novemberizing.Function;

public class exception {
    public static <IN, OUT> OUT safe(IN in, Function<IN, OUT> function, OUT v) {
        try {
            return function != null ? function.call(in) : v;
        } catch(Throwable e) {
            // functional.log.e(e);
        }
        return v;
    }
}
