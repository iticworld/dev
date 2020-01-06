package novemberizing;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Sync {
    private Lock __o;

    public void lock(){ __o.lock(); }
    public void unlock(){ __o.unlock(); }

    public Sync(){ __o = new ReentrantLock(); }
    public Sync(Lock o){ __o = (o != null ? o : new ReentrantLock()); }
}
