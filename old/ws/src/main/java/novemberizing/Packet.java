package novemberizing;

import com.google.gson.annotations.Expose;

public class Packet {
    public static final String req = "req";
    public static final String res = "res";
    public static final String broadcast = "shout";


    @Expose protected String type;
    @Expose protected String model;
    @Expose protected Integer id;

    public String type(){ return type; }
    public String model(){ return model; }
    public Integer id(){ return id; }

    public Packet(){
        type = null;
        model = null;
        id = null;
    }
}
