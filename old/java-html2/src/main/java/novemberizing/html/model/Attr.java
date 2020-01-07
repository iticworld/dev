package novemberizing.html.model;

import com.google.gson.annotations.Expose;

import java.util.Locale;

public class Attr {
    @Expose protected String category = null;
    @Expose protected String value = null;

    public String category(){ return category; }
    public String value(){ return value; }

    public String str(){
        return String.format(Locale.getDefault(), "%s=\"%s\"", category, value);
    }

    protected Attr(String category){
        this.category = category;
    }

    public Attr(){

    }
}