package novemberizing.ds;

import java.util.LinkedList;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

import static novemberizing.ds.Constant.Infinite;

/**
 *
 * @author novemberizing, me@novemberizing.net
 * @since 2017. 1. 17.
 */
@SuppressWarnings({"unused", "WeakerAccess", "EmptyCatchBlock"})
public class ConditionalList<T> {
    private LinkedList<T> __o = new LinkedList<>();
    private Lock __sync = new ReentrantLock();
    private Condition __condition = __sync.newCondition();

    public T front(){ return __o.pollFirst(); }
    public T back(){ return __o.pollLast(); }

    public void front(T o){ __o.addFirst(o); }
    public void back(T o){ __o.addLast(o); }

    public T pop(){ return __o.pollFirst(); }
    public void push(T o){ __o.addLast(o); }

    public int size(){ return __o.size(); }

    public void lock(){ __sync.lock(); }
    public void unlock(){ __sync.unlock(); }

    public void suspend(){ suspend(Infinite); }

    public void suspend(int nano){
        if(nano>0){
            try {
                __condition.awaitNanos(nano);
            } catch (InterruptedException e) {

            }
        } else {
            try {
                __condition.await();
            } catch (InterruptedException e) {

            }
        }
    }

    public void resume(){ resume(false); }

    public void resume(boolean all){
        if(all){
            __condition.signalAll();
        } else {
            __condition.signal();
        }
    }
}
