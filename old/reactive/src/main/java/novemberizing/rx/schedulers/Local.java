package novemberizing.rx.schedulers;

import novemberizing.ds.ConditionalList;
import novemberizing.ds.Executable;
import novemberizing.ds.Factory;
import novemberizing.util.Log;

/**
 *
 * @author novemberizing, me@novemberizing.net
 * @since 2017. 1. 17.
 */
@SuppressWarnings("unused")
public class Local extends Scheduler {
    private static final String Tag = "novemberizing.rx.schedulers.local";

    private static Factory<novemberizing.rx.Scheduler> __factory = null;
    private static ThreadLocal<novemberizing.rx.Scheduler> __schedulers = new ThreadLocal<>();

    public static void Set(Factory<novemberizing.rx.Scheduler> factory){ __factory = factory; }

    public static novemberizing.rx.Scheduler Get(){
        Log.f(Tag, "");
        novemberizing.rx.Scheduler scheduler = __schedulers.get();
        if(scheduler==null){
            scheduler = __factory!=null ? __factory.create() : new Local();
            if(scheduler==null){
                scheduler = new Local();
            }
            __schedulers.set(scheduler);
        }
        return scheduler;
    }

    public Local(){
        Log.f(Tag, "");
        __q = new ConditionalList<>();
    }

    @Override
    public void executed(Executable executable) {
        Log.f(Tag, "");
        super.executed(executable);
        onecycle();
    }

    @Override
    public void completed(Executable executable) {
        Log.f(Tag, "");
        super.completed(executable);
        onecycle();
    }

    @Override
    public void dispatch(Executable executable) {
        Log.f(Tag, "");
        super.dispatch(executable);
        onecycle();
    }

    @Override
    public void dispatch(Executable executable, Executable... executables) {
        Log.f(Tag, "");
        super.dispatch(executable, executables);
        onecycle();
    }

    @Override
    public void dispatch(Executable[] executables) {
        Log.f(Tag, "");
        super.dispatch(executables);
        onecycle();
    }
}
