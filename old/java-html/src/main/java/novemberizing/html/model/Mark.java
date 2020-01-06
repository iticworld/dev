package novemberizing.html.model;

import com.google.gson.annotations.Expose;

import java.util.Collection;
import java.util.HashMap;

/**
 * {@link Mark#tag} tag
 * {@link Mark#attrs} attribute map
 *
 * @author novemberizing <novemberizing@gmail.com>
 * @since 0.0.1
 */
public class Mark {
    @Expose private String tag;
    @Expose private HashMap<String, Attr> attrs;

    /**
     * retrieve tag
     *
     * @return {@link String} return a tag
     */
    public String tag(){ return tag; }


    public String id(){
        Attr attr = attrs != null ? attrs.get("id") : null;
        return attr != null ? attr.value : null;
    }

    public void id(String v){ put(new Attr("id", v)); }

    /**
     * retrieve attributes collection.
     *
     * @return {@link Collection<Attr>} return a attributes
     */
    public Collection<Attr> attrs(){ return attrs != null ? attrs.values() : null; }

    /**
     * set tag
     * @param v {@link String} tag
     */
    public void tag(String v) { this.tag = v; }

    /**
     * set attributes
     *
     * @param o {@link Collection<Attr>} attributes
     */
    public void attrs(Collection<Attr> o) {
        if(o != null) {
            if(attrs != null) {
                attrs.clear();
            } else {
                attrs = new HashMap<>();
            }
            for(Attr attr : o) {
                if(attr != null) {
                    attrs.put(attr.name, attr);
                }
            }
        }
    }

    /**
     * clear attributes
     */
    public void clear() { functional.map.clear(attrs); }

    /**
     * retrieve attribute by attribute name
     *
     * @param k {@link String} key
     * @return {@link Attr} attribute
     */
    public Attr get(String k) { return functional.map.get(attrs, k); }

    /**
     * delete attribute by name
     *
     * @param k {@link String} key
     */
    public void del(String k) { functional.map.del(attrs, k); }

    /**
     * put attribute
     *
     * @param attr {@link String} attribute
     */
    public void put(Attr attr) {
        if(attr != null) {
            if(attrs == null) {
                attrs = new HashMap<>();
            }
            attrs.put(attr.name, attr);
        }
    }

    /**
     * default constructor
     */
    public Mark(){
        this.tag = null;
        this.attrs = null;
    }

    /**
     * construct with one attribute
     *
     * @param attr {@link Attr} attribute
     */
    public Mark(Attr attr) {
        this.tag = null;
        this.attrs = null;
        put(attr);
    }

    /**
     * construct with tag
     *
     * @param tag {@link String} tag
     */
    public Mark(String tag) {
        this.tag = tag;
        this.attrs = null;
    }

    /**
     * construct with tag and one attribute
     *
     * @param tag {@link String} tag
     * @param attr {@link Attr} attribute
     */
    public Mark(String tag, Attr attr) {
        this.tag = tag;
        this.attrs = null;
        put(attr);
    }

    /**
     * construct with tag and attributes
     *
     * @param tag {@link String} tag
     * @param attrs {@link Collection<Attr>} attributes
     */
    public Mark(String tag, Collection<Attr> attrs){
        this.tag = tag;
        this.attrs = null;
        this.attrs(attrs);
    }
}
