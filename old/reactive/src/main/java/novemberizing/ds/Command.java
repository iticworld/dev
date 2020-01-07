package novemberizing.ds;

import novemberizing.util.Log;

/**
 *
 * @author novemberizing, me@novemberizing.net
 * @since 2017. 1. 17.
 */
@SuppressWarnings({"WeakerAccess", "unused"})
public abstract class Command implements Executable {
    private static final String Tag = "novemberizing.ds.command";

    protected Executor __executor = null;
    protected boolean __completed = false;

    @Override
    public void execute(Executor executor) {
        Log.f(Tag, "");
        if(__executor!=null){
            Log.d(Tag, this, "__executor!=null");
        }
        __executor = executor;
        execute();
    }

    public void executed() {
        Log.f(Tag, "");
        Executor executor = __executor;
        __executor = null;
        executor.executed(this);
    }

    public void complete() {
        Log.f(Tag, "");
        Executor executor = __executor;
        __completed = true;
        __executor = null;
        executor.completed(this);
    }

    public abstract void execute();

    @Override public boolean completed() { return __completed; }
}
