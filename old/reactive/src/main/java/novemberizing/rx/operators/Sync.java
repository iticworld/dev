package novemberizing.rx.operators;

import novemberizing.rx.Operator;
import novemberizing.rx.Subscriber;
import novemberizing.util.Log;

import java.util.LinkedList;

/**
 *
 * @author novemberizing, me@novemberizing.net
 * @since 2017. 1. 17.
 */
@SuppressWarnings("WeakerAccess")
public abstract class Sync<T, U> extends Operator<T, U> {
    private static final String Tag = "novemberizing.rx.operators.sync";
    private final LinkedList<Task<T, U>> __tasks = new LinkedList<>();
    private Operator.Task<T, U> __now;

    public Sync(){
        Log.f(Tag, "");
        __observer = new Subscriber<Task<T, U>>() {
            protected boolean __subscribe = true;
            @Override
            public void onNext(Task<T, U> o) {
                Log.f(Tag, "");
                __next(o);
            }

            @Override public void onError(Throwable e) { Log.e(Tag, e.getMessage()); }

            @Override public void onComplete() { Log.f(Tag, ""); }

            @Override public void subscribe(boolean v){ __subscribe = v; }

            @Override public boolean subscribed(){ return __subscribe; }
        };
    }

    @Override
    protected void in(Operator.Next<?, U> next, Operator.Task<T, U> task) {
        Log.f(Tag, "");
        synchronized (__tasks){
            if(__now==null){
                __now = task;
                on(task, task.in());
            } else {
                __tasks.add(task);
            }
        }
    }

    private void __next(Operator.Task<T, U> next){
        Log.f(Tag, "");
        synchronized (__tasks){
            if(next!=__now){
                Log.e(Tag, "next!=__now");
            }
            __now = null;
            while(__tasks.size()>0){
                __now = __tasks.pollFirst();
                if(__now!=null){
                    break;
                }
            }
        }
        if(__now!=null){
            on(__now, __now.in());
        }
    }
}
