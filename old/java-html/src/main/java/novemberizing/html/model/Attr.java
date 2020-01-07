package novemberizing.html.model;

import com.google.gson.annotations.Expose;

/**
 * {@link Attr#name} is a attribute name
 * {@link Attr#value} is a attribute value
 *
 * @author novemberizing <novemberizing@gmail.com>
 * @since 0.0.1
 */
public class Attr {
    @Expose protected String name;
    @Expose protected String value;

    /**
     * retrieve a attribute's name
     *
     * @return {@link String} return a attribute's name
     */
    public String name(){ return name; }

    /**
     * retrieve a attribute's value
     *
     * @return {@link String} return a attribute's value
     */
    public String value(){ return value; }

    /**
     * set a attribute's name
     *
     * @param v {@link String} attribute's name
     */
    public void name(String v){ name = v; }

    /**
     * set a attribute's value
     *
     * @param v {@link String} attribute's value
     */
    public void value(String v){ value = v; }

    /**
     * construct with a attribute's name
     *
     * @param name {@link String} a attribute's name
     */
    public Attr(String name){
        this.name = name;
        this.value = null;
    }

    /**
     * construct with a attribute's name and value.
     *
     * @param name {@link String} a attribute's name
     * @param value {@link String} a attribute's value
     */
    public Attr(String name, String value){
        this.name = name;
        this.value = value;
    }

    /**
     * default constructor
     *
     */
    public Attr(){
        this.name = null;
        this.value = null;
    }
}
