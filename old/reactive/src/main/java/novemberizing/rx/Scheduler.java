package novemberizing.rx;

import novemberizing.ds.Executable;
import novemberizing.ds.Executor;
import novemberizing.rx.schedulers.Local;
import novemberizing.util.Log;

/**
 *
 * @author novemberizing, me@novemberizing.net
 * @since 2017. 1. 17.
 */
@SuppressWarnings("WeakerAccess")
public abstract class Scheduler implements Executor {
    private static final String Tag = "novemberizing.rx.scheduler";

    private static ThreadLocal<Scheduler> __scheduler = new ThreadLocal<>();

    public static Scheduler New(){
        Log.f(Tag, "");
        return Local.Get();
    }

    public static Scheduler Local(){
        Log.f(Tag, "");
        return Local.Get();
    }

    protected static void Self(Scheduler self){
        Log.f(Tag, "");
        if(self!=null) {
            Scheduler scheduler = __scheduler.get();
            if (scheduler == null) {
                __scheduler.set(null);
            } else if (scheduler != self) {
                __scheduler.set(self);
            }
        } else {
            __scheduler.remove();
        }
    }

    public static Scheduler Self(){
        Log.f(Tag, "");
        Scheduler scheduler = __scheduler.get();
        if(scheduler==null){
            scheduler = Scheduler.New();
        }
        return scheduler;
    }

    public abstract void execute(Executable executable);
}
