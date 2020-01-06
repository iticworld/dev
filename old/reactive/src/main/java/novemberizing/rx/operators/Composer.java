package novemberizing.rx.operators;

import novemberizing.rx.Observable;
import novemberizing.rx.Operator;
import novemberizing.rx.Subscriber;
import novemberizing.util.Log;

/**
 *
 * @author novemberizing, me@novemberizing.net
 * @since 2017. 1. 17.
 */
@SuppressWarnings({"unused", "WeakerAccess"})
public class Composer<T, U, Z> extends Operator<T, Z> {
    private static final String Tag = "novemberizing.rx.operators.composer";

    private novemberizing.ds.func.Pair<T, U, Z> __func;
    private Observable<U> __secondary;
    private final Composer<T, U, Z> __self = this;
    private U __second;
    private T __first;

    protected Observable<U> secondary(){ return __secondary; }

    @Override
    protected void on(Task<T, Z> task, T in) {
        Log.f(Tag, "");
        synchronized (__self) {
            try {
                task.next(__func.call(__first = in, __second));
            } catch (Exception e) {
                task.error(e);
            }
            task.complete();
        }
    }

    public Composer(Observable<U> secondary, novemberizing.ds.func.Pair<T, U, Z> f){
        Log.f(Tag, "");
        __secondary = secondary;
        __func = f;
        __secondary.subscribe(new Subscriber<U>() {
            protected boolean __subscribe = true;

            @Override
            public void onNext(U o) {
                Log.f(Tag, "");
                synchronized (__self) {
                    emit(__func.call(__first, __second = o));
                }
            }

            @Override
            public void onError(Throwable e) {
                Log.f(Tag, "");
                Log.d(Tag, e.getMessage());
            }

            @Override
            public void onComplete() { Log.f(Tag, ""); }

            @Override public void subscribe(boolean v){ __subscribe = v; }

            @Override public boolean subscribed(){ return __subscribe; }
        });
    }
}
