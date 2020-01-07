package functional;

import novemberizing.Packet;

public class packet {
    public static String type(Packet packet){ return packet != null ? functional.string.v(packet.type()) : ""; }
}
