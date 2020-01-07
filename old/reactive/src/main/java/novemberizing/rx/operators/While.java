package novemberizing.rx.operators;

import novemberizing.rx.Operator;
import novemberizing.rx.Subscriber;
import novemberizing.util.Log;

/**
 *
 * @author novemberizing, me@novemberizing.net
 * @since 2017. 1. 17.
 */
@SuppressWarnings({"WeakerAccess", "SameParameterValue"})
public class While<T> extends Operator<T, T> {
    private static final String Tag = "novemberizing.rx.operators.while";

    protected Block.Op<T, T> __block;
    protected novemberizing.ds.func.Single<T, Boolean> __condition;

    public While(novemberizing.ds.func.Single<T, Boolean> condition, Block.Op<T, T> block) {
        Log.f(Tag, "");
        __block = block;
        __condition = condition;
    }

    public While(novemberizing.ds.func.Single<T, Boolean> condition, novemberizing.ds.func.Single<T, T> f){
        Log.f(Tag, "");
        __block = Operator.Block(f);
        __condition = condition;
    }

    public While(novemberizing.ds.func.Single<T, Boolean> condition, Operator<T, T> op){
        Log.f(Tag, "");
        __block = Operator.Block(op);
        __condition = condition;
    }

    public void execute(Block.Op<T, T> block, Operator.Task<T, T> task, T in){
        Log.f(Tag, "");
        Exec<T, T> exec = (Exec<T, T>) block.exec(in);
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
                    if (!__condition.call(o)) {
                        completed(true);
                        Operator.Complete(exec);
                    }
                }
            }

            @Override public void onError(Throwable e) { Log.e(Tag, e); }

            @Override
            public void onComplete() {
                Log.f(Tag, "");
                if(!completed()){
                    if(executed()){
                        execute(block, task, exec.out);
                    } else {
                        execute(block, task, exec.in);
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
    protected void on(Operator.Task<T, T> task, T in) {
        Log.f(Tag, "");
        if(__condition.call(in)){
            execute(__block, task, in);
        } else {
            task.next(in);
            task.complete();
        }
    }
}
