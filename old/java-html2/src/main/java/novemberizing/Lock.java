package novemberizing;

import java.util.concurrent.locks.ReentrantLock;

public class Lock {
    protected java.util.concurrent.locks.Lock __o;

    public void lock(){ __o.lock(); }
    public void unlock(){ __o.unlock(); }

    public Lock(){ __o = new ReentrantLock(); }
    public Lock(java.util.concurrent.locks.Lock o) { __o = (o != null ? o : new ReentrantLock()); }
}
