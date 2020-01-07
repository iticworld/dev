package novemberizing.rx;

/**
 *
 * @author novemberizing, me@novemberizing.net
 * @since 2017. 1. 21.
 */
public class Local {
    private Object __o;

    public void set(Object o){ __o = o; }
    public <T> T get(Class<T> c){ return c.cast(__o); }
    public Object get(){ return __o; }

    public Local(Object o){ __o = o; }

    public Local(){ __o = null; }
}
