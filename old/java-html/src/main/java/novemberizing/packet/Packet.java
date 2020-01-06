package novemberizing.packet;

import com.google.gson.annotations.Expose;

public class Packet {
    @Expose protected String type;
    @Expose protected String model;
    @Expose protected Integer id;

    public String type(){ return type; }
    public String model(){ return model; }
    public Integer id(){ return id; }

    public Packet(){}
}
