package novemberizing.rx.operators;

import novemberizing.ds.tuple.Pair;
import novemberizing.rx.Operator;
import novemberizing.util.Log;

import java.util.Collection;
import java.util.HashMap;
import java.util.Set;

import static novemberizing.ds.Constant.Infinite;

/**
 *
 * @author novemberizing, me@novemberizing.net
 * @since 2017. 1. 19
 */
@SuppressWarnings("unused")
public class Map<K, V> extends Operator<novemberizing.ds.tuple.Pair<K, V>, novemberizing.ds.tuple.Pair<K, V>> {
    private static final String Tag = "novemberizing.rx.operators.map";

    private final java.util.Map<K, V> __map;

    public Map(){
        Log.f(Tag, "");
        __map = new HashMap<>();
        replay(Infinite);
    }

    public Map(java.util.Map<K, V> map){
        Log.f(Tag, "");
        if(map!=null) {
            __map = map;
        } else {
            __map = new HashMap<>();
        }
        replay(Infinite);
    }

    @Override
    protected void on(Task<Pair<K, V>, Pair<K, V>> task, Pair<K, V> in) {
        Log.f(Tag, "");
        synchronized (__map){
            __map.put(in.first, in.second);
        }
        task.complete();
    }

    public Set<java.util.Map.Entry<K, V>> entries(){
        Log.f(Tag, "");
        Set<java.util.Map.Entry<K, V>> ret;
        synchronized (__map){
            ret = __map.entrySet();
        }
        return ret;
    }

    public Set<K> keys(){
        Log.f(Tag, "");
        Set<K> ret;
        synchronized (__map){
            ret = __map.keySet();
        }
        return ret;
    }

    public Collection<V> values(){
        Log.f(Tag, "");
        Collection<V> ret;
        synchronized (__map){
            ret = __map.values();
        }
        return ret;
    }

    public V get(K key){
        Log.f(Tag, "");
        V v;
        synchronized (__map){
            v = __map.get(key);
        }
        return v;
    }

    public V del(K key){
        Log.f(Tag, "");
        V v;
        synchronized (__map){
            v = __map.remove(key);
        }
        return v;
    }

    public void clear(){
        Log.f(Tag, "");
        synchronized (__map){
            __map.clear();
        }
    }

}
