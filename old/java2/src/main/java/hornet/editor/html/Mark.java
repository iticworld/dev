package hornet.editor.html;

import com.google.gson.annotations.Expose;

import java.util.Collection;
import java.util.HashMap;

public class Mark {
    @Expose private String name;
    @Expose private HashMap<String, Attr> attrs;

    public String name(){ return name; }
    public void name(String v){ name = v; }

    public String id(){
        Attr attr = functional.map.get(attrs, "id");
        return attr != null ? attr.value() : null;
    }

    public void id(String v){
        put(new Attr("id", v));
    }

    public Attr get(String k){ return functional.map.get(attrs, k); }
    public void del(String k){ functional.map.del(attrs, k); }
    public void put(Attr attr){
        if(attr != null) {
            if(attrs == null) {
                attrs = new HashMap<>();
            }
            attrs.put(attr.name(), attr);
        }
    }

    public Collection<Attr> attrs(){ return attrs != null ? attrs.values() : null; }

    public Mark(String name){
        this.name = name;
        this.attrs = null;
    }

    public Mark(String name, Attr attr) {
        this.name = name;
        this.attrs = null;
        put(attr);
    }

    public Mark(String name, Attr o, Attr... attrs) {
        this.name = name;
        this.attrs = null;
        put(o);
        if(attrs != null) {
            for(Attr attr : attrs) {
                put(attr);
            }
        }
    }

    public Mark(String name, Attr[] attrs) {
        this.name = name;
        this.attrs = null;
        if(attrs != null) {
            for(Attr attr : attrs) {
                put(attr);
            }
        }
    }

    public Mark(String name, Collection<Attr> attrs) {
        this.name = name;
        this.attrs = null;
        if(attrs != null) {
            for(Attr attr : attrs) {
                put(attr);
            }
        }
    }
}
