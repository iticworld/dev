package novemberizing.ds;

/**
 *
 * @author novemberizing, me@novemberizing.net
 * @since 2017. 1. 17.
 */
public interface Executor {
    void executed(Executable executable);
    void completed(Executable executable);

    void clear();

    void dispatch(Executable executable);
    void dispatch(Executable executable, Executable... executables);
    void dispatch(Executable[] executables);
}
