package novemberizing.util;

/**
 *
 * @author novemberizing, me@novemberizing.net
 * @since 2016/12/23
 */
@SuppressWarnings("unused, WeakerAccess, SameParameterValue")
public abstract class Logger {
    protected abstract void ___write(int type, String tag, String str);

    public void write(int type, String tag, String str){
        synchronized (this){
            ___write(type,tag,str);
        }
    }
}
