package novemberizing.rx;

import com.google.gson.annotations.Expose;

/**
 *
 * @author novemberizing, me@novemberizing.net
 * @since 2017. 1. 17.
 */
@SuppressWarnings("WeakerAccess")
public class Counter {
    @Expose private int __count = 0;

    synchronized protected void increase(){ __count++; }
    synchronized protected void decrease(){ __count--; }
    synchronized protected void increase(int count){ __count+=count; }
    synchronized protected void decrease(int count){ __count-=count; }

    synchronized public int get(){ return __count; }
}
