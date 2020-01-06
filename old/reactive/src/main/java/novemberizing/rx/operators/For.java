package novemberizing.rx.operators;

import novemberizing.ds.func.Empty;
import novemberizing.ds.func.Pair;
import novemberizing.ds.func.Single;
import novemberizing.rx.Operator;
import novemberizing.rx.Subscriber;
import novemberizing.util.Log;

/**
 *
 * @author novemberizing, me@novemberizing.net
 * @since 2017. 1. 18.
 */
@SuppressWarnings({"WeakerAccess", "SameParameterValue"})
public class For<T, U> extends Operator<T, T> {
    private static final String Tag = "novemberizing.rx.operators.for";
    protected Empty<U> __initializer;
    protected Single<U, U> __internal;
    protected Pair<T, U, Boolean> __condition;
    protected Block.Op<T, T> __block;

    public For(Empty<U> initializer,Pair<T, U, Boolean> condition, Single<U, U> internal, novemberizing.ds.func.Single<T, T> external){
        Log.f(Tag, "");
        __initializer = initializer;
        __condition = condition;
        __internal = internal;
        __block = Operator.Block(external);
    }

    public For(Empty<U> initializer,Pair<T, U, Boolean> condition, Single<U, U> internal,Operator<T, T> external){
        Log.f(Tag, "");
        __initializer = initializer;
        __condition = condition;
        __internal = internal;
        __block = Operator.Block(external);
    }

    public For(Empty<U> initializer,Pair<T, U, Boolean> condition, Single<U, U> internal, Block.Op<T, T> external){
        Log.f(Tag, "");
        __initializer = initializer;
        __condition = condition;
        __internal = internal;
        __block = external;
    }

    protected void execute(Task<T, T> task, novemberizing.ds.tuple.Pair<T, U> in){
        Log.f(Tag, "");
        Exec<T, T> exec = (Exec<T, T>) __block.exec(in.first);
        exec.subscribe(new Subscriber<T>() {
            protected boolean __subscribe = true;
            private boolean __executed = false;
            private boolean __completed = false;
            synchronized void executed(boolean v){ __executed = v; }
            synchronized boolean executed(){ return __executed; }
            synchronized void completed(boolean v){ __completed = v; }
            synchronized boolean completed(){ return __completed; }
            @Override
            public void onNext(T o) {
                Log.f(Tag, "");
                executed(true);
                if(!completed()) {
                    task.next(o);
                    in.second = __internal.call(in.second);
                    if (!__condition.call(o, in.second)) {
                        completed(true);
                        Operator.Complete(exec);
                    }
                }
            }

            @Override
            public void onError(Throwable e) {
                Log.e(Tag, e);
            }

            @Override
            public void onComplete() {
                Log.f(Tag, "");
                if(!completed()){
                    if(executed()){
                        execute(task, new novemberizing.ds.tuple.Pair<>(exec.out, in.second));
                    } else {
                        execute(task, new novemberizing.ds.tuple.Pair<>(exec.in, in.second));
                    }
                } else {
                    if(!executed()){
                        task.next(exec.in);
                    }
                    task.complete();
                }
            }

            @Override public void subscribe(boolean v){ __subscribe = v; }

            @Override public boolean subscribed(){ return __subscribe; }
        });
    }

    @Override
    protected void on(Task<T, T> task, T in) {
        Log.f(Tag, "");
        novemberizing.ds.tuple.Pair<T, U> pair = new novemberizing.ds.tuple.Pair<>(in, __initializer.call());
        if(__condition.call(in, pair.second)) {
            execute(task, pair);
        } else {
            task.next(in);
            task.complete();
        }
    }
}
