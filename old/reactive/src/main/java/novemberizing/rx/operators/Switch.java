package novemberizing.rx.operators;

import novemberizing.ds.func.Single;
import novemberizing.rx.Operator;
import novemberizing.rx.Subscriber;
import novemberizing.util.Log;

import java.util.HashMap;

/**
 *
 * @author novemberizing, me@novemberizing.net
 * @since 2017. 1. 18.
 */
@SuppressWarnings({"WeakerAccess", "unused"})
public class Switch<T, Z> extends Operator<T, Z> {
    private static final String Tag = "novemberizing.rx.operators.switch";

    protected Single<T, Integer> __hash;
    protected HashMap<Integer, Block.Op<T, Z>> __cases = new HashMap<>();
    protected Block.Op<T, Z> __default;

    public Switch(Single<T, Integer> hash){
        Log.f(Tag, "");
        __hash = hash;
    }

    public Switch<T, Z> _case(int i, Block.Op<T, Z> block){
        Log.f(Tag, "");
        if(__default!=null){
            Log.e(Tag, "__default!=null");
        } else if(__cases.get(i)!=null) {
            Log.e(Tag, "__case is exist");
        } else {
            __cases.put(i, block);
        }
        return this;
    }

    public Switch<T, Z> _case(int i, novemberizing.ds.func.Single<T, Z> f) {
        Log.f(Tag, "");
        if(__default!=null){
            Log.e(Tag, "__default!=null");
        } else if(__cases.get(i)!=null) {
            Log.e(Tag, "__case is exist");
        } else {
            __cases.put(i, Operator.Block(f));
        }
        return this;
    }

    public Switch<T, Z> _case(int i, Operator<T, Z> op) {
        Log.f(Tag, "");
        if(__default!=null){
            Log.e(Tag, "__default!=null");
        } else if(__cases.get(i)!=null) {
            Log.e(Tag, "__case is exist");
        } else {
            __cases.put(i, Operator.Block(op));
        }
        return this;
    }

    public Switch<T, Z> _default(Block.Op<T, Z> block) {
        Log.f(Tag, "");
        if(__default!=null){
            Log.e(Tag, "__default!=null");
        } else {
            __default = block;
        }
        return this;
    }


    public Switch<T, Z> _default(novemberizing.ds.func.Single<T, Z> f) {
        Log.f(Tag, "");
        if(__default!=null){
            Log.e(Tag, "__default!=null");
        } else {
            __default = Operator.Block(f);
        }
        return this;
    }

    public Switch<T, Z> _default(Operator<T, Z> op) {
        Log.f(Tag, "");
        if(__default!=null){
            Log.e(Tag, "__default!=null");
        } else {
            __default = Operator.Block(op);
        }
        return this;
    }

    protected void execute(Block.Op<T, Z> block, Task<T, Z> task, T in) {
        Log.f(Tag, "");
        block.exec(in).subscribe(new Subscriber<Z>() {
            protected boolean __subscribe = true;
            @Override
            public void onNext(Z o) {
                Log.f(Tag, task, o);
                task.next(o);
            }

            @Override public void onError(Throwable e) { Log.e(Tag, e); }

            @Override
            public void onComplete() {
                Log.f(Tag, task);
                task.complete();
            }

            @Override public void subscribe(boolean v){ __subscribe = v; }

            @Override public boolean subscribed(){ return __subscribe; }
        });
    }

    @Override
    protected void on(Task<T, Z> task, T in) {
        Log.f(Tag, "");
        Integer i = __hash.call(in);
        if(i!=null){
            Block.Op<T, Z> block = __cases.get(i);
            if(block!=null){
                execute(block, task, in);
            } else if(__default!=null) {
                execute(__default, task, in);
            } else {
                task.error(new RuntimeException("not exist callable op"));
                task.complete();
            }
        } else if(__default!=null) {
            execute(__default, task, in);
        } else {
            task.error(new RuntimeException("not exist callable op"));
            task.complete();
        }
    }
}
