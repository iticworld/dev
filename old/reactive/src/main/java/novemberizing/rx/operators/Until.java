package novemberizing.rx.operators;

import novemberizing.ds.func.Single;
import novemberizing.rx.Operator;
import novemberizing.util.Log;

/**
 *
 * @author novemberizing, me@novemberizing.net
 * @since 2017. 1. 17.
 */
public class Until<T> extends While<T> {
    private static final String Tag = "novemberizing.rx.operators.until";
    public Until(Block.Op<T, T> block, Single<T, Boolean> condition) {
        super(condition, block);
        Log.f(Tag, "");
    }

    public Until(Single<T, T> f, Single<T, Boolean> condition) {
        super(condition, f);
        Log.f(Tag, "");
    }

    public Until(Operator<T, T> op, Single<T, Boolean> condition) {
        super(condition, op);
        Log.f(Tag, "");
    }

    @Override
    protected void on(Operator.Task<T, T> task, T in) {
        Log.f(Tag, "");
        execute(__block, task, in);
    }
}
